#ifndef COMPANY_MANAGEMENT_COMPANY_H
#define COMPANY_MANAGEMENT_COMPANY_H
#include "structs.h"

void handleCompany(Companies *companies, Activities *activities);
void showCommentsCompany(Companies *companies);
void menuCompanies(bool *quit, Companies *companies, Activities *activities);

#endif
