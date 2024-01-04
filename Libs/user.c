#include "user.h"
#include "constVariables.h"
#include "structs.h"
#include "Geral.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Menus.h"

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

void handleUser(User *user, Companies *companies, Activities *activities) {
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
        menuUserSearch(&back, companies, user, activities);
    } while (back != true);
}

void handleUserSearchByName(Companies *companies, User *user){
    int index;
    Company *foundCompany = searchCompanyByName(companies, &index);
    bool back;
    if (foundCompany != NULL) {
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

void handleUserSearchByCategory(Companies *companies, User *user){
    menuSearchByCategory(companies, user);
}

void handleUserSearchByActivity(Companies *companies, Activities *activities, User *user) {
    int index;
    int optionActivity = menuShowActivity(activities, false, "0 leave");
    int numberCompaniesInActivity = showCompaniesInActivity(activities, companies, optionActivity - 1);
    if (numberCompaniesInActivity > 0) {
        Company *foundCompany = searchCompanyByName(companies, &index);
        if (foundCompany == NULL || strcmp(foundCompany->activity, activities->activities[optionActivity - 1].activity) != 0 ){
            puts("Error: Please search for a company that's in this Activity");
        } else {
            bool back;
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
void handleUserSelectByCategory(Companies *companies, User *user, int valueCategory){
    int count = numberCompaniesInCategory(companies, valueCategory);
    int index;
    if (count > 0) {
        searchByCategory(companies, valueCategory);
        Company *foundCompany = searchCompanyByName(companies, &index);
        if (foundCompany->category != valueCategory || foundCompany == NULL){
            puts("Error: Please search for a company that's in this category");
        } else {
            bool back;
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

void searchByCategory(Companies *companies, int valueCategory){
    header("COMPANIES FOUND");
    for (int i = 0; i < companies->numberCompanies; ++i) {
        if (companies->company[i].category == valueCategory)
            printf("-> %s\n", companies->company[i].nameCompany);
    }
}

void comment(User *user, Company *company, int index) {
    Comment *companyComments = &(company->comments[company->numberComments]);
    if (company->maxComments - company->numberComments == 1) {
        Comment *pComment = (Comment *) realloc(company->comments, company->maxComments * 2 * sizeof(Comment));
        if (pComment != NULL) {
            company->comments = pComment;
            company->maxComments *= 2;
        } else {
            printf("ERROR: Failed in realloc comment");
        }
    }
    strcpy(companyComments->user.name, user->name);
    strcpy(companyComments->user.email, user->email);
    header("COMMENT");
    getString(companyComments->title, "Title: ", TITLE);
    getString(companyComments->commentText, "Comment: ", COMMENT);
    company->numberComments++;
    updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, company, sizeof(Company));
}

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
