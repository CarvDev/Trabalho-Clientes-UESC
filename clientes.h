#ifndef CLIENTES_H
#define CLIENTES_H

typedef struct Clientes
{
    
    int codigo;
    char clientes[30];

} Clientes;

void executar_modulo_clientes(void);
/* 
Esse módulo inicia um do-while, que limpa a tela, imprime o menu de clientes, 
solicita que o usuário selecione a opção desejada, e então armazena o input
numa variável local. Essa variável será passada para um switch(case), que executará
a função correspondente a cada opção disponível no módulo. Caso o usuário digite 5
o programa retornará ao menu principal, quebrando o loop. Caso digite um número
inválido o programa irá informar.
*/

#endif