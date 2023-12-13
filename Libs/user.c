//
// Created by anton on 06/12/2023.
//

#include "user.h"
#include "constVariables.h"
#include "structs.h"
#include "Admin.h"
#include "Geral.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int lenCharArray(char *array){
    int count = 0;
    do{
        count++;
    } while (array[count] != '\n');
}
void runArrayAndChangeString(char *variable, char *array){
    int len = lenCharArray(array);
    for(int i = 0; i < len; i++){
        variable[i] = array[i];
    }
}

Company *searchByName(Companies *companies, char *txt){
    for (int i = 0; i < companies -> numberCompanies; i++){
        if (strcmp(companies->company[i].nameCompany, txt) == 0){
            return &(companies -> company[i]);
        }

    }
    return NULL;
}

void searchByCategory(Companies *companies, int valueCategory){
    int count = 0;
    header("COMPANIES FOUND");
    for (int i = 0; i < companies -> numberCompanies; i++){
        if (companies->company[i].category == valueCategory || companies->company[i].active == true){
            printf("%d: %s\n", i + 1, companies->company[i].nameCompany);
            count++;
        } else {
            puts(SEARCH_NOT_FOUND);
        }
    }
}

void comentar(User *user, Company *company) {
    if (company->maxComments - company->numberComments == 1) {
        Comment *pComment= (Comment *) realloc(company->comments, (company->maxComments + 10) * sizeof(Comment));
        if (pComment != NULL) {
            company->comments = pComment;
            company->maxComments *= 2;
        } else {
            printf("ERROR: Failed in realloc comment");
        }
    }
    strcpy(company->comments[company->numberComments].user.name, user->name);
    strcpy(company->comments[company->numberComments].user.email, user->email);
    system("clear");
    header("COMMENT");
    char *title = inputString("Title: ", TITLE, false);
    strcpy(company->comments[company->numberComments].title, title);
    free(title);
    char *comment = inputString("Comment: ", COMMENT, false);
    strcpy(company->comments[company->numberComments].commentText, comment);
    free(comment);
    company->numberComments++;
}

