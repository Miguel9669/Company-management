#include "user.h"
#include "constVariables.h"
#include "structs.h"
#include "Admin.h"
#include "Geral.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Menus.h"

void handleUser(User *user, bool *quit, Companies *companies, Activities *activities) {
    header("USER");
    getString(user->name, "Your name: ", MAX_NAME);
    getString(user->email, "Your email: ", MAX_EMAIL);
    bool back;
    do {
        back = false;
        menuUserSearch(&back, companies, user, activities);
    } while (back != true);
}

void handleUserSearchByName(Companies *companies, User *user){
    Company *foundCompany = searchCompanyByName(companies);
    bool back;
    if (foundCompany != NULL) {
        do{
            back = false;
            if (foundCompany->active) {
                showCompany(foundCompany);
                menuCompany(user, foundCompany, &back);
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
    int optionActivity = menuShowActivity(activities, false, "0 Sair");
    int numberCompaniesInActivity = showCompaniesInActivity(activities, companies, optionActivity - 1);
    if (numberCompaniesInActivity > 0) {
        Company *foundCompany = searchCompanyByName(companies);
        if (foundCompany == NULL || strcmp(foundCompany->activity, activities->activities[optionActivity - 1].activity) != 0 ){
            puts("Error: Please search for a company that's in this category");
        } else {
            bool back;
            do{
                back = false;
                showCompany(foundCompany);
                menuCompany(user, foundCompany, &back);
            } while (back != true);
        }
    } else {
        puts("No company here!!");
    }

}
void handleUserSelectByCategory(Companies *companies, User *user, int valueCategory){
    int count = numberCompaniesInCategory(companies, valueCategory);
    if (count > 0) {
        searchByCategory(companies, valueCategory);
        Company *foundCompany = searchCompanyByName(companies);
        if (foundCompany->category != valueCategory || foundCompany == NULL){
            puts("Error: Please search for a company that's in this category");
        } else {
            bool back;
            do{
                back = false;
                if (foundCompany->active) {
                    showCompany(foundCompany);
                    menuCompany(user, foundCompany, &back);
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

Company *searchCompanyByName(Companies *companies){
    char companySearchName[MAX_NAME_COMPANY];
    getString(companySearchName, "\nWhich company do you want to search: ", MAX_NAME_COMPANY);
    for (int i = 0; i < companies -> numberCompanies; i++){
        if (strcmp(companies->company[i].nameCompany, companySearchName) == 0){
            return &(companies -> company[i]);
        }
    }
    return NULL;
}

void searchByCategory(Companies *companies, int valueCategory){
    header("COMPANIES FOUND");
    for (int i = 0; i < companies->numberCompanies; ++i) {
        printf("-> %s", companies->company[i].nameCompany);

    }
}

void comment(User *user, Company *company) {
    Comment *companyComments = &(company->comments[company->numberComments]);
    if (company->maxComments - company->numberComments == 1) {
        Comment *pComment= (Comment *) realloc(company->comments, (company->maxComments + 10) * sizeof(Comment));
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
}

void rating(User *user, Company *company) {
    int userRating;
    do {
        userRating = inputNumber(USER_RATING_TXT);
        if (userRating >= 1 && userRating <= 5) {
            if (company->maxRates - company->numberRates == 1) {
                Rate *pRate = (Rate *) realloc(company->rates,(company->maxRates + 10) * sizeof(Rate));
                if (pRate != NULL) {
                    company->rates = pRate;
                    company->maxRates *= 2;
                } else {
                    printf("ERROR: Failed in realloc rating");
                    return;
                }
            }
            company->rates[company->numberRates].rate = userRating;
            company->numberRates++;
        } else {
            printf("Invalid rating!\n");
        }
    } while (userRating < 1 || userRating > 5);
}
