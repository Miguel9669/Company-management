//
// Created by anton on 06/12/2023.
//

#ifndef COMPANY_MANAGEMENT_USER_H
#define COMPANY_MANAGEMENT_USER_H

#define USER_RATING_TXT "Enter your rating (1 to 5)"


#include "structs.h"
Company *searchCompanyByName(Companies *companies, int *index);
void searchByCategory(Companies *companies, int valueCategory);
void comment(User *user, Company *company, int index);
void handleUser(User *user, Companies *companies, Activities *activities);
void handleUserSearchByName(Companies *companies, User *user);
void handleUserSearchByCategory(Companies *companies, User *user);
void handleUserSelectByCategory(Companies *companies, User *user, int valueCategory);
void rating(Company *company, int index);
void handleUserSearchByActivity(Companies *companies, Activities *activities, User *user);
bool isValidEmail(const char *email);
#endif //COMPANY_MANAGEMENT_USER_H