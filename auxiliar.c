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