#include <stdio.h>
#include <locale.h>
#include "clientes.h"
#include "auxiliar.h"
#include "produtos.h"
#include "vendas.h"

#define MAX_CLIENTES 100
#define MAX_PRODUTOS 100
#define MAX_VENDAS 500



int main(void) {
    // funções básicas para o funcionamento do programa:
    setlocale(LC_ALL, "pt_BR.UTF-8"); // para usar acentos, etc.
    // declaração de variáveis principais:
    Cliente lista_clientes[MAX_CLIENTES];
    int qtd_clientes = 0;
    int opcao;

    // carregar dados salvos
    inicializar_clientes(lista_clientes, &qtd_clientes, MAX_CLIENTES);
    inicializar_produtos();
    inicializar_vendas();

    // iniciando interação com o usuário:
    do {
        limpar_tela(0);
        printf("==========================================\n");
        printf("                *  LOJINHA  *        \n");
        printf("==========================================\n");
        printf("Digite a opcao desejada:\n"
            " 1. Cadastro de Clientes\n"
            " 2. Cadastro de Produtos\n"
            " 3. Venda\n"
            " 4. Sair do Sistema\n"
        );
        opcao = obter_opcao();
        switch (opcao)
        {
            case 1:
                // Cadastro de Clientes
                executar_modulo_clientes(lista_clientes, &qtd_clientes);
                break;
            case 2:
                //Cadastro de Produtos
                executar_modulo_produtos(); // ainda vazio, não há menu de produtos pronto para exibir
                break;
            case 3:
                // Venda
                menu_vendas(lista_clientes, &qtd_clientes);
                break;
            case 4:
                // Sair do Sistema — salvar dados antes de encerrar
                printf("[Fim do Programa]\n\n");
                persistir_clientes(lista_clientes, qtd_clientes);
                salvar_produtos();
                salvar_vendas();
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
