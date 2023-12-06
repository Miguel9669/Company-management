#include <stdio.h>
#include <stdlib.h>
#include "Libs/constVariables.h"
#include "Libs/Geral.h"
#include "Libs/user.h"
#include "Libs/structs.h"

int main() {
    //Companies companies = {.numberCompanies = 0};
    int menuUserSearch;
    char companySearch[MAX_NAME_COMPANY];
    bool quit = false;

    //do {
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
                        inputString(companySearch, "Diz a empresa que desejas procurar:");

                }
                break;
        }
   // } while (!quit);

}
