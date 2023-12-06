//
// Created by anton on 06/12/2023.
//

#ifndef COMPANY_MANAGEMENT_STRUCTS_H
#define COMPANY_MANAGEMENT_STRUCTS_H
#include "constVariables.h"
typedef enum {false, true} bool;
typedef enum {MICRO = 1, PME, LARGECOMPANY} Category;
typedef struct {
    char name[MAX_NAME];
    char email[MAX_EMAIL];
}User;

typedef struct{
    User user;
    char commentText[COMMENT];
    char title[TITLE];
} Comment;

typedef struct{
    char codigoPostal[MAX_CODIGO];
    char adress[MAX_ADRESS];
    char city[MAX_CITY];
}Local;

typedef struct{
    int nif;
    char nameCompany[MAX_NAME_COMPANY];
    Comment comments[100];
    char activity;
    Category category;
}Company;
typedef struct{
    int numberCompanies;
    Company company[100];
}Companies;

#endif //COMPANY_MANAGEMENT_STRUCTS_H
