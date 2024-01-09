#pragma once
#include <stdio.h>
#include <stdlib.h>

struct node { 
    int data;
    int level;
    struct node *left;
    struct node *right;
};

struct node *new_node(int data);
struct node *insert(struct node *root, int data);
struct node *lookup(struct node *root, int data);
struct node *find_min(struct node *root);
struct node *find_max(struct node *root);
struct node *delete_node(struct node *root, int data);
void print(struct node *root, int indent);
void free_tree(struct node *root);

struct node *split(struct node *root);
struct node *skew(struct node *root);