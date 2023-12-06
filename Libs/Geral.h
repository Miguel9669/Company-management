// Geral.h
#ifndef COMPANY_MANAGEMENT_GERAL_H
#define COMPANY_MANAGEMENT_GERAL_H
#include "structs.h"
void showCompany(Company *company);
void inputNumber(int *variable, char *txt);
void inputString(char *variable, char *txt);
int verifyNumber(int *variable, int min, int max);
int ShowMenuAndGetOption(char *txt, int min, int max, bool showOption);
void header(char *txt);

#endif //COMPANY_MANAGEMENT_GERAL_H