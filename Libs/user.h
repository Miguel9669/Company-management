//
// Created by anton on 06/12/2023.
//

#ifndef COMPANY_MANAGEMENT_USER_H
#define COMPANY_MANAGEMENT_USER_H
#include "structs.h"
Company *searchCompanyByName(Companies *companies);
void searchByCategory(Companies *companies, int valueCategory);
void comentar(User *user, Company *company);
void handleUser(User *user, bool *quit, Companies *companies);
void handleUserSearchByName(Companies *companies, User *user);
void handleUserSearchByCategory(Companies *companies, User *user);
void handleUserSelectByCategory(Companies *companies, User *user, int valueCategory);
#endif //COMPANY_MANAGEMENT_USER_H