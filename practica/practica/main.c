/**
* @file practica.c
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
#include "config.h"
#include "database.h"

// Function to get the base name of the program
char* base_name(char* path) {
    char* base = strrchr(path, '/');
    return base ? base + 1 : path;
}

int main(int argc, char* argv[]) {
    // Get the configuration
    char* program_name = base_name(argv[0]);
    Configuration* config = read_configuration(program_name);

    // Check the license key
    if (!check_key(config->key)) {
        printf("License key is not valid!\n");
        return -1;
    }

    // Load the database
    Policy* db = import_from_file(config->db_path);
    if (db == NULL) {
        printf("Database could not be loaded!\n");
        return -1;
    }

    // Create a new policy
    Policy* new_policy = create_policy(299, "New Insurer", 1, "VIN999", 20240000);
    Policy* new_policy2 = create_policy(111, "New Insurer", 1, "VIN111", 20240001);
    if (new_policy == NULL) {
        printf("Failed to create new policy!\n");
        return -1;
    }


    // Add the new policy to the database
    add_policy(&db, new_policy);
    add_policy(&db, new_policy2);

    // Search for the new policy
    Policy* policy = search_policy(db, 299);
    if (policy == NULL) {
        printf("New policy not found!\n");
    }
    else {
        printf("Found new policy: %s, %d, %s, %d\n", policy->insurer_name, policy->insurer_status, policy->vin_code, policy->expiry_date);
    }

    // Export the database to a new CSV file
    export_to_csv(db, "new_db.csv");

    // Delete the new policy
    delete_policy(&db, 999);

    free_policy(db);
    free(config->db_path);
    free(config->key);
    free(config);

    return 0;
}