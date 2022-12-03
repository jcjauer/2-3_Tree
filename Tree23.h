#ifndef Tree23_h
#define Tree23_h
#include <stdlib.h>
#include <stdio.h>
/*
- Estrutura dos nós da árvore
*/
typedef struct TreeNode {
    void *dataleft;
    void *dataright;
    struct TreeNode *root;
    struct TreeNode *left;
    struct TreeNode *middle;
    struct TreeNode *right;
} TreeNode;
/*
- O usuário da biblioteca deve fornecer uma função para comparação dos elementos
*/
typedef int (*TreeComparator)(void *element1, void *element2);
/*
- O usuário da biblioteca deve fornecer uma função para impressão dos dados do TreeNode
*/
typedef void (*printNode)(void *data);
/*
- Adiciona um novo elemento na árvore
*
- Argumentos: 
- - root: O endereço do ponteiro da raiz da árvore/subárvore
- - element: o elemento a ser adicionado
- - f: a função para comparação dos elementos
*
- Retorna:
- - 1 em caso de sucesso
- - 0 caso não tenha mais memória
- - -1 caso o elemento já exista na árvore
*
- Funções auxiliares
- - new root
- - split
*/
int add(TreeNode **treeRoot, TreeNode **root, void **element, TreeComparator f);
/*
- Cria uma nova raiz
*
- Argumentos: 
- - left: o filho da esquerda
- - middle: o filho do meio
- - element: o elemento a ser localizado e removido
*
- Retorna: 
- - o ponteiro da nova raiz em caso de sucesso
- - NULL caso não tenha mais memória
*/
TreeNode *newNode();
/*
- Equilibra a arvore
*
- Argumentos: 
- - root: O endereço do ponteiro da raiz da árvore/subárvore
- - element: o elemento a ser adicionado
- - f: a função para comparação dos elementos
*
- Retorna: 
- - 1 em caso de sucesso
- - 0 caso não faça nada
*/
int split(TreeNode **treeRoot, TreeNode **root,  void **element, TreeComparator f);
/*
- Ecolhe a mediana
*
- Argumentos: 
- - root: o endereço do ponteiro da raiz da árvore/subárvore
- - element: o endereço do elemento para as devidas alterações
- - f: a função para comparação dos elementos
*
- Retorna: 
- - 1 em caso de sucesso
- - 0 caso não encontre
*/
void chooseElement(TreeNode *root, void **element, TreeComparator f);
/*
- Remove um elemento na árvore
*
- Argumentos: 
- - root: A raiz da árvore/subárvore
- - key: o elemento a ser localizado e removido
- - f: a função para comparação dos elementos
*
- Retorna: 
- - 1 em caso de sucesso
- - 0 caso não encontre
*/
int removeTreeNode(TreeNode **root, void *key, TreeComparator f);
/*
- Localiza um elemento na árvore
*
- Argumentos: 
- - root: A raiz da árvore/subárvore
- - key: o elemento a ser localizado
- - f: a função para comparação dos elementos
- - element: um parâmetro de saída
*
- Retorna: 
- - 1 em caso de sucesso
- - 0 caso não encontre
*/
int find(TreeNode *root, void *data, TreeComparator f, void **element);
/*
- Imprime os elementos
*/
void show(TreeNode *root, printNode print);
/*
- Calcula a altura da árvore/subárvore
*
- Argumentos: 
- - root: A raiz da árvore/subárvore
*
- Retorna: 
- - inteiro que representa a altura da árvore
- - árvore com apenas um nó tem altura 0
*/
int height (TreeNode *root);
/*
- Destrói a árvore/subárvore
*
- Argumentos: 
- - root: A raiz da árvore/subárvore
*/
void destroy (TreeNode **root);

#endif