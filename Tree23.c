#include "Tree23.h"

int add(TreeNode **root, void **element, TreeComparator f) {
    // Verifica se exite raiz
    if((*root) == NULL) {
        *root = newNode();
        if((*root) == NULL)  return 0;
    }
    // Adiciona elemento nas folhas
    if((*root)->left == NULL && (*root)->middle == NULL && (*root)->right == NULL) {
        if((*root)->dataleft == NULL) {
            (*root)->dataleft = *element;
            *element = NULL;
            return 1;
        }
        else {
            int compleft = f(*element, (*root)->dataleft);
            if(compleft == 0) {
                *element = NULL;
                return -1;
            }
            else if((*root)->dataright == NULL) {
                if(compleft < 0) {
                    (*root)->dataright = (*root)->dataleft;
                    (*root)->dataleft = *element;
                    *element = NULL;
                    return 1;
                }
                else {
                    (*root)->dataright = *element;
                    *element = NULL;
                    return 1;
                }
            }
            else {
                int compright = f(*element, (*root)->dataright);
                if(compright == 0) {
                    *element = NULL;
                    return -1;
                }
                return split(root, element, f);
            }
        }    
    }
    // Adiciona elemento em no com um dado e dois filhos
    else if((*root)->dataleft != NULL && (*root)->dataright == NULL) {
        int compleft = f(*element, (*root)->dataleft);
        if(compleft == 0){
            *element == NULL;
            return -1;
        }
        else if(compleft < 0) {
            return add(&(*root)->left, element, f);
        }
        else {
            return add(&(*root)->middle, element, f);
        }
    }
    // Adiciona elemento em um no com dois dados e tres filhos
    else if((*root)->dataleft != NULL && (*root)->dataright != NULL) {
        int compleft = f(*element, (*root)->dataleft);
        int compright = f(*element, (*root)->dataright);
        if(compleft == 0 || compright == 0){
            *element == NULL;
            return -1;
        }
        else if(compleft < 0) {
            return add(&(*root)->left, element, f);
        }
        else if(compright > 0) {
            return add(&(*root)->right, element, f);
        }
        else {
            return add(&(*root)->middle, element, f);
        }
    }
    return 0;
}

TreeNode *newNode() {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if(newNode == NULL)  return NULL;
    newNode->root = NULL;
    newNode->left = NULL;
    newNode->middle = NULL;
    newNode->right = NULL;
    newNode->dataleft = NULL;
    newNode->dataright = NULL;
    return newNode;
}

int split(TreeNode **root, void **element, TreeComparator f) {
    if(*element == NULL) return 1;
    // Encotra o elemento que tem que subir na arvore
    int compleft = f(*element, (*root)->dataleft);
    int compright = f(*element, (*root)->dataright);
    void *aux;
    if(compleft < 0) {
        aux = (*root)->dataleft;
        (*root)->dataleft = *element;
        *element = aux;  
    }
    else if(compright > 0) {
        aux = (*root)->dataright;
        (*root)->dataright = *element;
        *element = aux;
    }
    // Se o elemento tem que subir e nao existe raiz, criamos uma nova raiz
    if((*root)->root == NULL){
        TreeNode *auxNode = *root;
        *root = newNode();
        (*root)->dataleft = *element;
        *element = NULL;
        (*root)->left = auxNode;
        (*root)->left->root = *root;
        (*root)->middle = newNode();
        (*root)->middle->root = *root;
        (*root)->middle->dataleft = (*root)->left->dataright;
        (*root)->left->dataright = NULL;
        return 1;
    }
    // Se o no tem um dado e dois filhos, adicionamos o elemento nele
    else if((*root)->root->dataleft != NULL && (*root)->root->dataright == NULL) {
        compleft = f(*element, (*root)->root->dataleft);
        if(compleft < 0) {
            TreeNode *auxRoot = (*root)->root;
            auxRoot->dataright = auxRoot->dataleft;
            auxRoot->dataleft = *element;
            *element = NULL;
            auxRoot->right = auxRoot->middle;
            auxRoot->middle = newNode();
            auxRoot->middle->root = auxRoot;
            auxRoot->middle->dataleft = auxRoot->left->dataright;
            auxRoot->left->dataright = NULL;
            return 1;
        }
        else {
            TreeNode *auxRoot = (*root)->root;
            auxRoot->dataright = *element;
            *element = NULL;
            auxRoot->right = newNode();
            auxRoot->right->root = auxRoot;
            auxRoot->right->dataleft = auxRoot->middle->dataright;
            auxRoot->middle->dataright = NULL;
            return 1;
        }
    }
    // Se o no tem dois dados e tres filhos, chamamos split novamente
    else if((*root)->dataleft != NULL && (*root)->dataright != NULL) {
        printf("\n23\n\n");
        return split(&(*root)->root, element, f);
    }
    return 0;
}

/*
int removeTreeNode(TreeNode **root, void *key, TreeComparator f) {
    if((*root) == NULL) return 0;
    int compvalue = f(key, (*root)->element);
    if(compvalue < 0) {
        removeTreeNode(&(*root)->left, key, f);
    }
    else if(compvalue > 0) {
        removeTreeNode(&(*root)->right, key, f);
    }
    else {
        TreeNode *aux = *root;
        if (((*root)->left == NULL) && ((*root)->right == NULL)) {
            free(aux);
            (*root) = NULL;
        }
        else if((*root)->left == NULL) {
            (*root) = (*root)->right;
            aux->right = NULL;
            free(aux);
            aux = NULL;
        }
        else if((*root)->right == NULL) {
            (*root) = (*root)->left;
            aux->left = NULL;
            free(aux);
            aux = NULL;
        }
        else {
            int hl = height((*root)->left);
            int hr = height((*root)->right);
            if(hl > hr) {
                aux = greaterRight(&(*root)->left);
                aux->left = (*root)->left;
                aux->right =  (*root)->right;
                (*root)->left = NULL;
                (*root)->right = NULL;
                free(*root);
                (*root) = aux;
                aux = NULL;
            }
            else {
                aux = smallerLeft(&(*root)->right);
                aux->left = (*root)->left;
                aux->right =  (*root)->right;
                (*root)->left = NULL;
                (*root)->right = NULL;
                free(*root);
                (*root) = aux;
                aux = NULL;
            }
        }
    }
}
*/

int find(TreeNode *root, void *key, TreeComparator f, void **element) {
    if(root == NULL) return 0;
    int compleft = f(key, root->dataleft);
    if(compleft < 0) {
        return find(root->left, key, f, element);
    }
    else if(compleft == 0) {
        *element = root->dataleft;
        return 1;
    }
    else if(compleft > 0) {
        if(root->dataright != NULL) {
            int compright = f(key, root->dataright);
            if(compright == 0) {
                *element = root->dataright;
                return 1;
            }
            else if(compright > 0) {
                return find(root->right, key, f, element);
            }
        }
        return find(root->middle, key, f, element);
    }
}

void show(TreeNode *root, printNode print) {
    if(root != NULL) {
        printf("( ");
            show(root->left, print);

            print(root->dataleft);

            show(root->middle, print);

            print(root->dataright);

            show(root->right, print);
        printf(") ");
    }
}

int height (TreeNode *root) {
    if(root == NULL) {
        return -1;
    }
    else {
        return 1 + height(root->left);
    }
}

void destroy (TreeNode **root) {
    if ((*root) == NULL) return;
    destroy(&(*root)->left);
    destroy(&(*root)->middle);
    destroy(&(*root)->right);
    free(*root);
    (*root) = NULL;
}