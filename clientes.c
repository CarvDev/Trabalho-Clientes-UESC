#include "clientes.h"
#include <stdio.h>
#include <stdlib.h>
#include "auxiliar.h"
#include "menus.h"

void executar_modulo_clientes(Cliente *lista, int *qtd, int max) {
    int opcao;
    do {
        limpar_tela(0);
        imprimir_menu_clientes();
        opcao = obter_opcao();
        switch (opcao)
        {
            case 1:
                // Incluir Cliente
                break;
            case 2:
                // Excluir Cliente
                break;
            case 3:
                // Alterar Cliente
                break;
            case 4:
                // Mostrar Cadastro de Clientes
                break;
            case 5:
                // Retornar
                break;
            default:
                printf("[Opção inválida]\nTente novamente...\n\n");
                break;
        }
    } while (opcao != 5);
}