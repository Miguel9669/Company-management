/**
 * @file user.h
 * @brief Header file containing user-related functions for the company management system.
 *
 * This file defines functions specific to user interactions in the company management system.
 * These functions include searching for companies, providing comments and ratings, and handling user interactions.
 *
 * @author Antonio, Miguel, Luis
 * @date 20-12-2023
 */
#ifndef COMPANY_MANAGEMENT_USER_H
#define COMPANY_MANAGEMENT_USER_H

#define USER_RATING_TXT "Enter your rating (1 to 5)"


#include "structs.h"
Company *searchCompanyByName(Companies *companies, int *index);
void searchByCategory(Companies *companies, int valueCategory);
void comment(User *user, Company *company, int index);
void handleUser(User *user, Companies *companies, Activities *activities, Informations *informations);
void handleUserSearchByName(Companies *companies, User *user, Informations *informations);
void handleUserSearchByCategory(Companies *companies, User *user, Informations *informations);
void handleUserSelectByCategory(Companies *companies, User *user, int valueCategory, Informations *informations);
void rating(Company *company, int index);
void handleUserSearchByActivity(Companies *companies, Activities *activities, User *user, Informations *informations);
bool isValidEmail(const char *email);
#endif //COMPANY_MANAGEMENT_USER_H