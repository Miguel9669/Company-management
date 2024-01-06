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
void inactiveActivity(Activity *activity, Companies *companies, int index);
void deleteActivity(Activities *activities, int index);
void activeActivity(Activity *activity, Companies *companies, int index);
void handleAdminActivity(Activities *activities, Companies *companies);
void deleteComment(Company *company, int index);
void handleAdminReports(Companies companies, Informations companiesExtraInformation);
void hideComments(Company *company, int index);

#endif
