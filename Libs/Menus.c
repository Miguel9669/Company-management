//
// Created by anton on 13/12/2023.
//

#include "Menus.h"
#include "Geral.h"
#include "user.h"
#include "Admin.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
void menuStart(User *user, bool *quit, Companies *companies, Activities *activities) {
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
            handleAdmin(companies, activities);
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

void menuAdmin(bool *quit, Companies *companies, Activities *activities) {
    int opcao = GetOption(MENU_ADMIN, 0, 5, false, true, ADMIN_MENU);
    switch (opcao) {
        case 0:
            puts("BYE");
            *quit = true;
            break;
        case 1:
            createCompany(companies, activities);
            break;
        case 2:
            modifyCompany(companies);
            break;
        case 3:
            deleteCompany(companies);
            break;
        case 4:
            handleAdminActivity(activities, companies);
            break;
        case 5:
            break;
    }
}

void menuCompany(User *user, Company *foundCompany, bool *back){
    int opcao = GetOption(MENU_INSIDE_COMPANY,0, 3, true, false, "");
    switch (opcao) {
        case 1:
            comment(user, foundCompany);
            break;
        case 2:
            rating(user, foundCompany);
            break;
        case 3:
            showComments(foundCompany);
            break;
        case 0:
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

int menuBranchActivity(Activities *activities) {
    int opcao;
    do{
        header("SELECT ACTIVITY");
        showCompaniesInActivity(activities);
        printf("0 Creat a new one");
        opcao = inputNumber("");
    } while (!verifyNumber(&opcao, 0, activities->numberActivities));

    switch (opcao) {
        case 0:
            creatActivity(activities);
            break;
    }
    return opcao;
}

int menuShowActivityAdmin(Activities *activities) {
    int opcao;
    do{
        header("SELECT ACTIVITY");
        showCompaniesInActivity(activities);
        opcao = inputNumber("");
    } while (!verifyNumber(&opcao, 0, activities->numberActivities));
    return opcao;
}

void menuActionAdminActivity(Activities *activities, int index, Companies *companies){
    int opcao;
    printf("%d", index);
    Activity *activity = &(activities->activities[index]);
    do {
        header(activities->activities[index].activity);
        if (activity->Active == false) {
            puts("0 Active");
        } else {
            puts("0 Inactive");
        }
        puts("-1 Delete");
        opcao = inputNumber("");
    } while (!verifyNumber(&opcao, -1, 0));
    switch (opcao) {
        case 0:
            if (activity->Active == false) {
                inactiveActivity(activity, companies);
            } else {
                activeActivity(activity, companies);
            }
            break;
        case -1:
            deleteActivity(activities, index - 1);
            break;
    }
}


