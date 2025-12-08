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

                printf("Insira o código do cliente: \n");

                scanf("%u", &lista[*qtd].CodigoClientes);

                (*qtd)++;

                break;

            case 2:

                // Excluir Cliente

                if (*qtd == 0){

                    printf("A lista está vazia! \n");

                    getchar();
                    
                    break;

                }

                int codigoRemover;
                int indiceEncontrado = -1; // significa que não achou nada.

                printf("Indique o código do cliente para ser removido: \n");

                scanf("%u", &codigoRemover);

                // Procurar se o cliente está cadastrado

                for(int i = 0; i < *qtd; i++){

                    if(lista[i].CodigoClientes == codigoRemover){

                        indiceEncontrado = i;

                        break;
                    }
                }

                if(indiceEncontrado != -1){

                    for(int i = indiceEncontrado; i < *qtd - 1; i++){

                        lista[i] = lista[i + 1];

                    }

                    (*qtd)--;

                    printf("Cliente removido com sucesso!\n");

                } else{

                    printf("Cliente não encontrado!\n");

                }


                 break;

            case 3:

                // Alterar Cliente

                if(*qtd == 0){

                    printf("A quantidade está vazia!\n");

                    getchar();

                    getchar();
                }

                int codigoAlterar;
                int indiceParaAlterar = -1;

                printf("Digite o código do cliente que deseja alterar: \n");

                scanf("%u", &codigoAlterar);

                // buscar o cliente

                for(int i = 0; i < *qtd; i++){

                    if(lista[i].CodigoClientes == codigoAlterar){

                        indiceParaAlterar = i;

                    }
                }

                if(indiceParaAlterar != -1){

                    printf("\nCLIENTE ENCONTRADO!\n");

                    // inserir novos dados

                    printf("Nome atual: %s\n", lista[indiceParaAlterar].NomeClientes);

                    printf("\nDigite o nome do novo cliente: \n");

                    scanf(" %[^\n]", lista[indiceParaAlterar].NomeClientes);

                    char opção;

                    printf("Deseja alterar o código do cliente? Digite (S/N).\n");

                    scanf(" %c", &opção);

                    if(opção == 's' || opção == 'S'){

                        printf("Digite o novo código: \n");

                        scanf("%u", &lista[indiceParaAlterar].CodigoClientes);

                        printf("Código atualizado com sucesso!\n");

                    } else {

                        printf("O código foi mantido.\n");
                    }

                    printf("Dados alterados com sucesso!\n");
                }

                break;

            case 4:
                //MOSTRAR CADASTRO DE CLIENTES;
                limpar_tela(0);

                printf("========= LISTAGEM DE CLIENTES =========\n\n");

                if(*qtd == 0){

                    printf("Nenhum cliente cadastrado no sistema. \n");

                } else {

                    printf("%-10s | %s\n", "CODIGO", "NOME DO CLIENTE");

                    printf("--------------------------------------------\n");

                    for(int i = 0; i < *qtd; i++) {

                        printf("%-10u | %s\n", lista[i].CodigoClientes, lista[i].NomeClientes);
                        
                    }

                }

                printf("\n========================================\n");

                printf("Pressione ENTER para voltar ao menu...");

                getchar();

                getchar();

                break;

            case 5:
            
                //retornar

                printf("Retornando ao menu principal...\n");

                break;

            default:

                printf("[Opção inválida]\nTente novamente...\n\n");

                break;
        }

    } while (opcao != 5);

}

