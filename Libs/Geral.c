#include "Geral.h"
#include "structs.h"
#include "constVariables.h"
#include "Admin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

static char *categoryString(Company company) {
    static char *string[] = {"Micro Empresa", "Pequena e média empresa", "Grande empresa"};
    return string[company.category - 1];
}
int getNumberFromFile(char *txt) {
    int var = 0;
    FILE *numberCompanies = fopen(txt, "rb");
    if (numberCompanies == NULL) {
        numberCompanies = fopen(txt, "wb");
        fwrite(&var, sizeof(int), 1, numberCompanies);
        fclose(numberCompanies);
        numberCompanies = fopen(txt, "rb+");
    }
    fread(&var, sizeof(int), 1, numberCompanies);
    fclose(numberCompanies);
    return var;
}
void updateNumberFromFile(int number, char *txt) {
    FILE *var = fopen(txt, "rb+");
    if (var == NULL) {
        puts("We couldn't find that file!!");
    }
    fseek(var, 0, SEEK_SET);
    fwrite(&number, sizeof(int), 1, var);
    fclose(var);
}

void updateStructCompany(char *txt, long position, Company *company, int structSize) {
    FILE *var = fopen(txt, "rb+");
    if (var != NULL) {
        fseek(var, position, SEEK_SET);
        fwrite(company, structSize, 1, var);
        fclose(var);
    }
}
void updateStructInformation(char *txt, Informations *informations) {
    FILE *var = fopen(txt, "wb");
    if (var == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    if (fwrite(informations->information, sizeof(Information), informations->numberInformation, var) != informations->numberInformation) {
        perror("Erro ao escrever no arquivo");
    }
    fclose(var);
}

void updateComments(Companies *companies) {
    FILE *comments = fopen(FILE_FOR_COMMENTS, "wb");
    for (int i = 0; i < companies->numberCompanies; ++i) {
        fwrite(companies->company[i].comments, sizeof(Comment), companies->company[i].numberComments, comments);
    }
    fclose(comments);
}
void loadComments(Companies *companies) {
    FILE *comments = fopen(FILE_FOR_COMMENTS, "rb");
    if (comments == NULL) {
        comments = fopen(FILE_FOR_COMMENTS, "wb");
        fclose(comments);
        comments = fopen(FILE_FOR_COMMENTS, "rb");
    }
    int numberComments = 0;
    for (int i = 0; i < companies->numberCompanies; ++i) {
        companies->company[i].comments = (Comment *) malloc(sizeof(Comment) * companies->company[i].maxComments);
        fseek(comments, sizeof(Comment) * numberComments, SEEK_SET);
        fread(companies->company[i].comments, sizeof(Comment), companies->company[i].numberComments, comments);
        numberComments += companies->company[i].numberComments;
    }
    fclose(comments);
}
void updateStructActivities(char *txt, long position, Activity *activity, int structSize) {
    FILE *var = fopen(txt, "rb+");
    if (var != NULL) {
        fseek(var, position, SEEK_SET);
        fwrite(activity, structSize, 1, var);
    }
    fclose(var);
}
void loadStructCompany(int number, char *txt, Company *company, int structSize) {
    FILE *var = fopen(txt, "rb+");
    if (var == NULL) {
        var = fopen(txt, "wb");
        if (var == NULL) {
            return;
        }
        fclose(var);
        var = fopen(txt, "rb+");
    }

    if (var != NULL) {
        fread(company, structSize, number, var);
    }
    fclose(var);
}
void loadStructInformation(int number, char *txt, Information *information, int structSize) {
    FILE *var = fopen(txt, "rb");
    if (var == NULL) {
        var = fopen(txt, "wb");
        fclose(var);
        return;
    }
    fread(information, structSize, number, var);
    fclose(var);
}
char* userCommentedTheMost(Company company, int *numberComments) {
    Name name[company.numberComments];
    int nameCounter[company.numberComments];

    for (int i = 0; i < company.numberComments; ++i) {
        strcpy(name[i].name, company.comments[i].user.name);
        nameCounter[i] = 0;
    }

    for (int i = 0; i < company.numberComments - 1; ++i) {
        nameCounter[i]++;
        for (int j = i + 1; j < company.numberComments; ++j) {
            if (strcmp(name[i].name, name[j].name) == 0) {
                nameCounter[i]++;
                strcpy(name[j].name, "");
            }
        }
    }

    int maxComments = 0;
    char finalName[MAX_NAME];

    for (int i = 0; i < company.numberComments; ++i) {
        if (nameCounter[i] > maxComments) {
            maxComments = nameCounter[i];
            strcpy(finalName, name[i].name);
        }
    }
    *numberComments = maxComments;
    return strdup(finalName);
}
void reportForCompany(Informations informations, int index, Company *company) {
    int searchCounter = informations.information[index].searchCounter;
    int numberCommentsUser;
    char name[MAX_NAME];
    strcpy(name, userCommentedTheMost(*company, &numberCommentsUser));
    char headerTxt[25];
    sprintf(headerTxt,"Report Company: %s!\n", company->nameCompany);
    header(headerTxt);
    printf("Company visits: %d!\n", searchCounter);
    printf("Rating/Visit percentage: %d%%!\n", (int)((companyAverageRating(company)/searchCounter) * 100));
    printf("Comment/Visit percentage: %d%%!\n", (int)(((double)company->numberComments/searchCounter) * 100));
    if (company->numberComments > 0)
        printf("The user |%s| was the one who commented the most with %d comments!", name, numberCommentsUser);
}


void mostSearchedCompanies(Companies companies, int size, Informations informations, int *array) {
    int actualHighNumbers = 0;
    
    for (int i = 0; i < size; i++) {
        array[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        actualHighNumbers = 0;
        for (int j = 0; j < companies.numberCompanies; j++) {
            int searchCounter = informations.information[j].searchCounter;


            int included = 0;
            for (int h = 0; h < i; h++) {
                if (j == array[h]) {
                    included = 1;
                    break;
                }
            }

            if (!included && searchCounter > actualHighNumbers) {
                actualHighNumbers = searchCounter;
                array[i] = j;
            }
        }
    }
}


void mostRatedCompanies(Companies companies, int size, int *array) {
    double actualHighNumbers;
    int counter;
    for(int i = 0; i < size; i++){
        actualHighNumbers = -1;
        for(int j = 0; j < companies.numberCompanies; j++){
            Company company = companies.company[j];
            double companyRate = companyAverageRating(&company);
            if(companyRate > actualHighNumbers){
                counter = 0;
                for(int h = 0; h < size; h++){
                    if(j == array[h]){
                        counter = 1;
                    }
                }
                if(counter == 0){
                    actualHighNumbers = companyRate;
                    array[i] = j;
                }

            }
        }
    }
}
void addToInformation(Informations *informations, int index, int *valueToAdd) {
    informations->information[index].searchCounter++;
    *valueToAdd += 1;
    printf("%d", informations->information[index].searchCounter);
    printf("%d", informations->information[index].searchByActivityCounter);
    printf("%d", informations->information[index].searchByCategoryCounter);
    printf("%d", informations->information[index].searchByNameCounter);
    updateStructInformation(FILE_WITH_EXTRA_INFORMATION, informations);
}
void listMostCompanies(Companies companies, Informations informations, bool searched, int sizeOfTop){

    if (companies.numberCompanies > 0) {
        int size = companies.numberCompanies >= sizeOfTop ? sizeOfTop : companies.numberCompanies;
        int array[size];
        if (searched) {
            mostSearchedCompanies(companies, size, informations, array);
            char top[sizeof("Top %d Most searched")];
            sprintf(top, "Top %d Most searched", sizeOfTop);
            header(top);
        } else {
            mostRatedCompanies(companies, size, array);
            char top[sizeof("Top %d with the best Rates")];
            sprintf(top, "Top %d with the best Rates", sizeOfTop);
            header(top);
        }
        for (int i = 0; i < size; i++) {
            printf("The %d company is : |%s| ", i + 1, companies.company[array[i]].nameCompany);
            if (searched) {
                printf("with %d\n", informations.information[array[i]].searchCounter);
            } else {
                printf("with %.2lf\n", companyAverageRating(&companies.company[array[i]]));
            }

        }
        if (sizeOfTop > companies.numberCompanies) {
            puts("There is no more companies!");
        }
    } else
        puts("No Companies!!");
}
void loadStructActivity(int number, char *txt, Activity *activity, int structSize) {
    FILE *var = fopen(txt, "rb+");
    if (var == NULL) {
        var = fopen(txt, "wb");
        if (var == NULL) {
            return;
        }
        fclose(var);
        var = fopen(txt, "rb+");
    }

    if (var != NULL) {
        fread(activity, structSize, number, var);
    }
    fclose(var);
}
int showComments(Company *company, bool admin) {
    int count = 1;
    header("COMMENTS");
    for (int i = 0; i < company->numberComments; ++i) {
        if (company->comments[i].commentHide == false && !admin && strcmp(company->comments[i].user.name, "") != 0) {
            printf("Comment Number: %d, Title: %s\n",
                   count,
                   company->comments[i].title);
            count++;
        } else if(admin) {
            printf("Comment Number: %d, Title: %s, Hide: %s\n",
                   count,
                   company->comments[i].title,
                   company->comments[i].commentHide == false ? "False" : "True");
            count++;
        }
    }
    if (count == 1) {
        puts("No Comments!");
        return 0;
    } else {
        int commentSelected = GetOption("", 1, company->numberComments, false, false, "");
        int opcao;
        do {
            header(company->comments[commentSelected - 1].title);
            printf("User: %s\nContent: %s\n----------------------------------------------------------------\n",
                   company->comments[commentSelected - 1].user.name,
                   company->comments[commentSelected - 1].commentText);
            if (!admin) {
                puts("\n0 Leave");
                opcao = inputNumber("");
            }
            if (admin)
                opcao = 0;
        } while (opcao != 0);
        return commentSelected;
    }
}

char *boolString(bool variable){
    switch (variable) {
        case 0:
            return "false";
        case 1:
            return "true";
    }
}

void showCompany(Company *company){
    header(company -> nameCompany);
    printf("Company Information:\n");
    printf("Name: %s\n", company->nameCompany);
    printf("NIF: %d\n", company->nif);
    printf("Activity: %s\n", company->activity);
    printf("Address: %s\n", company->local.adress);
    printf("City: %s\n", company->local.city);
    printf("Postal Code: %s\n", company->local.codigoPostal);
    printf("Category: %s\n", categoryString(*company));
    printf("Active: %s\n", boolString(company->active));
    printf("Rating average: %.2lf\n", companyAverageRating(company));
}
void getNameForCompany(Companies *companies, int index) {
    char newName[MAX_NAME_COMPANY];
    getString(newName, MSG_GET_NAME, MAX_NAME_COMPANY);
    if (isCompanyExists(companies, newName, 0, companies->numberCompanies)) {
        do {
            puts("There is a company with that name!!");
            getString(newName, MSG_GET_NAME, MAX_NAME_COMPANY);
        } while (isCompanyExists(companies, newName, 0, companies->numberCompanies));
    }
    strcpy(companies->company[index].nameCompany, newName);
}
void getNifForCompany(Company *company, Companies *companies, int numberCompanies) {
    do {
        company->nif = inputNumber(MSG_GET_NIF);

        if (verifyNif(company->nif) == -1 || isCompanyExists(companies, "", company->nif, numberCompanies) == 1) {
            puts(verifyNif(company->nif) == -1 ? ERROR_NIF : EXISTENT_NIF);
        }
    } while (verifyNif(company->nif) == -1 || isCompanyExists(companies, "", company->nif, numberCompanies) == 1);

}
int getActivityForCompany(Activities *activities, int (*function)(Activities *activities1)) {
    int optionActivity;
    do {
        optionActivity = function(activities);
    } while (optionActivity <= 0);
}
void getPostalCode(Company *company) {
    do {
        getString(company->local.codigoPostal, MSG_GET_CODPOSTAL, MAX_CODIGO);
        if (!verifyPostalCode(company->local.codigoPostal)) {
            puts("Postal Code invalid!");
        }
    } while (!verifyPostalCode(company->local.codigoPostal));
}
void reallocInStruct(int number, int max, Companies *companies, Activities *activities, Informations *informations,typeStruct structType){
    if (structType == COMPANIES) {
        if (max == number) {
            Company *pCompany = (Company *) realloc(companies->company,
                                                    (companies->maxCompanies) * 2 * sizeof(Company));
            if (pCompany != NULL) {
                companies->company = pCompany;
                companies->maxCompanies *= 2;
            } else {
                puts("Error: REALLOC FAIL.");
            }
        }
    } else if (structType == ACTIVITIES) {
        if (max == number) {
            Activity *pActivities = (Activity *) realloc(activities->activities,activities->maxActivities * 2 * sizeof(Activity));
            if(pActivities == NULL){
                puts("Error: Realloc Activity failed!!");
            } else {
                activities->activities = pActivities;
                activities->maxActivities *= 2;
            }
        }
    } else if (structType == INFORMATIONS) {
        if (max == number) {
            Information *pInformation = (Information *) realloc(informations->information, informations->maxInformation * 2 *
                    sizeof(Information));
            if (pInformation == NULL) {
                puts("Error: Realloc Information failed!!");
            } else {
                informations->information = pInformation;
                informations->maxInformation *= 2;
            }
        }
    }
}
int inputNumber(char *txt) {
    int variable;
    printf("%s\n", txt);
    while (scanf(" %d", &variable) != 1) {
        puts("ERROR: Only numbers.");
        cleanBuffer();
        return -1;
    }
    cleanBuffer();
    return variable;
}

void cleanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char *inputString(char *txt, int quant) {
    char *var = (char *)malloc(quant + 1);
    size_t len;
    if (var == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        sleep(4);
        exit(EXIT_FAILURE);
    }

    do {

        printf("%s", txt);
        if (fgets(var, quant + 1, stdin) != NULL) {
            len = strlen(var);
            if (len > 1 && var[len - 1] == '\n') {
                var[len - 1] = '\0';
            } else {
                cleanBuffer();
            }
        }
        if (len > quant) {
            puts(INVALID_INPUT);
        }


    } while (len == 0 || len == 1 || len > quant);
    
    return var;
}
void companyChangeActiveStatus(Activities *activities, Companies *companies, Company *company, int index) {
    for (int i = 0; i < activities->numberActivities; i++) {
        if (strcmp(companies->company[index].activity, activities->activities[i].activity) == 0) {
            if (activities->activities[i].Active == true) {
                company->active = companies->company[index].active == true ? false : true;
            } else
                puts("THE ACTIVITY IS INACTIVE!!");
        }
    }
}
void activitiesChangeActiveStatus(Activity *activity, Companies *companies, int index) {
    if (activity->Active == false) {
        activeActivity(activity, companies, index);
    } else {
        inactiveActivity(activity, companies, index);
    }
}
void verifyNumberComments(Company *company) {
    if (company->comments == NULL) {
        fprintf(stderr, "Error allocating comments\n");
        exit(EXIT_FAILURE);
    }
}
void createNameActivity(Activities *activities) {
    getString(activities->activities[activities->numberActivities].activity, "Name of the Activity: ", ACTIVITY);
    if (isActivityExist(activities, activities->activities[activities->numberActivities].activity)) {
        do {
            puts("There is an Activity with that name!!");
            getString(activities->activities[activities->numberActivities].activity, "Name of the Activity: ", ACTIVITY);
        } while (isActivityExist(activities, activities->activities[activities->numberActivities].activity));
    }
}
int verifyNumber(int variable, int min, int max){

    if ((variable < min) || (variable > max)){
        return 0;
    } else {
        return 1;
    }
}

int verifyNif(int nif) {
    int count = 0;
    while (nif > 0) {
        nif /= 10;
        count++;
    }

    if (count == 9) {
        return nif;
    } else {
        return -1;
    }
}
int verifyPostalCode(char *postalCode) {
    if (strlen(postalCode) == 8 && isdigit(postalCode[0]) && isdigit(postalCode[1]) && isdigit(postalCode[2]) && isdigit(postalCode[3])) {
        if (postalCode[4] == '-' && isdigit(postalCode[5]) && isdigit(postalCode[6]) && isdigit(postalCode[7])) {
            return 1;
        }
    }
    return 0;
}
int showCompaniesInActivity(Activities *activities, Companies *companies, int index) {
    int count = 0;
    if (isCompanyExistInActivity(&(activities->activities[index]), companies)) {
        for (int i = 0; i < companies->numberCompanies; i++) {
            if (strcmp(activities->activities[index].activity, companies->company[i].activity) == 0 && companies->company[i].active) {
                printf("%d ", count + 1);
                printf("%s\n", companies->company[i].nameCompany);
                count++;
            }
        }
    }
    return count;
}
void showActivity(Activities *activities, bool admin){
    int count = 1;
    if (activities->numberActivities > 0){
        for (int i = 0; i < activities->numberActivities; i++) {
            if (activities->activities[i].Active) {
                printf("%d", count);
                printf(" %s", activities->activities[i].activity);
                printf("\n");
                count++;
            } else {
                if (admin) {
                    count++;
                    printf("%d", i + 1);
                    printf(" %s", activities->activities[i].activity);
                    printf("\n");
                }
            }
        }
        if (count == 0) {
            puts("There is no activity to select!!");
        }
    } else {
        puts("There is no activity to select!!");
    }

}

int GetOption(char *txt, int min, int max, bool showOption, bool showHeader, char *txtHeader) {
    int number;
    do {
        if (showHeader){
            header(txtHeader);
        }
        if(showOption){
            puts("\n------------------------------------------------------------------");
        }
        puts(txt);
        number = inputNumber("");
        if (!verifyNumber(number, min, max)) {
            puts("Invalid option!");
        }
    } while (!verifyNumber(number, min, max));
    return number;
}

int isCompanyExists(const Companies *companies, char *name, int nif, int numberCompanies) {
    for (int i = 0; i < numberCompanies; ++i) {
        if (strcmp(name, "") != 0) {
            if (strcmp(companies->company[i].nameCompany, name) == 0) {
                return 1;
            }
        }
        if (nif != 0) {
            if (companies->company[i].nif == nif) {
                return 1;
            }
        }
    }
    return 0;
}

int isActivityExist(Activities *activities, char *name) {
    for (int i = 0; i < activities->numberActivities; ++i) {
        if (strcmp(activities->activities[i].activity, name) == 0) {
            return 1;
        }
    }
    return 0;
}

int findCompanyIndexByNif(const Companies *companies, int nif) {
    for (int i = 0; i < companies->numberCompanies; ++i) {
        if (companies->company[i].nif == nif) {
            return i;
        }
    }
    return -1;
}

int numberCompaniesInCategory(Companies *companies, int valueCategory) {
    int count = 0;
    for (int i = 0; i < companies -> numberCompanies; i++){
        if (companies->company[i].category == valueCategory && companies->company[i].active == true){
            count++;
        }
    }
    return count;
}
int isCompanyExistInActivity(Activity *activity, const Companies *companies) {
    for (int i = 0; i < companies->numberCompanies; ++i) {
        if (strcmp(companies->company[i].activity, activity->activity) == 0) {
            return 1;
        }
    }
    return 0;
}
void getString(char *dest, char *txt, int charLen){
    char *variable = inputString(txt, charLen);
    strcpy(dest, variable);
    free(variable);
}

void header(char *txt) {
    puts("\n------------------------------------------------------------------------------------------");
    printf("                      %s\n", txt);
    puts("------------------------------------------------------------------------------------------");
}

double companyAverageRating(Company *company) {
    if ((double)company->sumRates/company->numberRates > 0)
        return (double)company->sumRates/company->numberRates;
    else
        return 0;
}

