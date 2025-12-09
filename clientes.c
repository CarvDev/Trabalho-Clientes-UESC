#include "clientes.h"
#include <stdio.h>
#include <stdlib.h>
#include "auxiliar.h"
#include "menus.h"

void inicializar_clientes(Cliente *lista, int *qtd, int max) {
    *qtd = carregar("clientes.txt", lista, max, sizeof(Cliente), ler_cliente_item);
}

void persistir_clientes(Cliente *lista, int qtd) {
    salvar("clientes.txt", lista, qtd, sizeof(Cliente), salvar_cliente_item);
}


void executar_modulo_clientes(Cliente *lista, int *qtd) {

    int opcao;

    do {

        limpar_tela(0);
        imprimir_menu_clientes();
        opcao = obter_opcao();

        switch (opcao) {

            case 1: {
                // Incluir Cliente

                printf("Insira o código do cliente: \n");
                scanf("%u", &lista[*qtd].CodigoClientes);
                limpar_buffer();

                printf("Insira o nome do cliente: \n");
                scanf(" %[^\n]", lista[*qtd].NomeClientes);
                persistir_clientes(lista, *qtd + 1);
                printf("Cliente cadastrado com sucesso!\n");
                (*qtd)++;
                break;
            }

            case 2: {
                // Excluir Cliente
                if (*qtd == 0) {
                    printf("A lista está vazia! \n");
                    limpar_tela(1);
                    break;
                }

                unsigned int codigoRemover;
                int indiceEncontrado = -1;

                printf("Indique o código do cliente para ser removido: \n");
                scanf("%u", &codigoRemover);

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

                } else {
                    printf("Cliente não encontrado!\n");
                }

                break;
            }

            case 3: {
                // Alterar Cliente

                if (*qtd == 0) {
                    printf("A lista está vazia!\n");
                    getchar();
                    getchar();
                    break;
                }

                unsigned int codigoAlterar;
                int indiceParaAlterar = -1;

                printf("Digite o código do cliente que deseja alterar: \n");
                scanf("%u", &codigoAlterar);

                for(int i = 0; i < *qtd; i++){
                    if(lista[i].CodigoClientes == codigoAlterar){
                        indiceParaAlterar = i;
                        break;
                    }
                }

                if(indiceParaAlterar != -1){
                    printf("\nCLIENTE ENCONTRADO!\n");

                    printf("Nome atual: %s\n", lista[indiceParaAlterar].NomeClientes);
                    printf("Digite o novo nome: \n");

                    scanf(" %[^\n]", lista[indiceParaAlterar].NomeClientes);

                    char op;
                    printf("Deseja alterar o código? (S/N): ");
                    scanf(" %c", &op);

                    if(op == 's' || op == 'S'){
                        printf("Digite o novo código: \n");
                        scanf("%u", &lista[indiceParaAlterar].CodigoClientes);
                        printf("Código atualizado!\n");
                    }

                    printf("Dados alterados com sucesso!\n");

                } else {
                    printf("Cliente não encontrado!\n");
                }

                break;
            }

            case 4: {
                // MOSTRAR LISTA

                limpar_tela(0);
                printf("========= LISTAGEM DE CLIENTES =========\n\n");

                if (*qtd == 0) {
                    printf("Nenhum cliente cadastrado.\n");
                } else {
                    printf("%-10s | %s\n", "CODIGO", "NOME DO CLIENTE");
                    printf("--------------------------------------------\n");

                    for (int i = 0; i < *qtd; i++) {
                        printf("%-10u | %s\n",
                               lista[i].CodigoClientes,
                               lista[i].NomeClientes);
                    }
                }

                printf("\n========================================\n");
                printf("Pressione ENTER para voltar ao menu...");
                limpar_tela(1);

                break;
            }

            case 5:
                printf("Retornando ao menu principal...\n");
                limpar_tela(1);
                break;

            default:
                printf("[Opção inválida] Tente novamente...\n");
                limpar_tela(1);
                break;
        }

    } while (opcao != 5);
}

int encontrar_cliente(Cliente *lista, int qtd, unsigned int codigo) {
    for (int i = 0; i < qtd; i++) {
        if (lista[i].CodigoClientes == codigo) {
            return i;
        }
    }
    return -1;
}
