#ifndef COMPANY_MANAGEMENT_MENUS_H
#define COMPANY_MANAGEMENT_MENUS_H
#include "structs.h"
void menuStart(User *user, bool *quit, Companies *companies, Activities *activities, Informations *informations);
void menuCompanies(bool *quit, Companies *companies, Activities *activities, Informations informations);
void menuUserSearch(bool *quit, Companies *companies, User *user, Activities *activities, Informations *informations);
void menuAdmin(bool *quit, Companies *companies, Activities *activities, Informations *informations);
void menuCompany(User *user, Company *foundCompany, bool *back, int index, Companies *companies);
void menuSearchByCategory(Companies *companies, User *user, Informations *informations);
int menuBranchActivity(Activities *activities);
void menuActionAdminActivity(Activities *activities, int index, Companies *companies);
int menuShowActivity(Activities *activities, bool admin, char *txt);
int menuCompanyReport(Company *company, Informations informations, int index);
int menuModify(Companies *companies, int index, Activities *activities, Type userType, char *txt, int min, int max, Informations informations);
void menuComments(Company *company, Type userType, Companies *companies);
void menuAdminReports (bool *back, Companies companies, Informations informations, int topRate, int topSearched);
#endif //COMPANY_MANAGEMENT_MENUS_H
