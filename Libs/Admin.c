#include "Admin.h"
#include <stdio.h>
#include "structs.h"
#include <string.h>
#include "Geral.h"
#include <stdlib.h>
#include "constVariables.h"
#include <unistd.h>
#include "Menus.h"

void handleAdmin(Companies *companies, Activities *activities){
    bool back;
    do {
        back = false;
        menuAdmin(&back, companies, activities);
    } while (back != true);
}

void createCompany(Companies *companies, Activities *activities) {
    int numberCompanies = companies->numberCompanies;
    Company *company = &(companies->company[numberCompanies]);
    companies->numberCompanies++;
    reallocInStruct(companies->numberCompanies, companies->maxCompanies, companies, NULL, COMPANIES);
    getNameForCompany(companies, numberCompanies);
    getNifForCompany(company, companies, numberCompanies);
    int optionActivity = getActivityForCompany(activities, menuBranchActivity);
    strcpy(company->activity, activities->activities[optionActivity - 1].activity);
    getString(company->local.adress, MSG_GET_ADRESS, MAX_ADRESS);
    getString(company->local.city, MSG_GET_CITY, MAX_CITY);
    getPostalCode(company);
    company->category = GetOption(MENU_SEARCH_BY_CATEGORY, 1, 3, true, false, "");
    iniciateCommentsAndRates(company);
    company->active = true;
    updateNumberFromFile(companies->numberCompanies, FILE_NUMBER_COMPANIES_NAME);
    updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * (companies->numberCompanies - 1), &companies->company[numberCompanies], sizeof(Company));
}

void iniciateCommentsAndRates(Company *company) {
    company->numberComments = company->numberRates = 0;
    company->maxComments = 5;
    company->comments = (Comment *)malloc(company->maxComments * sizeof(Comment));

    if (company->comments == NULL) {
        fprintf(stderr, "Erro ao alocar memória para comentários ou avaliações\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < company->maxComments; ++i) {
        company->comments[i].commentHide = false;
    }
}

void deleteCompany(Companies *companies, int index) {
    if (companies->company[index].numberComments > 0) {
        puts("You can not delete this company! But u can set as an inactive company.");
        return;
    }
    for (int i = index; i < companies->numberCompanies; ++i) {
        if (i != companies->numberCompanies)
            companies->company[i] = companies->company[i + 1];
    }
    Company *company = &companies->company[companies->numberCompanies];
    company->nif = 0;
    strcpy(company->nameCompany, "");
    strcpy(company->activity,"");
    strcpy(company->local.adress, "");
    strcpy(company->local.city, "");
    strcpy(company->local.codigoPostal, "");
    company->active = false;
    printf("Company deleted successfully.\n");
    updateStructCompany(FILE_WITH_COMPANIES, 0, companies->company, sizeof(Company) * companies->numberCompanies);
    memset(&companies->company[companies->numberCompanies - 1], 0, sizeof(Company));
    companies->numberCompanies--;
    updateNumberFromFile(companies->numberCompanies, FILE_NUMBER_COMPANIES_NAME);
}

void creatActivity(Activities *activities){
    reallocInStruct(activities->numberActivities, activities->maxActivities, NULL, activities, ACTIVITIES);
    getString(activities->activities[activities->numberActivities].activity, "Name of the Activity: ", ACTIVITY);
    if (isActivityExist(activities, activities->activities[activities->numberActivities].activity)) {
        puts("There is an Activity with that name!!");
        do {
            getString(activities->activities[activities->numberActivities].activity, "Name of the Activity: ", ACTIVITY);
        } while (isActivityExist(activities, activities->activities[activities->numberActivities].activity));
    }
    activities->activities[activities->numberActivities].Active = true;
    activities->numberActivities++;
    updateNumberFromFile(activities->numberActivities, FILE_NUMBER_ACTIVITIES_NAME);
    updateStructActivities(FILE_WITH_ACTIVITIES, sizeof(Activity) * (activities->numberActivities - 1), &activities->activities[activities->numberActivities - 1], sizeof(Activity));
}

void inactiveActivity(Activity *activity, Companies *companies, int index) {
    activity->Active = false;
    updateStructActivities(FILE_WITH_ACTIVITIES, sizeof(Activity) * index, activity, sizeof(Activity));
    for (int i = 0; i < companies->numberCompanies; i++) {
        if (strcmp(companies->company[i].activity, activity->activity) == 0) {
            companies->company[i].active = false;
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * i, &companies->company[i], sizeof(Company));
        }
    }
}

void activeActivity(Activity *activity, Companies *companies, int index) {
    activity->Active = true;
    updateStructActivities(FILE_WITH_ACTIVITIES, sizeof(Activity) * index, activity, sizeof(Activity));
    for (int i = 0; i < companies->numberCompanies; i++) {
        if (strcmp(companies->company[i].activity, activity->activity) == 0) {
            companies->company[i].active = true;
            updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * i, &companies->company[i], sizeof(Company));
        }
    }
}

void handleAdminActivity(Activities *activities, Companies *companies) {
    int optionActivity;
    bool back;
    do {
        back = false;
        optionActivity = menuShowActivity(activities, true, "0 Create Activity\n-1 Sair");
        if (optionActivity != -1 && optionActivity != 0)
            menuActionAdminActivity(activities, optionActivity - 1, companies);

        if (optionActivity == 0) {
            creatActivity(activities);
        }
    } while (optionActivity != -1);
}

void deleteActivity(Activities *activities, int index) {
    for (int i = index; i < activities->numberActivities - 1; i++) {
        activities->activities[i] = activities->activities[i + 1];
        updateStructActivities(FILE_WITH_ACTIVITIES, sizeof(Activity) * index, &activities->activities[index], sizeof(Activity));
    }
    activities->numberActivities--;
    updateNumberFromFile(activities->numberActivities, FILE_NUMBER_ACTIVITIES_NAME);
}

void modifyCompany(Companies *companies, Activities *activities, Type userType, char *txt, int min, int max) {
    int nif, index, opcao;

    if (companies->numberCompanies > 0) {
        nif = inputNumber(OPERATING_NIF_COMPANY);
        index = findCompanyIndexByNif(companies, nif);
        if (index == -1) {
            printf("Company not found: %d\n", nif);
            return;
        }

        do {
            opcao = menuModify(companies, index, activities, userType, txt, min, max);
        } while (opcao != 0 && opcao != 9);
    } else {
        printf("No companies to modify.\n");
    }
}

void deleteComment(Company *company, int index) {
    for (int i = index; i < company->numberComments - 1; i++) {
        company->comments[i] = company->comments[i + 1];
    }
    company->numberComments--;
    updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * (index + 1), company, sizeof(Company));
}

void hideComments(Company *company, int index) {
    for (int i = 0; i < company->numberComments; i++) {
        if (i == index) {
            if (company->comments[i].commentHide == false) {
                company->comments[i].commentHide = true;
                updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, company, sizeof(Company));
            }
            else{
                company->comments[i].commentHide = false;
                updateStructCompany(FILE_WITH_COMPANIES, sizeof(Company) * index, company, sizeof(Company));
            }
        }
    }
}







