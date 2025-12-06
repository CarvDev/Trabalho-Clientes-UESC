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

#endif