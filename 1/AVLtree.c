#include <stdlib.h>
#include "AVLtree.h"

int count_delete = 0;
int count_elements = 1;

struct avltree *avltree_create(int key, char *value)
{
	struct avltree *node;
	node = malloc(sizeof(*node));
	if (node)
	{
		node->key = key;
		node->value = value;
		node->left = NULL;
		node->right = NULL;
		node->height = 0;
		node->is_visited = 0;
		node->deleted = 0;
	}
	return node;
}

int search_max(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}

int avltree_height(struct avltree *tree)
{
	if (tree)
		return tree->height;
	else
		return -1;
}

int avltree_balance(struct avltree *tree)
{
	return avltree_height(tree->left) - avltree_height(tree->right);
}

struct avltree *avltree_right_rotate(struct avltree *tree)
{
	struct avltree *left;
	left = tree->left;
	tree->left = left->right;
	left->right = tree;
	tree->height =  search_max(avltree_height(tree->left), avltree_height(tree->right)) + 1;
	left->height =  search_max(avltree_height(left->left), tree->height) + 1;
	return left;
}

struct avltree *avltree_left_rotate(struct avltree *tree)
{
	struct avltree *right;
	right = tree->right;
	tree->right = right->left;
	right->left = tree;
	tree->height =  search_max(avltree_height(tree->left), avltree_height(tree->right)) + 1;
	right->height =  search_max(avltree_height(right->right), tree->height) + 1;
	return right;
}

struct avltree *avltree_leftright_rotate(struct avltree *tree)
{
	tree->left = avltree_left_rotate(tree->left);
	return avltree_right_rotate(tree);
}

struct avltree *avltree_rightleft_rotate(struct avltree *tree)
{
	tree->right = avltree_right_rotate(tree->right);
	return avltree_left_rotate(tree);
}

struct avltree *avltree_add(struct avltree *tree, int key, char *value)
{
	if (!tree)
	{
		return avltree_create(key, value);
	}
	if (key < tree->key)
	{
		tree->left = avltree_add(tree->left, key, value);
		if (avltree_balance(tree) == 2)
		{
			if (key < tree->left->key)
			{
				tree = avltree_right_rotate(tree);
			}
			else
			{
				tree = avltree_leftright_rotate(tree);
			}
		}
		tree->height =  search_max(avltree_height(tree->left), avltree_height(tree->right)) + 1;
		count_elements++;
	}
	else if (key > tree->key)
	{
		tree->right = avltree_add(tree->right, key, value);
		if (avltree_balance(tree) == -2)
		{
			if (key > tree->right->key)
			{
				tree = avltree_left_rotate(tree);
			}
			else
			{
				tree = avltree_rightleft_rotate(tree);
			}
		}
		tree->height =  search_max(avltree_height(tree->left), avltree_height(tree->right)) + 1;
		count_elements++;
	}
	else if (key == tree->key && tree->deleted == 1)
	{
		tree->deleted = 0;
		count_delete--;
		count_elements++;
	}
	return tree;
}

struct avltree *avltree_lookup(struct avltree *tree, int key)
{
	while (tree)
	{
		if (key == tree->key && tree->deleted == 0)
		{
			return tree;
		}
		else if (key < tree->key)
		{
			tree = tree->left;
		}
		else if (key > tree->key)
		{
			tree = tree->right;
		}
		else
		{
			return NULL;
		}
	}
	return tree;
}

void avltree_free(struct avltree *tree)
{
	if (!tree)
		return;
	avltree_free(tree->left);
	avltree_free(tree->right);
	free(tree);
}

struct avltree *avltree_delete(struct avltree *tree, int key)
{
	if (!tree)
	{
		return tree;
	}
	avltree_lookup(tree, key)->deleted = 1;
	count_delete++;
	if (count_delete >= count_elements / 3){
	   	struct avltree *new_tree = avltree_create(tree->key,tree->value);
		new_tree = avltree_copy(tree,new_tree);
		avltree_free(tree);
	   	return new_tree;
	}
	return tree;
}

struct avltree *avltree_copy(struct avltree *tree, struct avltree *new_tree)
{
	if (tree == NULL)
		return tree;
	struct avltree *right = tree->right;
	struct avltree *left = tree->left;
	if (tree->deleted == 0)
	{
		new_tree = avltree_add(new_tree, tree->key, tree->value);
	}
	if (left && right)
	{
		avltree_copy(left, new_tree);
		avltree_copy(right, new_tree);
	}
	else if (left)
		avltree_copy(left, new_tree);
	else if (right)
		avltree_copy(right, new_tree);
	return new_tree;
}

struct avltree *avltree_min(struct avltree *tree)
{
	if (!tree)
		return NULL;
	while (tree->left)
	{
		if (tree->left->deleted == 1 && tree->left->left == NULL)
			return tree;
		tree = tree->left;
	}
	return tree;
}
struct avltree *avltree_max(struct avltree *tree)
{
	if (!tree)
		return NULL;
	while (tree->right)
	{
		if (tree->right->deleted == 1 && tree->right->right == NULL)
			return tree;
		tree = tree->right;
	}
	return tree;
}

void avltree_is_visited_clear(struct avltree *tree)
{
	if (tree)
	{
		tree->is_visited = 0;
		avltree_is_visited_clear(tree->right);
		avltree_is_visited_clear(tree->left);
	}
}

void avltree_print_dfs(struct avltree *tree)
{
	if (tree == NULL)
		return;
	if (tree->is_visited == 0 && tree->deleted == 0)
		printf("height=%d:value %s key %d %c\n", avltree_height(tree), tree->value,tree->key, tree->direction);
	tree->is_visited = 1;
	if (tree->left)
	{
		tree->left->direction = 'L';
		avltree_print_dfs(tree->left);
	}
	if (tree->right)
	{
		tree->right->direction = 'R';
		avltree_print_dfs(tree->right);
	}
	avltree_is_visited_clear(tree);
}