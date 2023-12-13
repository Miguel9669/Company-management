#include "Admin.h"
#include <stdio.h>
#include "structs.h"
#include <string.h>
#include "Geral.h"
#include <stdlib.h>
#include "constVariables.h"
#include <unistd.h>

int findCompanyIndexByNif(const Companies *companies, int nif) {
    for (int i = 0; i < companies->numberCompanies; ++i) {
        if (companies->company[i].nif == nif) {
            return i;
        }
    }
    return -1;
}

int isCompanyExists(const Companies *companies, char *name, int nif, int numberCompanies) {
    for (int i = 0; i < numberCompanies; ++i) {
        if (strcmp(companies->company[i].nameCompany, name) == 0 || companies->company[i].nif == nif) {
            return 1;
        }
    }
    return 0;
}

void createCompany(Companies *companies) {
    int nif;
    int numberCompanies = companies->numberCompanies;
    char *companyName = NULL;
    char *atividade = NULL;
    char *adress = NULL;
    char *city = NULL;
    char *codPostal = NULL;
    companies->numberCompanies++;

    if (companies->numberCompanies == companies->maxCompanies) {
        Company *pCompany= (Company *) realloc(companies->company, (companies->maxCompanies + 10) * sizeof(Company));
        if (pCompany != NULL) {
            companies->company = pCompany;
            companies->maxCompanies *= 2;
        } else {
            puts("Error: REALLOC FAIL.");
            sleep(4);
        }
    }
    companyName = inputString(MSG_GET_NAME, MAX_NAME, true);


    if (isCompanyExists(companies, companyName, 0, numberCompanies)) {
        do {
            free(companyName);
            strcpy(companyName, inputString(EXISTENT_COMPANY, MAX_NAME_COMPANY, true));
        } while (isCompanyExists(companies, companyName, 0, numberCompanies));
    }
    strcpy(companies->company[numberCompanies].nameCompany, companyName);
    free(companyName);
    //Finnish!


    //Verify NIF
    do {
        system("clear");
        companies->company[numberCompanies].nif = inputNumber(MSG_GET_NIF);

        if (verifyNif(companies->company[numberCompanies].nif) == -1 || isCompanyExists(companies, "", companies->company[numberCompanies].nif, numberCompanies) == 1) {
            puts(verifyNif(companies->company[numberCompanies].nif) == -1 ? ERROR_NIF : EXISTENT_NIF);
            sleep(4);
        }
    } while (verifyNif(companies->company[numberCompanies].nif) == -1 || isCompanyExists(companies, "", companies->company[numberCompanies].nif, numberCompanies) == 1);

    atividade = inputString(MSG_GET_ACTIVITY, 10, true);
    strcpy(companies->company[numberCompanies].activity, atividade);
    free(atividade);
    adress = inputString(MSG_GET_ADRESS, MAX_ADRESS, true);
    strcpy(companies->company[numberCompanies].local.adress, adress);
    free(adress);
    city = inputString(MSG_GET_CITY, MAX_CITY, true);
    strcpy(companies->company[numberCompanies].local.city, city);
    free(city);
    codPostal = inputString(MSG_GET_CODPOSTAL, MAX_CODIGO, true);
    strcpy(companies->company[numberCompanies].local.codigoPostal, codPostal);
    free(codPostal);
    system("clear");
    companies->company[numberCompanies].category = ShowMenuAndGetOption(MENU_SEARCH_BY_CATEGORY, 1, 3, true, false, "");
    iniciateCommentsAndRates(&companies->company[numberCompanies]);
    companies->company[numberCompanies].active = true;
}

void iniciateCommentsAndRates(Company *company) {
    company->numberComments = 0;
    company->numberRates = 0;
    company->maxComments = 5;
    company->maxRates = 5;
    company->comments = (Comment *)malloc(company->maxComments * sizeof(Comment));
    company->rates = (Rate *)malloc(company->maxRates * sizeof(Rate));

    if (company->comments == NULL || company->rates == NULL) {
        fprintf(stderr, "Erro ao alocar memória para comentários ou avaliações\n");
        exit(EXIT_FAILURE);
    }
}
void deleteCompany(Companies *companies) {
    int nif, index;

    if (companies->numberCompanies > 0) {
        nif = inputNumber(MSG_GET_NIF);
        index = findCompanyIndexByNif(companies, nif);

        if (index == -1) {
            printf("Company not found: %d\n", nif);
            sleep(4);
        }
        for (int i = index; i < companies->numberCompanies; ++i) {
            companies->company[i] = companies->company[i + 1];
        }
        companies->company[companies->numberCompanies].nif = 0;
        strcpy(companies->company[companies->numberCompanies].nameCompany, "");
        strcpy(companies->company[companies->numberCompanies].activity,"");
        strcpy(companies->company[companies->numberCompanies].local.adress, "");
        strcpy(companies->company[companies->numberCompanies].local.city, "");
        strcpy(companies->company[companies->numberCompanies].local.codigoPostal, "");
        printf("Company deleted successfully.\n");
        companies->numberCompanies--;
    } else {
        printf("No companies to delete.\n");
        sleep(4);
    }
}


void modifyCompany(Companies *companies) {
    int nif, index, menuModify;
    char newName[MAX_NAME_COMPANY], newActivity[10], newAddress[MAX_ADRESS], newCity[MAX_CITY], newCodigoPostal[MAX_CODIGO];

    if (companies->numberCompanies > 0) {
        nif = inputNumber(MSG_GET_NIF);
        index = findCompanyIndexByNif(companies, nif);

        if (index == -1) {
            printf("Company not found: %d\n", nif);
            sleep(4);
            return;
        }

        do {
            showCompany(&(companies->company[index]), true);
            menuModify = ShowMenuAndGetOption(MENU_MODIFY, 0, 6, false, true, MODIFY_MENU);
            cleanBuffer();
            switch (menuModify) {
                case 1:
                    strcpy(newName, inputString("New name: ", MAX_NAME_COMPANY, true));
                    strcpy(companies->company[index].nameCompany, newName);
                    break;
                case 2:
                    strcpy(newActivity, inputString("New activity: ", 10, true));
                    strcpy(companies->company[index].activity, newActivity);
                    break;
                case 3:
                    strcpy(newAddress, inputString("New address: ", MAX_ADRESS, true));
                    strcpy(companies->company[index].local.adress, newAddress);
                    break;
                case 4:
                    strcpy(newCity, inputString("New city: ", MAX_CITY, true));
                    strcpy(companies->company[index].local.city, newCity);
                    break;
                case 5:
                    strcpy(newCodigoPostal, inputString("New Postal Code: ", MAX_CODIGO, true));
                    strcpy(companies->company[index].local.codigoPostal, newCodigoPostal);
                    break;
                case 6:
                    system("clear");
                    companies->company[index].category = ShowMenuAndGetOption(MENU_SEARCH_BY_CATEGORY, 1, 3, true, false, "");
                    break;
                case 0:
                    printf("Leaving!.\n");
                    break;
                default:
                    printf("Invalid option, try again!.\n");
                    sleep(4);
            }
        } while (menuModify != 0);

    } else {
        printf("No companies to modify.\n");
        sleep(4);
    }
}

