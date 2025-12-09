#ifndef CLIENTES_H
#define CLIENTES_H
#define TAMANHO 30

typedef struct Cliente
{
    
    unsigned int CodigoClientes;
    char NomeClientes[TAMANHO];

} Cliente;
int encontrar_cliente(Cliente *lista, int qtd, unsigned int codigo);
void inicializar_clientes(Cliente *lista, int *qtd, int max);
void persistir_clientes(Cliente *lista, int qtd);
void executar_modulo_clientes(Cliente *lista, int *qtd);
/* 
Esse módulo inicia um do-while, que limpa a tela, imprime o menu de clientes, 
solicita que o usuário selecione a opção desejada, e então armazena o input
numa variável local. Essa variável será passada para um switch(case), que executará
a função correspondente a cada opção disponível no módulo. Caso o usuário digite 5
o programa retornará ao menu principal, quebrando o loop. Caso digite um número
inválido o programa irá informar.
*/

#endif