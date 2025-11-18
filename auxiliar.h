// função para limpar o buffer, mais eficaz e portável que fflush, que só funciona no Windows
void limpar_buffer(void);

//limpa tela
void limpar_tela(int op);