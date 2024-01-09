#include "AA.h"

struct node *new_node(int data) { 
    struct node *n = malloc(sizeof(struct node));
    n->data = data;
    n->level = 1; 
    n->left = NULL;
    n->right = NULL;
    return n;
}
 
struct node *split(struct node *root) { 
    if ((root == NULL) || (root->right->right == NULL))
    {
        return root;
    }
    if (root->right->right->level != root->level)
    {
        return root;
    }
    struct node* right = root->right;
    root->right = right->left;
    right->left = root;
    root = right;
    root->level++;
    return root;
} 
 
struct node *skew(struct node *root) { 
    if ((root == NULL) || (root->left == NULL))
    {
        return root;
    }
    if (root->level != root->left->level)
    {
        return root;
    }
    struct node* left = root->left;
    root->left = left->right;
    left->right = root;
    root = left;
    return root;
} 
 
struct node *insert(struct node *root, int data) { 
    if (root == NULL)
        return new_node(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        return root;
    root = skew(root);
    root = split(root); 
    return root; 
} 

struct node *lookup(struct node *root, int data) { 
    if (root == NULL)
        return NULL;
    if (data == root->data)
        return root;
    if (data < root->data)
        return lookup(root->left, data);
    return lookup(root->right, data);
}

struct node *find_min(struct node *root) { 
    if (root == NULL)
        return NULL;
    while (root->left)
        root = root->left;
    return root;
}

struct node *find_max(struct node *root) { 
    if (root == NULL)
        return NULL;
    while (root->right)
        root = root->right;
    return root;
}
 
struct node* delete_node(struct node* root, int data) 
{ 
        if (root == NULL)
    {
        return root;
    }
    struct node* deleted = NULL;
    struct node* last = root;
    if (data < root->data)
    {
        root->left = delete_node(root->left, data);
    }
    else
    {
        deleted = root;
        root->right = delete_node(root->right, data);
    }
    if ((root == last) && (deleted != NULL) && (data == deleted->data))
    {
        deleted->data = root->data;
        deleted = NULL;
        root = root->right;
        free(last);
    }
    else if ((root->left == NULL) || (root->right == NULL))
    {
        return root;
    }
    else if ((root->left->level < root->level - 1) || (root->right->level < root->level - 1))
    {
        root->level--;
        if (root->right->level > root->level)
        {
            root->right->level = root->level;
        }
        root = skew(root);
        root->right = skew(root->right);
        root->right->right = skew(root->right->right);
        root = split(root);
        root->right = split(root->right);
    }
    return root;
}

void free_tree(struct node *root) { 
    if (root == NULL)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void print(struct node *root, int indent) { 
    if (root == NULL)
        return;
    print(root->right, indent + 4); 
    for (int i = 0; i < indent; i++) { 
        printf(" ");
    } 
    printf("%d(%d)\n", root->data, root->level);
    print(root->left, indent + 4);
}