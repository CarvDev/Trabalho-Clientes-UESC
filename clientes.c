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

                    for(int i = indiceEncontrado; i < *qtd - 1; i--){

                        lista[i] = lista[i + 1];

                    }

                    (*qtd)--;

                    printf("Cliente removido com sucesso!\n");

                } else{

                    printf("Cliente não encontrado.\n");

                }


                 break;

            case 3:

                // Alterar Cliente

                break;

            case 4:
                //MOSTRAR CADASTRO DE CLIENTES;
                limpar_tela(0);
                break;

            case 5:
            
                //retornar

                break;

            default:

                printf("[Opção inválida]\nTente novamente...\n\n");

                break;
        }

    } while (opcao != 5);

}

