//
// Created by anton on 06/12/2023.
//

#include "user.h"
#include "constVariables.h"
#include "structs.h"
#include "Admin.h"
#include <stdio.h>

char name[MAX_NAME];
char email[MAX_EMAIL];

int lenCharArray(char *array){
    int count = 0;
    do{

    } while (array[count] != '\n');
}
void runArrayAndChangeString(char *variable, char *array){
    int len = lenCharArray(array);
    for(int i = 0; i < len; i++){
        variable[i] = array[i];
    }
}

Company *searchByName(Companies *companies, char *txt){
    for (int i = 0; i < companies -> numberCompanies; i++){
        if (companies -> company[i].nameCompany == txt){
            return &(companies -> company[i]);
        }

    }
    return 0;
}