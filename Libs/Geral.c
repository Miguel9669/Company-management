#include "Geral.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

static char *categoryString(Company company) {
    static char *string[] = {"Micro Empresa", "Pequena e média empresa", "Grande empresa"};
    return string[company.category - 1];
}

void showComments(Company *company) {
    int count = 1;
    for (int i = 0; i < company->numberComments; ++i) {
        if ((company->comments[i].commentHide)) {
            printf("\nComment Number: %d, User: %s, Title: %s, Comment: %s\n",
                   count,
                   company->comments[i].user.name,
                   company->comments[i].title,
                   company->comments[i].commentText);
            count++;
        }
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
    printf("Active: %s\n", boolString(company->active));
    printf("Rating average: %.2f\n", companyAverageRating(company));
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

char *inputString(char *txt, int quant) {
    char *var = (char *)malloc(quant + 1);
    size_t len;
    if (var == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        sleep(4);
        exit(EXIT_FAILURE);
    }

    do {

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
        if (len > quant) {
            puts(INVALID_INPUT);
        }


    } while (len == 0 || len > quant);  // Continue pedindo entrada até que algo seja digitado

    return var;
}

int verifyNumber(int *variable, int min, int max){

    if ((*variable < min) || (*variable > max)){
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
int verifyPostalCode(char *postalCode) {
    if (strlen(postalCode) == 8 && isdigit(postalCode[0]) && isdigit(postalCode[1]) && isdigit(postalCode[2]) && isdigit(postalCode[3])) {
        if (postalCode[4] == '-' && isdigit(postalCode[5]) && isdigit(postalCode[6]) && isdigit(postalCode[7])) {
            return 1;
        }
    }
    return 0;
}
int showCompaniesInActivity(Activities *activities, Companies *companies, int index) {
    int count = 0;
    if (isCompanyExistInActivity(&(activities->activities[index]), companies)) {
        for (int i = 0; i < companies->numberCompanies; i++) {
            if (strcmp(activities->activities[index].activity, companies->company[i].activity) == 0 && companies->company[i].active) {
                printf("%d ", count + 1);
                printf("%s", companies->company[i].nameCompany);
                count++;
            }
        }
    }
    return count;
}
void showActivity(Activities *activities, bool admin){
    int count = 1;
    if (activities->numberActivities > 0){
        for (int i = 0; i < activities->numberActivities; i++) {
            if (activities->activities[i].Active) {
                printf("%d", count);
                printf(" %s", activities->activities[i].activity);
                printf("\n");
                count++;
            } else {
                if (admin) {
                    count++;
                    printf("%d", i + 1);
                    printf(" %s", activities->activities[i].activity);
                    printf("\n");
                }
            }
        }
        if (count == 0) {
            puts("There is no activity to select!!");
        }
    } else {
        puts("There is no activity to select!!");
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
            puts("Invalid option!");
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

int isActivityExist(Activities *activities, char *name) {
    for (int i = 0; i < activities->numberActivities; ++i) {
        if (strcmp(activities->activities[i].activity, name) == 0) {
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
int isCompanyExistInActivity(Activity *activity, const Companies *companies) {
    for (int i = 0; i < companies->numberCompanies; ++i) {
        if (strcmp(companies->company[i].activity, activity->activity) == 0) {
            return 1;
        }
    }
    return 0;
}
void getString(char *dest, char *txt, int charLen){
    char *variable = inputString(txt, charLen);
    strcpy(dest, variable);
    free(variable);
}

void header(char *txt) {
    puts("\n------------------------------------------------------------------------------------------");
    printf("                      %s\n", txt);
    puts("------------------------------------------------------------------------------------------");
}

double companyAverageRating(Company *company) {
    int i;
    double sum = 0.0, averageRating;
    if (company->numberRates == 0) {
        return 0;
    }
    for (i = 0; i < company->numberRates; i++) {
        sum += company->rates[i].rate;
    }
    averageRating = sum / company->numberRates;
    return averageRating;
}

