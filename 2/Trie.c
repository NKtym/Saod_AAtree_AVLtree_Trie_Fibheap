#include <stdlib.h>
#include <string.h> 
#include "Trie.h"

struct trie *trie_create()
{
    struct trie *node;
    if ((node = malloc(sizeof(*node))) == NULL)
        return NULL;
    node->value = '\0';
    node->key = NULL;
    node->sibling = NULL;
    node->child = NULL;
    return node;
}

struct trie *trie_lookup(struct trie *root, char *key)
{
    struct trie *node, *list;
    for (list = root; *key != '\0'; key++) {
        for (node = list; node != NULL; node = node->sibling) {
            if (node->value == *key)
                break;
        }
        if (node != NULL)
            list = node->child;
        else
            return NULL;
    }
    return node;
}

struct trie *trie_insert(struct trie *root, char *key, char* value)
{
    struct trie *node, *parent, *list;
    parent = NULL;
    for (list = root; *key != '\0'; key++) {
        for (node = list; node != NULL; node = node->sibling){
            if (node->value == *key)
                break;
        }
        if (node == NULL) {
            node = trie_create();
            node->value = *key;
            node->sibling = list;
            if (parent != NULL)
                parent->child = node;
            else
                root = node;
            list = NULL;
        } 
        else {
            list = node->child;
        }
        parent = node;
    }
    if (node->key)
        free(node->key);
    node->key = strdup(value);
    return root;
}

struct trie *trie_delete(struct trie *root, char *key){
    int found;
    return trie_delete_dfs(root, NULL, key, &found);
}

struct trie *trie_delete_dfs(struct trie *root, struct trie *parent,char *key, int *found){
    struct trie *node, *prev = NULL;
    *found = (*key == '\0' && root == NULL) ? 1 : 0;
    if (root == NULL || *key == '\0')
        return root;
    for (node = root; node != NULL; node = node->sibling) {
        if (node->value == *key)
            break;
        prev = node;
    }
    if (node == NULL)
        return root;
    trie_delete_dfs(node->child, node, key + 1, found);
    if (*found > 0 && node->child == NULL) {
        if (prev != NULL)
            prev->sibling = node->sibling;
        else {
            if (parent != NULL)
                parent->child = node->sibling;
            else
                root = node->sibling;
        }
        free(node->key);
        free(node);
    }
    return root;
}

void trie_print(struct trie *root){
    if(!root)
        return;
    int cnt=0;
    struct trie *node, *parent;
    parent=root;
    while(root){
        if(root->sibling){
            node=root->sibling;
            trie_print(node);
            for(int i=0; i<cnt; i++){
                printf("%c\n",parent->value);
                parent=parent->child;
            }
        }
        printf("%c\n",root->value);
        if(!root->child && root->key){
            printf("Value: %s\n",root->key);
            cnt=0;
        }
        root=root->child;
        cnt++;
    }
}