#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "AVL_tree.h"
#define NO_CHILD 9999999

#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)

typedef struct BSTNode_struct BSTNode;

struct BSTNode_struct {
    BSTNode *ptLeft, *ptRight;

    //length of the edge from this node to its children
    int edge_length;

    int height;

    int element;

    //-1=I am left, 0=I am root, 1=right
    int parent_dir;

    //max supported unit32 in dec, 10 digits max
    char label[11];
};


int maximum(int x, int y) {
  if(x > y){
    return x;
  }else{
    return y;
  }
}

int minimum(int x, int y) {
  if(x < y){
    return x;
  }else{
    return y;
  }
}

int getLevel(Tree *root, int value){
  if (root == NULL) {
    return 0;
  }
  if (value > root->value) {
    return 1 + getLevel(root->bigger, value);
  }else if(value < root->value){
    return 1 + getLevel(root->smaller, value);
  }else{
    return 1;
  }
}

Tree *loadTreeFromFile(char filename[100]){
  FILE *fp;
  Tree* root = (Tree*)(malloc(sizeof(Tree)));
  Tree* old_node, *new_branch;
  int number, place_not_found;
  char space;

  fp = fopen(filename, "r");
  if(fp == NULL){
    printf("ERRO 404: Arquivo não encontrado\n");
  }

  fscanf(fp, "%d%c", &root->value, &space);
  root->smaller = NULL;
  root->bigger = NULL;
  root->height = 1;

  while(!feof(fp)){
    new_branch = (Tree*)(malloc(sizeof(Tree)));
    fscanf(fp, "%d%c", &new_branch->value, &space);
    new_branch->smaller = NULL;
    new_branch->bigger = NULL;

    old_node = root;

    int place_not_found = 1;

    while(place_not_found){
      if(new_branch->value > old_node->value){
        if(old_node->bigger == NULL){
          old_node->bigger = new_branch;
          place_not_found = 0;
          new_branch->height = old_node->height + 1;
        }else{
          old_node = old_node->bigger;
        }
      }else{
        if(old_node->smaller == NULL){
          old_node->smaller = new_branch;
          place_not_found = 0;
          new_branch->height = old_node->height + 1;
        }else{
          old_node = old_node->smaller;
        }
      }
    }
  }
  return root;
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

Tree *find_min(Tree *t) {
    if (t == NULL) {
        return NULL;
    }
    else if (t->smaller == NULL) {
        return t;
    }
    else {
        return find_min(t->smaller);
    }
}

Tree *find_max(Tree *t) {
    if (t == NULL) {
        return NULL;
    }
    else if (t->bigger == NULL) {
        return t;
    }
    else {
        return find_max(t->bigger);
    }
}

Tree *find(int elem, Tree *t) {
    if (t == NULL) {
        return NULL;
    }

    if (elem < t->value) {
        return find(elem, t->smaller);
    }
    else if (elem > t->value) {
        return find(elem, t->bigger);
    }
    else {
        return t;
    }
}

//Insert i into the tree t, duplicate will be discarded
//Return a pointer to the resulting tree.

//adjust gap between left and right nodes
int gap = 3;

//used for printing next node in the same level,
//this is the x coordinate of the next char printed
int print_next;

BSTNode *build_ascii_tree_recursive(Tree *t) {
    BSTNode *node;

    if (t == NULL) return NULL;

    node = malloc(sizeof(BSTNode));
    node->ptLeft = build_ascii_tree_recursive(t->smaller);
    node->ptRight = build_ascii_tree_recursive(t->bigger);

    if (node->ptLeft != NULL) {
        node->ptLeft->parent_dir = -1;
    }

    if (node->ptRight != NULL) {
        node->ptRight->parent_dir = 1;
    }

    sprintf(node->label, "%d", t->value);
    node->element = strlen(node->label);

    return node;
}


//Copy the tree into the ascii node structre
BSTNode *build_ascii_tree(Tree *t) {
    BSTNode *node;
    if (t == NULL){
      return NULL;
    }
    node = build_ascii_tree_recursive(t);
    node->parent_dir = 0;
    return node;
}

//Free all the nodes of the given tree
void free_ascii_tree(BSTNode *node) {
    if (node == NULL) return;
    free_ascii_tree(node->ptLeft);
    free_ascii_tree(node->ptRight);
    free(node);
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(BSTNode *node, int x, int y) {
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parent_dir == -1);
    lprofile[y] = minimum(lprofile[y], x - ((node->element - isleft) / 2));
    if (node->ptLeft != NULL) {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
            lprofile[y + i] = minimum(lprofile[y + i], x - i);
        }
    }
    compute_lprofile(node->ptLeft, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_lprofile(node->ptRight, x + node->edge_length + 1, y + node->edge_length + 1);
}

void compute_rprofile(BSTNode *node, int x, int y) {
    int i, notleft;
    if (node == NULL){
      return;
    }
    notleft = (node->parent_dir != -1);
    rprofile[y] = maximum(rprofile[y], x + ((node->element - notleft) / 2));
    if (node->ptRight != NULL) {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
            rprofile[y + i] = maximum(rprofile[y + i], x + i);
        }
    }
    compute_rprofile(node->ptLeft, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_rprofile(node->ptRight, x + node->edge_length + 1, y + node->edge_length + 1);
}

//This function fills in the edge_length and
//height fields of the specified tree
void filledge(BSTNode *node) {
    int h, hmin, i, delta;
    if (node == NULL){
      return;
    }
    filledge(node->ptLeft);
    filledge(node->ptRight);

    /* first fill in the edge_length of node */
    if (node->ptRight == NULL && node->ptLeft == NULL) {
        node->edge_length = 0;
    }else {
        if (node->ptLeft != NULL) {
            for (i = 0; i < node->ptLeft->height && i < MAX_HEIGHT; i++) {
                rprofile[i] = -INFINITY;
            }
            compute_rprofile(node->ptLeft, 0, 0);
            hmin = node->ptLeft->height;
        }else {
            hmin = 0;
        }
        if (node->ptRight != NULL) {
            for (i = 0; i < node->ptRight->height && i < MAX_HEIGHT; i++) {
                lprofile[i] = INFINITY;
            }
            compute_lprofile(node->ptRight, 0, 0);
            hmin = minimum(node->ptRight->height, hmin);
        }
        else {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++) {
            delta = maximum(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        //If the node has two children of height 1, then we allow the
        //two leaves to be within 1, instead of 2
        if (((node->ptLeft != NULL && node->ptLeft->height == 1) ||
             (node->ptRight != NULL && node->ptRight->height == 1)) && delta > 4) {
            delta--;
        }

        node->edge_length = ((delta + 1) / 2) - 1;
    }

    //now fill in the height of node
    h = 1;
    if (node->ptLeft != NULL) {
        h = maximum(node->ptLeft->height + node->edge_length + 1, h);
    }
    if (node->ptRight != NULL) {
        h = maximum(node->ptRight->height + node->edge_length + 1, h);
    }
    node->height = h;
}

//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
void printLevel(BSTNode *node, int x, int level) {
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parent_dir == -1);
    if (level == 0) {
        for (i = 0; i < (x - print_next - ((node->element - isleft) / 2)); i++) {
            printf(" ");
        }
        print_next += i;
        printf("%s", node->label);
        print_next += node->element;
    }
    else if (node->edge_length >= level) {
        if (node->ptLeft != NULL) {
            for (i = 0; i < (x - print_next - (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->ptRight != NULL) {
            for (i = 0; i < (x - print_next + (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    }
    else {
        printLevel(node->ptLeft,
                   x - node->edge_length - 1,
                   level - node->edge_length - 1);
        printLevel(node->ptRight,
                   x + node->edge_length + 1,
                   level - node->edge_length - 1);
    }
}

//prints ascii tree for given Tree structure
void showTree(Tree *t) {
    BSTNode *proot;
    int xmin, i;
    if (t == NULL){
      return;
    }
    proot = build_ascii_tree(t);
    filledge(proot);
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        lprofile[i] = INFINITY;
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        xmin = minimum(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->height; i++) {
        print_next = 0;
        printLevel(proot, -xmin, i);
        printf("\n");
    }
    if (proot->height >= MAX_HEIGHT) {
        printf("(A árvore é maior que %d, ela pode ser desenhada incorretamente)\n", MAX_HEIGHT);
    }
    free_ascii_tree(proot);
}

void isFull(Tree* root){
  int number_of_elements, height;
  height = getHeight(root);
  number_of_elements = pow(2, height) - 1;

  if (number_of_elements == amount_of_elements(root)) {
    printf("A árvore é cheia\n");
  }else{
    printf("A árvore não é cheia\n");
  }
}

int amount_of_elements(Tree* branch){
  if(branch == NULL){
    return 0;
  }else if(branch->smaller == NULL && (branch->bigger)){
    return 1;
  } else {
    return 1 + amount_of_elements(branch->smaller) + amount_of_elements(branch->bigger);
  }
}

void searchValue(Tree* root, int value){
  Tree *branch = root;
  Tree *daddy = NULL, *brother = NULL;
  int not_found = 1;

  while(not_found){
    if(value == branch->value){
      not_found = 0;
      printf("Elemento %d encontrado\n", value);
      printf("\tNível do nó: %d\n", getLevel(root, value));
      if (daddy == NULL) {
        printf("\tO elemento é a raiz\n");
      }else{
        printf("\tPai: %d\n", daddy->value);
        if(daddy->smaller != NULL && (daddy->bigger != NULL)){
          printf("\tIrmão: %d\n", brother->value);
        }
      }

    }else if (value > branch->value) {
      if (branch->bigger == NULL) {
        printf("O valor %d não pertence a árvore!\n", value);
        not_found = 0;
      }else{
        daddy = branch;
        brother = branch->smaller;
        branch = branch->bigger;
      }
    }else{
      if(branch->smaller == NULL){
        printf("O valor %d não pertence a árvore!\n", value);
        not_found = 0;
      }else{
        daddy = branch;
        brother = branch->bigger;
        branch = branch->smaller;
      }
    }
  }
}

int getHeight(Tree* root){
  if(root == NULL){
    return 0;
  }else{
    return 1 + maximum(getHeight(root->bigger), getHeight(root->smaller));
  }
}

void printInOrder(Tree* root){
  if (root->smaller != NULL) {
    printInOrder(root->smaller);
  }
  printf("%d ", root->value);
  if (root->bigger != NULL) {
    printInOrder(root->bigger);
  }
}

void printPreOrder(Tree* root){
  printf("%d ", root->value);
  if (root->smaller != NULL) {
    printPreOrder(root->smaller);
  }
  if (root->bigger != NULL) {
    printPreOrder(root->bigger);
  }
}

void printPosOrder(Tree* root){
  if (root->smaller != NULL) {
    printPosOrder(root->smaller);
  }
  if (root->bigger != NULL) {
    printPosOrder(root->bigger);
  }
  printf("%d ", root->value);
}

Tree *balanceTree(Tree* root){
  Tree *daddy, *grandpa, *kid;
  if (!isBalanced(root)) {
    root = setBackbone(root);

    while (!isBalanced(root)) {
      grandpa = root;
      daddy = root;
      if (daddy !=NULL) {
        kid = daddy->bigger;
      }
      if (kid != NULL) {
        root = rotationLeft(NULL, daddy, kid, root);
      }

      grandpa = daddy;
      daddy = kid;
      kid = daddy->bigger;

      while ((daddy != NULL) && !isBalanced(root)) {
        grandpa = daddy;
        daddy = kid;
        if (daddy !=NULL) {
          kid = daddy->bigger;
        }

        if (kid != NULL) {
          root = rotationLeft(grandpa, daddy, kid, root);
        }

        grandpa = daddy;
        daddy = kid;
        if (daddy != NULL) {
          kid = daddy->bigger;
        }
      }
    }
  }
  return root;
  showTree(root);
}

Tree * setBackbone(Tree *root){
  Tree *grandpa, *daddy, *kid;

  while (root->smaller != NULL) {
    root = rotationRight(NULL, root, root->smaller);
  }

  grandpa = root;
  daddy = root->bigger;

  while (daddy->bigger != NULL) {
    grandpa = root;
    daddy = root->bigger;

    while ((daddy->smaller == NULL) && (daddy->bigger !=NULL)) {
      grandpa = grandpa->bigger;
      daddy = daddy->bigger;
    }

    while(daddy->smaller != NULL) {
      daddy = rotationRight(grandpa, daddy, daddy->smaller);
    }
  }
  return root;
}

Tree* rotationRight(Tree *grandpa, Tree *daddy, Tree *kid){

  if (grandpa != NULL) {
    grandpa->bigger = kid;
  }

  daddy->smaller = kid->bigger;
  kid->bigger = daddy;

  return kid;
}


Tree* rotationLeft(Tree *grandpa, Tree *daddy, Tree *kid, Tree *root){
  kid->smaller = daddy;
  daddy->bigger = NULL;

  if (grandpa != NULL) {
    if (grandpa->smaller == daddy) {
      grandpa->smaller = kid;
    }else{
      grandpa->bigger = kid;
    }
  }

  if (daddy == root) {
    root = kid;
  }
  return root;
}

int isBalanced(Tree *root){
    int left_h = 0;
    int right_h = 0;

    if(root == NULL){
      return 1;
    }
    if (root->smaller != NULL) {
      left_h = getHeight(root->smaller);
    }
    if (root->bigger != NULL) {
      right_h = getHeight(root->bigger);
    }

    int smaller_height = minimum(left_h,right_h);
    int bigger_height = maximum(left_h,right_h);
    int differrence = bigger_height - smaller_height;

    if((differrence <= 1 ) && isBalanced(root->smaller) && isBalanced(root->bigger)){
      //Arvore balanceada
      return 1;
    } else{
      //Arvore não balanceada
      return 0;
    }
}

Tree *removeValue(Tree* root, int number){
  if(root == NULL){
		printf("Valor %d nao encontrado na arvore!", number);
    return root;
  }
  if(number < root->value){
    root->smaller = removeValue(root->smaller,number);
  }else if(number > root->value){
    root->bigger = removeValue(root->bigger,number);
  }else{
    if(root->smaller == NULL){
      Tree *temp = root->bigger;
      free(root);
			printf("Valor removido com sucesso!\n");
      return temp;
    }else if(root->bigger == NULL){
      Tree *temp = root->smaller;
			printf("Valor removido com sucesso!\n");
      free(root);
      return temp;
    }
    Tree *temp = find_min(root->bigger);
    root->value = temp->value;
    root->bigger = removeValue(root->bigger,temp->value);

  }
  return root;
}

Tree *insertValue(int value, Tree *root){
  Tree* old_node, *new_branch;
  int number, place_not_found;

  new_branch = (Tree*)(malloc(sizeof(Tree)));
  new_branch->value = value;
  new_branch->smaller = NULL;
  new_branch->bigger = NULL;

  old_node = root;

  place_not_found = 1;

  while(place_not_found){
    if(new_branch->value > old_node->value){
      if(old_node->bigger == NULL){
        old_node->bigger = new_branch;
        place_not_found = 0;
        new_branch->height = old_node->height + 1;
      }else{
        old_node = old_node->bigger;
      }
    }else{
      if(old_node->smaller == NULL){
        old_node->smaller = new_branch;
        place_not_found = 0;
        new_branch->height = old_node->height + 1;
      }else{
        old_node = old_node->smaller;
      }
    }
  }
  return root;
}
