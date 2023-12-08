#include "Admin.h"
#include <stdio.h>
#include "structs.h"
#include <string.h>
#include "Geral.h"
#include "constVariables.h"

void createCompany(Companies *companies) {
    int nif, c;
    do {
        nif = inputNumber(MSG_GET_NIF);
    } while (verifyNif(nif) == -1);

    strcpy(companies->company[companies->numberCompanies].nameCompany, inputString(MSG_GET_NAME, MAX_NAME_COMPANY));
    companies->company[companies->numberCompanies].nif = nif;
    strcpy(companies->company[companies->numberCompanies].activity, inputString(MSG_GET_ACTIVITY, 10));
    strcpy(companies->company[companies->numberCompanies].local.adress, inputString(MSG_GET_ADRESS, MAX_ADRESS));
    strcpy(companies->company[companies->numberCompanies].local.city, inputString(MSG_GET_CITY, MAX_CITY));
    strcpy(companies->company[companies->numberCompanies].local.codigoPostal, inputString(MSG_GET_CODPOSTAL, MAX_CODIGO));
    companies->numberCompanies++;
}

int findCompanyIndexByNif(const Companies *companies, int nif) {
    for (int i = 0; i < companies->numberCompanies; ++i) {
        if (companies->company[i].nif == nif) {
            return i;
        }
    }
    return -1;
}

void deleteCompany(Companies *companies) {
    int nif, index, choice, menuModify;

    if (companies->numberCompanies > 0) {
        nif = inputNumber(MSG_GET_NIF);
        index = findCompanyIndexByNif(companies, nif);

        if (index == -1) {
            printf("Company not found: %d\n", nif);
            return;
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
    }
}


void modifyCompany(Companies *companies) {
    int nif, index, choice, menuModify;
    char newName[MAX_NAME_COMPANY], newActivity[10], newAddress[MAX_ADRESS], newCity[MAX_CITY], newCodigoPostal[MAX_CODIGO];

    if (companies->numberCompanies > 0) {

        nif = inputNumber(MSG_GET_NIF);

        index = findCompanyIndexByNif(companies, nif);

        if (index == -1) {
            printf("Company not found: %d\n", nif);
            return;
        }

        do {
            header(MODIFY_MENU);
            menuModify = ShowMenuAndGetOption(MENU_MODIFY, 0, 5, false);

            switch (menuModify) {
                case 1:
                    strcpy(newName, inputString("New name: ", MAX_NAME_COMPANY));
                    strcpy(companies->company[index].nameCompany, newName);
                    break;
                case 2:
                    strcpy(newActivity, inputString("New activity: ", 10));
                    strcpy(companies->company[index].activity, newActivity);
                    break;
                case 3:
                    strcpy(newAddress, inputString("New address: ", MAX_ADRESS));
                    strcpy(companies->company[index].local.adress, newAddress);
                    break;
                case 4:
                    strcpy(newCity, inputString("New city: ", MAX_CITY));
                    strcpy(companies->company[index].local.city, newCity);
                    break;
                case 5:
                    strcpy(newCodigoPostal, inputString("New Postal Code: ", MAX_CODIGO));
                    strcpy(companies->company[index].local.codigoPostal, newCodigoPostal);
                    break;
                case 0:
                    printf("Leaving!.\n");
                    break;
                default:
                    printf("Invalid option, try again!.\n");
            }
        } while (menuModify != 0);

    } else {
        printf("No companies to modify.\n");
    }
}

