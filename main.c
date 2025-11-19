#include <stdio.h>
#include <locale.h>
#include "clientes.h"
#include "menus.h"
#include "auxiliar.h"
#include "produtos.h"
#include "vendas.h"

int main(void) {
    // funções básicas para o funcionamento do programa:
    setlocale(LC_ALL, "pt_BR.UTF-8"); // para usar acentos, etc.

    // declarando variáveis para a main:
    int opcao;

    // iniciando interação com o usuário:
    do {
        limpar_tela(0);
        imprimir_menu_principal();
        opcao = obter_opcao();
        switch (opcao)
        {
            case 1:
                // Cadastro de Clientes
                executar_modulo_clientes(); // informações sobre o módulo em "clientes.h"
                break;
            case 2:
                //Cadastro de Produtos
                executar_modulo_produtos(); // ainda vazio, não há menu de produtos pronto para exibir
                break;
            case 3:
                // Venda
                executar_modulo_vendas(); // ainda vazio, não há menu de vendas pronto para exibir
                break;
            case 4:
                // Sair do Sistema
                printf("[Fim do Programa]\n\n");
                break;
            default:
                // Caso de erro (opção inválida)
                printf("[Opção inválida]\nTente novamente...\n\n");
                break;
        }
    }
    while (opcao != 4);
    
    return 0;   
}
