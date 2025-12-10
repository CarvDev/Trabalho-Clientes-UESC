#ifndef VENDAS_H
#define VENDAS_H
#include "produtos.h"
#include "clientes.h"
#define MAX_VENDAS 500

typedef struct {
    Produto produto[100];
    int Quantidade[100];
    int total_itens;
    float PrecoTotal;
    float PrecoPago;
    float Troco;
}Carrinho;

typedef struct {
    unsigned int CodigoVenda;
    unsigned int codigo_cliente;
    Cliente cliente;
    Carrinho carrinho;
} Venda;

/* Inicializar e persistir vendas em arquivo */
void inicializar_vendas(void);
void salvar_vendas(void);

/* Finalizar uma venda e adicionar ao registro */
void finalizar_vendas(Venda *venda);

/* Processar pagamento da compra */
float pagamento(float valor_total, float *troco);

/* Exibir mensagem de compra finalizada */
void mensagem_finalizar_venda(void);

/* Executar módulo de vendas */
void executar_modulo_vendas(Cliente *lista_clientes, int *qtd_clientes);

/* Visualizar vendas realizadas */
void visualizar_vendas(void);

/* Menu do módulo de vendas */
void menu_vendas(Cliente *lista_clientes, int *qtd_clientes);

/* Excluir uma venda pelo ID */
void excluir_venda(void);

#endif