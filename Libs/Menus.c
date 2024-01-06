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

void menuStart(User *user, bool *quit, Companies *companies, Activities *activities, Informations *informations) {
    int option = GetOption(MENU_START, 0, 3, false, true, "START");
    switch (option) {
        case 0:
            puts("BYE");
            *quit = true;
            break;
        case 1:
            handleUser(user, companies, activities, informations);
            break;
        case 2:
            handleAdmin(companies, activities, informations);
            break;
        case 3:
            handleCompany(companies, activities, *informations);
            break;
    }
}

void menuUserSearch(bool *quit, Companies *companies, User *user, Activities *activities, Informations *informations) {
    int option = GetOption(MENU_USER_SEARCH, 0, 3, false, true, SEARCH_COMPANY);
    switch (option) {
        case 0:
            puts("BYE");
            *quit = true;
            break;
        case 1:
            handleUserSearchByName(companies, user, informations);
            break;
        case 2:
            handleUserSearchByCategory(companies, user, informations);
            break;
        case 3:
            handleUserSearchByActivity(companies, activities, user, informations);
            break;
    }
}

void menuAdmin(bool *quit, Companies *companies, Activities *activities, Informations *informations) {
    int option1 = GetOption(MENU_ADMIN, 0, 4, false, true, ADMIN_MENU);
    switch (option1) {
        case 0:
            puts("BYE");
            *quit = true;
            break;
        case 1:
            createCompany(companies, activities, informations);
            break;
        case 2:
            modifyCompany(companies, activities, ADMIN, MENU_MANAGE_COMPANY_ADMIN, 0, 9, *informations);
            break;
        case 3:
            handleAdminActivity(activities, companies);
            break;
        case 4:
            handleAdminReports(*companies, *informations);
            break;
    }
}
void menuAdminReports (bool *back, Companies companies, Informations informations, int topRate, int topSearched) {
    char ola[sizeof(MENU_ADMIN_REPORTS)];
     sprintf(ola, MENU_ADMIN_REPORTS, topSearched, topRate);
    int option = GetOption(ola, 0, 2, false, true, "REPORTS");
    switch (option) {
        case 0:
            *back = true;
            break;
        case 1:
            listMostCompanies(companies, informations, true, topSearched);
            break;
        case 2:
            listMostCompanies(companies, informations, false, topRate);
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

void menuCompanies(bool *quit, Companies *companies, Activities *activities, Informations informations) {
    int option = GetOption(MENU_COMPANY, 0, 1, true, false, COMPANY_MENU);
    switch (option) {
        case 0:
            puts("BYE");
            *quit = true;
            break;
        case 1:
            modifyCompany(companies, activities, COMPANY, MENU_MANAGE_COMPANY_COMPANY, 0, 9, informations);
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

void menuSearchByCategory(Companies *companies, User *user, Informations *informations){
    int option = GetOption(MENU_SEARCH_BY_CATEGORY,1,3,true, false, "");
    switch(option){
        case 1 :
            handleUserSelectByCategory(companies, user, 1, informations);
            break;
        case 2 :
            handleUserSelectByCategory(companies, user, 2, informations);
            break;
        case 3 :
            handleUserSelectByCategory(companies, user, 3, informations);
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

int menuModify(Companies *companies, int index, Activities *activities, Type userType, char *txt, int min, int max, Informations informations) {
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
            optionActivity = getActivityForCompany(activities, menuBranchActivity);
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
            getPostalCode(company);
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
                }
            }
            break;
        case 8:
            menuComments(company, userType, companies);
            break;
        case 9:
            if (userType == COMPANY) {
                handleMenuReports(company, informations, index);
            } else if (userType == ADMIN)
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
int menuCompanyReport(Company *company, Informations informations, int index) {
    char menu[sizeof(MENU_REPORTS_IN_COMPANY_COMPANY)];
    sprintf(menu, MENU_REPORTS_IN_COMPANY_COMPANY, company->nameCompany);
    int option = GetOption(menu, 0, 1, false, true, "REPORTS");
    switch (option) {
        case 1:
            reportForCompany(informations, index, company);
            break;
        case 0:
            return 0;
    }
    return 1;
}

