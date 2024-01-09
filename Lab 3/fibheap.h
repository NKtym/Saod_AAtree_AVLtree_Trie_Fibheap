#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node {
    struct node *parent;
    struct node *child;
    struct node *left;
    struct node *right;
    int key;
    char *value;
    int mark;
    int degree;
};

struct fibheap {
    int nnodes;
    struct node *min;
};

struct fibheap *fibheap_insert(struct fibheap *heap, int key, char *value);
struct node *fibheap_min(struct fibheap *heap);
struct fibheap *fibheap_union(struct fibheap *heap1, struct fibheap *heap2);
struct node *fibheap_delete_min(struct fibheap *heap);
void fibheap_decrease_key(struct fibheap *heap, struct node *node, int newkey);
struct fibheap *fibheap_delete(struct fibheap *heap, int key);
void print_heap(struct node *node);

void fibheap_add_to_root_list(struct node *node, struct node *heap);
void fibheap_link_lists(struct node* node1,struct node* node2);
void fibheap_remove_node_from_root_list(struct node *node, struct fibheap *heap);
void fibheap_link(struct fibheap *heap, struct node *tmp, struct node *chiled_minimal);
void consolidate(struct fibheap *heap);
int get_degree(struct node *node);
void fibheap_cascading_cut(struct fibheap *heap, struct node *node);
void fibheap_cut(struct fibheap *heap, struct node *node, struct node *parent);
struct node *fibheap_find_node_child(struct node *node, int key);
struct node* fibheap_find_node(struct fibheap *heap, int key);