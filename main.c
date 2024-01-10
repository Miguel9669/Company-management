/**
 * @file main.c
 * @brief Main source file for the company management system.
 *
 * This file contains the main function for the company management system.
 * It initializes the necessary data structures, loads data from files, and starts the main menu loop.
 * After the user exits the program, it frees allocated memory.
 *
 * @author Antonio, Miguel, Luis
 * @date 20-12-2023
 */
#include <stdlib.h>
#include "Libs/constVariables.h"
#include "Libs/Geral.h"
#include "Libs/structs.h"
#include "Libs/Menus.h"

int main() {
    int numberCompanies = getNumberFromFile(FILE_NUMBER_COMPANIES_NAME);
    int numberActivities = getNumberFromFile(FILE_NUMBER_ACTIVITIES_NAME);
    Companies companies = {.numberCompanies = numberCompanies,
                           .maxCompanies = numberCompanies > 10 ? numberCompanies * 2 : 10,
                           .company = (Company *) malloc(companies.maxCompanies * sizeof(Company))};
    Informations informations = {
            .maxInformation = numberCompanies > 10 ? numberCompanies * 2 : 10,
            .numberInformation = numberCompanies,
            .information = (Information *)
                    malloc(informations.maxInformation * sizeof(Information))
    };
    Activities activities = {
            .numberActivities = numberActivities,
            .maxActivities = numberActivities == 0 ? 5 : numberActivities * 2,
            .activities = (Activity *) malloc(activities.maxActivities * sizeof(Activity))};

    loadStructCompany(numberCompanies, FILE_WITH_COMPANIES, companies.company, sizeof(Company));
    loadComments(&companies);
    loadStructActivity(numberActivities, FILE_WITH_ACTIVITIES, activities.activities, sizeof(Activity));
    loadStructInformation(numberCompanies, FILE_WITH_EXTRA_INFORMATION, informations.information, sizeof(Information));

    User user;
    bool quit;
    do {
        quit = false;
        menuStart(&user, &quit, &companies, &activities, &informations);
    } while (quit != true);

    for (int i = 0; i < companies.numberCompanies; ++i) {
        free(companies.company[i].comments);
    }
    free(informations.information);
    free(activities.activities);
    free(companies.company);
    return 0;
}
