//
// Created by anton on 04/12/2023.
//

#include "Admin.h"
#include <stdio.h>
enum CATEGORY{
    Micro = 1,
    PME = 2,
    GrandeEmpresa = 3
};

struct Empresas{
    int nif;
    char name[60];
    char industryActivity;
    char adress;
    char city;

};
