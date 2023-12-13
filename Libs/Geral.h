// Geral.h
#ifndef COMPANY_MANAGEMENT_GERAL_H
#define COMPANY_MANAGEMENT_GERAL_H
#include "structs.h"
void showCompany(Company *company, bool showAnyway);
int inputNumber(char *txt);
char *inputString(char *txt, int quant, bool cleanConsole);
int verifyNumber(int *variable, int min, int max);
int GetOption(char *txt, int min, int max, bool showOption, bool showHeader, char *txtHeader);
void header(char *txt);
void showComments(Company *company);
int verifyNif(int nif);
int lenString(char *variable);
void cleanBuffer();
void getString(char *dest, char *txt, int charLen);
int numberCompaniesInCategory(Companies *companies, int valueCategory);

#endif //COMPANY_MANAGEMENT_GERAL_H