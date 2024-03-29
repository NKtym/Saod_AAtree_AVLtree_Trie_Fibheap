#pragma once
#include <stdio.h>

struct trie{
    char *key;
    char value;
    struct trie *sibling; /* Sibling node */
    struct trie *child;
};

struct trie *trie_create();
struct trie *trie_insert(struct trie *root, char *key, char* value);
struct trie *trie_lookup(struct trie *root, char *key);
struct trie *trie_delete(struct trie *root, char *key);
struct trie *trie_delete_dfs(struct trie *root, struct trie *parent,char *key, int *found);
void trie_print(struct trie *root);