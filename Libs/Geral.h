// Geral.h
#ifndef COMPANY_MANAGEMENT_GERAL_H
#define COMPANY_MANAGEMENT_GERAL_H
#include "structs.h"
void showCompany(Company *company);
int inputNumber(char *txt);
char *inputString(char *txt, int quant);
void showActivity(Activities *activities, bool admin);
int verifyNumber(int *variable, int min, int max);
int GetOption(char *txt, int min, int max, bool showOption, bool showHeader, char *txtHeader);
void header(char *txt);
int showComments(Company *company, bool admin);
int verifyNif(int nif);
void cleanBuffer();
void getString(char *dest, char *txt, int charLen);
int numberCompaniesInCategory(Companies *companies, int valueCategory);
char *boolString(bool variable);
int findCompanyIndexByNif(const Companies *companies, int nif);
int isCompanyExists(const Companies *companies, char *name, int nif, int numberCompanies);
int isActivityExist(Activities *activities, char *name);
double companyAverageRating(Company *company);
int isCompanyExistInActivity(Activity *activity, const Companies *companies);
int showCompaniesInActivity(Activities *activities, Companies *companies, int index);
int verifyPostalCode(char *postalCode);
#endif //COMPANY_MANAGEMENT_GERAL_H