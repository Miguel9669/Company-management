#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Libs/constVariables.h"
#include "Libs/Geral.h"
#include "Libs/user.h"
#include "Libs/structs.h"
#include "Libs/Admin.h"
#include <unistd.h>
void insideCompany(User *user, Company *foundCompany, bool *back){

    *back = false;
    switch (ShowMenuAndGetOption(MENU_INSIDE_COMPANY,0, 3, true, false, "")) {
        case 1:
            comentar(user, foundCompany);
            break;
        case 2:
            break;
        case 3:
            system("clear");
            showComments(foundCompany);
            break;
        case 0:
            system("clear");
            *back = true;
            break;
    }
}
int main() {
    Companies companies = {.numberCompanies = 0, .maxCompanies = 10,
                           .company = (Company *) malloc(companies.maxCompanies * sizeof(Company))};
    User user;
    char *name = NULL, *email = NULL;
    int menuUserSearch, menuAdmin;
    bool quit = false, back = false;
    int companyCategory;

    do {
        system("clear");
        switch (ShowMenuAndGetOption(MENU_START, 0, 3, false, true, "START")) {
            case 0:
                system("clear");
                printf("Bye");
                quit = true;
                break;
            case 1:
                name = inputString("Your name: ", MAX_NAME, true);
                strcpy(user.name, name);
                free(name);
                email = inputString("Your email: ", MAX_EMAIL, true);
                strcpy(user.email, email);
                free(email);
                system("clear");
                do{
                    menuUserSearch = ShowMenuAndGetOption(MENU_USER_SEARCH, 0, 3, false, true, SEARCH_COMPANY);
                    switch (menuUserSearch) {
                        case 0:
                            system("clear");
                            printf("Bye");
                            quit = true;
                            break;
                        case 1:
                            system("clear");
                            char *companySearch = NULL;
                            companySearch = inputString("Which company do you want to search: ", MAX_NAME_COMPANY, false);
                            Company *foundCompany = searchByName(&companies, companySearch);
                            free(companySearch);
                            if (foundCompany != NULL) {
                                do{
                                    showCompany(foundCompany);
                                    insideCompany(&user, foundCompany, &back);
                                } while (back != true);
                            }
                            break;
                        case 2 :
                            system("clear");
                            switch(ShowMenuAndGetOption(MENU_SEARCH_BY_CATEGORY,1,3,true, false, "")){
                                case 1 :
                                    do{
                                        system("clear");
                                        searchByCategory(&companies, 1);
                                        companySearch = inputString("Which company do you want to search: ", MAX_NAME_COMPANY, false);
                                        foundCompany = searchByName(&companies, companySearch);
                                        free(companySearch);
                                        if (foundCompany->category != 1 || foundCompany == NULL){
                                            puts("Error: Please search for a company that's in this category");
                                            sleep(4);
                                        } else {
                                            do{
                                                showCompany(foundCompany);
                                                insideCompany(&user, foundCompany, &back);
                                            } while (back != true);
                                        }
                                    } while (foundCompany == NULL && foundCompany->category != 3 && back != true);
                                    break;
                                case 2 :
                                    do{
                                        system("clear");
                                        searchByCategory(&companies, 2);
                                        companySearch = inputString("Which company do you want to search: ", MAX_NAME_COMPANY, false);
                                        foundCompany = searchByName(&companies, companySearch);
                                        free(companySearch);
                                       if (foundCompany->category != 2 || foundCompany == NULL){
                                            puts("Error: Please search for a company that's in this category");
                                            sleep(4);
                                        } else {
                                           do{
                                               showCompany(foundCompany);
                                               insideCompany(&user, foundCompany, &back);
                                           } while (back != true);
                                       }
                                    } while (foundCompany == NULL && foundCompany->category != 3 && back != true);
                                    break;
                                case 3 :
                                    do{
                                        system("clear");
                                        searchByCategory(&companies, 3);
                                        companySearch = inputString("Which company do you want to search: ", MAX_NAME_COMPANY, false);
                                        foundCompany = searchByName(&companies, companySearch);
                                        free(companySearch);
                                        if (foundCompany->category != 3 || foundCompany == NULL){
                                            puts("Error: Please search for a company that's in this category");
                                            sleep(4);
                                        } else {
                                            do{
                                                showCompany(foundCompany);
                                                insideCompany(&user, foundCompany, &back);
                                            } while (back != true);
                                        }
                                    } while (foundCompany == NULL && foundCompany->category != 3 && back != true);
                                    break;
                            }
                    }
                } while (quit != true);
                break;
            case 2:
                system("clear");
                menuAdmin = ShowMenuAndGetOption(MENU_ADMIN, 0, 3, false, true, ADMIN_MENU);
                switch (menuAdmin) {
                    case 0:
                        system("clear");
                        printf("Bye");
                        quit = true;
                        break;
                    case 1:
                        system("clear");
                        createCompany(&companies);
                        break;
                    case 2:
                        system("clear");
                        modifyCompany(&companies);
                        break;
                    case 3:
                        system("clear");
                        deleteCompany(&companies);
                        break;
                    case 4:
                        system("clear");
                        break;
                    case 5:
                        system("clear");
                        break;
                }
                break;
        }
    } while (!quit);
    free(companies.company);

}
