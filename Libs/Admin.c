#include "Admin.h"
#include <stdio.h>
#include "structs.h"
#include <string.h>
#include "Geral.h"
#include <stdlib.h>
#include "constVariables.h"
#include <unistd.h>
#include "Menus.h"

void handleAdmin(Companies *companies){
    bool back;
    do {
        back = false;
        menuAdmin(&back, companies);
    } while (back != true);
}


void createCompany(Companies *companies) {
    int numberCompanies = companies->numberCompanies;
    Company *company = &(companies->company[numberCompanies]);
    companies->numberCompanies++;

    if (companies->numberCompanies == companies->maxCompanies) {
        Company *pCompany= (Company *) realloc(companies->company, (companies->maxCompanies + 10) * sizeof(Company));
        if (pCompany != NULL) {
            companies->company = pCompany;
            companies->maxCompanies *= 2;
        } else {
            puts("Error: REALLOC FAIL.");
        }
    }
    getString(company->nameCompany, MSG_GET_NAME, MAX_NAME_COMPANY);

    if (isCompanyExists(companies, company->nameCompany, 0, numberCompanies)) {
        do {
            getString(company->nameCompany, MSG_GET_NAME, MAX_NAME_COMPANY);
        } while (isCompanyExists(companies, company->nameCompany, 0, numberCompanies));
    }

    do {
        system("clear");
        companies->company[numberCompanies].nif = inputNumber(MSG_GET_NIF);

        if (verifyNif(company->nif) == -1 || isCompanyExists(companies, "", company->nif, numberCompanies) == 1) {
            puts(verifyNif(company->nif) == -1 ? ERROR_NIF : EXISTENT_NIF);
        }
    } while (verifyNif(company->nif) == -1 || isCompanyExists(companies, "", company->nif, numberCompanies) == 1);

    getString(company->activity, MSG_GET_ACTIVITY, 10);
    getString(company->local.adress, MSG_GET_ADRESS, MAX_ADRESS);
    getString(company->local.city, MSG_GET_CITY, MAX_CITY);
    getString(company->local.codigoPostal, MSG_GET_CODPOSTAL, MAX_CODIGO);

    company->category = GetOption(MENU_SEARCH_BY_CATEGORY, 1, 3, false, false, "");
    iniciateCommentsAndRates(company);
    company->active = true;
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
        Company *company = &(companies->company[companies->numberCompanies]);
        nif = inputNumber(MSG_GET_NIF);
        index = findCompanyIndexByNif(companies, nif);

        if (index == -1) {
            printf("Company not found: %d\n", nif);
            sleep(4);
        }
        for (int i = index; i < companies->numberCompanies; ++i) {
            companies->company[i] = companies->company[i + 1];
        }
        company->nif = 0;
        strcpy(company->nameCompany, "");
        strcpy(company->activity,"");
        strcpy(company->local.adress, "");
        strcpy(company->local.city, "");
        strcpy(company->local.codigoPostal, "");
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
            showCompany(&(companies->company[index]));
            menuModify = GetOption(MENU_MODIFY, 0, 7, false, true, MODIFY_MENU);
            switch (menuModify) {
                case 1:
                    getString(newName, "New name: ", MAX_NAME_COMPANY);
                    strcpy(companies->company[index].nameCompany, newName);
                    break;
                case 2:
                    getString(newActivity, "New activity: ", 10);
                    strcpy(companies->company[index].activity, newActivity);
                    break;
                case 3:
                    getString(newAddress, "New address: ", MAX_ADRESS);
                    strcpy(companies->company[index].local.adress, newAddress);
                    break;
                case 4:
                    getString(newCity, "New city: ", MAX_CITY);
                    strcpy(companies->company[index].local.city, newCity);
                    break;
                case 5:
                    getString(newCodigoPostal, "New Postal Code: ", MAX_CODIGO);
                    strcpy(companies->company[index].local.codigoPostal, newCodigoPostal);
                    break;
                case 6:
                    companies->company[index].category = GetOption(MENU_SEARCH_BY_CATEGORY, 1, 3, true, false, "");
                    break;
                case 7:
                    companies->company[index].active = companies->company[index].active == true ? false : true;
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
    }
}

