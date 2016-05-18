#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeA.h"

void cleanTree(node *root) {
	if(root) {
		cleanTree(root->right);
		cleanTree(root->left);
		free(root->username);
		free(root->password);
		free(root);
	}
}

void insertTree(node **t, char *name, char *pass) {

	//result para reduzir no numero de calculos (strcmp)
	int result=0;

	node *temp = NULL;

	if(!(*t)) {
		temp = (node *) malloc(sizeof(node));
		//temp->username = (char *) malloc(sizeof(char)*1024);
		//temp->password = (char *) malloc(sizeof(char)*1024);
		temp->left = NULL;
		temp->right= NULL;
		
		temp->username=strdup(name);
		temp->password=strdup(pass);

		*t = temp;
	}
	else if((result=strcmp(name,(*t)->username)) != 0) {
		if(result < 0)
			insertTree(&(*t)->left, name, pass);
		
		if(result > 0)
			insertTree(&(*t)->right,name, pass);
	}
	
}


void printTree(node *t, FILE *fd) {

	if(t != NULL) {
		printTree(t->left,fd);
		fprintf(fd,"%s;%s\n",t->username,t->password);
		printTree(t->right,fd);
	}
}
