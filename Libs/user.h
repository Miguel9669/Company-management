//
// Created by anton on 06/12/2023.
//

#ifndef COMPANY_MANAGEMENT_USER_H
#define COMPANY_MANAGEMENT_USER_H
#include "structs.h"

int lenCharArray(char *array);
void runArrayAndChangeString(char *variable, char *array);
Company *searchByName(Companies *companies, char *txt);
void searchByCategory(Companies *companies, int valueCategory, Company **company);
#endif //COMPANY_MANAGEMENT_USER_H