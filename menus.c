#include <stdio.h>
#include "menus.h"
#include "auxiliar.h"

int obter_opcao() {
    int opc; // Variável para armazer a opção selecionada
    int scanf_retorno; // Variável para checar o retorno do scanf

    while (1) {
        printf("> "); // caractere '>' para uma melhor exibição do programa no terminal
        
        // Armazena o valor de retorno da função scanf
        scanf_retorno = scanf("%d", &opc);

        // Caso de erro para quando o input NÃO for um número (ex: 'a') (scanf_retorno será 0)
        if (scanf_retorno == 0) {
            printf("[Erro: Digite apenas números]\nTente novamente...\n\n");
            limpar_buffer(); // Limpa o input inválido (ex: 'a\n')
            continue; // Pula para a próxima iteração do loop

        } else break; // Quebra o loop
    }
    
    limpar_buffer();
    return opc; // Retorna a opção selecionada
}

void mostra_menu_principal() {
    printf("Digite a opcao desejada:\n"
        " 1. Cadastro de Clientes\n"
        " 2. Cadastro de Produtos\n"
        " 3. Venda\n"
        " 4. Sair do Sistema\n"
    );
}

void mostra_menu_clientes() {
    printf("Digite a opção desejada:\n"
    "1. Incluir Cliente\n"
    "2. Excluir Cliente\n"
    "3. Alterar Cliente\n"
    "4. Mostrar Cadastro de Clientes\n"
    "5. Retornar\n"
    );
}