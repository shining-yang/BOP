/*
 * Output the maximum path sum within a binary tree
 */
#include <stdlib.h>
#include <stdio.h>

#ifndef INT_MIN
#define INT_MIN	(-(int)(~0U >> 1) - 1)
#endif

int max(int a, int b)
{
	return a > b ? a : b;
}

struct bi_node_t {
	int	data;
	struct bi_node_t	*left, *right;
};

struct bi_node_t* alloc_bi_node(int data)
{
	struct bi_node_t* node = (struct bi_node_t*)malloc(sizeof(struct bi_node_t));
	if (node != NULL) {
		node->data = data;
		node->left = NULL;
		node->right = NULL;
	}

	return node;
}

void free_bi_node(struct bi_node_t* node)
{
	if (node != NULL) {
		free_bi_node(node->left);
		free_bi_node(node->right);
		free(node);
	}
}

double g_max_path_sum = INT_MIN;

int find_max_path_sum(struct bi_node_t* tree)
{
	int s, l, r; // self, left, right

	if (tree == NULL) { // use 0 for empty node
		return 0;
	}

	s = tree->data;
	l = find_max_path_sum(tree->left);
	r = find_max_path_sum(tree->right);

	// choose at most ONE path
	int max_path = max(s, max(l, r) + s);

	int max_path_top = max(max_path, s + l + r);
	g_max_path_sum = max(g_max_path_sum, max_path_top);

	return max_path;
}

void main()
{
	struct bi_node_t* t = NULL;
	t = alloc_bi_node(10);
	t->left = alloc_bi_node(2);
	t->right = alloc_bi_node(10);
	t->left->left = alloc_bi_node(20);
	t->left->right = alloc_bi_node(1);
	t->right->right = alloc_bi_node(-25);
	t->right->right->left = alloc_bi_node(3);
	t->right->right->right = alloc_bi_node(4);

	find_max_path_sum(t);
	printf("MAX PATH SUM is: %f\n", g_max_path_sum);

	free_bi_node(t);
}
