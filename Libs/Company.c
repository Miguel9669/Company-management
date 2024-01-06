#include "Company.h"
#include <stdio.h>
#include "structs.h"
#include "Geral.h"
#include "Admin.h"
#include <string.h>
#include "constVariables.h"
#include "Menus.h"
#include "user.h"

void handleCompany(Companies *companies, Activities *activities, Informations informations){
    bool back;
    do {
        back = false;
        menuCompanies(&back, companies, activities, informations);
    } while (back != true);
}


void handleMenuReports(Company *company, Informations informations, int index) {
    int option;
    do {
        option = menuCompanyReport(company, informations, index);
    } while (option != 0);
}

