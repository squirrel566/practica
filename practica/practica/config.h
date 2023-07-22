/**
* @file config.h
* @author ������� �. �., ��. 515�
* @date 11.07.2023
* @brief  ��������, ������ 25
*
* �������. ������ ����������. ������ � �������������� . �������� 1
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