#include "Company.h"
#include "Admin.h"
#include <stdio.h>
#include "structs.h"
#include <string.h>
#include "Geral.h"
#include <stdlib.h>
#include "constVariables.h"
#include <unistd.h>
#include "Menus.h"

void handleCompany(Companies *companies, Activities *activities){
    bool back;
    do {
        back = false;
        menuCompanies(&back, companies, activities);
    } while (back != true);
}
