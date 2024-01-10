/**
 * @file Admin.h
 * @brief Header file containing declarations of administrative functions for company management.
 *
 * This file defines functions responsible for administrative tasks related to company and activity management.
 * These functions are intended for use by administrators in the company management system.
 *
 * @author Antonio, Miguel, Luis
 * @date 20-12-2023
 */
#ifndef COMPANY_MANAGEMENT_ADMIN_H
#define COMPANY_MANAGEMENT_ADMIN_H
#include "structs.h"

void createCompany(Companies *companies, Activities *activities, Informations *informations);
void deleteCompany(Companies *companies, int index);
void modifyCompany(Companies *companies, Activities *activities, Type userType, char *txt, int min, int max, Informations informations);
void handleAdmin(Companies *companies, Activities *activities, Informations *informations);
void iniciateCommentsAndRates(Company *company);
void iniciateInformation(Informations *informations, int index);
void creatActivity(Activities *activities);
void deleteActivity(Activities *activities, int index);
void inactiveActivity(Activity *activity, Companies *companies, int index);
void activeActivity(Activity *activity, Companies *companies, int index);
void handleAdminActivity(Activities *activities, Companies *companies);
void deleteComment(Company *company, int index);
void hideComments(Company *company, int index);
void handleAdminReports(Companies companies, Informations companiesExtraInformation);


#endif
