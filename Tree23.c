#include "Tree23.h"

int add(TreeNode **root, void *element, TreeComparator f) {
    if((*root) == NULL) {
        TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
        if(newNode == NULL)  return -1;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->middle = NULL;
        newNode->element = element;
        (*root) = newNode;
        return 1;
    }
    int compvalue = f(element, (*root)->element);
    if(compvalue > 0) { 
        return add(&(*root)->right, element, f);
    }
    else if(compvalue < 0){
        return add(&(*root)->left, element, f);
    }
    else {
        return -1;
    }
}

int find(TreeNode *root, void *key, TreeComparator f, void **element) {
    if(root == NULL) return 0;
    int compvalue = f(key, root->element);
    if(compvalue == 0) {
        *element = root->element;
        return 1;
    }
    if(compvalue > 0) return find(root->right, key, f, element);
    return find(root->left, key, f, element);
}

void in_order(TreeNode *root, printNode print) {
    if(root != NULL) {
        in_order(root->left, print);
        print(root->element);
        in_order(root->right, print);
    }
}

void pre_order(TreeNode *root, printNode print) {
    if(root != NULL) {
        print(root->element);
        pre_order(root->left, print);
        pre_order(root->right, print);
    }
}

void post_order(TreeNode *root, printNode print) {
    if(root != NULL) {
        print(root->element); 
        post_order(root->left, print);
        post_order(root->right, print);
    }
}

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

int height (TreeNode *root) {
    if(root == NULL) {
        return -1;
    }
    else {
        int hl = height(root->left);
        int hr = height(root->right);
        if (hl > hr) return hl + 1;
        return hr + 1;
    }
}

void destroy (TreeNode **root) {
    if (*root==NULL) return;
    destroy(&(*root)->left);
    destroy(&(*root)->right);
    free(*root);
    *root=NULL;
}

TreeNode *smallerLeft(TreeNode **no) {
    if((*no)->left != NULL) {
        return smallerLeft(&(*no)->left);
    }
    else {
        TreeNode *aux = *no;
        if((*no)->right != NULL) {
            *no = (*no)->right;
        }
        else {
            *no = NULL;
        }
        return aux;
    }
}

TreeNode *greaterRight(TreeNode **no) {
    if((*no)->right != NULL) {
        return greaterRight(&(*no)->right);
    }
    else {
        TreeNode *aux = *no;
        if((*no)->left != NULL) {
            *no = (*no)->left;
        }
        else {
            *no = NULL;
        }
        return aux;
    }
}