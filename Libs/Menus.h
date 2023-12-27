#ifndef COMPANY_MANAGEMENT_MENUS_H
#define COMPANY_MANAGEMENT_MENUS_H
#include "structs.h"
void menuStart(User *user, bool *quit, Companies *companies, Activities *activities);
void menuUserSearch(bool *quit, Companies *companies, User *user, Activities *activities);
void menuAdmin(bool *quit, Companies *companies, Activities *activities);
void menuCompany(User *user, Company *foundCompany, bool *back);
void menuSearchByCategory(Companies *companies, User *user);
int menuBranchActivity(Activities *activities);
void menuActionAdminActivity(Activities *activities, int index, Companies *companies);
int menuShowActivity(Activities *activities, bool admin, char *txt);
int menuModify(Companies *companies, int index, Activities *activities);
#endif //COMPANY_MANAGEMENT_MENUS_H
