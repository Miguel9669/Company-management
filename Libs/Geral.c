//
// Created by anton on 04/12/2023.
//

#include "Geral.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>


void showCompany(Company *company){
    if (company == 0){
        printf("%s", SEARCH_NOT_FOUND);
    } else {
        printf("%s\n%c\n%u", company->nameCompany, company->activity, company->category);
    }

}

void inputNumber(int *variable, char *txt) {
    printf("%s", txt);
    printf(">>> ");
    scanf(" %d", variable);
}

void inputString(char *variable, char *txt){
    puts(txt);
    printf(">>> ");
    scanf(" %[^\n]s", variable);
}

int verifyNumber(int *variable, int min, int max){

    if ((*variable < min) || (*variable > max)){
        return 0;
    } else {
        return 1;
    }

}

int ShowMenuAndGetOption(char *txt, int min, int max, bool showOption) {
    int number;
    do {
        system("clear");
        if(showOption){
            puts("------------------------------------------------------------------");
        }
        puts(txt);
        inputNumber(&number, "");
    } while (!verifyNumber(&number, min, max));
    return number;
}


void header(char *txt) {
    puts("------------------------------------------------------------------------------------------");
    printf("                      %s\n", txt);
    puts("------------------------------------------------------------------------------------------");
}