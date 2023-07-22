/**
* @file database.c
* @author Ашихміна Д. О., гр. 515і
* @date 11.07.2023
* @brief  практика, варіант 25
*
* Функції. Швидке сортування. Робота з відлагоджувачем . Завдання 1
*/
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
 
Policy* create_policy(int policy_number, char* insurer_name, int insurer_status, char* vin_code, int expiry_date) {
    Policy* new_policy = (Policy*)malloc(sizeof(Policy));
    if (new_policy == NULL) {
        printf("Error! Unable to allocate memory for new policy.\n");
        return NULL;
    }
    new_policy->policy_number = policy_number;
    new_policy->insurer_name = _strdup(insurer_name); // Duplicate the string
    new_policy->insurer_status = insurer_status;
    new_policy->vin_code = _strdup(vin_code);
    new_policy->expiry_date = expiry_date;
    new_policy->next = NULL;
    return new_policy;
}

void add_policy(Policy** head, Policy* policy) {
    if (*head == NULL) {
        *head = policy;
    }
    else {
        Policy* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = policy;
    }
}

Policy* search_policy(Policy* head, int policy_number) {
    Policy* current = head;
    while (current != NULL) {
        if (current->policy_number == policy_number) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void delete_policy(Policy** head, int policy_number) {
    Policy* current = *head;
    Policy* prev = NULL;

    if (current != NULL && current->policy_number == policy_number) {
        *head = current->next; // Changed head
        free(current); // Free old head
        return;
    }

    // Search for the policy to be deleted, keep track of the previous node
    while (current != NULL && current->policy_number != policy_number) {
        prev = current;
        current = current->next;
    }

    // If policy was not present in database
    if (current == NULL) {
        return;
    }

    // Unlink the node from linked list
    prev->next = current->next;

    free(current); // Free memory
}

void free_policy(Policy* head) {
    Policy* current = head;
    while (current != NULL) {
        Policy* next_policy = current->next;
        free(current->insurer_name);
        free(current->vin_code);
        free(current);
        current = next_policy;
    }
}

void export_to_csv(Policy* head, char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error! Unable to open file for writing.\n");
        return;
    }
    Policy* current = head;
    while (current != NULL) {
        fprintf(file, "%d,%s,%d,%s,%d\n", current->policy_number, current->insurer_name, current->insurer_status, current->vin_code, current->expiry_date);
        current = current->next;
    }
    fclose(file);
}

void removeLastCharacter(char* str) {
    int length = strlen(str);
    if (length > 0) {
        str[length - 1] = '\0';  // Устанавливаем нулевой символ на предпоследнюю позицию
    }
}

Policy* import_from_file(char* filename) {
    removeLastCharacter(filename);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error! Unable to open file for reading.\n");
        return NULL;
    }

    Policy* head = NULL;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        int policy_number;
        char insurer_name[50];
        int insurer_status;
        char vin_code[20];
        int expiry_date;

        sscanf(line, "%d,%49[^,],%d,%19[^,],%d", &policy_number, insurer_name, &insurer_status, vin_code, &expiry_date);

        Policy* new_policy = create_policy(policy_number, insurer_name, insurer_status, vin_code, expiry_date);
        if (new_policy != NULL) {
            add_policy(&head, new_policy);
        }
    }
    fclose(file);
    return head;
}
