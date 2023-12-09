// Geral.h
#ifndef COMPANY_MANAGEMENT_GERAL_H
#define COMPANY_MANAGEMENT_GERAL_H
#include "structs.h"
void showCompany(Company *company);
int inputNumber(char *txt);
char *inputString(char *txt, int quant);
int verifyNumber(int *variable, int min, int max);
int ShowMenuAndGetOption(char *txt, int min, int max, bool showOption);
void header(char *txt);
void showComments(Company *company);
int verifyNif(int nif);
int lenString(char *variable);

#endif //COMPANY_MANAGEMENT_GERAL_H