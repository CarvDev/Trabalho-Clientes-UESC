#include "clientes.h"
#include <stdio.h>
#include "auxiliar.h"
#include "menus.h"

void inicializar_clientes(Cliente *lista, int *qtd, int max) {
    *qtd = carregar("clientes.txt", lista, max, sizeof(Cliente), ler_cliente_item);
}

void persistir_clientes(Cliente *lista, int qtd) {
    salvar("clientes.txt", lista, qtd, sizeof(Cliente), salvar_cliente_item);
}

static int cliente_existe(Cliente *lista, unsigned int codigo, int qtd) {
    // iteração para verificar se já existe um cliente com código informado 
    for (int i = 0; i < qtd; i++) {
        if (lista[i].CodigoClientes == codigo) {
            return 1;
        }
    }
    // se não existe retorna 0
    return 0;
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

                unsigned int codigoTemp; // variável temporária para salvar o código do cliente, antes de passar para a lista                
                printf("Insira o código do cliente: \n");
                scanf("%u", &codigoTemp);
                limpar_buffer();

                // verifica se já existe um outro cliente com esse código
                if(cliente_existe(lista, codigoTemp, *qtd)) {
                    printf("Já existe um cliente com esse código. Por favor tente novamente com um código diferente\n");
                    limpar_tela(1);
                    break;
                }

                lista[*qtd].CodigoClientes = codigoTemp;
                printf("Insira o nome do cliente: \n");
                fgets(lista[*qtd].NomeClientes, TAMANHO_NOME, stdin);
                printf("Cliente cadastrado com sucesso!\n");
                limpar_tela(1);
                (*qtd)++;

                persistir_clientes(lista, *qtd);
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
                limpar_buffer();

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
                    limpar_tela(1);
                    persistir_clientes(lista, *qtd);
                    
                } else {
                    printf("Cliente não encontrado!\n");
                    limpar_tela(1);
                }
                
                break;
            }

            case 3: {
                // Alterar Cliente

                if (*qtd == 0) {
                    printf("A lista está vazia!\n");
                    limpar_tela(1);
                    break;
                }
                
                unsigned int codigoAlterar;
                int indiceParaAlterar = -1;
                
                printf("Digite o código do cliente que deseja alterar: \n");
                scanf("%u", &codigoAlterar);
                limpar_buffer();
                
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
                    
                    fgets(lista[indiceParaAlterar].NomeClientes, TAMANHO_NOME, stdin);
                    
                    printf("Nome atualizado!\n");

                    char op;
                    printf("Deseja alterar o código? (S/N): ");
                    scanf(" %c", &op);
                    
                    if(op == 's' || op == 'S'){
                        unsigned int novoCodigoTemp;
                        printf("Digite o novo código: \n");
                        scanf("%u", &novoCodigoTemp);
                        limpar_buffer();
                        if (!cliente_existe(lista, novoCodigoTemp, *qtd)) {
                            lista[*qtd].CodigoClientes = novoCodigoTemp;
                            printf("Código atualizado!\n");
                        } else printf("Já existe um outro cliente com esse código, portanto o código não foi alterado.\n");
                    }

                    limpar_tela(1);
                    persistir_clientes(lista, *qtd);
                    
                } else {
                    printf("Cliente não encontrado!\n");
                    limpar_tela(1);
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
