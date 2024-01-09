#include <stdio.h>
#include "AVLtree.h"

int main()
{
    struct avltree* head = avltree_create(16, "16");
    head = avltree_add(head, 3, "3");
    head = avltree_add(head, 21, "21");
    head = avltree_add(head, 2, "2");
    head = avltree_add(head, 7, "7");
    head = avltree_add(head, 24, "24");
    head = avltree_add(head, 5, "5");
    head = avltree_add(head, 9, "9");
    avltree_print_dfs(head);
    head = avltree_delete(head, 9);
    head = avltree_delete(head, 21);
    head = avltree_delete(head, 7);
    head = avltree_delete(head, 2);
    head = avltree_delete(head, 3);
    printf("\n");
    avltree_print_dfs(head);
    avltree_free(head);
    return 0;
}