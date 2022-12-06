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

void* removeTreeNode(TreeNode **treeRoot, TreeNode **root, void *key, TreeComparator f) {
    if((*root) == NULL) return NULL;
    int compleft = f(key, (*root)->dataleft);
    if(compleft < 0) {
        return removeTreeNode(treeRoot, &(*root)->left, key, f);
    }
    else {
        if(compleft > 0) {
            if((*root)->dataright == NULL) {
                return removeTreeNode(treeRoot, &(*root)->middle, key, f);
            }
            else {
                int compright = f(key, (*root)->dataright);
                if(compright < 0) {
                    return removeTreeNode(treeRoot, &(*root)->middle, key, f);
                }
                else if(compright > 0) {
                    return removeTreeNode(treeRoot, &(*root)->right, key, f);
                }
                // Remover dataright
                else {
                    return removeSplit(treeRoot, root, key, f);
                }
            }
        }
        // Remover dataleft
        else {
            return removeSplit(treeRoot, root, key, f);
        }
    }
    return NULL;
}

void* removeSplit(TreeNode **treeRoot, TreeNode **root, void *key, TreeComparator f) {
    int compleft = f(key, (*root)->dataleft);
    void *aux = NULL;
    TreeNode *auxNode = NULL;
    //e raiz e não tem folhas
    if((*root)->root == NULL && (*root)->left == NULL) {
        if(compleft != 0) {
            aux = (*root)->dataright;
            (*root)->dataright = NULL;
            return aux;
        }
        else {
            aux = (*root)->dataleft;
            if((*root)->dataright != NULL) {
                (*root)->dataleft = (*root)->dataright;
                (*root)->dataright = NULL;
                return aux;
            }
            else {
                (*root)->dataleft = NULL;
                return aux; 
            }
        }
    }
    //e folha
    else if((*root)->left == NULL) {
        // remove dataright
        if(compleft != 0) {
            aux = (*root)->dataright;
            (*root)->dataright = NULL;
            return aux;
        }
        // remove dataleft
        else {
            // dataleft recebe o dataright
            if((*root)->dataright != NULL) {
                aux = (*root)->dataleft;
                (*root)->dataleft = (*root)->dataright;
                (*root)->dataright = NULL;
                return aux;
            }
            // dataleft recebe um valor do nó anterior
            else {
                aux = (*root)->dataleft;
                (*root)->dataleft = NULL;
                auxNode = (*root);
                // subindo pela direita
                if(auxNode->root->right == auxNode) {
                    auxNode = auxNode->root;
                    if(auxNode->middle->dataright != NULL) {
                        auxNode->right->dataleft = auxNode->dataright;
                        auxNode->dataright = auxNode->middle->dataright;
                        auxNode->middle->dataright = NULL;
                        return aux;
                    }
                    else {
                        auxNode->middle->dataright = auxNode->dataright;
                        auxNode->dataright = NULL;
                        free(auxNode->right);
                        auxNode->right = NULL;
                        return aux;
                    }
                }
                // subindo pela esquerda
                else if(auxNode->root->left == auxNode) {
                    auxNode = auxNode->root;
                    auxNode->left->dataleft = auxNode->dataleft;
                    if(auxNode->middle->dataright != NULL) {
                        auxNode->dataleft = auxNode->middle->dataleft;
                        auxNode->middle->dataleft = auxNode->middle->dataright;
                        auxNode->middle->dataright = NULL;
                        return aux;
                    }
                    else {
                        if(auxNode->dataright != NULL) {
                            auxNode->dataleft = auxNode->middle->dataleft;
                            auxNode->middle->dataleft = auxNode->dataright;
                            if(auxNode->right->dataright != NULL) {
                                auxNode->dataright = auxNode->right->dataleft;
                                auxNode->right->dataleft = auxNode->right->dataright;
                                auxNode->right->dataright = NULL;
                                return aux;
                            }
                            else {
                                auxNode->middle->dataright = auxNode->right->dataleft;
                                auxNode->right->dataleft = NULL;
                                auxNode->dataright = NULL;
                                free(auxNode->right);
                                auxNode->dataright = NULL;
                                return aux;
                            }
                        }
                        // continua subindo
                        else {
                            auxNode->left->dataright = auxNode->middle->dataleft;
                            auxNode->middle->dataleft = NULL;
                            free(auxNode->middle);
                            auxNode->middle = NULL;
                            // continua >>>
                        }
                    }
                }
                // subindo pelo meio
                else {
                    auxNode = auxNode->root;
                    if(auxNode->dataright != NULL) {
                        auxNode->middle->dataleft = auxNode->dataright;
                        if(auxNode->right->dataright != NULL) {
                            auxNode->dataright = auxNode->right->dataleft;
                            auxNode->right->dataleft = auxNode->right->dataright;
                            auxNode->right->dataright = NULL;
                            return aux;
                        }
                        else {
                            auxNode->middle->dataright = auxNode->right->dataleft;
                            auxNode->right->dataleft = NULL;
                            auxNode->dataright = NULL;
                            free(auxNode->right);
                            auxNode->right = NULL;
                            return aux;
                        }
                    }
                    else {
                        if(auxNode->left->dataright != NULL) {
                            auxNode->middle->dataleft = auxNode->dataleft;
                            auxNode->dataleft = auxNode->left->dataright;
                            auxNode->left->dataright = NULL;
                            return aux;
                        }
                        // continua subindo
                        else {
                            auxNode->left->dataright = auxNode->middle->dataleft;
                            auxNode->middle->dataleft = NULL;
                            free(auxNode->middle);
                            auxNode->middle = NULL;
                            //continua >>>
                        }
                    }
                }
            }
        }
    }
    //nao e folha
    else {
        //remove dataright
        if(compleft != 0) {
            aux = (*root)->dataright;
            auxNode = (*root);
            ////////////////////////////////////////////// BUSCA O MENOR auxNode->right
            auxNode = auxNode->right;
            while(auxNode->left != NULL) {
                auxNode = auxNode->left;
            }
            (*root)->dataright = auxNode->dataleft;
            if(auxNode->dataright != NULL) {
                auxNode->dataleft = auxNode->dataright;
                auxNode->dataright = NULL;
                return aux;
            }
            else {
                auxNode->dataleft = NULL;
                // subindo pela direita
                if(auxNode->root->right == auxNode) {
                    auxNode = auxNode->root;
                    if(auxNode->middle->dataright != NULL) {
                        auxNode->right->dataleft = auxNode->dataright;
                        auxNode->dataright = auxNode->middle->dataright;
                        auxNode->middle->dataright = NULL;
                        return aux;
                    }
                    else {
                        auxNode->middle->dataright = auxNode->dataright;
                        auxNode->dataright = NULL;
                        free(auxNode->right);
                        auxNode->right = NULL;
                        return aux;;
                    }
                }
                // subindo pela esquerda
                else if(auxNode->root->left == auxNode) {
                    auxNode = auxNode->root;
                    auxNode->left->dataleft = auxNode->dataleft;
                    if(auxNode->middle->dataright != NULL) {
                        auxNode->dataleft = auxNode->middle->dataleft;
                        auxNode->middle->dataleft = auxNode->middle->dataright;
                        auxNode->middle->dataright = NULL;
                        return aux;
                    }
                    else {
                        if(auxNode->dataright != NULL) {
                            auxNode->dataleft = auxNode->middle->dataleft;
                            auxNode->middle->dataleft = auxNode->dataright;
                            if(auxNode->right->dataright != NULL) {
                                auxNode->dataright = auxNode->right->dataleft;
                                auxNode->right->dataleft = auxNode->right->dataright;
                                auxNode->right->dataright = NULL;
                                return aux;
                            }
                            else {
                                auxNode->middle->dataright = auxNode->right->dataleft;
                                auxNode->right->dataleft = NULL;
                                auxNode->dataright = NULL;
                                free(auxNode->right);
                                auxNode->dataright = NULL;
                                return aux;
                            }
                        }
                        // continua subindo
                        else {
                            auxNode->left->dataright = auxNode->middle->dataleft;
                            auxNode->middle->dataleft = NULL;
                            free(auxNode->middle);
                            auxNode->middle = NULL;
                            // continua >>>
                        }
                    }
                }
                // subindo pelo meio
                else {
                    auxNode = auxNode->root;
                    if(auxNode->dataright != NULL) {
                        auxNode->middle->dataleft = auxNode->dataright;
                        if(auxNode->right->dataright != NULL) {
                            auxNode->dataright = auxNode->right->dataleft;
                            auxNode->right->dataleft = auxNode->right->dataright;
                            auxNode->right->dataright = NULL;
                            return aux;
                        }
                        else {
                            auxNode->middle->dataright = auxNode->right->dataleft;
                            auxNode->right->dataleft = NULL;
                            auxNode->dataright = NULL;
                            free(auxNode->right);
                            auxNode->right = NULL;
                            return aux;
                        }
                    }
                    else {
                        if(auxNode->left->dataright != NULL) {
                            auxNode->middle->dataleft = auxNode->dataleft;
                            auxNode->dataleft = auxNode->left->dataright;
                            auxNode->left->dataright = NULL;
                            return aux;
                        }
                        // continua subindo
                        else {
                            auxNode->left->dataright = auxNode->middle->dataleft;
                            auxNode->middle->dataleft = NULL;
                            free(auxNode->middle);
                            auxNode->middle = NULL;
                            //continua >>>
                        }
                    }
                }
            }
        }
        //remove dataleft
        else {
            aux = (*root)->dataleft;
            auxNode = (*root);
            ////////////////////////////////////////////// BUSCA O MAIOR auxNode->left
            auxNode = auxNode->left;
            while(auxNode->left != NULL) {
                if(auxNode->dataright != NULL) {
                    auxNode = auxNode->right;
                }
                else {
                    auxNode = auxNode->middle;
                }
            }
            if(auxNode->dataright != NULL) {
                (*root)->dataleft = auxNode->dataright;
                auxNode->dataright = NULL;
                return aux;
            }
            else {
                (*root)->dataleft = auxNode->dataleft; 
                auxNode->dataleft = NULL;
                // subindo pela direita
                if(auxNode->root->right == auxNode) {
                    auxNode = auxNode->root;
                    if(auxNode->middle->dataright != NULL) {
                        auxNode->right->dataleft = auxNode->dataright;
                        auxNode->dataright = auxNode->middle->dataright;
                        auxNode->middle->dataright = NULL;
                        return aux;
                    }
                    else {
                        auxNode->middle->dataright = auxNode->dataright;
                        auxNode->dataright = NULL;
                        free(auxNode->right);
                        auxNode->right = NULL;
                        return aux;;
                    }
                }
                // subindo pela esquerda
                else if(auxNode->root->left == auxNode) {
                    auxNode = auxNode->root;
                    auxNode->left->dataleft = auxNode->dataleft;
                    if(auxNode->middle->dataright != NULL) {
                        auxNode->dataleft = auxNode->middle->dataleft;
                        auxNode->middle->dataleft = auxNode->middle->dataright;
                        auxNode->middle->dataright = NULL;
                        return aux;
                    }
                    else {
                        if(auxNode->dataright != NULL) {
                            auxNode->dataleft = auxNode->middle->dataleft;
                            auxNode->middle->dataleft = auxNode->dataright;
                            if(auxNode->right->dataright != NULL) {
                                auxNode->dataright = auxNode->right->dataleft;
                                auxNode->right->dataleft = auxNode->right->dataright;
                                auxNode->right->dataright = NULL;
                                return aux;
                            }
                            else {
                                auxNode->middle->dataright = auxNode->right->dataleft;
                                auxNode->right->dataleft = NULL;
                                auxNode->dataright = NULL;
                                free(auxNode->right);
                                auxNode->dataright = NULL;
                                return aux;
                            }
                        }
                        // continua subindo
                        else {
                            auxNode->left->dataright = auxNode->middle->dataleft;
                            auxNode->middle->dataleft = NULL;
                            free(auxNode->middle);
                            auxNode->middle = NULL;
                            // continua >>>
                        }
                    }
                }
                // subindo pelo meio
                else {
                    auxNode = auxNode->root;
                    if(auxNode->dataright != NULL) {
                        auxNode->middle->dataleft = auxNode->dataright;
                        if(auxNode->right->dataright != NULL) {
                            auxNode->dataright = auxNode->right->dataleft;
                            auxNode->right->dataleft = auxNode->right->dataright;
                            auxNode->right->dataright = NULL;
                            return aux;
                        }
                        else {
                            auxNode->middle->dataright = auxNode->right->dataleft;
                            auxNode->right->dataleft = NULL;
                            auxNode->dataright = NULL;
                            free(auxNode->right);
                            auxNode->right = NULL;
                            return aux;
                        }
                    }
                    else {
                        if(auxNode->left->dataright != NULL) {
                            auxNode->middle->dataleft = auxNode->dataleft;
                            auxNode->dataleft = auxNode->left->dataright;
                            auxNode->left->dataright = NULL;
                            return aux;
                        }
                        // continua subindo
                        else {
                            auxNode->left->dataright = auxNode->middle->dataleft;
                            auxNode->middle->dataleft = NULL;
                            free(auxNode->middle);
                            auxNode->middle = NULL;
                            //continua >>>
                        }
                    }
                }
            }          
        }
    }
    // continuando >>>
    if(auxNode != NULL) {
        TreeNode *auxRoot;
        while(auxNode->root != NULL) {
            auxRoot = auxNode->root;
            //subindo pela esquerda
            if(auxRoot->left == auxNode) {
                if(auxRoot->middle->dataright != NULL) {
                    auxNode->dataleft = auxRoot->dataleft;
                    auxRoot->dataleft = auxRoot->middle->dataleft;
                    auxRoot->middle->dataleft = auxRoot->middle->dataright;
                    auxRoot->middle->dataright = NULL;
                    auxNode->middle = auxRoot->middle->left;
                    auxNode->middle->left->root = auxNode->middle;
                    auxRoot->middle->left = auxRoot->middle->middle;
                    auxRoot->middle->middle = auxRoot->middle->right;
                    auxRoot->middle->right = NULL;
                    return aux;
                }
                else {
                    auxNode->dataleft = auxRoot->dataleft;
                    auxNode->dataright = auxRoot->middle->dataleft;
                    auxRoot->middle->dataleft = NULL;
                    auxNode->middle = auxRoot->middle->left;
                    auxRoot->middle->left = NULL;
                    auxNode->right = auxRoot->middle->middle;
                    auxRoot->middle->middle = NULL;
                    free(auxRoot->middle);
                    if(auxRoot->dataright != NULL) {
                        auxRoot->dataleft = auxRoot->dataright;
                        auxRoot->dataright = NULL;
                        auxRoot->middle = auxRoot->right;
                        auxRoot->right = NULL;
                        return aux;
                    }
                    else{
                        auxRoot->middle = NULL;
                        auxNode = auxRoot; //?????????????????????????????????? PARADA
                    }
                }
            }
            //subindo pela direita
            else if(auxRoot->right == auxNode) {
                if(auxRoot->middle->dataright != NULL) {
                    auxNode->dataleft = auxRoot->dataright;
                    auxRoot->dataright = auxRoot->middle->dataright;
                    auxRoot->middle->dataright = NULL;
                    auxNode->middle = auxNode->left;
                    auxNode->left = auxRoot->middle->right;
                    auxRoot->middle->right = NULL;
                    auxNode->left->root = auxNode;
                    return aux;
                }
                else {
                    auxRoot->middle->dataright = auxRoot->dataright;
                    auxRoot->dataright = NULL;
                    auxRoot->middle->right = auxNode->left;
                    auxRoot->middle->right->root = auxRoot->middle;
                    auxNode->left = NULL;
                    free(auxNode);
                    auxRoot->right = NULL;
                    return aux;
                }
            }
            //subindo pelo meio
            else {
                if(auxRoot->left->dataright != NULL) {
                    auxNode->dataleft = auxRoot->dataleft;
                    auxRoot->dataleft = auxRoot->left->dataright;
                    auxRoot->left->dataright = NULL;
                    auxNode->middle = auxNode->left;
                    auxNode->left = auxRoot->left->right;
                    auxRoot->left->right = NULL;
                    auxNode->left->root = auxNode;
                    return aux;
                }
                else {
                    auxRoot->left->dataright = auxRoot->dataleft;
                    auxRoot->left->right = auxNode->left;
                    auxNode->left = NULL;
                    free(auxRoot->middle);
                    if(auxRoot->dataright != NULL) {
                        auxRoot->dataleft = auxRoot->dataright;
                        auxRoot->dataright = NULL;
                        auxRoot->middle = auxRoot->right;
                        auxRoot->right = NULL;
                        return aux;
                    }
                    else{
                        auxRoot->middle = NULL;
                        auxNode = auxRoot; //?????????????????????????????????? PARADA
                    }
                }
            }
        }
        //////////////////////////////////////////// AQUI ESTA A PARADA
        if (auxNode->root == NULL) {
            auxNode->left->root = NULL;
            *treeRoot = auxNode->left;
            auxNode->left = NULL;
            free(auxNode);
            auxNode = NULL;
            return aux;
        }
    }
    return NULL;
}

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
        int hl, hm, hr;
        hl = height(root->left);
        hm = height(root->middle);
        hr = height(root->right);
        if (hl >= hm && hl >= hr) {
            return 1 + hl;
        }
        else if(hm >= hr) {
            return 1 + hm;
        }
        else {
            return 1 + hr;
        }
        
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