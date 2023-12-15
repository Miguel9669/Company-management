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
    Companies companies = {.numberCompanies = 0,
                           .maxCompanies = 10,
                           .company = (Company *) malloc(companies.maxCompanies * sizeof(Company))};
    Activities activities = {
            .numberActivities = 0,
            .maxActivities = 5,
            .activities = (Activity *) malloc(activities.maxActivities * sizeof(Activity))};
    User user;
    bool quit;

    do {
        quit = false;
        menuStart(&user, &quit, &companies, &activities);
    } while (quit != true);
    free(activities.activities);
    free(companies.company);

}
