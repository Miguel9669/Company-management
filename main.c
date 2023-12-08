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
    char companySearch[MAX_NAME_COMPANY];
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
                        strcpy(companySearch, inputString("Which company do you want to sheach: ", MAX_NAME_COMPANY));
                        Company *foundCompany = searchByName(&companies, companySearch);
                        showCompany(foundCompany);
                        switch (ShowMenuAndGetOption(Menu_user_SEARCH_BY_NAME,-1, 1, true)) {
                            case 0:
                                showComments(foundCompany);
                                break;
                            case -1:
                                quit = true;
                                break;
                            case 1:
                                break;
                        }
                        break;
                    case 2 :
                        system("clear");
                        switch(ShowMenuAndGetOption(MENU_SEARCH_BY_CATEGORY,1,3,true)){
                            case 1 :
                                searchByCategory(&companies, 1, &companyCategory);
                            case 2 :
                                searchByCategory(&companies, 2, &companyCategory);
                            case 3 :
                                searchByCategory(&companies, 3, &companyCategory);
                        }
                }
                break;

            case 2:
                header(ADMIN_MENU);
                menuAdmin = ShowMenuAndGetOption(MENU_ADMIN, 0, 3, false);
                switch (menuAdmin) {
                    case 0:
                        printf("Bye");
                        quit = true;
                        break;
                    case 1:
                        createCompany(&companies);
                        break;
                    case 2:
                        modifyCompany(&companies);
                        break;
                    case 3:
                        deleteCompany(&companies);
                        break;
                    case 4:
                        break;
                    case 5:
                        break;
                }
                break;
        }
    } while (!quit);

}
