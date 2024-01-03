#include "Menus.h"
#include "Geral.h"
#include "user.h"
#include "Admin.h"
#include <stdio.h>
#include "string.h"
#include "Company.h"

int menushowActivity(Activities *activities, bool admin, char *txt) {
    int option;
    do{
        header("SELECT ACTIVITY");
        showActivity(activities, admin);
        printf("%s", txt);
        option = inputNumber("");
    } while (!verifyNumber(option, -1, activities->numberActivities));
    return option;
}

void menuStart(User *user, bool *quit, Companies *companies, Activities *activities) {
    int option = GetOption(MENU_START, 0, 3, false, true, "START");
    switch (option) {
        case 0:
            puts("BYE");
            *quit = true;
            break;
        case 1:
            handleUser(user, companies, activities);
            break;
        case 2:
            handleAdmin(companies, activities);
            break;
        case 3:
            handleCompany(companies, activities);
            break;
    }
}

void menuUserSearch(bool *quit, Companies *companies, User *user, Activities *activities) {
    int option = GetOption(MENU_USER_SEARCH, 0, 3, false, true, SEARCH_COMPANY);
    switch (option) {
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
            handleUserSearchByActivity(companies, activities, user);
            break;
    }
}

void menuAdmin(bool *quit, Companies *companies, Activities *activities) {
    int option1 = GetOption(MENU_ADMIN, 0, 3, false, true, ADMIN_MENU);
    switch (option1) {
        case 0:
            puts("BYE");
            *quit = true;
            break;
        case 1:
            createCompany(companies, activities);
            break;
        case 2:
            modifyCompany(companies, activities, ADMIN, MENU_MANAGE_COMPANY_ADMIN, 0, 9);
            break;
        case 3:
            handleAdminActivity(activities, companies);
            break;

    }
}
void menuComments(Company *company, Type userType, Companies *companies) {
    int optionComments;
    if (company->numberComments > 0) {
        do {
            optionComments = showComments(company, true);
        } while (!verifyNumber(optionComments, 0, company->numberComments));
    } else {
        puts("No comments!!!");
        return;
    }

    if (userType == ADMIN) {
        int option = GetOption(MENU_COMMENTS,0,2,true,false,"");
        switch (option) {
            case 0:
                puts("BYE");
                break;
            case 1:
                deleteComment(company, optionComments - 1);
                updateComments(companies);
                break;
            case 2:
                hideComments(company, optionComments - 1);
                updateComments(companies);
                break;
        }
    }
    if (userType == COMPANY) {
        hideComments(company, optionComments - 1);
        updateComments(companies);
    }
}

void menuCompanies(bool *quit, Companies *companies, Activities *activities) {
    int option = GetOption(MENU_COMPANY, 0, 1, true, false, COMPANY_MENU);
    switch (option) {
        case 0:
            puts("BYE");
            *quit = true;
            break;
        case 1:
            modifyCompany(companies, activities, COMPANY, MENU_MANAGE_COMPANY_COMPANY, 0, 8);
            break;
    }
}

void menuCompany(User *user, Company *foundCompany, bool *back, int index, Companies *companies){
    int option = GetOption(MENU_INSIDE_COMPANY,0, 3, true, false, "");
    switch (option) {
        case 1:
            comment(user, foundCompany, index);
            updateComments(companies);
            break;
        case 2:
            rating(foundCompany, index);
            break;
        case 3:
            showComments(foundCompany, false);
            break;
        case 0:
            *back = true;
            break;
    }
}

void menuSearchByCategory(Companies *companies, User *user){
    int option = GetOption(MENU_SEARCH_BY_CATEGORY,1,3,true, false, "");
    switch(option){
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
    int option = menushowActivity(activities, false, "0 Creat a new one");

    switch (option) {
        case 0:
            creatActivity(activities);
    }
    return option;
}

int menuShowActivity(Activities *activities, bool admin, char *txt) {
    return menushowActivity(activities, admin, txt);
}

void menuActionAdminActivity(Activities *activities, int index, Companies *companies){
    int option;
    Activity *activity = &(activities->activities[index]);
    do {
        header(activity->activity);
        if (activity->Active == false) {
            puts("0 Active");
        } else {
            puts("0 Inactive");
        }
        puts("-1 Delete");
        puts("-2 Leave");
        option = inputNumber("");
    } while (option != 0 && option != -1 && option != -2);
    switch (option) {
        case 0:
            if (activity->Active == false) {
                activeActivity(activity, companies, index);
            } else {
                inactiveActivity(activity, companies, index);
            }
            break;
        case -1:
            if (isCompanyExistInActivity(&activities->activities[index], companies) == 1){
                puts("You cant delete this Activity, because there are companies associated to this activity!");
            } else {
                deleteActivity(activities, index);
            }
            break;
        case -2:
            break;
    }
}

int menuModify(Companies *companies, int index, Activities *activities, Type userType, char *txt, int min, int max) {
    char newName[MAX_NAME_COMPANY];
    int optionActivity;
    int numberCompanies = companies->numberCompanies;
    Company *company = &companies->company[index];
    showCompany(company);
    int menuModify = GetOption(txt, min, max, false, true, MODIFY_MENU);
    switch (menuModify) {
        case 1:
            getNameForCompany(companies, index);
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, &companies->company[index], sizeof(Company));
            break;
        case 2:
            do {
                optionActivity = menuShowActivity(activities, true, "0 Leave");
            } while (optionActivity < 0);

            strcpy(company->activity, activities->activities[optionActivity - 1].activity);
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, &companies->company[index], sizeof(Company));
            break;
        case 3:
            getString(company->local.adress, "New address: ", MAX_ADRESS);
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, &companies->company[index], sizeof(Company));
            break;
        case 4:
            getString(company->local.city, "New city: ", MAX_CITY);
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, &companies->company[index], sizeof(Company));
            break;
        case 5:
            do {
                getString(company->local.codigoPostal, MSG_GET_CODPOSTAL, MAX_CODIGO);
                if (!verifyPostalCode(company->local.codigoPostal)) {
                    puts("Postal Code invalid!");
                }
            } while (!verifyPostalCode(company->local.codigoPostal));
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, &companies->company[index], sizeof(Company));
            break;
        case 6:
            company->category = GetOption(MENU_SEARCH_BY_CATEGORY, 1, 3, true, false, "");
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, &companies->company[index], sizeof(Company));
            break;
        case 7:
            for (int i = 0; i < activities->numberActivities; i++) {
                if (strcmp(companies->company[index].activity, activities->activities[i].activity) == 0) {
                    if (activities->activities[i].Active == true) {
                        company->active = companies->company[index].active == true ? false : true;
                        updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, &companies->company[index], sizeof(Company));
                    } else
                        puts("THE ACTIVITY IS INACTIVE!!");
                        puts("THE ACTIVITY IS INACTIVE!!");
                }
            }
            break;
        case 8:
            menuComments(company, userType, companies);
            break;
        case 9:
            deleteCompany(companies, index);
            break;
        case 0:
            printf("Leaving!.\n");
            break;
        default:
            printf("Invalid option, try again!.\n");
    }
    return menuModify;
}

