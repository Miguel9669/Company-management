#include "Company.h"
#include <stdio.h>
#include "structs.h"
#include "Geral.h"
#include "Admin.h"
#include <string.h>
#include "constVariables.h"
#include "Menus.h"
#include "user.h"

void handleCompany(Companies *companies, Activities *activities){
    bool back;
    do {
        back = false;
        menuCompanies(&back, companies, activities);
    } while (back != true);
}

void showCommentsCompany(Companies *companies) {
    Company *foundCompany = searchCompanyByName(companies);
    if (foundCompany == NULL) {
        printf("No company with that name!");
        return;
    }
    showComments(foundCompany, true);
}


