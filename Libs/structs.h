#ifndef COMPANY_MANAGEMENT_STRUCTS_H
#define COMPANY_MANAGEMENT_STRUCTS_H
#include "constVariables.h"
typedef enum {false, true} bool;
typedef enum {MICRO = 1, PME, LARGE_COMPANY} Category;
typedef enum {USER = 1, ADMIN, COMPANY} Type;
typedef enum {ACTIVITIES, COMPANIES} typeStruct;

typedef struct {
    bool Active;
    char activity[ACTIVITY];
}Activity;

typedef struct {
    int maxActivities;
    int numberActivities;
    Activity *activities;
}Activities;

typedef struct {
    char name[MAX_NAME];
    char email[MAX_EMAIL];
}User;

typedef struct {
    char name[MAX_NAME];
    int rate;
} Rate;

typedef struct{
    User user;
    char commentText[COMMENT];
    char title[TITLE];
    bool commentHide;
} Comment;

typedef struct{
    char codigoPostal[MAX_CODIGO];
    char adress[MAX_ADRESS];
    char city[MAX_CITY];
}Local;

typedef struct{
    int numberRates, numberComments, nif, maxRates, maxComments;
    char nameCompany[MAX_NAME_COMPANY];
    bool active;
    Rate *rates;
    Comment *comments;
    Local local;
    char activity[ACTIVITY];
    Category category;
}Company;

typedef struct{
    int maxCompanies;
    int numberCompanies;
    Company *company;
}Companies;

#endif //COMPANY_MANAGEMENT_STRUCTS_H
