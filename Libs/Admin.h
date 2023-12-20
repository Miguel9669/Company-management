#ifndef COMPANY_MANAGEMENT_ADMIN_H
#define COMPANY_MANAGEMENT_ADMIN_H

#define EXISTENT_COMPANY "Existent company, Try again: "
#define EXISTENT_NIF "Existent nif, Try again: "
#define EXISTENT_POSTAL "Existent Postal Code, Try again: "
#define ERROR_NIF "NIF need to be between 100000000 - 999999999: "

#include "structs.h"
void createCompany(Companies *companies, Activities *activities);
void deleteCompany(Companies *companies);
void modifyCompany(Companies *companies, Activities *activities);
void handleAdmin(Companies *companies, Activities *activities);
void iniciateCommentsAndRates(Company *company);
void creatActivity(Activities *activities);
void inactiveActivity(Activity *activity, Companies *companies);
void deleteActivity(Activities *activities, int index);
void activeActivity(Activity *activity, Companies *companies);
void handleAdminActivity(Activities *activities, Companies *companies);

#endif
