//DSA2015
//hw6_3

//ddd
//2015.6.7

#include <stdio.h>
#include <stdlib.h>

//#include "avl.h"
extern "C"
{
#include "avl_ntudsa.h"
}

#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define N 100000
#define M 200000
#define P 100000000
#define S 1000000000000


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

void preorder_integer_avl(const struct avl_node *node)
{
	if (node == NULL)
		return ;
	printf ("%d ", node->avl_data);
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

void link_integer_avl(struct avl_node *node_x, struct avl_table *tree_y)
{
	if (node_x == NULL || tree_y == NULL)
	{
		return;
	}

	for (int i = 1; i <= node_x->avl_cnt; i++)
	{
		int *p_link_avl = avl_probe(tree_y, node_x->avl_data);
	}
	
	if (node_x->avl_link[0] != NULL || node_x->avl_link[1] != NULL)
	{
		link_integer_avl(node_x->avl_link[0], tree_y);
		link_integer_avl(node_x->avl_link[1], tree_y);
	}
}

struct avl_table *union_integer_avl(struct avl_table *tree_x, struct avl_table *tree_y)
{
	if (tree_x == NULL || tree_y == NULL)
	{
		return tree_x;
	}

	if (tree_x->avl_count > tree_y->avl_count)
	{
		//insert y to x
		link_integer_avl(tree_y->avl_root, tree_x);
		return tree_x;
	}
	else
	{
		//insert x to y
		link_integer_avl(tree_x->avl_root, tree_y);
		return tree_y;
	}
}

void max_number_avl(struct avl_node *node, long long s, int &max_number)
{
	if (node == NULL)
	{
		return;
	}

	if (s < node->avl_sum[0])
	{
		max_number_avl(node->avl_link[0], s, max_number);
	}
	else if (s >= node->avl_sum[0])
	{
		max_number = max_number + node->avl_cnode[0];
		s = s - node->avl_sum[0];
		if (s < node->avl_data)
		{
			return;
		}
		else if (s >= node->avl_data)
		{
			long long node_total_price;
			node_total_price = node->avl_data * node->avl_cnt;
			if (s < node_total_price)
			{
				max_number = max_number + (s / node->avl_data);
				return;
			}
			else if (s >= node_total_price)
			{
				max_number = max_number + node->avl_cnt;
				s = s - node_total_price;
				max_number_avl(node->avl_link[1], s, max_number);
			}			
		}
	}
	return;
}

//disjoint-set forest
int set_rank[N];  
int parent[N];
  
void makeSet(int x)  
{  
    parent[x] = x;  
    set_rank[x] = 0; 
}  
  
int findSet(int x) 
{  
    if (x != parent[x])  // path compression  
	{
		parent[x] = findSet(parent[x]);  
	}
	return parent[x];  
} 

void linkSet(int x, int y)  
{  
    if (set_rank[x] > set_rank[y])  //union by rank  
	{
		parent[y] = x;
		//owner[y] = owner[x];
	}  
    else 
	{  
        parent[x] = y;
		//owner[y] = owner[x];
        if (set_rank[x] == set_rank[y])  
            set_rank[y] = set_rank[y] + 1;  
    }  
}  
  
void unionSet(int x, int y)  
{  
    linkSet(findSet(x), findSet(y));
}  

int main() 
{
	int n, m;
	cin >> n;
	cin >> m;

	vector<struct avl_table *> price_tree_vector;
	struct avl_table *avl_tree_price;
	avl_tree_price = avl_create(int_compare, NULL, NULL);
	price_tree_vector.push_back(avl_tree_price);
	
	vector<long long> price_vector;
	price_vector.push_back(0);
	for (int i = 1; i <= n; i++)
	{
		long long price_i;
		cin >> price_i;
		price_vector.push_back(price_i);
	}

	for (int i = 1; i <= n; i++)
	{
		avl_tree_price = avl_create(int_compare, NULL, NULL);
		int *p_avl = avl_probe(avl_tree_price, price_vector[i]);
		price_tree_vector.push_back(avl_tree_price);
		//preorder_integer_avl(price_tree_vector[i]->avl_root);
	}

	int owner[N];
	for (int i = 1;	i <= n; i++)
	{
		makeSet(i);
		owner[i] = i;
	}

	for (int j = 1; j <= m; j++)
	{
		int incident;
		cin >> incident;
		if (incident == 1)
		{
			int current_game;
			int interest_game;
			cin >> current_game;
			cin >> interest_game;

			int current_owner;
			int interest_owner;
			current_owner = owner[ findSet(current_game) ];
			interest_owner = owner[ findSet(interest_game) ];
			if (current_owner != interest_owner)
			{
				linkSet( findSet(current_game), findSet(interest_game) );
				owner[ findSet(interest_game) ] = current_owner;
				
				struct avl_table *price_tree_union;
				price_tree_union = union_integer_avl(price_tree_vector[current_owner], price_tree_vector[interest_owner]);				
				price_tree_vector[current_owner] = price_tree_union;
				price_tree_vector[interest_owner] = NULL;

				//preorder_integer_avl(price_tree_vector[current_owner]->avl_root);			
				//cout << price_tree_vector[current_owner]->avl_root->avl_cnt << endl;
			}
		}

		else if (incident == 2)
		{
			int current_game2;
			long long money;
			cin >> current_game2;
			cin >> money;

			int current_owner2;
			current_owner2 = owner[ findSet(current_game2) ];

			//search in tree: price_tree_vector[current_owner2]
			int max_number;
			max_number = 0;
			max_number_avl(price_tree_vector[current_owner2]->avl_root, money, max_number);

			cout << current_owner2 << " " << max_number <<endl;
		}
	}
	
	return 0;
}



