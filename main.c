#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Libs/constVariables.h"
#include "Libs/Geral.h"
#include "Libs/user.h"
#include "Libs/structs.h"
#include "Libs/Admin.h"
#include <unistd.h>

int main() {
    Companies companies = {.numberCompanies = 0, .company = NULL};
    companies.company = (Company *) malloc(companies.numberCompanies * sizeof(Company));
    int menuUserSearch, menuAdmin;
    bool quit = false;
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
                system("clear");
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
                        showCompany(foundCompany);
                        if (foundCompany != NULL) {
                            switch (ShowMenuAndGetOption(Menu_user_SEARCH_BY_NAME,-1, 1, true, false, "")) {
                                case 1:
                                    break;
                                case 2:
                                    break;
                                case 3:
                                    system("clear");
                                    showComments(foundCompany);
                                    break;
                                case -1:
                                    system("clear");
                                    quit = true;
                                    break;
                                case 0:
                                    system("clear");
                                    break;
                            }
                        }
                        break;
                    case 2 :
                        system("clear");
                        switch(ShowMenuAndGetOption(MENU_SEARCH_BY_CATEGORY,1,3,true, false, "")){
                            case 1 :
                                system("clear");
                                searchByCategory(&companies, 1);
                                char *companySearch = NULL;
                                cleanBuffer();
                                companySearch = inputString("Which company do you want to search: ", MAX_NAME_COMPANY, false);
                                Company *foundCompany = searchByName(&companies, companySearch);
                                free(companySearch);
                                if (foundCompany == NULL) {
                                    puts("Error: Please search for a company that exists");
                                    sleep(4);

                                } else if (foundCompany->category != 1){
                                    puts("Error: Please search for a company that's in this category");
                                    sleep(4);
                                } else {
                                    showCompany(foundCompany);
                                }
                                break;
                            case 2 :
                                system("clear");
                                searchByCategory(&companies, 2);
                                break;
                            case 3 :
                                system("clear");
                                searchByCategory(&companies, 3);
                                break;
                        }
                }
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
