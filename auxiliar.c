#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "produtos.h"
#include "vendas.h"

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

void listar_algo(const char *arquivo,const char *oqseralistado) {
    FILE *f = fopen(arquivo, "r");
    if (!f) {
        printf("Erro ao abrir o arquivo %s\n", arquivo);
        return;
    }

    char linha[256];
    printf("\n=======================================\n");
    printf("          CADASTRO DE %s\n",oqseralistado);
    printf("\n=======================================\n\n");


    while (fgets(linha, sizeof(linha), f) != NULL) {
        printf("- %s", linha);
    }

    fclose(f);
}

void salvar(const char *nome_arquivo, void *vetor,int total,int tamanho_item,void (*salvar_item)(FILE *, void *))
{
    FILE *f = fopen(nome_arquivo, "w");
    if (!f) {
        printf("Erro ao abrir %s\n", nome_arquivo);
        return;
    }

    for (int i = 0; i < total; i++) {
        void *item = (char *)vetor + i * tamanho_item;
        salvar_item(f, item);
    }

    fclose(f);
}

void salvar_cliente_item(FILE *f, void *item) {
    Cliente *c = (Cliente *)item;
    fprintf(f, "%u|%s\n", c->CodigoClientes, c->NomeClientes);
}
// FAZER UMA STRUCT CHAMADA PRODUTO
void salvar_produto_item(FILE *f, void *item) {
    Produto *p = (Produto *)item;
    fprintf(f, "%d|%s|%.2f\n",p->codigo_produto,p->nome_produto,p->preco_produto);
}
void salvar_venda_item(FILE *f, void *item) {
    Venda *v = (Venda *)item;

    fprintf(f, "%u|%u|%.2f|%.2f|%.2f|%d|",
            v->CodigoVenda,
            v->cliente.CodigoClientes,
            v->carrinho.PrecoTotal,
            v->carrinho.PrecoPago,
            v->carrinho.Troco,
            v->carrinho.total_itens
    );

    for (int i = 0; i < v->carrinho.total_itens; i++) {
        fprintf(f, "%d,%d",
                v->carrinho.produto[i].codigo_produto,
                v->carrinho.Quantidade[i]
        );

        if (i < v->carrinho.total_itens - 1)
            fprintf(f, ";");
    }

    fprintf(f, "\n");
}

/* EXEMPLO DE COMO USAR ESSA FUNÇÃO GENERICA:

salvar("vendas.txt",
       vendas,
       total_vendas,
       sizeof(Venda),
       salvar_venda_item
);
*/

// carrega tudo dos arquivos numa struct
int carregar(const char *nome_arquivo,void *vetor,int max_itens,int tamanho_item,int (*ler_item)(const char *, void *)){
    FILE *f = fopen(nome_arquivo, "r");
    if (!f) {
        printf("Arquivo %s nao existe. Criando um novo...\n", nome_arquivo);
        return 0; // nada carregado
    }

    // verificar se o arquivo esta vazio
    fseek(f, 0, SEEK_END);
    long tamanho_arquivo = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    if (tamanho_arquivo == 0) {
        printf("Arquivo %s esta vazio. Nenhum dado carregado.\n", nome_arquivo);
        fclose(f);
        return 0;
    }

    char linha[512];
    int total = 0;

    while (fgets(linha, sizeof(linha), f) != NULL && total < max_itens) {
        void *item = (char *)vetor + total * tamanho_item;

        if (ler_item(linha, item)) {
            total++;
        }
    }

    fclose(f);
    return total;
}
int ler_cliente_item(const char *linha, void *item) {
    Cliente *c = (Cliente *)item;

    return sscanf(linha, "%u|%29[^\n]",
                  &c->CodigoClientes,
                  c->NomeClientes) == 2;
}

int ler_produto_item(const char *linha, void *item) {
    Produto *p = (Produto *)item;

    return sscanf(linha, "%d|%[^|]|%f",
                  &p->codigo_produto, p->nome_produto, &p->preco_produto) == 3;
}

int ler_venda_item(const char *linha, void *item) {
    Venda *v = (Venda *)item;

    // lê cabeçalho básico da venda
    int cabecalho_lido = sscanf(
        linha, "%u|%u|%f|%d|",
        &v->CodigoVenda,
        &v->cliente.CodigoClientes,
        &v->carrinho.PrecoTotal,
        &v->carrinho.total_itens
    );

    if (cabecalho_lido != 4)
        return 0;

    // agora localizar a parte de produtos
    const char *ptr = strchr(linha, '|');
    ptr = strchr(ptr + 1, '|');
    ptr = strchr(ptr + 1, '|');
    ptr = strchr(ptr + 1, '|');

    if (!ptr) return 0;
    ptr++; // pular '|'

    // ler pares p,q
    int i = 0;
    while (i < v->carrinho.total_itens && *ptr != '\0') {
        int p, q;
        int lidos = sscanf(ptr, "%d,%d", &p, &q);
        if (lidos != 2) break;

        v->carrinho.produto[i].codigo_produto = p;
        v->carrinho.Quantidade[i] = q;
        i++;

        ptr = strchr(ptr, ';');
        if (!ptr) break;
        ptr++; // pular ';'
    }

    return 1;
}

/* EXEMPLO DE USO DA FUNÇÃO ACIMA:
    total_clientes = carregar(
    "clientes.txt",
    clientes,
    MAX_CLIENTES,
    sizeof(Cliente),
    ler_cliente_item
);
*/