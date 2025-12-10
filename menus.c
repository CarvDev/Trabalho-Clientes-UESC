#include <stdio.h>
#include "menus.h"
#include "auxiliar.h"


// os menus abaixo precisam ser reformatados para estar de acordo com o modelo que professor mandou
void imprimir_menu_principal() {
    printf("==========================================\n");
    printf("                *  LOJINHA  *        \n");
    printf("==========================================\n");
    printf("Digite a opcao desejada:\n"
        " 1. Cadastro de Clientes\n"
        " 2. Cadastro de Produtos\n"
        " 3. Venda\n"
        " 4. Sair do Sistema\n"
    );
}

void imprimir_menu_clientes() {
    printf("Digite a opcao desejada:\n"
    "1. Incluir Cliente\n"
    "2. Excluir Cliente\n"
    "3. Alterar Cliente\n"
    "4. Mostrar Cadastro de Clientes\n"
    "5. Retornar\n"
    );
}