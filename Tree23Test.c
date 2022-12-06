#include "Tree23.h"
#include <stdlib.h>
#include <stdio.h>

//Elemento que será guardado na árvore
typedef struct TreeElement {
    int data;
} TreeElement;
//Função para comparar os elementos
static int IntergerComparator(void *element1, void *element2) {
    TreeElement *e1 = (TreeElement *) element1;
    TreeElement *e2 = (TreeElement *) element2;
    if ((*e1).data > (*e2).data)
        return 1;
    if ((*e1).data < (*e2).data)
        return -1;
    return 0;
}
// Função para printar um elemento
void printInteger(void *element) {
    TreeElement *e = (TreeElement *) element;
    if(e != NULL) {
        printf("%d ", (*e).data);
    }
}
// Função de teste principal
int main () {
    int opc = 0;
    TreeNode *root = NULL;
    TreeElement *element = NULL;
    // Loop principal
    do {
        //menu
        printf("\n");
        printf("Escolha uma opção: \n");
        printf("(1) - Adicionar elemento;\n");
        printf("(2) - Encontrar elemento;\n");
        printf("(3) - Remover elemento;\n");
        printf("(4) - Ver arvore;\n");
        printf("(0) - Sair.\n");
        scanf("%d", &opc);
        switch ( opc ) {
            case 1 :
                element = (TreeElement *)malloc(sizeof(TreeElement));
                if(element == NULL) break;
                printf("Digite o elemento: ");
                scanf("%d", &(*element).data);
                void *aux = element;
                add(&root, &root, &aux, IntergerComparator);
                printf("Altura da árvore: %d\n", height(root));
                printf("Árvore:\n");
                show(root, printInteger);
                printf("\n");
                break;
            case 2 :
                element = (TreeElement *)malloc(sizeof(TreeElement));
                if(element == NULL) break;
                printf("Digite o elemento: ");
                scanf("%d", &(*element).data);
                void *auxFind = NULL;
                if(find(root, element, &IntergerComparator, &auxFind) == 1) {
                    TreeElement *auxPrint = (TreeElement *) auxFind;
                    printf("Elemento encontrado: "); printInteger(auxPrint); printf("\n");
                }
                else {
                    printf("Elemento não encontrado ou inexistente.\n");
                }
                break;
            case 3 :
                element = (TreeElement *)malloc(sizeof(TreeElement));
                if(element == NULL) break;
                printf("Digite o elemento: ");
                scanf("%d", &(*element).data);
                void *auxRemoveNode = element;
                aux = removeTreeNode(&root, &root, auxRemoveNode, IntergerComparator);
                if(aux != NULL) {
                    TreeElement *auxRemoveNode = (TreeElement *) aux;
                    printf("Elemento encontrado: "); printInteger(auxRemoveNode); printf(". Removido.\n");
                    aux = NULL;
                    free(auxRemoveNode);
                    auxRemoveNode = NULL;
                }
                else {
                    printf("Elemento não removido ou inexistente.\n");
                }
                break;
            case 4 :
                printf("Altura da árvore: %d\n", height(root));
                printf("Árvore:\n");
                show(root, printInteger);
                printf("\n");
                break;
            case 0 :
                printf("\n");
                printf("Saindo.\n");
                break;
            default :
                printf("\n");
                printf("Opção inválida.\n");
        }
    } while (opc != 0);
    destroy(&root);
    return EXIT_SUCCESS;
}