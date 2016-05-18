#ifndef UTILS_H
#define UTILS_H

#include <unistd.h> /* Por causa do tipo de dados: ssize_t do readLine() */

#define FOLDER_NAME	"Contas/"

typedef struct sComando
{
	char **output;
	int linhas;
} *Comando, NComando;

void clrscr(void);
char *duplicaString(char *str, int ini, int fim);
char *juntaString(char *str1, char *str2);
int contaCaracter(char *str, char caracter);
char *tiraPlicasAspas(char *str);
int criarMatriz(int ***a, int l, int c);
Comando leComando(char *comando);
ssize_t readLine(int fildes, void *buf, size_t nbyte);

#endif