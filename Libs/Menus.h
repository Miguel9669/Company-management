//
// Created by anton on 13/12/2023.
//

#ifndef COMPANY_MANAGEMENT_MENUS_H
#define COMPANY_MANAGEMENT_MENUS_H
#include "structs.h"
void menuStart(User *user, bool *quit, Companies *companies, Activities *activities);
void menuUserSearch(bool *quit, Companies *companies, User *user);
void menuAdmin(bool *quit, Companies *companies, Activities *activities);
void menuCompany(User *user, Company *foundCompany, bool *back);
void menuSearchByCategory(Companies *companies, User *user);
int menuBranchActivity(Activities *activities, Companies *companies);
#endif //COMPANY_MANAGEMENT_MENUS_H
