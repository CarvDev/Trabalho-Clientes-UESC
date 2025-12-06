#include <stdio.h>
#include <string.h>
#include "produtos.h"
#include "auxiliar.h"

static Produto lista_produtos[Maximo_Produto];
static int total_produtos = 0;
static int dados_carregados = 0;

static int buscar_indice_produto(int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (lista_produtos[i].codigo_produto == codigo) {
            return i;
        }
    }
    return -1;
}

void inicializar_produtos() {
    if (!dados_carregados) {
        // Usa a sua função genérica do auxiliar.c
        total_produtos = carregar("produtos.txt", lista_produtos, Maximo_Produto, sizeof(Produto), ler_produto_item);
        dados_carregados = 1;
    }
}

void inserir_produto() {
    if (total_produtos >= Maximo_Produto) {
        printf("\nErro: Capacidade maxima de produtos atingida\n");
        limpar_tela(1);
        return;
    }

    Produto p;
    printf("\n--------------- NOVO PRODUTO ---------------\n");
    
    printf("Digite o codigo: ");
    scanf("%d", &p.codigo_produto);
    limpar_buffer();

    if (buscar_indice_produto(p.codigo_produto) != -1) {
        printf("Erro: Codigo ja usado em outro produto!\n");
        limpar_tela(1);
        return;
    }

    printf("Digite o nome: ");
    fgets(p.nome_produto, 50, stdin);
    p.nome_produto[strcspn(p.nome_produto, "\n")] = 0;

    printf("Digite o preco: ");
    scanf("%f", &p.preco_produto);

    lista_produtos[total_produtos] = p;
    total_produtos++;

    salvar_dados();
    
    printf("\nProduto foi cadastrado e salvo com sucesso!\n");
    limpar_tela(1);
}

void excluir_produto() {
    int codigo;
    printf("\n--- EXCLUIR PRODUTO ---\n");
    printf("Digite o codigo para excluir o produto: ");
    scanf("%d", &codigo);

    int index;

     index = buscar_indice_produto(codigo);
    if (index == -1) {
        printf("Produto nao foi encontrado.\n");
    } else {
        printf("Removendo: %s\n", lista_produtos[index].nome_produto);
        
        for (int i = index; i < total_produtos - 1; i++) {
            lista_produtos[i] = lista_produtos[i+1];
        }
        total_produtos--;
        
        salvar_dados();
        printf("Produto foi excluido com sucesso.\n");
    }
    limpar_tela(1);
}

void alterar_produto() {
    int codigo;
    printf("\n--------------- ALTERAR PRODUTO ---------------\n");
    printf("Digite o codigo para alterar o produto: ");
    scanf("%d", &codigo);
    limpar_buffer();

    int index = buscar_indice_produto(codigo);
    if (index != -1) {
        printf("Atual: %s (R$ %.2f)\n", lista_produtos[index].nome_produto, lista_produtos[index].preco_produto);
        
        printf("Digite o novo nome: ");
        fgets(lista_produtos[index].nome_produto, 50, stdin);
        lista_produtos[index].nome_produto[strcspn(lista_produtos[index].nome_produto, "\n")] = 0;

        printf("Digite o novo preco: ");
        scanf("%f", &lista_produtos[index].preco_produto);
        
        salvar_dados();
        printf("Produto foi atualizado!\n");
    } else {
        printf("Produto nao foi encontrado.\n");
    }
    limpar_tela(1);
}

void visualizar_produto() {
     
    printf("\n--------------- PRODUTOS ---------------n");
    for (int i = 0; i < total_produtos; i++) {
        printf("COD: %d | NOME: %s | R$ %.2f\n", 
               lista_produtos[i].codigo_produto, 
               lista_produtos[i].nome_produto, 
               lista_produtos[i].preco_produto);
    }
    printf("-------------------------\n");
    limpar_tela(1);
} 

// --- MENU ---
void executar_modulo_produtos() {
    inicializar_produtos();

    int opcao;
    do {
        limpar_tela(0);
        printf("\n=== GESTAO DE PRODUTOS ===\n");
        printf("1. Inserir Produto\n");
        printf("2. Excluir Produto\n");
        printf("3. Alterar Produto\n");
        printf("4. Visualizar Lista\n");
        printf("5. Voltar\n");

        opcao = obter_opcao();
        opcao = 5;
        switch (opcao)
        {
            case 1:
                inserir_produto();
                break;
            case 2:
                excluir_produto();
                break;
            case 3:
                alterar_produto();
                break;
            case 4:
                visualizar_produto();
                break;
            case 5:
                break;
            default:
                printf("[Opção inválida]\nTente novamente...\n\n");
                impar_tela(1);
                break;
        }
    } while (opcao != 5);
}