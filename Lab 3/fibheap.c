#include "fibheap.h"

void fibheap_add_to_root_list(struct node *node, struct node *heap) {
    if (heap == NULL) 
        return;
    if (heap->left == heap) {
        heap->left = node;
        heap->right = node;
        node->right = heap;
        node->left = heap;
    } else {
        struct node *lnode = heap->left;
        heap->left = node;
        node->right = heap;
        node->left = lnode;
        lnode->right = node;
    }
}

struct fibheap *fibheap_insert(struct fibheap *heap, int key, char *value) {
    struct node* node = malloc(sizeof(struct node));
    node->key = key;
    node->value = value;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->right = node;
    node->left = node;
    node->mark = 0;
    fibheap_add_to_root_list(node, heap->min);
    if (heap->min == NULL || node->key < heap->min->key)
        heap->min = node;
    heap->nnodes += 1;
    return heap;
}

struct node *fibheap_min(struct fibheap *heap) {
    return heap->min; 
}

void fibheap_link_lists(struct node* node1,struct node* node2) {
    if (node1 == NULL || node2 == NULL)
        return;
    struct node* left1 = node1->left;
    struct node* left2 = node2->left;
    left1->right = node2;
    node2->left = left1;
    left2->right = node1;
    node1->left = left2;
}


struct fibheap *fibheap_union(struct fibheap *heap1, struct fibheap *heap2) {
    if (heap1 == NULL)
        return heap2;
    if (heap2 == NULL)
        return heap1;
    struct fibheap *heap = malloc(sizeof(struct fibheap));
    heap->min = heap1->min;
    fibheap_link_lists(heap1->min, heap2->min);
    if (heap1->min == NULL || (heap2->min != NULL && heap2->min->key < heap->min->key))
        heap->min = heap2->min;
    heap->nnodes = heap1->nnodes + heap2->nnodes;
    free(heap1);
    free(heap2);
    return heap;
}

void fibheap_remove_node_from_root_list(struct node *node, struct fibheap *heap) {
    if (heap == NULL || node == NULL)
        return;
    if (node->parent != NULL)
        return;
    if (node->left == node)
        heap->min = NULL;
    else{
        node->left->right = node->right;
        node->right->left = node->left;
        if (node == heap->min) 
        {
            if (node->right == node) {
                heap->min = NULL;
            } else {
                heap->min = node->right;
            }
        }
    }
}

void fibheap_link(struct fibheap *heap, struct node *tmp, struct node *chiled_minimal) {
    fibheap_remove_node_from_root_list(tmp, heap);
    tmp->left = tmp->right = tmp;
    tmp->parent = chiled_minimal;
    if (chiled_minimal->child) {
        fibheap_link_lists(chiled_minimal->child, tmp);
    } else {
        chiled_minimal->child = tmp;
    }
    chiled_minimal->degree++;
    tmp->mark = 0;
}

void consolidate(struct fibheap *heap) {
    int max_degree = floor(log2(heap->nnodes));
    struct node** root = calloc(max_degree+1, sizeof(struct node*));
    struct node *node_min = heap->min;
    do {
        int node_min_degree = node_min->degree;
        while (root[node_min_degree] != NULL) {
            struct node * temp = root[node_min_degree];
            if (node_min->key > temp->key) {
                struct node * tmp = node_min;
                node_min = temp;
                temp = tmp;
            }
            if (temp == heap->min) {
                heap->min = node_min;
            }
            fibheap_link(heap, temp, node_min);
            if (node_min->right == node_min) {
                heap->min = node_min;
            }
            root[node_min_degree] = NULL;
            node_min_degree++;
        }
        root[node_min_degree] = node_min;
        node_min = node_min->right;
    } while (node_min != heap->min);
    heap->min = NULL;
    for (int i = 0; i <= max_degree; i++) {
        if (root[i] != NULL) {
            if (heap->min == NULL || root[i]->key < heap->min->key)
                heap->min = root[i];
        }
    }
    free(root);
}

void fibheap_cut(struct fibheap *heap, struct node *node, struct node *parent) {
    if (node->right == node)
        parent->child = NULL;
    else {
        parent->child = node->right;
        node->right->left = node->left;
        node->left->right = node->right;
    }
    node->left = heap->min;
    node->right = heap->min->right;
    heap->min->right = node;
    node->right->left = node;
    
    node->parent = NULL;
    node->mark = 0;
}

void fibheap_cascading_cut(struct fibheap *heap, struct node *node) {
    struct node *parent = node->parent;
    if (parent == NULL)
        return;
    if (node->mark == 0) {
        node->mark = 1;
    }
    else {
        fibheap_cut(heap, node, parent);
        fibheap_cascading_cut(heap, parent);
    }
}

int get_degree(struct node *node){
    int max = 0;
    struct node *node_child = node->child;
    while (node_child) {
        if(node_child->degree > max)
            max = node_child->degree;
        node_child = node_child->right;
        if (node_child == node->child || node_child == node) {
            node_child = NULL;
        }
    }
    return max; 
}

void fibheap_decrease_key(struct fibheap *heap, struct node *node, int newkey) {
    if (newkey > node->key)
        return;
    node->key = newkey;
    struct node *parent = node->parent;
    if(parent != NULL)
        parent->degree = get_degree(parent);
    if (parent != NULL && node->key < parent->key) {
        fibheap_cut(heap, node, parent);
        fibheap_cascading_cut(heap, parent);
    }
    if (node->key < heap->min->key)
        heap->min = node;
}


struct node *fibheap_delete_min(struct fibheap *heap) {
    struct node *minimal = heap->min;
    if (minimal == NULL) {
        return NULL;
    }
    for (struct node* child_minimal = minimal->child; child_minimal != NULL; child_minimal = child_minimal->right) {
        fibheap_add_to_root_list(child_minimal, heap->min);
        child_minimal->parent = NULL;
        if (child_minimal->right == minimal->child || child_minimal->right == minimal) {
            child_minimal->right = NULL;
        }
    }
    fibheap_remove_node_from_root_list(minimal, heap);
    if (minimal == minimal->right) {
        heap->min = NULL;
    } else {
        heap->min = minimal->right;
        consolidate(heap);
    }
    heap->nnodes -= 1;
    return minimal;
}

struct node *fibheap_find_node_child(struct node *node, int key) {
    if (node == NULL) {
        return NULL;
    }
    if (node->key == key) {
        return node;
    }
    struct node *child_node = node->child;
    if (child_node != NULL) {
        do {
            struct node *found = fibheap_find_node_child(child_node, key);
            if (found) {
                return found;
            }
            child_node = child_node->right;
        } while (child_node != node->child);
    }
    return NULL;
}


struct node* fibheap_find_node(struct fibheap *heap, int key) {
    if (heap == NULL || heap->min == NULL)
        return NULL;
    struct node *min_node = heap->min;
    struct node *node = min_node;
    do {
        if (node->key == key) 
            return node;
        if (node->child != NULL) {
            struct node *child_node = node->child;
            do {
                struct node *found = fibheap_find_node_child(child_node, key);
                if (found)
                    return found;
                child_node = child_node->right;
            } while (child_node != node->child);
        }
        node = node->right;
    } while (node != min_node);
    return NULL;
}

struct fibheap *fibheap_delete(struct fibheap *heap, int key) {
    struct node * node = fibheap_find_node(heap, key);
    fibheap_decrease_key(heap, node, (int)-INFINITY);
    fibheap_delete_min(heap);
    return heap;
}

void print_heap(struct node *node) {
    if (node == NULL) {
        printf("Heap is NULL\n");
        return;
    }
    struct node *tmp = node;
    do {
        if (tmp->child == NULL && tmp->parent != NULL) 
        {
            printf("Node(%d): parent(%d), no child\n", tmp->key,tmp->parent->key);
        } 
        else if(tmp->child == NULL && tmp->parent == NULL)
        {
            printf("Node(%d): no parent, no child\n", tmp->key);
        } 
        else if(tmp->child != NULL && tmp->parent == NULL){
            printf("Node(%d): no parent, child(%d)\n", tmp->key,tmp->child->key);
            print_heap(tmp->child);
        }
        else if(tmp->child != NULL && tmp->parent != NULL){
            printf("Node(%d):parent(%d), child (%d)\n", tmp->key,tmp->parent->key, tmp->child->key);
            print_heap(tmp->child);
        }
        tmp = tmp->right;
    } while (tmp != node);
}