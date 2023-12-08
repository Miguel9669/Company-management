#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Libs/constVariables.h"
#include "Libs/Geral.h"
#include "Libs/user.h"
#include "Libs/structs.h"
#include "Libs/Admin.h"

int main() {
    Companies companies = {.numberCompanies = 0};
    int menuUserSearch, menuAdmin;
    char *companySearch[MAX_NAME_COMPANY];
    bool quit = false;
    int companyCategory[100];

    do {
        switch (ShowMenuAndGetOption(MENU_START, 0, 3, true)) {
            case 0:
                printf("Bye");
                quit = true;
                break;
            case 1:
                header(SEARCH_COMPANY);
                menuUserSearch = ShowMenuAndGetOption(MENU_USER_SEARCH, 0, 3, false);
                switch (menuUserSearch) {
                    case 0:
                        printf("Bye");
                        quit = true;
                        break;
                    case 1:
                        system("clear");
                        if (companies.numberCompanies > 0){
                            strcpy(*companySearch, inputString("Which company do you want to search: ", MAX_NAME_COMPANY));
                            Company *foundCompany = searchByName(&companies, *companySearch);
                            showCompany(foundCompany);
                            switch (ShowMenuAndGetOption(Menu_user_SEARCH_BY_NAME,-1, 1, true)) {
                                case 1:
                                    system("clear");
                                    header("COMMENTS");
                                    showComments(foundCompany);
                                    break;
                                case -1:
                                    system("clear");
                                    quit = true;
                                    break;
                                case 0:
                                    break;
                            }
                            break;
                        }else {
                            system("clear");
                            printf("No companies to Search.\n");
                            break;
                        }
                    case 2 :
                        system("clear");
                        switch(ShowMenuAndGetOption(MENU_SEARCH_BY_CATEGORY,1,3,true)){
                            case 1 :
                                system("clear");
                                searchByCategory(&companies, 1, &companyCategory);
                                break;
                            case 2 :
                                system("clear");
                                searchByCategory(&companies, 2, &companyCategory);
                                break;
                            case 3 :
                                system("clear");
                                searchByCategory(&companies, 3, &companyCategory);
                                break;
                        }
                }
                break;

            case 2:
                system("clear");
                header(ADMIN_MENU);
                menuAdmin = ShowMenuAndGetOption(MENU_ADMIN, 0, 3, false);
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

}
