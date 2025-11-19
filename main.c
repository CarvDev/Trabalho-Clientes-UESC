#include <stdio.h>
#include <locale.h>
#include "menus.h"

int main(void) {
    setlocale(LC_ALL, "pt_BR.UTF-8"); // para usar acentos, etc.
    // declarando variáveis globais:
    int opcao_principal;

    do {
        mostra_menu_principal();
        opcao_principal = obter_opcao();
        switch (opcao_principal)
        {
            case 1:
                mostra_menu_clientes();

                // implementar opção 1 (Gerenciar Clientes)

                // minha ideia:    
                /* Criar funções para 'submenus', por exemplo: 
                função mostra_menu_clientes(), depois usar a função 
                obter_opcaao para salvar a opcao escolhida numa variável, 
                em seguida usar um switch(case) para ativar as funções
                relacionadas ao submenu atual (no caso o de gerenciar clientes).

                Exemplo {
                    int opcao_clientes;
                    
                    do {
                        mostra_menu_clientes();
                        opcao_clientes = obter_opcao();

                        switch(opcao_clientes) 
                        {
                            case 1: Incluir Cliente
                            case 2: Excluir Cliente
                            case 3: Alterar Cliente
                            case 4: Retornar
                        }
                    } while (opcao_clientes != 4)
                }
                */

                break;
            case 2:
                // implementar opção 2 (Gerenciar Produtos)

                break;
            case 3:
                // implementar opção 3

                break;
            case 4:
                printf("[Fim do Programa]\n\n");
                break;
            default:     
                printf("[Opção inválida]\nTente novamente...\n\n");
                break;
        }
    }
    while (opcao_principal != 4);
    
    return 0;   
}
