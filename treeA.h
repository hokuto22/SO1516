#ifndef treeA_h
#define treeA_h

struct avl_node {
	char *username;
	char *password;
	struct avl_node *right;
	struct avl_node *left;
};

typedef struct avl_node node;

struct avl_tree {
	struct avl_node *root;
};

typedef struct avl_tree tree;

//Limpa a estrutura
void cleanTree(node* root);

tree* createTree();

node* createNode();

int heightTree(node* node);

int balanceFactor(node* node);

node* rotateLL(node* node);

node* rotateLR(node* node);

node* rotateRL(node* node);

node* rotateRR(node* node);

node* balanceNode(node* node);

void balanceTree(tree* root);

//Insere na arvore
void insertTree(tree* root, char *name, char *pass);

//Print da arvore
void printTree(node* root, FILE *fd);

int existUser(node* root, char *name);

#endif
