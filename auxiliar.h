#ifndef AUXILIAR_H
#define AUXILIAR_H

// função para limpar o buffer, mais eficaz e portável que fflush, que só funciona no Windows
void limpar_buffer(void);

//limpa tela
void limpar_tela(int op);

/*
Imprime o caractere '>', em seguida solicita para o usuário o input de um 
número inteiro e o retorna. Possui uma verificação para caso o usuário digite 
uma letra, evitando um loop infinito (devido à poluição do buffer)
*/
int obter_opcao(void);



// ===============================
//     FUNÇÃO GENÉRICA SALVAR
// ===============================

void salvar(const char *nome_arquivo,void *vetor,int total,int tamanho_item,void (*salvar_item)(FILE *, void *));

// ===============================
// SALVAR ITENS ESPECÍFICOS
// ===============================

void salvar_cliente_item(FILE *f, void *item);
void salvar_produto_item(FILE *f, void *item);
void salvar_venda_item(FILE *f, void *item);


// ===============================
//     FUNÇÃO GENÉRICA CARREGAR
// ===============================

int carregar(const char *nome_arquivo,void *vetor,int max_itens,int tamanho_item,int (*ler_item)(const char *, void *));


// ===============================
// CARREGAR ITENS ESPECÍFICOS
// ===============================

int ler_cliente_item(const char *linha, void *item);
int ler_produto_item(const char *linha, void *item);
int ler_venda_item(const char *linha, void *item);
#endif
