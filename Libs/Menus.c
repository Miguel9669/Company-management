#include "Menus.h"
#include "Geral.h"
#include "user.h"
#include "Admin.h"
#include <stdio.h>
#include "string.h"
#include "Company.h"

/**
 * @brief Displays the activity menu for user selection, allowing the creation of a new activity.
 *
 * This function shows the activity menu, including the option to create a new activity.
 * It prompts the user to select an activity from the list and validates the input.
 *
 * @param activities A pointer to the Activities structure containing the list of activities.
 * @param admin A boolean indicating whether the user is an admin.
 * @param txt Additional text to display in the menu.
 * @return The user's selected activity option.
 */
int menushowActivity(Activities *activities, bool admin, char *txt) {
    int option;
    do{
        header("SELECT ACTIVITY");
        showActivity(activities, admin);
        printf("%s", txt);
        option = inputNumber("");
    } while (!verifyNumber(option, -1, activities->numberActivities));
    return option;
}

/**
 * @brief Displays the initial menu and handles user's choice for different roles.
 *
 * This function presents the main menu to the user, allowing them to choose between different roles
 * such as user, admin, or company. It then calls the corresponding handler functions based on the user's choice.
 *
 * @param user A pointer to the User structure for user-related operations.
 * @param quit A pointer to a boolean variable indicating whether the program should quit.
 * @param companies A pointer to the Companies structure for company-related operations.
 * @param activities A pointer to the Activities structure for activity-related operations.
 * @param informations A pointer to the Informations structure for tracking information.
 */
void menuStart(User *user, bool *quit, Companies *companies, Activities *activities, Informations *informations) {
    int option = GetOption(MENU_START, 0, 3, false, true, "START");
    switch (option) {
        case 0:
            puts("BYE");
            *quit = true;
            break;
        case 1:
            handleUser(user, companies, activities, informations);
            break;
        case 2:
            handleAdmin(companies, activities, informations);
            break;
        case 3:
            handleCompany(companies, activities, *informations);
            break;
    }
}

/**
 * @brief Displays the user search menu and handles user's choice for different search options.
 *
 * This function presents the user search menu, allowing the user to choose between searching by name,
 * category, or activity. It then calls the corresponding handler functions based on the user's choice.
 *
 * @param quit A pointer to a boolean variable indicating whether the program should quit.
 * @param companies A pointer to the Companies structure for company-related operations.
 * @param user A pointer to the User structure for user-related operations.
 * @param activities A pointer to the Activities structure for activity-related operations.
 * @param informations A pointer to the Informations structure for tracking information.
 */
void menuUserSearch(bool *quit, Companies *companies, User *user, Activities *activities, Informations *informations) {
    int option = GetOption(MENU_USER_SEARCH, 0, 3, false, true, SEARCH_COMPANY);
    switch (option) {
        case 0:
            puts("BYE");
            *quit = true;
            break;
        case 1:
            handleUserSearchByName(companies, user, informations);
            break;
        case 2:
            handleUserSearchByCategory(companies, user, informations);
            break;
        case 3:
            handleUserSearchByActivity(companies, activities, user, informations);
            break;
    }
}

/**
 * @brief Displays the main menu for administrators and handles user's choices.
 *
 * This function presents the main menu for administrators, allowing the user to create a company, modify existing
 * companies, manage activities, generate reports, or exit the program. It calls the corresponding handler functions
 * based on the user's choice.
 *
 * @param quit A pointer to a boolean variable indicating whether the user wants to quit the program.
 * @param companies A pointer to the Companies structure containing the list of companies.
 * @param activities A pointer to the Activities structure for activity-related operations.
 * @param informations A pointer to the Informations structure for tracking information.
 */
void menuAdmin(bool *quit, Companies *companies, Activities *activities, Informations *informations) {
    int option1 = GetOption(MENU_ADMIN, 0, 4, false, true, ADMIN_MENU);
    switch (option1) {
        case 0:
            puts("BYE");
            *quit = true;
            break;
        case 1:
            createCompany(companies, activities, informations);
            break;
        case 2:
            modifyCompany(companies, activities, ADMIN, MENU_MANAGE_COMPANY_ADMIN, 0, 9, *informations);
            break;
        case 3:
            handleAdminActivity(activities, companies);
            break;
        case 4:
            handleAdminReports(*companies, *informations);
            break;
    }
}

/**
 * @brief Displays the menu for administrative reports and handles user's choices.
 *
 * This function presents the menu for administrative reports, allowing the user to list companies based on search or rating.
 * It calls the corresponding handler functions based on the user's choice.
 *
 * @param back A pointer to a boolean variable indicating whether the user wants to go back to the previous menu.
 * @param companies A reference to the Companies structure containing the list of companies.
 * @param informations A reference to the Informations structure for tracking information.
 * @param topRate The top-rated companies to display in the report.
 * @param topSearched The most searched companies to display in the report.
 */
void menuAdminReports (bool *back, Companies companies, Informations informations, int topRate, int topSearched) {
    char ola[sizeof(MENU_ADMIN_REPORTS)];
     sprintf(ola, MENU_ADMIN_REPORTS, topSearched, topRate);
    int option = GetOption(ola, 0, 2, false, true, "REPORTS");
    switch (option) {
        case 0:
            *back = true;
            break;
        case 1:
            listMostCompanies(companies, informations, true, topSearched);
            break;
        case 2:
            listMostCompanies(companies, informations, false, topRate);
            break;
    }
}

/**
 * @brief Displays the menu for managing comments on a company and handles user's choices.
 *
 * This function presents the menu for managing comments on a company, allowing the user (admin or company) to
 * delete or hide comments. It calls the corresponding handler functions based on the user's choice.
 *
 * @param company A pointer to the Company structure representing the company with comments.
 * @param userType The type of user (ADMIN or COMPANY) interacting with the comments.
 * @param companies A pointer to the Companies structure containing the list of companies.
 */
void menuComments(Company *company, Type userType, Companies *companies) {
    int optionComments;
    if (company->numberComments > 0) {
        do {
            optionComments = showComments(company, true);
        } while (!verifyNumber(optionComments, 0, company->numberComments));
    } else {
        puts("No comments!!!");
        return;
    }

    if (userType == ADMIN) {
        int option = GetOption(MENU_COMMENTS,0,2,true,false,"");
        switch (option) {
            case 0:
                puts("BYE");
                break;
            case 1:
                deleteComment(company, optionComments - 1);
                updateComments(companies);
                break;
            case 2:
                hideComments(company, optionComments - 1);
                updateComments(companies);
                break;
        }
    }
    if (userType == COMPANY) {
        int option = GetOption(MENU_COMMENTS_COMPANY,0,1,true,false,"");
        switch (option) {
            case 0:
                puts("BYE");
                break;
            case 1:
                hideComments(company, optionComments - 1);
                updateComments(companies);
                break;
        }
    }
}

/**
 * @brief Displays the menu for managing companies and handles user's choices.
 *
 * This function presents the menu for managing companies, allowing the user to modify a company or exit the program.
 * It calls the corresponding handler functions based on the user's choice.
 *
 * @param quit A pointer to a boolean variable indicating whether the user wants to quit the program.
 * @param companies A pointer to the Companies structure containing the list of companies.
 * @param activities A pointer to the Activities structure for activity-related operations.
 * @param informations A pointer to the Informations structure for tracking information.
 */
void menuCompanies(bool *quit, Companies *companies, Activities *activities, Informations informations) {
    int option = GetOption(MENU_COMPANY, 0, 1, true, false, COMPANY_MENU);
    switch (option) {
        case 0:
            puts("BYE");
            *quit = true;
            break;
        case 1:
            modifyCompany(companies, activities, COMPANY, MENU_MANAGE_COMPANY_COMPANY, 0, 9, informations);
            break;
    }
}

/**
 * @brief Displays the menu for user interaction with a specific company and handles user's choices.
 *
 * This function presents the menu for user interaction with a specific company, allowing actions such as
 * commenting, rating, showing comments, or returning to the previous menu. It calls the corresponding handler
 * functions based on the user's choice.
 *
 * @param user A pointer to the User structure for user-related operations.
 * @param foundCompany A pointer to the Company structure representing the selected company.
 * @param back A pointer to a boolean variable indicating whether the user wants to go back to the previous menu.
 * @param index The index of the company in the list.
 * @param companies A pointer to the Companies structure containing the list of companies.
 */
void menuCompany(User *user, Company *foundCompany, bool *back, int index, Companies *companies){
    int option = GetOption(MENU_INSIDE_COMPANY,0, 3, true, false, "");
    switch (option) {
        case 1:
            comment(user, foundCompany, index);
            updateComments(companies);
            break;
        case 2:
            rating(foundCompany, index);
            break;
        case 3:
            showComments(foundCompany, false);
            break;
        case 0:
            *back = true;
            break;
    }
}

/**
 * @brief Displays the menu for user selection by category and handles user's choices.
 *
 * This function presents the menu for selecting companies based on category.
 * It prompts the user to choose a category and calls the corresponding handler function for further actions.
 *
 * @param companies A pointer to the Companies structure containing the list of companies.
 * @param user A pointer to the User structure for user-related operations.
 * @param informations A pointer to the Informations structure for tracking information.
 */
void menuSearchByCategory(Companies *companies, User *user, Informations *informations){
    int option = GetOption(MENU_SEARCH_BY_CATEGORY,1,3,true, false, "");
    switch(option){
        case 1 :
            handleUserSelectByCategory(companies, user, 1, informations);
            break;
        case 2 :
            handleUserSelectByCategory(companies, user, 2, informations);
            break;
        case 3 :
            handleUserSelectByCategory(companies, user, 3, informations);
            break;
    }
}

/**
 * @brief Displays the activity branch menu, allowing the user to create a new activity or select an existing one.
 *
 * This function shows the activity branch menu, allowing the user to either create a new activity or select an existing one.
 * It calls the menushowActivity function to display the list of activities and handles the user's choice accordingly.
 *
 * @param activities A pointer to the Activities structure containing the list of activities.
 * @return The user's selected activity option.
 */
int menuBranchActivity(Activities *activities) {
    int option = menushowActivity(activities, false, "0 Creat a new one");
    switch (option) {
        case 0:
            creatActivity(activities);
    }
    return option;
}

/**
 * @brief Displays the activity menu for user selection, allowing the creation of a new one.
 *
 * This function shows the activity menu, including the option to create a new activity.
 * It prompts the user to select an activity from the list and validates the input.
 *
 * @param activities A pointer to the Activities structure containing the list of activities.
 * @param admin A boolean indicating whether the user is an admin.
 * @param txt Additional text to display in the menu.
 * @return The user's selected activity option.
 */
int menuShowActivity(Activities *activities, bool admin, char *txt) {
    return menushowActivity(activities, admin, txt);
}

/**
 * @brief Displays the admin action menu for managing activities and handles user's choices.
 *
 * This function presents the admin action menu for a specific activity, allowing the admin to change the activity's
 * active status, delete the activity (if no associated companies exist), or leave the menu. It performs the selected action.
 *
 * @param activities A pointer to the Activities structure containing the list of activities.
 * @param index The index of the activity in the list.
 * @param companies A pointer to the Companies structure for company-related operations.
 */
void menuActionAdminActivity(Activities *activities, int index, Companies *companies){
    int option;
    Activity *activity = &(activities->activities[index]);
    do {
        header(activity->activity);
        if (activity->Active == false) {
            puts("0 Active");
        } else {
            puts("0 Inactive");
        }
        puts("-1 Delete");
        puts("-2 Leave");
        option = inputNumber("");
    } while (option != 0 && option != -1 && option != -2);
    switch (option) {
        case 0:
            activitiesChangeActiveStatus(activity, companies, index);
            break;
        case -1:
            if (isCompanyExistInActivity(&activities->activities[index], companies) == 1){
                puts("You cant delete this Activity, because there are companies associated to this activity!");
            } else {
                deleteActivity(activities, index);
            }
            break;
        case -2:
            break;
    }
}

/**
 * @brief Displays the menu for modifying company information and handles user's choices.
 *
 * This function presents the menu for modifying various attributes of a company based on the user's choice.
 * It allows the user to modify the company name, activity, address, city, postal code, category, and more.
 * The modifications are then applied and updated in the Companies structure.
 *
 * @param companies A pointer to the Companies structure containing the list of companies.
 * @param index The index of the company to be modified.
 * @param activities A pointer to the Activities structure for activity-related operations.
 * @param userType The type of user initiating the modification (ADMIN or COMPANY).
 * @param txt Additional text to display in the menu.
 * @param min The minimum valid option.
 * @param max The maximum valid option.
 * @param informations A pointer to the Informations structure for tracking information.
 * @return The user's selected option.
 */
int menuModify(Companies *companies, int index, Activities *activities, Type userType, char *txt, int min, int max, Informations informations) {
    int optionActivity;
    Company *company = &companies->company[index];
    showCompany(company);
    int menuModify = GetOption(txt, min, max, false, true, MODIFY_MENU);
    switch (menuModify) {
        case 1:
            getNameForCompany(companies, index);
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, &companies->company[index], sizeof(Company));
            break;
        case 2:
            optionActivity = getActivityForCompany(activities, menuBranchActivity);
            strcpy(company->activity, activities->activities[optionActivity - 1].activity);
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, &companies->company[index], sizeof(Company));
            break;
        case 3:
            getString(company->local.adress, "New address: ", MAX_ADRESS);
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, &companies->company[index], sizeof(Company));
            break;
        case 4:
            getString(company->local.city, "New city: ", MAX_CITY);
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, &companies->company[index], sizeof(Company));
            break;
        case 5:
            getPostalCode(company);
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, &companies->company[index], sizeof(Company));
            break;
        case 6:
            company->category = GetOption(MENU_SEARCH_BY_CATEGORY, 1, 3, true, false, "");
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, &companies->company[index], sizeof(Company));
            break;
        case 7:
            companyChangeActiveStatus(activities, companies, company, index);
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, &companies->company[index], sizeof(Company));
            break;
        case 8:
            menuComments(company, userType, companies);
            break;
        case 9:
            if (userType == COMPANY) {
                handleMenuReports(company, informations, index);
            } else if (userType == ADMIN)
                deleteCompany(companies, index);
            break;
        case 0:
            printf("Leaving!.\n");
            break;
        default:
            printf("Invalid option, try again!.\n");
    }
    return menuModify;
}

/**
 * @brief Displays the company reports menu for admin or company users.
 *
 * This function displays the menu for viewing reports related to a company and performs the selected action.
 * It prompts the user to choose whether to view reports for the given company or leave the menu.
 *
 * @param company A pointer to the Company structure for which reports are displayed.
 * @param informations A pointer to the Informations structure for tracking information.
 * @param index The index of the company.
 * @return 0 if the user chooses to leave the menu, 1 otherwise.
 */
int menuCompanyReport(Company *company, Informations informations, int index) {
    char menu[sizeof(MENU_REPORTS_IN_COMPANY_COMPANY)];
    sprintf(menu, MENU_REPORTS_IN_COMPANY_COMPANY, company->nameCompany);
    int option = GetOption(menu, 0, 1, false, true, "REPORTS");
    switch (option) {
        case 1:
            reportForCompany(informations, index, company);
            break;
        case 0:
            return 0;
    }
    return 1;
}

