#include "Tree23.h"

int add(TreeNode **treeRoot, TreeNode **root, void **element, TreeComparator f) {
    // Verifica se exite raiz
    if((*root) == NULL) {
        *root = newNode();
        if((*root) == NULL)  return 0;
    }
    // Adiciona elemento nas folhas
    if((*root)->left == NULL && (*root)->middle == NULL && (*root)->right == NULL) {
        if((*root)->dataleft == NULL) {
            (*root)->dataleft = *element;
            return 1;
        }
        else {
            int compleft = f(*element, (*root)->dataleft);
            if(compleft == 0) {
                return -1;
            }
            else if((*root)->dataright == NULL) {
                if(compleft < 0) {
                    (*root)->dataright = (*root)->dataleft;
                    (*root)->dataleft = *element;
                    return 1;
                }
                else {
                    (*root)->dataright = *element;
                    return 1;
                }
            }
            else {
                int compright = f(*element, (*root)->dataright);
                if(compright == 0) {
                    return -1;
                }
                return split(treeRoot, root, element, f);
            }
        }    
    }
    // Adiciona elemento em no com um dado e dois filhos
    else if((*root)->dataleft != NULL && (*root)->dataright == NULL) {
        int compleft = f(*element, (*root)->dataleft);
        if(compleft == 0){
            return -1;
        }
        else if(compleft < 0) {
            return add(treeRoot, &(*root)->left, element, f);
        }
        else {
            return add(treeRoot, &(*root)->middle, element, f);
        }
    }
    // Adiciona elemento em um no com dois dados e tres filhos
    else if((*root)->dataleft != NULL && (*root)->dataright != NULL) {
        int compleft = f(*element, (*root)->dataleft);
        int compright = f(*element, (*root)->dataright);
        if(compleft == 0 || compright == 0){
            return -1;
        }
        else if(compleft < 0) {
            return add(treeRoot, &(*root)->left, element, f);
        }
        else if(compright > 0) {
            return add(treeRoot, &(*root)->right, element, f);
        }
        else {
            return add(treeRoot, &(*root)->middle, element, f);
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

int split(TreeNode **treeRoot, TreeNode **root, void **element, TreeComparator f) {
    // Encontra o elemento que tem que subir na arvore e divide o nó
    TreeNode *auxNode = newNode();
    if(auxNode == NULL)  return 0;
    chooseElement(*root, element, f);
    auxNode->dataleft = *element;
    auxNode->root = (*root)->root;
    auxNode->left = *root;
    auxNode->left->root = auxNode;
    auxNode->middle = newNode();
    if(auxNode->middle == NULL)  return 0;
    auxNode->middle->root = auxNode;
    auxNode->middle->dataleft = auxNode->left->dataright;
    auxNode->left->dataright = NULL;
    // Loop
    if (auxNode->root == NULL) {
        *treeRoot = auxNode;
        return 1;
    }    
    while(auxNode->root != NULL) {
        if(auxNode->root->dataleft != NULL && auxNode->root->dataright == NULL) {
            root = &auxNode->root;
            int compleft = f(*element, (*root)->dataleft);
            if(compleft < 0) {
                (*root)->dataright = (*root)->dataleft;
                (*root)->dataleft = auxNode->dataleft;
                (*root)->right = (*root)->middle;
                (*root)->middle = auxNode->middle;
                (*root)->middle->root = *root;
                (*root)->left = auxNode->left;
                (*root)->left->root = *root;   
            }
            else {
                (*root)->dataright = auxNode->dataleft;
                (*root)->middle = auxNode->left;
                (*root)->middle->root = *root;
                (*root)->right = auxNode->middle;
                (*root)->right->root = *root;
            }
            auxNode->dataleft = NULL;
            auxNode->root = NULL;
            auxNode->left = NULL;
            auxNode->middle = NULL;
            free(auxNode);
            auxNode = NULL;
            return 1;
        }
        else if(auxNode->root->dataleft != NULL && auxNode->root->dataright != NULL) {
            *root = auxNode->root;
            int compleft = f(*element, (*root)->dataleft);
            int compright = f(*element, (*root)->dataright);
            chooseElement(*root, element, f);
            TreeNode *aux = auxNode;
            auxNode = newNode();
            auxNode->root = (*root)->root;
            auxNode->dataleft = *element;
            if(compleft < 0) {
                auxNode->middle = *root;
                auxNode->middle->root = auxNode;
                auxNode->left = aux;
                auxNode->left->root = auxNode;
                auxNode->left->dataleft = auxNode->middle->dataleft;
                auxNode->middle->dataleft = auxNode->middle->dataright;
                auxNode->middle->dataright = NULL;
                auxNode->middle->left = auxNode->middle->middle; 
                auxNode->middle->middle = auxNode->middle->right; 
                auxNode->middle->right = NULL; 
            }
            else if(compright > 0) {
                auxNode->left = *root;
                auxNode->left->root = auxNode;
                auxNode->middle = aux;
                auxNode->middle->root = auxNode;
                auxNode->middle->dataleft = auxNode->left->dataright;
                auxNode->left->dataright = NULL;
                auxNode->left->right = NULL;
            }
            else {
                auxNode->left = *root;
                auxNode->left->root = auxNode;
                auxNode->middle = aux;
                auxNode->middle->root = auxNode;
                auxNode->left->middle = auxNode->middle->left;
                auxNode->left->middle->root = auxNode->left;
                auxNode->middle->left = auxNode->middle->middle;
                auxNode->middle->middle = auxNode->left->right;
                auxNode->middle->middle->root = auxNode->middle;
                auxNode->left->right = NULL;
            }
            if (auxNode->root == NULL) {
                *treeRoot = auxNode;
                return 1;
            } 
        }
    }
}

void chooseElement(TreeNode *root, void **element, TreeComparator f) {
    int compleft = f(*element, root->dataleft);
    int compright = f(*element, root->dataright);
    void *aux;
    if(compleft < 0) {
        aux = root->dataleft;
        root->dataleft = *element;
        *element = aux;  
    }
    else if(compright > 0) {
        aux = root->dataright;
        root->dataright = *element;
        *element = aux;
    }
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
