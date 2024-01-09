#include "AA.h"

int main(){
    printf("Work insert:\n");
    struct node* head = new_node(16);
    head = insert(head, 13);
    head = insert(head, 19);
    head = insert(head, 300);
    head = insert(head, 69);
    head = insert(head, 2);
    head = insert(head, 301);
    print(head,0);
    printf("\nWork lookup:\n");
    struct node* head2 = lookup(head, 69);
    print(head2,0);
    printf("\nMax head: %d", find_max(head)->data);
    printf("\nMin head: %d\n", find_min(head)->data);
    printf("\nMax head2: %d", find_max(head2)->data);
    printf("\nMin head2: %d\n", find_min(head2)->data);
    printf("\nWork delete 300:\n");
    head = delete_node(head,300);
    print(head,0);
    printf("\nWork delete 2:\n");
    head = delete_node(head,2);
    print(head,0);
    printf("\nWork delete 69:\n");
    head = delete_node(head,69);
    print(head,0);
    free_tree(head);
}