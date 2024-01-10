/**
 * @file Company.h
 * @brief Header file containing declarations of functions related to company operations.
 *
 * This file defines functions specific to company operations and menu handling.
 * These functions are intended for use in the company management system.
 *
 * @author Antonio, Miguel, Luis
 * @date 20-12-2023
 */

#ifndef COMPANY_MANAGEMENT_COMPANY_H
#define COMPANY_MANAGEMENT_COMPANY_H
#include "structs.h"

void handleCompany(Companies *companies, Activities *activities, Informations informations);
void handleMenuReports(Company *company, Informations informations, int index);
#endif
