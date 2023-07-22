/**
* @file 0database.h
* @author Ашихміна Д. О., гр. 515і
* @date 11.07.2023
* @brief  практика, варіант 25
*
* Функції. Швидке сортування. Робота з відлагоджувачем . Завдання 1
*/
#ifndef DATABASE_H
#define DATABASE_H

typedef struct Policy {
    int policy_number;
    char* insurer_name;
    int insurer_status; // 0 - inactive, 1 - active
    char* vin_code;
    int expiry_date; // format DDMMYY
    struct Policy* next;
} Policy;

Policy* create_policy(int policy_number, char* insurer_name, int insurer_status, char* vin_code, int expiry_date);
void add_policy(Policy** head, Policy* policy);
void delete_policy(Policy** head, int policy_number);
Policy* search_policy(Policy* head, int policy_number);
void free_policy(Policy* head);
void export_to_csv(Policy* head, char* filename);
Policy* import_from_file(char* filename);

#endif // DATABASE_H
