#ifndef PRODUTOS_H
#define PRODUTOS_H

#define Maximo_Produto 100

typedef struct produtos
{
    int codigo_produto;
    char nome_produto[50];
    float preco_produto;
    
}Produto;

void executar_modulo_produtos(); 
void inicializar_produtos();
void salvar_produtos();
int buscar_indice_produto(int codigo);
void visualizar_produtos();
Produto *obter_produto_por_indice(int index);
int obter_total_produtos(void);

#endif