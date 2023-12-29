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
    int numberCompanies = getNumberFromFile(FILE_NUMBER_COMPANIES_NAME);
    int numberActivities = getNumberFromFile(FILE_NUMBER_ACTIVITIES_NAME);
    Companies companies = {.numberCompanies = numberCompanies,
                           .maxCompanies = numberCompanies > 10 ? numberCompanies * 2 : 10,
                           .company = (Company *) malloc(companies.maxCompanies * sizeof(Company))};
    Activities activities = {
            .numberActivities = numberActivities,
            .maxActivities = numberActivities == 0 ? 5 : numberActivities * 2,
            .activities = (Activity *) malloc(activities.maxActivities * sizeof(Activity))};
    inicializeStructs(numberCompanies, FILE_WITH_COMPANIES, companies.company, sizeof(Company));
    inicializeStructs(numberActivities, FILE_WITH_ACTIVITIES, activities.activities, sizeof(Activity));
    User user;
    bool quit;

    do {
        quit = false;
        menuStart(&user, &quit, &companies, &activities);
    } while (quit != true);
    free(activities.activities);
    free(companies.company);

}
