#include "Admin.h"
#include <stdio.h>
#include "structs.h"
#include <string.h>
#include "Geral.h"
#include "constVariables.h"


void createCompany(Companies *companies) {
    int nif;
    do {
        nif = inputNumber(MSG_GET_NIF);
    } while (verifyNif(nif) == -1);

    strcpy(companies->company[companies->numberCompanies].nameCompany, inputString(MSG_GET_NAME, MAX_NAME_COMPANY));
    companies->company[companies->numberCompanies].nif = nif;
    strcpy(companies->company[companies->numberCompanies].activity, inputString(MSG_GET_ACTIVITY, 10));
    strcpy(companies->company[companies->numberCompanies].local.adress, inputString(MSG_GET_ADRESS, MAX_ADRESS));
    strcpy(companies->company[companies->numberCompanies].local.city, inputString(MSG_GET_CITY, MAX_CITY));
    strcpy(companies->company[companies->numberCompanies].local.codigoPostal, inputString(MSG_GET_CODPOSTAL, MAX_CODIGO));

}
