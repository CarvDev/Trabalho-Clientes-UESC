#include <stdio.h>
#include <stdlib.h>

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limpar_tela(int op) {
    if (op == 1){
        printf("\n Aperte Enter para continuar ");
        getchar();
    }
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}