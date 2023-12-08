//
// Created by anton on 06/12/2023.
//

#include "user.h"
#include "constVariables.h"
#include "structs.h"
#include "Admin.h"
#include "Geral.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

int lenCharArray(char *array){
    int count = 0;
    do{
        count++;
    } while (array[count] != '\n');
}
void runArrayAndChangeString(char *variable, char *array){
    int len = lenCharArray(array);
    for(int i = 0; i < len; i++){
        variable[i] = array[i];
    }
}

Company *searchByName(Companies *companies, char *txt){
    if (companies->numberCompanies > 0) {
        for (int i = 0; i < companies -> numberCompanies; i++){
            if (strcmp(companies->company[i].nameCompany, txt) == 0){
                return &(companies -> company[i]);
            }

        }
        return NULL;
    } else {
        printf("No companies to delete.\n");
    }

}

void searchByCategory(Companies *companies, int valueCategory, Company **company){
    if (companies->numberCompanies > 0) {
        int count = 0;
        header("COMPANIES FOUND");
        for (int i = 0; i < companies -> numberCompanies; i++) {
            header(companies->company[i].nameCompany);
            count++;
            company[count] = &(companies->company[i]);
            if (companies->company[i].category == valueCategory) {
                header(companies->company[i].nameCompany);
                company[count] = &(companies->company[i]);
                count++;
            }
        }
    } else {
        printf("No companies to Search.\n");
    }
}

