#include <stdio.h>
#include "produtos.h"
#include "auxiliar.h"

// falta finalizar
void executar_modulo_produtos() {
    int opcao;
    do {
        limpar_tela(0);
        //imprimir_menu_produtos();
        //opcao = obter_opcao();
        opcao = 5;
        switch (opcao)
        {
            case 1:
                // Inserir Produto
                break;
            case 2:
                // Excluir Produto
                break;
            case 3:
                // Alterar Produto
                break;
            case 4:
                // Visualizar Lista de Produtos
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