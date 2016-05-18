#ifndef treeA_h
#define treeA_h

struct bin_tree {
	char *username;
	char *password;
	struct bin_tree *right;
	struct bin_tree *left;
};

typedef struct bin_tree node;

//Limpa a estrutura
void cleanTree(node *root);

//Insere na arvore
void insertTree(node **t, char *name, char *pass);

//Print da arvore
void printTree(node *t, FILE *fd);

#endif
