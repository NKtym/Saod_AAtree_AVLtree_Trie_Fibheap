#include <stdio.h>
#include "Trie.h"

int main()
{
    struct trie* head = trie_create();
    head = trie_insert(head, "Roma", "Rom");
    head = trie_insert(head, "Pasha", "Pafa");
    head = trie_insert(head, "Artem", "Tema");
    printf("Cлучай c добавлением 1");
    trie_print(head);
    head = trie_insert(head, "Arrizona", "Arriz");
    printf("\nCлучай c добавлением 2");
    trie_print(head);
    head = trie_insert(head, "Papka", "Papka");
    printf("\nCлучай c добавлением 3");
    trie_print(head);
    head = trie_insert(head, "Papapa", "Papapa");
    printf("\nCлучай c добавлением 4");
    trie_print(head);
    printf("\nПоиск");
    trie_print(trie_lookup(head,"R"));
    trie_delete(head,"Roma");
    printf("\nСлучай с удалением");
    trie_print(head);
    trie_delete(head,"Papapa");
    printf("\nСлучай с удалением2");
    trie_print(head);
    trie_delete(head,"Pasha");
    printf("\nСлучай с удалением3");
    trie_print(head);
    return 0;
}