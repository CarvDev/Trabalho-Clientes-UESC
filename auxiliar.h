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

#endif
