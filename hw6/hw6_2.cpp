

#include <stdio.h>
#include <stdlib.h>
//#include "avl.h"
extern "C"
{
#include "avl.h"
#include "bst.h"
#include "rb.h"
}

#include <iostream>
#include <string>

#define N 128
using namespace std;


void preorder_integer_avl(const struct avl_node *node)
{
	if (node == NULL)
		return ;
	printf ("%d ", *( (int *) node->avl_data ) );
	if (node->avl_link[0] != NULL || node->avl_link[1] != NULL)
	{
		putchar ('(');
		preorder_integer_avl ( node->avl_link[0] );
		putchar (',');
		putchar (' ');
		preorder_integer_avl ( node->avl_link[1] );
		putchar (')');
	}
}

int int_compare(const void *pa, const void *pb, void *param)
{
	int a = *(const int *)pa ;
	int b = *(const int *)pb ;
	
	if (a < b) 
		return -1;
	else if (a > b)
		return +1;
	else 
		return 0 ;
}

int str_compare(const void *pa, const void *pb, void *param)
{
	string a = *(const string *)pa;
	string b = *(const string *)pb;

	if (a < b) 
		return -1;
	else if (a > b)
		return +1;
	else 
		return 0 ;
}

void preorder_string_avl(const struct avl_node *node)
{
	if (node == NULL)
		return ;
	cout << *((string *) node->avl_data) << " ";
	if (node->avl_link[0] != NULL || node->avl_link[1] != NULL)
	{
		putchar ('(');
		preorder_string_avl( node->avl_link[0] );
		putchar (',');
		putchar (' ');
		preorder_string_avl( node->avl_link[1] );
		putchar (')');
	}
}

void preorder_string_bst(const struct bst_node *node)
{
	if (node == NULL)
		return ;
	cout << *((string *) node->bst_data) << " ";
	if (node->bst_link[0] != NULL || node->bst_link[1] != NULL)
	{
		putchar ('(');
		preorder_string_bst( node->bst_link[0] );
		putchar (',');
		putchar (' ');
		preorder_string_bst( node->bst_link[1] );
		putchar (')');
	}
}

void preorder_string_rb(const struct rb_node *node)
{
	if (node == NULL)
		return ;
	cout << *((string *) node->rb_data) << " ";
	if (node->rb_link[0] != NULL || node->rb_link[1] != NULL)
	{
		putchar ('(');
		preorder_string_rb( node->rb_link[0] );
		putchar (',');
		putchar (' ');
		preorder_string_rb( node->rb_link[1] );
		putchar (')');
	}
}

int main() 
{
	struct avl_table *avl_tree;
	avl_tree = avl_create(str_compare, NULL, NULL);

	struct bst_table *bst_tree;
	bst_tree = bst_create(str_compare, NULL, NULL);

	struct rb_table *rb_tree;
	rb_tree = rb_create(str_compare, NULL, NULL);

	int i;
	for (i = 0; i <= 31; i++)
	{
		string *element = new string;
		cin >> *element;
		void **p_avl = avl_probe(avl_tree, element);
		void **p_bst = bst_probe(bst_tree, element);
		void **p_rb = rb_probe(rb_tree, element);
	}

	preorder_string_avl(avl_tree->avl_root);
	cout << endl;
	preorder_string_bst(bst_tree->bst_root);
	cout << endl;
	preorder_string_rb(rb_tree->rb_root);
	puts("");
	return 0;
}



