//
// Created by anton on 04/12/2023.
//

#include "Geral.h"
#include <stdio.h>

void inputNumber(int *variable, char *txt) {
    printf("%s", txt);
    printf(">>> ");
    scanf("%d", variable);
}

void inputString(char *variable, char *txt){
    puts(txt);
    printf(">>> ");
    scanf("%[^\n]s", variable);
}

int verifyNumber(int *variable, int min, int max){

    if ((*variable < min) || (*variable > max)){
        return 0;
    } else {
        return 1;
    }

}

void menu(char *txt){
    puts(txt);

}