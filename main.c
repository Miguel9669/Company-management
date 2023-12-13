#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Libs/constVariables.h"
#include "Libs/Geral.h"
#include "Libs/user.h"
#include "Libs/structs.h"
#include "Libs/Admin.h"
#include <unistd.h>
#include "Libs/Menus.h"

int main() {
    Companies companies = {.numberCompanies = 0, .maxCompanies = 10,
                           .company = (Company *) malloc(companies.maxCompanies * sizeof(Company))};
    User user;
    bool quit;

    do {
        quit = false;
        menuStart(&user, &quit, &companies);
    } while (quit != true);

    free(companies.company);

}
