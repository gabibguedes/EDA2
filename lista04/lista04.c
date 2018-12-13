#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "AVL_tree.h"

void menu(Tree *root);
void menu_options();
void wait_user_response();
void loadNewTree();

int main(){
  Tree * arvore = NULL;
  loadNewTree();
  return 0;
}

void menu_options() {
  system("clear");
  printf("--------------------------------------------------------------------------------\n");
  printf("-%*s MENU INICIAL: %*s-\n",32," ",31," " );
  printf("--------------------------------------------------------------------------------\n");
  printf("Seja bem-vindo! O que deseja fazer?\n\n");
  printf("01- Imprimir a árvore\n");
  printf("02- Inserir valor na árvore\n");
  printf("03- Remover um valor da árvore\n");
  printf("04- Buscar valor na árvore\n");
  printf("05- Imprimir a altura da árvore\n");
  printf("06- Imprimir os valores da árvore em ordem\n");
  printf("07- Imprimir os valores da árvore em pré-ordem\n");
  printf("08- Imprimir os valores da árvore em pós-ordem\n");
  printf("09- Carregar uma nova árvore dos arquivos\n");
  printf("10- Sair\n");
  printf("--------------------------------------------------------------------------------\n");
}

void menu(Tree *root){
  int value;
  menu_options();
  scanf("%d", &value);
  switch (value){
    case 1:
      system("clear");
      printf("--------------------------------------------------------------------------------\n");
      printf("-%*s Sua Árvore: %*s-\n",33," ",32," " );
      printf("--------------------------------------------------------------------------------\n");
      printf("\n\n");
      showTree(root);
      wait_user_response();
      menu(root);
     	break;

    case 2: 
      system("clear");
      printf("--------------------------------------------------------------------------------\n");
      printf("-%*s Adicionar valor: %*s-\n",31," ",31," " );
      printf("--------------------------------------------------------------------------------\n");
      int new;
      showTree(root);
      printf("\n\nValor a ser adicionado: ");
      scanf("%d", &new);
      printf("\n");
      root = insertValue(new, root);
      root = balanceTree(root); 
      printf("\nNova árvore:\n\n");
      showTree(root);
      wait_user_response();
      menu(root);
      break;

    case 3:
      system("clear");
      printf("--------------------------------------------------------------------------------\n");
      printf("-%*s Remover valor: %*s-\n",31," ",31," " );
      printf("--------------------------------------------------------------------------------\n");
      int delete;
      showTree(root);
      printf("\n\nValor a ser removido: ");
      scanf("%d", &delete);
      printf("\n");
      root = removeValue(root, delete);
      root = balanceTree(root); 
      printf("\nNova árvore:\n\n");
      showTree(root);
      wait_user_response();
      menu(root);
      break;

    case 4:
      system("clear");
      printf("--------------------------------------------------------------------------------\n");
      printf("-%*s Busca: %*s-\n",36," ",34," " );
      printf("--------------------------------------------------------------------------------\n");
      int number;
      showTree(root);
      printf("\nNúmero: ");
      scanf("%d", &number);
      printf("\n");
      searchValue(root,number);
      wait_user_response();
      menu(root);
      break;

    case 5:
      system("clear");
      printf("--------------------------------------------------------------------------------\n");
      printf("-%*s Altura: %*s-\n",35," ",34," " );
      printf("--------------------------------------------------------------------------------\n");
      int height;
      showTree(root);
      printf("\n\nA altura da árvore é %d\n", getHeight(root));
      wait_user_response();
      menu(root);
      break;


    case 6:
      system("clear");
      printf("--------------------------------------------------------------------------------\n");
      printf("-%*s Em ordem: %*s-\n",34," ",34," " );
      printf("--------------------------------------------------------------------------------\n");
      showTree(root);
      printf("\nValores em ordem: ");
      printInOrder(root);
      printf("\n");
      wait_user_response();
      menu(root);
      break;

    case 7:
      system("clear");
      printf("--------------------------------------------------------------------------------\n");
      printf("-%*s Pré-ordem: %*s-\n",34," ",33," " );
      printf("--------------------------------------------------------------------------------\n");
      showTree(root);
      printf("\nValores em pré-ordem: ");
      printPreOrder(root);
      printf("\n");
      wait_user_response();
      menu(root);
      break;

    case 8:
      system("clear");
      printf("--------------------------------------------------------------------------------\n");
      printf("-%*s Pós-ordem: %*s-\n",34," ",33," " );
      printf("--------------------------------------------------------------------------------\n");
      showTree(root);
      printf("\nValores em pós-ordem: ");
      printPosOrder(root);
      printf("\n");
      wait_user_response();
      menu(root);
      break;

    case 9:
      loadNewTree();
      break;

    case 10:
      exit(-1);
      break;

    default :
      printf ("Por favor, insira uma opção valida!\n");
      getchar();
      sleep(2);
      menu(root);
      break;
    }
}

void wait_user_response(){
  getchar();
  printf("\n\nAperte ENTER para voltar ao menu\n");
  getchar();
}

void loadNewTree(){
  Tree *new_tree;
  int file;
  system("clear");
  printf("--------------------------------------------------------------------------------\n");
  printf("-%*s Nova Árvore: %*s-\n",32," ",32," " );
  printf("--------------------------------------------------------------------------------\n");
  printf("Escolha um arquivo para carregar sua árvore\n");
  printf("1 -bst1.txt\n");
  printf("2 -bst2.txt\n");
  printf("3 -bst3.txt\n");
  printf("4 -bst4.txt\n");
  printf("5 -bst5.txt\n");
  printf("6 -bst6.txt\n\n");
  scanf("%d", &file);
  switch (file) {
    case 1:
      new_tree = loadTreeFromFile("BSTs/bst1.txt");
      new_tree = balanceTree(new_tree); 
      menu(new_tree);
      break;
    case 2:
      new_tree = loadTreeFromFile("BSTs/bst2.txt");
      new_tree = balanceTree(new_tree); 
      menu(new_tree);
      break;
    case 3:
      new_tree = loadTreeFromFile("BSTs/bst3.txt");
      new_tree = balanceTree(new_tree); 
      menu(new_tree);
      break;
    case 4:
      new_tree = loadTreeFromFile("BSTs/bst4.txt");
      new_tree = balanceTree(new_tree); 
      menu(new_tree);
      break;
    case 5:
      new_tree = loadTreeFromFile("BSTs/bst5.txt");
      new_tree = balanceTree(new_tree); 
      menu(new_tree);
      break;
    case 6:
      new_tree = loadTreeFromFile("BSTs/bst6.txt");
      new_tree = balanceTree(new_tree); 
      menu(new_tree);
      break;
    default :
      printf ("\nPor favor, insira uma opcao valida!\n");
      getchar();
      sleep(2);
      loadNewTree();
      break;
  }
}
