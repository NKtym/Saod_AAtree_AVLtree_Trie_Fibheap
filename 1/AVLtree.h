#pragma once
#include <stdio.h>

struct avltree{
    int key;
    char *value;
    int height;
    struct avltree *left;
    struct avltree *right;
    int is_visited;
    int deleted;
    char direction;
};

struct avltree *avltree_create(int key, char *value);
struct avltree *avltree_add(struct avltree *tree, int key, char *value);
struct avltree *avltree_lookup(struct avltree *tree, int key);
struct avltree *avltree_delete(struct avltree *tree, int key);
struct avltree *avltree_min(struct avltree *tree);
struct avltree *avltree_max(struct avltree *tree);
void avltree_free(struct avltree *tree);
void avltree_print_dfs(struct avltree *tree);
int avltree_height(struct avltree *tree);
int avltree_balance(struct avltree *tree);
struct avltree *avltree_right_rotate(struct avltree *tree);
struct avltree *avltree_left_rotate(struct avltree *tree);
struct avltree *avltree_leftright_rotate(struct avltree *tree);
struct avltree *avltree_rightleft_rotate(struct avltree *tree);
void avltree_is_visited_clear(struct avltree *root);
struct avltree *avltree_copy(struct avltree *tree, struct avltree *new_tree);
