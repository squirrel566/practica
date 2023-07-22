/**
* @file config.h
* @author Ашихміна Д. О., гр. 515і
* @date 11.07.2023
* @brief  практика, варіант 25
*
* Функції. Швидке сортування. Робота з відлагоджувачем . Завдання 1
*/
#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    char* db_path;
    char* key;
} Configuration;

Configuration* read_configuration(char* program_name);
int check_key(char* key);

#endif