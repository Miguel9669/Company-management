//
// Created by anton on 04/12/2023.
//

#include "Geral.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *categoryString(Company company) {
    static char *string[] = {"Micro Empresa", "Pequena e média empresa", "Grande empresa"};
    return string[company.category - 1];
}

void showComments(Company *company) {
    int i = 0;
    printf("%s: %s", company->comments[i].user.name, company->comments[i].commentText);
}

void showCompany(Company *company){
    if (company == NULL){
        printf("%s\n", SEARCH_NOT_FOUND);
    } else {
        header(company -> nameCompany);
        printf("Name: %s\nActivity type: %c\nCompany category: %s", company->nameCompany, company->activity,
               categoryString(*company));
    }

}

int inputNumber(char *txt) {
    int variable;
    printf("%s", txt);
    printf(">>> ");
    scanf(" %d", &variable);
    return variable;
}

char *inputString(char *txt, int quant){
    char var[quant];
    puts(txt);
    printf(">>> ");
    scanf(" %[^\n]s", &var);
    return var;
}

int verifyNumber(int *variable, int min, int max){

    if ((*variable < min) || (*variable > max)){
        return 0;
    } else {
        return 1;
    }
}

int verifyNif(int nif){
    int count;
    int Nif;
    while (nif > 0){
        nif /= 10;
        count++;
    }
    if (count == 9) {
        return nif;
    } else {
        return -1;
    }
}

int ShowMenuAndGetOption(char *txt, int min, int max, bool showOption) {
    int number;
    do {
        system("clear");
        if(showOption){
            puts("\n------------------------------------------------------------------");
        }
        puts(txt);
        number = inputNumber("");
    } while (!verifyNumber(&number, min, max));
    return number;
}


void header(char *txt) {
    puts("\n------------------------------------------------------------------------------------------");
    printf("                      %s\n", txt);
    puts("------------------------------------------------------------------------------------------");
}