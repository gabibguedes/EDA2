#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef struct tree {
  int value;
  int height;
  struct tree* smaller;
  struct tree* bigger;
} Tree;


Tree *loadTreeFromFile(char[100]);
int getLevel(Tree*, int);
void showTree(Tree*);
void isFull(Tree*);
void searchValue(Tree*, int);
int getHeight(Tree*);
Tree * removeValue(Tree*, int);
void printInOrder(Tree*);
void printPreOrder(Tree*);
void printPosOrder(Tree*);
Tree *balanceTree(Tree*);
int amount_of_elements(Tree*);
void putTreeInMatrix(Tree*, int**);

void fillLevel(Tree *nodes[],Tree *node,int targetLevel,int level,int nr);
void printNode(int , int);
void printCentered(int,char*);
void printSlahes(int , int , Tree *const *nodes);
void printNodesForLevel(Tree *,int, int);

int isBalanced(Tree *);
Tree* rotationRight(Tree *, Tree *, Tree *);
Tree* rotationLeft(Tree *, Tree *, Tree *, Tree*);
Tree* setBackbone(Tree *);
Tree* insertValue(int, Tree*);
#endif
