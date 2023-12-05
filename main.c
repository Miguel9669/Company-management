#include <stdio.h>
#include "Libs/Geral.h"

void menuGetOption(int *variable, char *txt, int min, int max) {
    do {
        menu(txt);
        inputNumber(variable, "");
    } while (!verifyNumber(variable, min, max));
}

int main() {
    int ola;
    menuGetOption(&ola, "1 - Administrador\n"
                      "2 - Utilizador\n"
                      "3 - Empresa\n"
                      "0 - Sair\n", 0, 3);
    printf("%d", verifyNumber(&ola, 0, 3));
    printf("%d", ola);
    return 0;
}
