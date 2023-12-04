#include <stdio.h>
#include "Libs/Geral.h"

void menuProfile(int *variable) {
    menu("1 - Administrador\n"
         "2 - Utilizador\n"
         "3 - Empresa\n"
         "0 - Sair\n");
    inputNumber(variable, "");
}

void atributeProfile
int main() {
    int ola;
    menuProfile(&ola);
    printf("%d", verifyNumber(&ola, 0, 3));
    printf("%d", ola);
    return 0;
}
