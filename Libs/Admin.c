#include "Admin.h"
#include <stdio.h>
#include "structs.h"
#include <string.h>
#include "Geral.h"
#include <stdlib.h>
#include "constVariables.h"
#include "Menus.h"

/**
 * @brief Handles administrative actions.
 *
 * This function enters a loop to handle various administrative actions based on user input,
 * and it continues until the user chooses to go back.
 *
 * @param companies Pointer to the Companies structure.
 * @param activities Pointer to the Activities structure.
 * @param informations Pointer to the Informations structure.
 */
void handleAdmin(Companies *companies, Activities *activities, Informations *informations){
    bool back;
    do {
        back = false;
        menuAdmin(&back, companies, activities, informations);
    } while (back != true);
}

/**
 * @brief Creates a new company and adds it to the Companies structure.
 *
 * This function is used to create a new company and adds it to the Companies structure.
 * It collects information such as the company's name, nif, address, city, postal code, category, initializes the new company's
 * rates and comments, initialize the company active in true and update the number from file and the struct company.
 *
 * @param companies A pointer to the Companies structure to which the new company will be added.
 * @param activities A pointer to the Activities structure containing available activities for the company.
 * @param informations A pointer to the Informations structure containing additional information.
 */
void createCompany(Companies *companies, Activities *activities, Informations *informations) {
    reallocInStruct(informations->numberInformation, informations->maxInformation, NULL, NULL, informations,INFORMATIONS);
    reallocInStruct(companies->numberCompanies, companies->maxCompanies, companies, NULL, NULL, COMPANIES);
    int numberCompanies = companies->numberCompanies;
    Company *company = &(companies->company[numberCompanies]);
    getNameForCompany(companies, numberCompanies);
    getNifForCompany(company, companies, numberCompanies);
    int optionActivity = getActivityForCompany(activities, menuBranchActivity);
    strcpy(company->activity, activities->activities[optionActivity - 1].activity);
    getString(company->local.adress, MSG_GET_ADRESS, MAX_ADRESS);
    getString(company->local.city, MSG_GET_CITY, MAX_CITY);
    getPostalCode(company);
    company->category = GetOption(MENU_SEARCH_BY_CATEGORY, 1, 3, true, false, "");
    iniciateCommentsAndRates(company);
    company->active = true;
    iniciateInformation(informations, numberCompanies);
    companies->numberCompanies++;
    updateStructInformation(FILE_WITH_EXTRA_INFORMATION, informations);
    updateNumberFromFile(companies->numberCompanies, FILE_NUMBER_COMPANIES_NAME);
    updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * (companies->numberCompanies - 1), &companies->company[numberCompanies], sizeof(Company));
}

/**
 * @brief Initializes information.
 *
 * This function increments the total number of information and initialize several variables to zero in this case
 * searchByNameCounter, searchByCategoryCounter, searchByActivityCounter and searchCounter.
 *
 * @param informations Pointer to the Information structure.
 * @param index of the information to be initialized.
 */
void iniciateInformation(Informations *informations, int index) {
    informations->numberInformation++;
    Information *information = &informations->information[index];
    information->searchByNameCounter = 0;
    information->searchByCategoryCounter = 0;
    information->searchByActivityCounter = 0;
    information->searchCounter = 0;
}

/**
 * @brief Initializes comments and rates for a Company.
 *
 * This function aims to initialize several variables related to company comments and rates.
 * It sets the sum of rates to 0, the number of comments and rates to 0, and allocates memory
 * for storing comments with an initial capacity. It also initializes individual comment properties.
 *
 * @param company Pointer to the Company structure.
 */
void iniciateCommentsAndRates(Company *company) {
    company->sumRates = 0;
    company->numberComments = company->numberRates = 0;
    company->maxComments = 5;
    company->comments = (Comment *)malloc(company->maxComments * sizeof(Comment));

    verifyNumberComments(company);

    for (int i = 0; i < company->maxComments; ++i) {
        company->comments[i].commentHide = false;
    }
}

/**
 * @brief Deletes a company.
 *
 * This function removes a company at the specified index from the
 *
 * This function removes a company at the specified index from the list of companies.
 * If the company has comments, it cannot be deleted but can be set as an inactive company.
 * The function updates the Companies structure and writes the changes to a file.
 *
 * @param companies Pointer to the Companies structure.
 * @param index Index of the company to be deleted.
 */
void deleteCompany(Companies *companies, int index) {
    if (companies->company[index].numberComments > 0) {
        puts("You can not delete this company! But u can set as an inactive company.");
        return;
    }
    for (int i = index; i < companies->numberCompanies; ++i) {
        if (i != companies->numberCompanies)
            companies->company[i] = companies->company[i + 1];
    }
    Company *company = &companies->company[companies->numberCompanies];
    company->nif = 0;
    strcpy(company->nameCompany, "");
    strcpy(company->activity,"");
    strcpy(company->local.adress, "");
    strcpy(company->local.city, "");
    strcpy(company->local.codigoPostal, "");
    company->active = false;
    printf("Company deleted successfully.\n");
    updateStructCompany(FILE_WITH_COMPANIES, 0, companies->company, sizeof(Company) * companies->numberCompanies);
    memset(&companies->company[companies->numberCompanies - 1], 0, sizeof(Company));
    companies->numberCompanies--;
    updateNumberFromFile(companies->numberCompanies, FILE_NUMBER_COMPANIES_NAME);
}

/**
 * @brief Creates a new activity.
 *
 * This function dynamically reallocates memory to accommodate a new activity in the list.
 * It then prompts the user to enter details for the new activity, sets it as active,
 * increments the total number of activities, and updates the external files.
 *
 * @param activities Pointer to the Activities structure.
 */
void creatActivity(Activities *activities){
    reallocInStruct(activities->numberActivities, activities->maxActivities, NULL, activities, NULL, ACTIVITIES);
    createNameActivity(activities);
    activities->activities[activities->numberActivities].Active = true;
    activities->numberActivities++;
    updateNumberFromFile(activities->numberActivities, FILE_NUMBER_ACTIVITIES_NAME);
    updateStructActivities(FILE_WITH_ACTIVITIES, sizeof(Activity) * (activities->numberActivities - 1), &activities->activities[activities->numberActivities - 1], sizeof(Activity));
}

/**
 * @brief Deactivates an activity and updates related companies accordingly.
 *
 * This function deactivates the specified activity and updates the external files
 * with the changes. It also sets the related companies as inactive.
 *
 * @param activity Pointer to the Activity structure to be deactivated.
 * @param companies Pointer to the Companies structure.
 * @param index Index of the activity to be deactivated.
 */
void inactiveActivity(Activity *activity, Companies *companies, int index) {
    activity->Active = false;
    updateStructActivities(FILE_WITH_ACTIVITIES, sizeof(Activity) * index, activity, sizeof(Activity));
    for (int i = 0; i < companies->numberCompanies; i++) {
        if (strcmp(companies->company[i].activity, activity->activity) == 0) {
            companies->company[i].active = false;
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * i, &companies->company[i], sizeof(Company));
        }
    }
}

/**
 * @brief Activates an activity and updates related companies accordingly.
 *
 * This function activates the specified activity and updates the external files
 * with the changes. It also sets the related companies as active.
 *
 * @param activity Pointer to the Activity structure to be activated.
 * @param companies Pointer to the Companies structure.
 * @param index Index of the activity to be activated.
 */
void activeActivity(Activity *activity, Companies *companies, int index) {
    activity->Active = true;
    updateStructActivities(FILE_WITH_ACTIVITIES, sizeof(Activity) * index, activity, sizeof(Activity));
    for (int i = 0; i < companies->numberCompanies; i++) {
        if (strcmp(companies->company[i].activity, activity->activity) == 0) {
            companies->company[i].active = true;
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * i, &companies->company[i], sizeof(Company));
        }
    }
}

/**
 * @brief Handles administrative actions related to activities.
 *
 * This function displays a menu of administrative actions related to activities,
 * and based on user input, it either performs the selected action or creates a new activity.
 *
 * @param activities Pointer to the Activities structure.
 * @param companies Pointer to the Companies structure.
 */
void handleAdminActivity(Activities *activities, Companies *companies) {
    int optionActivity;
    do {
        optionActivity = menuShowActivity(activities, true, "0 Create Activity\n-1 Sair");
        if (optionActivity != -1 && optionActivity != 0)
            menuActionAdminActivity(activities, optionActivity - 1, companies);

        if (optionActivity == 0) {
            creatActivity(activities);
        }
    } while (optionActivity != -1);
}

/**
 * @brief Handles administrative reports.
 *
 * This function enters a loop to handle administrative reports based on user input,
 * and it continues until the user chooses to go back.
 *
 * @param companies Companies structure.
 * @param informations Informations structure.
 */
void handleAdminReports(Companies companies, Informations informations) {
    bool back;
    do {
        back = false;
        menuAdminReports(&back, companies, informations, 2, 2);
    } while (!back);
}

/**
 * @brief Deletes an activity.
 *
 * This function removes an activity at the specified index from the list of activities.
 * It shifts the remaining activities to fill the gap and updates the Activities structure accordingly.
 *
 * @param activities Pointer to the Activities structure.
 * @param index Index of the activity to be deleted.
 */
void deleteActivity(Activities *activities, int index) {
    for (int i = index; i < activities->numberActivities - 1; i++) {
        activities->activities[i] = activities->activities[i + 1];
        updateStructActivities(FILE_WITH_ACTIVITIES, sizeof(Activity) * index, &activities->activities[index], sizeof(Activity));
    }
    activities->numberActivities--;
    updateNumberFromFile(activities->numberActivities, FILE_NUMBER_ACTIVITIES_NAME);
}

/**
 * @brief Modifies a company based on user input and menu options.
 *
 * This function allows the user to input a company's NIF, finds the corresponding company,
 * and then enters a menu loop for modifying various aspects of the company based on user choices.
 * The modification options are presented through the menu provided by the `menuModify` function.
 *
 * @param companies Pointer to the Companies structure.
 * @param activities Pointer to the Activities structure.
 * @param userType Type of user (user, admin or company).
 * @param txt Additional text for user interaction.
 * @param min Minimum menu option.
 * @param max Maximum menu option.
 * @param informations Informations structure.
 */
void modifyCompany(Companies *companies, Activities *activities, Type userType, char *txt, int min, int max, Informations informations) {
    int nif, index, opcao;

    if (companies->numberCompanies > 0) {
        nif = inputNumber(OPERATING_NIF_COMPANY);
        index = findCompanyIndexByNif(companies, nif);
        if (index == -1) {
            printf("Company not found: %d\n", nif);
            return;
        }

        do {
            opcao = menuModify(companies, index, activities, userType, txt, min, max, informations);
        } while (opcao != 0);
    } else {
        printf("No companies to modify.\n");
    }
}

/**
 * @brief Delete comment for a specific Company.
 *
 *This function removes a comment at the specified index from the Company list of comments.
 *After that the function shifts the remaining comments to fill the gap and updates the Company structure accordingly.
 *
 * @param company Pointer to the Company structure.
 * @param index Index of the comment to be deleted.
 */
void deleteComment(Company *company, int index) {
    for (int i = index; i < company->numberComments - 1; i++) {
        company->comments[i] = company->comments[i + 1];
    }
    company->numberComments--;
    updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * (index + 1), company, sizeof(Company));
}

/**
 * @brief Hides or display a comment for a specific Company.
 *
 * This function toggles the visibility state of a comment at the specified index for a Company.
 * If the comment is currently visible, it hides it, otherwise, it display it.
 * The function updates the Company structure and writes the changes to a file.
 *
 * @param company Pointer to the Company structure.
 * @param index Index of the comment to be hidden or unhidden.
 */
void hideComments(Company *company, int index) {
    for (int i = 0; i < company->numberComments; i++) {
        if (i == index) {
            if (company->comments[i].commentHide == false) {
                company->comments[i].commentHide = true;
                updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, company, sizeof(Company));
            }
            else{
                company->comments[i].commentHide = false;
                updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, company, sizeof(Company));
            }
        }
    }
}







