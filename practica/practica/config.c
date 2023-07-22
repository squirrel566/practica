/**
* @file config.c
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
#include <stdint.h>

uint32_t jenkins_one_at_a_time_hash(char* key, size_t len) {
    uint32_t hash, i;
    for (hash = i = 0; i < len; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

int check_key(char* key) {
    uint32_t hashed_key = jenkins_one_at_a_time_hash(key, strlen(key));
    printf("%zu\n", hashed_key);
    uint32_t expected_hash = 3804681663;  // Замініть це значення хешем від вашого правильного ключа
    return hashed_key == expected_hash;
}

Configuration* read_configuration(char* program_name) {
    // Construct configuration file name
    char cfg_filename[100];
    sprintf(cfg_filename, "%s.cfg", program_name);

    // Open file
    FILE* cfg_file = fopen(cfg_filename, "r");
    if (cfg_file == NULL) {
        printf("Error opening configuration file %s\n", cfg_filename);
        return NULL;
    }

    Configuration* config = malloc(sizeof(Configuration));
    if (config == NULL) {
        printf("Error allocating memory for configuration.\n");
        fclose(cfg_file);
        return NULL;
    }

    // Read configuration
    char line[256];
    while (fgets(line, sizeof(line), cfg_file)) {
        char* eq_pos = strchr(line, '=');
        if (eq_pos != NULL) {
            *eq_pos = '\0';
            char* key = line;
            char* value = eq_pos + 1;
            if (strcmp(key, "DB") == 0) {
                config->db_path = _strdup(value);
            }
            else if (strcmp(key, "KEY") == 0) {
                config->key = _strdup(value);
            }
        }
    }

    fclose(cfg_file);
    return config;
}
