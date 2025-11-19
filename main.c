#include <stdio.h>
#include <locale.h>
#include "menus.h"
#include "auxiliar.h"

int main(void) {
    setlocale(LC_ALL, "pt_BR.UTF-8"); // para usar acentos, etc.
    // declarando variáveis globais:
    int opcao_principal;
    int opcao_clientes;

    do {
        mostra_menu_principal();
        opcao_principal = obter_opcao();
        switch (opcao_principal)
        {
            case 1:
                do
                {
                    limpar_tela(0);
                    mostra_menu_clientes();
                    opcao_clientes = obter_opcao();
                    switch (opcao_clientes)
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
                } while (opcao_clientes != 5);
                break;
            case 2:
                // implementar opção 2 (Cadastro de Produtos)

                break;
            case 3:
                // implementar opção 3 (Venda)

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
