#include "utils.h"
#include "userT.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>

#define US_LOGIN_SUCCESSFUL	-1
#define US_NOT_REGISTERED   -2
#define US_ALREADY_EXISTS   -3
#define US_WRONG_PASS  		-4

static node *users;
static char path[] = "/home/$USER/.Backup/"
static int processesinqueue;

/* Armazena os dados dos utilizadores em ficheiro: 
retorna 0 em caso de sucesso. */
int saveUsers(node *users)
{
	FILE *fp;

	int error = 0;
	char file[1024];
	char *dir;

	strcpy(dir, path);
	strcat(dir, "users.log")
	fp = fopen(dir,"w+");
	if (fp < 0)
	{
		perror("saveUsers fopen");
		_exit(EXIT_FAILURE);
	}

	printU(users, fp);

	erro = fclose(fp);
	if (erro < 0)
	{
		perror("saveUsers write 2");
		_exit(EXIT_FAILURE);
	}
	
	return 0;
}

int login(char *username, char *pass){
	int res = 0;

	res = existU(username, pass);
	if (res == -2) 
		return US_NOT_REGISTERED;
	else{ 
		if(res == -4) 
			return US_WRONG_PASS;
	}else 
		return res;
}

int reg(char *username, char *pass){
	int res;
	char dir[1024];

	strcpy(dir, path);
	strcat(dir, "USERs/");
	strcat(dir, username);
	strcat(dir, "/");
	


	res = insertU(&users, username, pass);

	if(res == 1) 
		return US_ALREADY_EXISTS;
	else {
		strcpy(dir, path);

	}

		return res;
}

int readFifo(char *fifo, char ***message)
{
	int fd = 0, i = 0, tam = 1024, n = 0, erro = 0;
	char *buffer;
	char *token, *strArray[128];
	
	fd = open(fifo, O_RDONLY);
	if (fd < 0)
	{
		perror("readFifo open");
		_exit(EXIT_FAILURE);
	}
	
	buffer = (char *)malloc(sizeof(char ) * tam);
	n = readline(fd, buffer, sizeof(buffer));
	
	if (n < 0){
		perror("shell read");
		_exit(EXIT_FAILURE);
	}
	
	token = strtok(buffer, " ");

	while(token != NULL){
		strArray[i] = strdup(token);
		token = strtok(NULL, " ");
		i++;
	}

	erro = close(fd);
	if (erro < 0)
	{
		perror("readFifo close");
		_exit(EXIT_FAILURE);
	}
	*message = strArray;
	
	/*printf("MENSAGEM RECEBIDA = [%s]", tipo);
	for (j = 0; j < i; j++)
		printf(":[%s]", buffer[j]);
	printf("\n");*/
	
	if (strcmp(strArray[1], "log") == 0) return 1;
	if (strcmp(strArray[1], "reg") == 0) return 2;
	if (strcmp(strArray[2], "backup") == 0) return 3;
	if (strcmp(strArray[2], "restore") == 0) return 4;
	
	return -1; /* Tipo de mensagem inválido */
}

int main(){
	int fd = 0, tipe = 0; 
	char **message = NULL; 
	char *dir;
	loaddata();

	strcpy(dir, path);
	strcat(dir,"FIFOs/fifo");
	fd =makefifo(path, 0666);
	if (fd < 0){
		if(errno != EEXIST){
			perror("main mkfifo");
			_exit(EXIT_FAILURE);
		}
	}
	while(1){

		fd = open("/home/$USER/.Backup/FIFOs/fifo", O_RONLY);
		if(fd < 0){
			perror("main open fifo");
			_exit(EXIT_FAILURE);
		}
		message = NULL;
		tipe = readFifo("/home/$USER/.Backup/FIFOs/fifo", &message);
		switch (tipe){
			case 1:
				sucess = login(message[3],message[4]);
				switch(sucess){
					case 0:
						sendMessage(message[2], "US_LOGIN_SUCCESSFUL");
					case UT_NAO_EXISTE: /* Utilizador não existe */
		    			sendMessage(message[2], "UT_NAO_EXISTE");
		    			break;
		    			
		    		case UT_PASS_ERRADA: /* Pass errada */
		    			sendMessage(message[2], "UT_PASS_ERRADA");
		    			break;
		    			
		    		default:
		    			sendMessage(message[2], "ERRO");
		    			break;
		    	}
    			break;

    			case 2: /* Registar */
		    	sucesso = reg(message[3], message[4]);
		    	switch (sucesso)
		    	{
		    		case 0: /* Sucesso */
				    	sendMessage(mensagem[2], "OK");
		    			break;
		    			
		    		case UT_JA_EXISTE: /* Utilizador já existe */
		    			sendMessage(message[2], "UT_JA_EXISTE");
		    			break;
		    			
		    		default:
		    			sendMessage(mensagem[2], "ERRO");
		    			break;
		    	}
    			break;

    			case 3: /*backup*/
    					/* FUNCAO DE BACKUP*/
    			break;

    			case 4: /*restore*/
    				/*FUNCAO DE RESTORE*/
    			break;

    			default:
    				break;
				}
		}

		return EXIT_SUCCESS;
	}