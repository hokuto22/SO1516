#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeA.c"

int main(int argc, char* argv[]){

	node *root = NULL;

	FILE* fp;

	fp = fopen("teste.log", "w+");

	insertTree(&root,"Zeca","Estaciona");
	insertTree(&root,"Joana","Fana");
	insertTree(&root,"Carlos","Silvita");
	insertTree(&root,"Fanecas","Fritas");

	printTree(root,fp);

	cleanTree(root);

	fclose(fp);

	return 0;

}

