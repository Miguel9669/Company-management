#include "Geral.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *categoryString(Company company) {
    static char *string[] = {"Micro Empresa", "Pequena e média empresa", "Grande empresa"};
    return string[company.category - 1];
}

int lenString(char *variable) {
    int count = 0;
    while (variable[count] != '\0') {
        count++;
    }
}
void showComments(Company *company) {
    for (int i = 0; i < company->numberComments; ++i) {
        printf("\n%s: %s(%s)", company->comments[i].user.name, company->comments[i].title, company->comments[i].commentText);
    }
    sleep(4);
}
char *boolString(bool variable){
    switch (variable) {
        case 0:
            return "false";
        case 1:
            return "true";
    }
}
void showCompany(Company *company){
    system("clear");
    header(company -> nameCompany);
    printf("Company Information:\n");
    printf("Name: %s\n", company->nameCompany);
    printf("NIF: %d\n", company->nif);
    printf("Activity: %s\n", company->activity);
    printf("Address: %s\n", company->local.adress);
    printf("City: %s\n", company->local.city);
    printf("Postal Code: %s\n", company->local.codigoPostal);
    printf("Category: %s\n", categoryString(*company));
    printf("Active: %s", boolString(company->active));
}

int inputNumber(char *txt) {
    int variable;
    printf("%s\n", txt);
    while (scanf(" %d", &variable) != 1) {
        puts("ERROR: Only numbers.");
        cleanBuffer();
        return -1;
    }
    cleanBuffer();
    return variable;
}
void cleanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
char *inputString(char *txt, int quant, bool cleanConsole) {
    char *var = (char *)malloc(quant + 1);
    size_t len;
    if (var == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        sleep(4);
        exit(EXIT_FAILURE);
    }

    do {
        if(cleanConsole){
            system("clear");
        }

        printf("%s", txt);
        if (fgets(var, quant + 1, stdin) != NULL) {
            len = strlen(var);
            if (len > 1 && var[len - 1] == '\n') {
                var[len - 1] = '\0';
            } else {
                // Limpar o buffer de entrada se necessário
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
        }
        if (len >= quant) {
            puts(INVALID_INPUT);
            sleep(4);
        }


    } while (len == 0 || len >= quant);  // Continue pedindo entrada até que algo seja digitado

    return var;
}


int verifyNumber(int *variable, int min, int max){

    if ((*variable < min) || (*variable > max) || *variable == -1){
        return 0;
    } else {
        return 1;
    }
}

int verifyNif(int nif) {
    int count = 0;
    while (nif > 0) {
        nif /= 10;
        count++;
    }

    if (count == 9) {
        return nif;
    } else {
        return -1;
    }
}

int GetOption(char *txt, int min, int max, bool showOption, bool showHeader, char *txtHeader) {
    int number;
    do {
        if (showHeader){
            header(txtHeader);
        }
        if(showOption){
            puts("\n------------------------------------------------------------------");
        }
        puts(txt);
        number = inputNumber("");
        if (!verifyNumber(&number, min, max)) {
            system("clear");
        }
    } while (!verifyNumber(&number, min, max));
    return number;
}
int isCompanyExists(const Companies *companies, char *name, int nif, int numberCompanies) {
    for (int i = 0; i < numberCompanies; ++i) {
        if (strcmp(companies->company[i].nameCompany, name) == 0 || companies->company[i].nif == nif) {
            return 1;
        }
    }
    return 0;
}
int findCompanyIndexByNif(const Companies *companies, int nif) {
    for (int i = 0; i < companies->numberCompanies; ++i) {
        if (companies->company[i].nif == nif) {
            return i;
        }
    }
    return -1;
}
int numberCompaniesInCategory(Companies *companies, int valueCategory) {
    int count = 0;
    for (int i = 0; i < companies -> numberCompanies; i++){
        if (companies->company[i].category == valueCategory && companies->company[i].active == true){
            count++;
        }
    }
    return count;
}
void getString(char *dest, char *txt, int charLen){
    char *variable = inputString(txt, charLen, false);
    strcpy(dest, variable);
    free(variable);
}
void header(char *txt) {
    puts("\n------------------------------------------------------------------------------------------");
    printf("                      %s\n", txt);
    puts("------------------------------------------------------------------------------------------");
}