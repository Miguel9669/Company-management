#ifndef COMPANY_MANAGEMENT_ADMIN_H
#define COMPANY_MANAGEMENT_ADMIN_H
#include "structs.h"
void createCompany(Companies *companies);
int findCompanyIndexByNif(const Companies *companies, int nif);
void deleteCompany(Companies *companies);
void modifyCompany(Companies *companies);


#endif
