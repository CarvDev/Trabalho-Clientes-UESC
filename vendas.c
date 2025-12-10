#include <stdio.h>
#include "auxiliar.h"
#include "vendas.h"
#include "clientes.h"
#include "produtos.h"


/* armazenamento local de vendas */
static Venda vendas[MAX_VENDAS];
static int total_vendas = 0;

void inicializar_vendas(Cliente *lista_clientes, int qtd_clientes) {
    total_vendas = carregar("vendas.txt", vendas, MAX_VENDAS, sizeof(Venda), ler_venda_item);
    /* garantir que os IDs comecem em 1 e sejam sequenciais e preencher nome do cliente */
    for (int i = 0; i < total_vendas; i++) {
        vendas[i].CodigoVenda = i + 1;
        int idx = encontrar_cliente(lista_clientes, qtd_clientes, vendas[i].cliente.CodigoClientes);
        if (idx != -1) {
            vendas[i].cliente = lista_clientes[idx];
        } else {
            vendas[i].cliente.NomeClientes[0] = '\0';
        }
        /* preencher dados dos produtos (nome e preco) a partir do codigo */
        for (int j = 0; j < vendas[i].carrinho.total_itens; j++) {
            int codigo = vendas[i].carrinho.produto[j].codigo_produto;
            int pidx = buscar_indice_produto(codigo);
            if (pidx != -1) {
                Produto *pp = obter_produto_por_indice(pidx);
                if (pp != NULL) {
                    vendas[i].carrinho.produto[j] = *pp;
                }
            } else {
                vendas[i].carrinho.produto[j].nome_produto[0] = '\0';
                vendas[i].carrinho.produto[j].preco_produto = 0.0f;
            }
        }
    }
}

void salvar_vendas(void) {
    salvar("vendas.txt", vendas, total_vendas, sizeof(Venda), salvar_venda_item);
}

void finalizar_vendas(Venda *venda){
    vendas[total_vendas] = *venda;
    vendas[total_vendas].CodigoVenda = total_vendas + 1; /* ids iniciam em 1 */
    total_vendas++;
    salvar_vendas();
}

float pagamento(float valor_total, float *troco){
    float valor_pago;
    printf("O valor total da compra é R$ %.2f\n", valor_total);
    printf("Digite o valor pago pelo cliente: R$ ");
    scanf("%f", &valor_pago);
    limpar_buffer();

    while (valor_pago < valor_total){
        printf("Valor insuficiente! Por favor, insira um valor igual ou maior que R$ %.2f\n", valor_total);
        scanf("%f", &valor_pago);
        limpar_buffer();
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
        printf("- %s | Quantidade: %d | Preco unitario: R$ %.2f\n",
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
    limpar_tela(0);
    // verificar se há clientes cadastrados
    if (*qtd_clientes == 0) {
        printf("Nenhum cliente cadastrado no sistema!\n");
        printf("Por favor, cadastre clientes antes de realizar vendas.\n");
        limpar_tela(1);
        return;
    }

    // verificar se há produtos cadastrados
    if (obter_total_produtos() == 0) {
        printf("Nenhum produto cadastrado no sistema!\n");
        printf("Por favor, cadastre produtos antes de realizar vendas.\n");
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
            limpar_tela(1);
        }
        
        limpar_buffer();
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

    // inicia venda
    Venda venda_atual;
    venda_atual.carrinho.PrecoTotal = 0;
    venda_atual.carrinho.total_itens = 0;

    int indice_produto = -1;

    while (pedido != -1){
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
        limpar_buffer();

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

            venda_atual.codigo_cliente = lista_clientes[codigo_valido].CodigoClientes;

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
        limpar_buffer();

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

void visualizar_vendas() {
    limpar_tela(0);
    if (total_vendas == 0) {
        printf("Nenhuma venda cadastrada no sistema!\n");
        limpar_tela(1);
        return;
    }
    printf("\n=======================================\n");
    printf("          LISTA DE VENDAS REALIZADAS          \n");
    printf("=======================================\n\n");
    for (int i = 0; i < total_vendas; i++) {
        printf("Venda ID: %u | Cliente: %s | Total: R$ %.2f\n",
               vendas[i].CodigoVenda,
               vendas[i].cliente.NomeClientes,
               vendas[i].carrinho.PrecoTotal);
    }
    printf("\n=======================================\n");
    limpar_tela(1);
}

void excluir_venda(void) {
    limpar_tela(0);
    if (total_vendas == 0) {
        printf("Nenhuma venda cadastrada no sistema!\n");
        limpar_tela(1);
        return;
    }

    unsigned int id;
    printf("Digite o ID da venda a ser excluida: ");
    if (scanf("%u", &id) != 1) {
        printf("Entrada invalida!\n");
        limpar_buffer();
        limpar_tela(1);
        return;
    }
    limpar_buffer();

    int indice = -1;
    for (int i = 0; i < total_vendas; i++) {
        if (vendas[i].CodigoVenda == id) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Venda com ID %u nao encontrada.\n", id);
        limpar_tela(1);
        return;
    }


    for (int i = indice; i < total_vendas - 1; i++) {
        vendas[i] = vendas[i + 1];
        vendas[i].CodigoVenda = i + 1; 
    }

    total_vendas--;

    if (total_vendas > 0) {
        vendas[total_vendas - 1].CodigoVenda = total_vendas;
    }

    salvar_vendas();
    printf("Venda %u removida com sucesso.\n", id);
    limpar_tela(1);
}

void mostrar_nota_fiscal(void) {
    limpar_tela(0);
    if (total_vendas == 0) {
        printf("Nenhuma venda cadastrada no sistema!\n");
        limpar_tela(1);
        return;
    }

    unsigned int id;
    printf("Digite o ID da venda para visualizar a nota fiscal: ");
    if (scanf("%u", &id) != 1) {
        printf("Entrada invalida!\n");
        limpar_buffer();
        limpar_tela(1);
        return;
    }
    limpar_buffer();

    int indice = -1;
    for (int i = 0; i < total_vendas; i++) {
        if (vendas[i].CodigoVenda == id) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Venda com ID %u nao encontrada.\n", id);
        limpar_tela(1);
        return;
    }

    Venda *v = &vendas[indice];

    printf("\n========================================\n");
    printf("              NOTA FISCAL\n");
    printf("========================================\n");
    printf("Venda ID: %u\n", v->CodigoVenda);
    printf("Cliente: %s\n", v->cliente.NomeClientes);
    printf("\nProdutos:\n");

    printf("%-4s %-30s %-10s %-10s %-10s\n", "#", "Nome", "Qtd", "Preco", "Subtotal");
    for (int i = 0; i < v->carrinho.total_itens; i++) {
        Produto *p = &v->carrinho.produto[i];
        int qtd = v->carrinho.Quantidade[i];
        float subtotal = p->preco_produto * qtd;
        printf("%-4d %-30s %-10d R$ %-8.2f R$ %-8.2f\n", i + 1, p->nome_produto, qtd, p->preco_produto, subtotal);
    }

    printf("\nTotal: R$ %.2f\n", v->carrinho.PrecoTotal);
    printf("Valor pago: R$ %.2f\n", v->carrinho.PrecoPago);
    printf("Troco: R$ %.2f\n", v->carrinho.Troco);
    printf("========================================\n\n");

    limpar_tela(1);
}

void menu_vendas(Cliente *lista_clientes, int *qtd_clientes) {
    int opcao;
    do {
        limpar_tela(0);
        printf("==========================================\n");
        printf("          *  MODULO DE VENDAS  *        \n");
        printf("==========================================\n");
        printf("1. Realizar nova venda\n");
        printf("2. Visualizar vendas realizadas\n");
        printf("3. Ver nota fiscal\n");
        printf("4. Excluir venda\n");
        printf("5. Retornar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1:
                executar_modulo_vendas(lista_clientes, qtd_clientes);
                // limpar_tela(1);
                break;
            case 2:
                visualizar_vendas();
                break;
            case 3:
                mostrar_nota_fiscal();
                break;
            case 4:
                excluir_venda();
                break;
            case 5:
                printf("Retornando ao menu principal...\n");
                limpar_tela(1);
                break;
            default:
                printf("[Opcao invalida]\nTente novamente...\n\n");
                limpar_tela(1);
                break;
        }
    } while (opcao != 5);
}