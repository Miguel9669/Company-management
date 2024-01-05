#ifndef COMPANY_MANAGEMENT_MENUS_H
#define COMPANY_MANAGEMENT_MENUS_H
#include "structs.h"
void menuStart(User *user, bool *quit, Companies *companies, Activities *activities, CompaniesExtraInformation *companiesExtraInformation);
void menuCompanies(bool *quit, Companies *companies, Activities *activities);
void menuUserSearch(bool *quit, Companies *companies, User *user, Activities *activities);
void menuAdmin(bool *quit, Companies *companies, Activities *activities, CompaniesExtraInformation companiesExtraInformation);
void menuCompany(User *user, Company *foundCompany, bool *back, int index, Companies *companies);
void menuSearchByCategory(Companies *companies, User *user);
int menuBranchActivity(Activities *activities);
void menuActionAdminActivity(Activities *activities, int index, Companies *companies);
int menuShowActivity(Activities *activities, bool admin, char *txt);
int menuModify(Companies *companies, int index, Activities *activities, Type userType, char *txt, int min, int max);
void menuComments(Company *company, Type userType, Companies *companies);
void menuAdminReports (bool *back, Companies companies, CompaniesExtraInformation companiesExtraInformation, int topRate, int topSearched);
#endif //COMPANY_MANAGEMENT_MENUS_H
