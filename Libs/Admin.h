#ifndef COMPANY_MANAGEMENT_ADMIN_H
#define COMPANY_MANAGEMENT_ADMIN_H

#define EXISTENT_COMPANY "Existent company, Try again: "
#define EXISTENT_NIF "Existent nif, Try again: "
#define EXISTENT_POSTAL "Existent Postal Code, Try again: "
#define ERROR_NIF "NIF need to be between 100000000 - 999999999: "

#include "structs.h"
void createCompany(Companies *companies);
int findCompanyIndexByNif(const Companies *companies, int nif);
int isCompanyExists(const Companies *companies, const char *name, int nif);
void deleteCompany(Companies *companies);
void modifyCompany(Companies *companies);


#endif
