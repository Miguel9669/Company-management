#include "user.h"
#include "constVariables.h"
#include "structs.h"
#include "Geral.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Menus.h"

/**
 * @brief Checks if the given email address is valid.
 *
 * This function checks if the email address has the correct format with
 * the presence of '@' and '.' symbols in the right positions.
 *
 * @param email The input email address to be validated.
 *
 * @return true if the email is valid, false otherwise.
 */
bool isValidEmail(const char *email) {
    const char *atSymbol = strchr(email, '@');
    if (atSymbol == NULL || atSymbol == email) {
        return false;
    }

    const char *dotSymbol = strchr(atSymbol, '.');
    if (dotSymbol == NULL || dotSymbol == atSymbol + 1) {
        return false;
    }

    if (dotSymbol[1] == '\0') {
        return false;
    }

    return true;
}

/**
 * @brief Handles user-related operations, including name and email input, and user search menu.
 *
 * This function interacts with the user to get their name and email, ensuring a valid email address.
 * It then provides a menu for user search operations on companies, activities, and information.
 *
 * @param user A pointer to the User structure to store user information.
 * @param companies A pointer to the Companies structure for user search operations.
 * @param activities A pointer to the Activities structure for user search operations.
 * @param informations A pointer to the Informations structure for user search operations.
 */
void handleUser(User *user, Companies *companies, Activities *activities, Informations *informations) {
    header("USER");
    getString(user->name, GET_USER_NAME, MAX_NAME);

    do {
        getString( user->email, GET_USER_EMAIL, MAX_EMAIL);
        if (!isValidEmail(user->email)) {
            puts(INVALID_EMAIL);
        }
    } while (!isValidEmail(user->email));

    bool back;
    do {
        back = false;
        menuUserSearch(&back, companies, user, activities, informations);
    } while (back != true);
}

/**
 * @brief Handles user search by company name, displaying information and providing a menu for further actions.
 *
 * This function searches for a company by name, displays its information, and allows the user to perform
 * actions through a menu (if the company is found and active).
 *
 * @param companies A pointer to the Companies structure for searching companies.
 * @param user A pointer to the User structure for user-related operations.
 * @param informations A pointer to the Informations structure for tracking search counter.
 */
void handleUserSearchByName(Companies *companies, User *user, Informations *informations){
    int index;
    Company *foundCompany = searchCompanyByName(companies, &index);
    bool back;
    if (foundCompany != NULL) {
        if(foundCompany->active)
            addToInformation(informations, index, &informations->information[index].searchByNameCounter);
        do{
            back = false;
            if (foundCompany->active) {
                showCompany(foundCompany);
                menuCompany(user, foundCompany, &back, index, companies);
            } else {
                puts(SEARCH_NOT_FOUND);
                break;
            }

        } while (back != true);
    }
}

/**
 * @brief Handles user search by category, displaying a menu for category selection.
 *
 * This function presents a menu for the user to select a category for searching companies.
 * It then calls the appropriate functions to perform the search and display results.
 *
 * @param companies A pointer to the Companies structure for searching companies.
 * @param user A pointer to the User structure for user-related operations.
 * @param informations A pointer to the Informations structure for tracking search counter.
 */
void handleUserSearchByCategory(Companies *companies, User *user, Informations *informations){
    menuSearchByCategory(companies, user, informations);
}

/**
 * @brief Handles user search by activity, allowing selection and interaction with companies in the chosen activity.
 *
 * This function prompts the user to select an activity and then displays companies associated with that activity.
 * The user can then search for a specific company within the selected activity and interact with it through a menu.
 *
 * @param companies A pointer to the Companies structure for searching companies.
 * @param activities A pointer to the Activities structure for retrieving activity information.
 * @param user A pointer to the User structure for user-related operations.
 * @param informations A pointer to the Informations structure for tracking search counter.
 */
void handleUserSearchByActivity(Companies *companies, Activities *activities, User *user, Informations *informations) {
    int index;
    int optionActivity = menuShowActivity(activities, false, "0 leave");
    int numberCompaniesInActivity = showCompaniesInActivity(activities, companies, optionActivity - 1);
    if (numberCompaniesInActivity > 0) {
        Company *foundCompany = searchCompanyByName(companies, &index);
        if (foundCompany == NULL || strcmp(foundCompany->activity, activities->activities[optionActivity - 1].activity) != 0 ){
            puts("Error: Please search for a company that's in this Activity");
        } else {
            bool back;
            addToInformation(informations, index, &informations->information[index].searchByActivityCounter);
            do{
                back = false;
                showCompany(foundCompany);
                menuCompany(user, foundCompany, &back, index, companies);
            } while (back != true);
        }
    } else {
        puts("No company here!!");
    }
}

/**
 * @brief Handles user selection by category, allowing interaction with companies in the chosen category.
 *
 * This function prompts the user to select a category and then displays companies associated with that category.
 * The user can then search for a specific company within the selected category and interact with it through a menu.
 *
 * @param companies A pointer to the Companies structure for searching companies.
 * @param user A pointer to the User structure for user-related operations.
 * @param valueCategory The category value for filtering companies.
 * @param informations A pointer to the Informations structure for tracking search counter.
 */
void handleUserSelectByCategory(Companies *companies, User *user, int valueCategory, Informations *informations){
    int count = numberCompaniesInCategory(companies, valueCategory);
    int index;
    if (count > 0) {
        searchByCategory(companies, valueCategory);
        Company *foundCompany = searchCompanyByName(companies, &index);
        if (foundCompany->category != valueCategory || foundCompany == NULL){
            puts("Error: Please search for a company that's in this category");
        } else {
            bool back;
            if (foundCompany->active)
                addToInformation(informations, index, &informations->information[index].searchByCategoryCounter);
            do{
                back = false;
                if (foundCompany->active) {
                    showCompany(foundCompany);
                    menuCompany(user, foundCompany, &back, index, companies);
                } else {
                    puts(SEARCH_NOT_FOUND);
                    break;
                }
            } while (back != true);
        }
    } else {
        puts(SEARCH_NOT_FOUND_IN_CATEGORY);
    }
}

/**
 * @brief Searches for a company by name within the given list of companies.
 *
 * This function prompts the user to enter a company name and searches for a matching company within the list.
 *
 * @param companies A pointer to the Companies structure containing the list of companies.
 * @param index A pointer to an integer that will store the index of the found company (if any).
 * @return A pointer to the found Company structure, or NULL if not found.
 */
Company *searchCompanyByName(Companies *companies, int *index){
    char companySearchName[MAX_NAME_COMPANY];

    if (companies->numberCompanies <= 0) {
        printf("No companies");
        return NULL;
    }

    getString(companySearchName, "\nWhich company do you want to search (by name): ", MAX_NAME_COMPANY);
    for (int i = 0; i < companies -> numberCompanies; i++){
        if (strcmp(companies->company[i].nameCompany, companySearchName) == 0){
            *index = i;
            return &(companies -> company[i]);
        }
    }
    return NULL;
}

/**
 * @brief Displays companies from the given list that match the specified category.
 *
 * This function iterates through the list of companies and prints the names of companies
 * that belong to the specified category.
 *
 * @param companies A pointer to the Companies structure containing the list of companies.
 * @param valueCategory The category value for filtering companies.
 */
void searchByCategory(Companies *companies, int valueCategory){
    header("COMPANIES FOUND");
    for (int i = 0; i < companies->numberCompanies; ++i) {
        if (companies->company[i].category == valueCategory)
            printf("-> %s\n", companies->company[i].nameCompany);
    }
}

/**
 * @brief Adds a comment to the specified company by the given user.
 *
 * This function allows a user to add a comment to a company. It allocates additional memory
 * for comments if needed, then prompts the user for a title and comment text.
 *
 * @param user A pointer to the User structure providing the user information.
 * @param company A pointer to the Company structure to which the comment is added.
 * @param index The index of the company in the data file.
 */
void comment(User *user, Company *company, int index) {
    if (company->maxComments == company->numberComments) {
        Comment *pComment = (Comment *) realloc(company->comments, company->maxComments * 2 * sizeof(Comment));
        if (pComment != NULL) {
            company->comments = pComment;
            company->maxComments *= 2;
        } else {
            printf("ERROR: Failed in realloc comment");
        }
    }
    Comment *companyComments = &(company->comments[company->numberComments]);
    strcpy(companyComments->user.name, user->name);
    strcpy(companyComments->user.email, user->email);
    header("COMMENT");
    getString(companyComments->title, "Title: ", TITLE);
    getString(companyComments->commentText, "Comment: ", COMMENT);
    company->numberComments++;
    updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, company, sizeof(Company));
}

/**
 * @brief Adds a rating to the specified company.
 *
 * This function allows a user to add a rating to a company, validating the rating
 * to be between 1 and 5. It updates the company's rating information accordingly.
 *
 * @param company A pointer to the Company structure to which the rating is added.
 * @param index The index of the company in the data file.
 */
void rating(Company *company, int index) {
    int userRating;
    do {
        userRating = inputNumber(USER_RATING_TXT);
        if (userRating >= 1 && userRating <= 5) {
            company->sumRates += userRating;
            company->numberRates++;
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, company, sizeof(Company));
        } else {
            printf("Invalid rating!\n");
        }
    } while (userRating < 1 || userRating > 5);
}
