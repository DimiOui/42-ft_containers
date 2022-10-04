#ifndef MAP_BINARY_TREE_HPP
#define MAP_BINARY_TREE_HPP

#pragma once

#include <cstdlib>
#include "pair.hpp"


namespace ft
{
	struct tree_node
	{
		struct tree_node *parent;
		struct tree_node *left;
		struct tree_node *right;
		std::size_t color;
		void* val;

		explicit tree_node() : parent(NULL), left(NULL), right(NULL), color(0), val(NULL) {}
		tree_node(const tree_node &x) : parent(x.parent), left(x.left),
											right(x.right), color(x.color), val(x.val) {}
		~tree_node() {}

		tree_node &operator=(const tree_node &x)
		{
			if (this != &x)
			{
				parent = x.parent;
				left = x.left;
				right = x.right;
				color = x.color;
				val = x.val;
			}
			return (*this);
		}

		tree_node *min_tree_node(tree_node *node, tree_node *prev)
		{
			if (node->val != NULL && prev->val != NULL)
				while (node->left)
					node = node->left;
			return (node);
		}

		tree_node *max_tree_node(tree_node *node, tree_node *prev)
		{
			if (node->val != NULL && prev->val != NULL)
				while (node->right)
					node = node->right;
			return (node);
		}

		tree_node *next_node()
		{
			tree_node *temp = this;
			tree_node *prev;

			if (temp->right)
			{
				prev = temp;
				temp = temp->right;
				temp = temp->min_tree_node(temp, prev);
			}
			else
			{
				while (temp->parent
						&& temp == temp->parent->right)
					temp = temp->parent;
				temp = temp->parent;
			}
			return(temp);
		}

		tree_node *prev_node()
		{
			tree_node *temp = this;
			tree_node *prev;

			if (temp->left)
			{
				prev = temp;
				temp = temp->left;
				temp = temp->max_tree_node(temp, prev);
			}
			else
			{
				while (temp->parent
						&& temp == temp->parent->left)
					temp = temp->parent;
				temp = temp->parent;
			}
			return (temp);
		}
	};
}

#endif
