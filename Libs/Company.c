#include "Company.h"
#include "structs.h"
#include "Menus.h"

/**
 * @brief Handles actions for a specific company.
 *
 * This function enters a loop to handle various actions related to a specific company based on user input,
 * and it continues until the user chooses to go back.
 *
 * @param companies Pointer to the Companies structure.
 * @param activities Pointer to the Activities structure.
 * @param informations Informations structure.
 */
void handleCompany(Companies *companies, Activities *activities, Informations informations){
    bool back;
    do {
        back = false;
        menuCompanies(&back, companies, activities, informations);
    } while (back != true);
}

/**
 * @brief Handles actions for company reports.
 *
 * This function enters a loop to handle various actions related to company reports based on user input,
 * and it continues until the user chooses to exit the menu.
 *
 * @param company Pointer to the Company structure.
 * @param informations Informations structure.
 * @param index Index of the company.
 */
void handleMenuReports(Company *company, Informations informations, int index) {
    int option;
    do {
        option = menuCompanyReport(company, informations, index);
    } while (option != 0);
}

