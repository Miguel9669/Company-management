#ifndef COMPANY_MANAGEMENT_STRUCTS_H
#define COMPANY_MANAGEMENT_STRUCTS_H
#include "constVariables.h"
typedef enum {false, true} bool;
typedef enum {MICRO = 1, PME, LARGE_COMPANY} Category;
typedef enum {USER = 1, ADMIN, COMPANY} Type;
typedef enum {ACTIVITIES, COMPANIES, INFORMATIONS} typeStruct;
typedef struct {
    int searchCounter, searchByNameCounter, searchByCategoryCounter, searchByActivityCounter;
} Information;

typedef struct {
    int maxInformation, numberInformation;
    Information *information;
} Informations;

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
    int numberRates, numberComments, nif, maxRates, maxComments, sumRates;
    char nameCompany[MAX_NAME_COMPANY];
    bool active;
    Comment *comments;
    Local local;
    char activity[ACTIVITY];
    Category category;
    Type type;
}Company;

typedef struct{
    int maxCompanies;
    int numberCompanies;
    Company *company;
}Companies;

#endif //COMPANY_MANAGEMENT_STRUCTS_H
