//
// Created by anton on 13/12/2023.
//

#include "Menus.h"
#include "Geral.h"
#include "user.h"
#include "Admin.h"
#include <stdlib.h>
#include <stdio.h>
void menuStart(User *user, bool *quit, Companies *companies) {
    int opcao = GetOption(MENU_START, 0, 3, false, true, "START");
    switch (opcao) {
        case 0:
            puts("BYE");
            *quit = true;
            break;
        case 1:
            handleUser(user, quit, companies);
            break;
        case 2:
            handleAdmin(companies);
            break;
        case 3:
            break;
    }
}

void menuUserSearch(bool *quit, Companies *companies, User *user) {
    int opcao = GetOption(MENU_USER_SEARCH, 0, 3, false, true, SEARCH_COMPANY);
    switch (opcao) {
        case 0:
            puts("BYE");
            *quit = true;
            break;
        case 1:
            handleUserSearchByName(companies, user);
            break;
        case 2:
            handleUserSearchByCategory(companies, user);
            break;
        case 3:
            break;
    }
}

void menuAdmin(bool *quit, Companies *companies) {
    int opcao = GetOption(MENU_ADMIN, 0, 5, false, true, ADMIN_MENU);
    switch (opcao) {
        case 0:
            puts("BYE");
            *quit = true;
            break;
        case 1:
            createCompany(companies);
            break;
        case 2:
            modifyCompany(companies);
            break;
        case 3:
            deleteCompany(companies);
            break;
        case 4:
            break;
        case 5:
            break;
    }
}

void menuCompany(User *user, Company *foundCompany, bool *back){
    int opcao = GetOption(MENU_INSIDE_COMPANY,0, 3, true, false, "");
    switch (opcao) {
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

void menuSearchByCategory(Companies *companies, User *user){
    int opcao = GetOption(MENU_SEARCH_BY_CATEGORY,1,3,true, false, "");
    switch(opcao){
        case 1 :
            handleUserSelectByCategory(companies, user, 1);
            break;
        case 2 :
            handleUserSelectByCategory(companies, user, 2);
            break;
        case 3 :
            handleUserSelectByCategory(companies, user, 3);
            break;
    }
}


