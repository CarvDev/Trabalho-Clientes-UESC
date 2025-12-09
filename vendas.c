#include <stdio.h>
#include "auxiliar.h"
#include "vendas.h"
#include "clientes.h"
#include "produtos.h"


/* armazenamento local de vendas */
static Venda vendas[MAX_VENDAS];
static int total_vendas = 0;

void inicializar_vendas(void) {
    total_vendas = carregar("vendas.txt", vendas, MAX_VENDAS, sizeof(Venda), ler_venda_item);
}

void salvar_vendas(void) {
    salvar("vendas.txt", vendas, total_vendas, sizeof(Venda), salvar_venda_item);
}

void finalizar_vendas(Venda *venda){
    vendas[total_vendas] = *venda;
    vendas[total_vendas].CodigoVenda = total_vendas;
    total_vendas++;
}

float pagamento(float valor_total, float *troco){
    float valor_pago;
    printf("O valor total da compra é R$ %.2f\n", valor_total);
    printf("Digite o valor pago pelo cliente: R$ ");
    scanf("%f", &valor_pago);

    while (valor_pago < valor_total){
        printf("Valor insuficiente! Por favor, insira um valor igual ou maior que R$ %.2f\n", valor_total);
        scanf("%f", &valor_pago);
    }

    *troco = valor_pago - valor_total;
    return valor_pago;
}

void mensagem_finalizar_venda(){
    printf("================================================\n");
    printf("              * Compra [ %u ] - finalizada *\n", vendas[total_vendas -1].CodigoVenda);
    printf("================================================\n");

    printf("Cliente: %s\n", vendas[total_vendas -1].cliente.NomeClientes);
    printf("Valor total: R$ %.2f\n\n", vendas[total_vendas -1].carrinho.PrecoTotal);

    printf("PRODUTOS COMPRADOS:\n");
    for (int i = 0; i < vendas[total_vendas -1].carrinho.total_itens; i++){
        printf("- %s | Quantidade: %d | Preço unitário: R$ %.2f\n",
            vendas[total_vendas -1].carrinho.produto[i].nome_produto,
            vendas[total_vendas -1].carrinho.Quantidade[i],
            vendas[total_vendas -1].carrinho.produto[i].preco_produto
        );
    }

    printf("\nValor pago: R$ %.2f\n", vendas[total_vendas -1].carrinho.PrecoPago);
    printf("Troco: R$ %.2f\n", vendas[total_vendas -1].carrinho.Troco);

    printf("================================================\n\n");
}

void executar_modulo_vendas(Cliente *lista_clientes, int *qtd_clientes)
{
    // verificar se há clientes cadastrados
    if (*qtd_clientes == 0) {
        printf("Nenhum cliente cadastrado no sistema!\n");
        printf("Por favor, cadastre clientes antes de realizar vendas.\n");
        limpar_tela(1);
        return;
    }


    unsigned int codigo_cliente_dado;
    int codigo_valido = -1;
    int pedido = 0, quantidade_produto;

    // pedir cliente
    while (codigo_valido == -1){
        printf("================================================\n");
        printf("              * MODULO DE VENDAS *\n");
        printf("================================================\n");
        printf("Digite o codigo do cliente:  ");
        
        if (scanf("%u", &codigo_cliente_dado) != 1) {
            printf("Entrada invalida! Digite um numero valido.\n");
            limpar_buffer();
            limpar_tela(1);
            continue;
        }

        codigo_valido = encontrar_cliente(lista_clientes, *qtd_clientes, codigo_cliente_dado);

        if(codigo_valido == -1){
            printf("Codigo invalido! Tente novamente.\n");
            limpar_tela(1);
        }
        else{
            printf("\n================================================\n");
            printf("         Bem-vindo(a), %s!\n", lista_clientes[codigo_valido].NomeClientes);
            printf("================================================\n");
            limpar_tela(1);
        }
    }
    // verificar se há produtos cadastrados
    if (obter_total_produtos() == 0) {
        printf("Nenhum produto cadastrado no sistema!\n");
        printf("Por favor, cadastre produtos antes de realizar vendas.\n");
        limpar_tela(1);
        return;
    } 

    // inicia venda
    Venda venda_atual;
    venda_atual.carrinho.PrecoTotal = 0;
    venda_atual.carrinho.total_itens = 0;

    int indice_produto = -1;

    while (1){
        printf("================================================\n");
        printf("              * Carrinho de compras *\n");
        printf("================================================\n");

        printf("Cliente: %s\n", lista_clientes[codigo_valido].NomeClientes);
        printf("Valor total atual: R$ %.2f\n\n", venda_atual.carrinho.PrecoTotal);

        // listar produtos
        visualizar_produtos();

        // pedir produto
        printf("\nDigite o codigo do produto para adicionar (ou -1 para finalizar): ");
        scanf("%d", &pedido);

        if (pedido == -1){
            if (venda_atual.carrinho.total_itens == 0){
                printf("Carrinho vazio. Compra cancelada.\n");
                limpar_tela(1);
                return;
            }

            // pagamento
            venda_atual.carrinho.PrecoPago =
                pagamento(venda_atual.carrinho.PrecoTotal, &venda_atual.carrinho.Troco);

            venda_atual.cliente = lista_clientes[codigo_valido];

            finalizar_vendas(&venda_atual);

            mensagem_finalizar_venda();
            limpar_tela(1);
            return;
        }

        // verificar produto
        indice_produto = buscar_indice_produto(pedido);

        if(indice_produto == -1){
            printf("Codigo de produto invalido!\n");
            limpar_tela(1);
            continue;
        }

        printf("Digite a quantidade: ");
        scanf("%d", &quantidade_produto);

        // adicionar ao carrinho
        int i = venda_atual.carrinho.total_itens;

        Produto *p = obter_produto_por_indice(indice_produto);
        if (p != NULL) {
            venda_atual.carrinho.produto[i] = *p;
            venda_atual.carrinho.Quantidade[i] = quantidade_produto;
            venda_atual.carrinho.total_itens++;
            venda_atual.carrinho.PrecoTotal += p->preco_produto * quantidade_produto;
        }

        limpar_tela(0);
    }
}