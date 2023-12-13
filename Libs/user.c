//
// Created by anton on 06/12/2023.
//

#include "user.h"
#include "constVariables.h"
#include "structs.h"
#include "Admin.h"
#include "Geral.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Menus.h"

int lenCharArray(char *array){
    int count = 0;
    do{
        count++;
    } while (array[count] != '\n');
}
void handleUser(User *user, bool *quit, Companies *companies) {
    header("USER");
    getString(user->name, "Your name: ", MAX_NAME);
    getString(user->email, "Your email: ", MAX_EMAIL);
    bool back;
    do {
        back = false;
        menuUserSearch(&back, companies, user);
    } while (back != true);
}
void handleUserSearchByName(Companies *companies, User *user){
    Company *foundCompany = searchCompanyByName(companies);
    bool back;
    if (foundCompany != NULL) {
        do{
            back = false;
            showCompany(foundCompany, false);
            menuCompany(user, foundCompany, &back);
        } while (back != true);
    }
}
void handleUserSearchByCategory(Companies *companies, User *user){
    menuSearchByCategory(companies, user);
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
                showCompany(foundCompany, false);
                menuCompany(user, foundCompany, &back);
            } while (back != true);
        }
    } else {
        puts(SEARCH_NOT_FOUND_IN_CATEGORY);
    }


}
void runArrayAndChangeString(char *variable, char *array){
    int len = lenCharArray(array);
    for(int i = 0; i < len; i++){
        variable[i] = array[i];
    }
}

Company *searchCompanyByName(Companies *companies){
    char companySearchName[MAX_NAME_COMPANY];
    getString(companySearchName, "Which company do you want to search: ", MAX_NAME_COMPANY);
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

void comentar(User *user, Company *company) {
    if (company->maxComments - company->numberComments == 1) {
        Comment *pComment= (Comment *) realloc(company->comments, (company->maxComments + 10) * sizeof(Comment));
        if (pComment != NULL) {
            company->comments = pComment;
            company->maxComments *= 2;
        } else {
            printf("ERROR: Failed in realloc comment");
        }
    }
    strcpy(company->comments[company->numberComments].user.name, user->name);
    strcpy(company->comments[company->numberComments].user.email, user->email);
    system("clear");
    header("COMMENT");
    char *title = inputString("Title: ", TITLE, false);
    strcpy(company->comments[company->numberComments].title, title);
    free(title);
    char *comment = inputString("Comment: ", COMMENT, false);
    strcpy(company->comments[company->numberComments].commentText, comment);
    free(comment);
    company->numberComments++;
}

