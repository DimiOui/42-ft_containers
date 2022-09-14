#ifndef MAP_BST_HPP
# define MAP_BST_HPP

#pragma once

#include <cstdlib>
#include "pair.hpp"

namespace ft
{

	template <class Pair>
	struct search_tree_node
	{
		struct search_tree_node* parent;
		struct search_tree_node* left;
		struct search_tree_node* right;
		Pair val;

		explicit search_tree_node() : parent(NULL), left(NULL), right(NULL), val() {}
		explicit search_tree_node(const Pair& value) : parent(NULL), left(NULL), right(NULL),
											val(value) {}
		search_tree_node(const search_tree_node& x) : parent(x.parent), left(x.left),
									right(x.right), val(x.val) {}
		~search_tree_node() {}

		search_tree_node& operator= (const search_tree_node& x)
		{
			if (this != &x)
			{
				parent = x.parent;
				left = x.left;
				right = x.right;
				val = x.val;
			}
			return (*this);
		}

		search_tree_node* min_node(search_tree_node *node)
		{
			if (!node)
				return (NULL);
			while (node->left)
				node = node->left;
			return (node);
		}

		search_tree_node* max_node(search_tree_node *node)
		{
			if (!node)
				return (NULL);
			while (node->right)
				node = node->right;
			return (node);
		}

		search_tree_node* next_node()
		{
			search_tree_node* temp = this;
			search_tree_node* temp_parent = temp->parent;

			if (temp->right)
				return (min_node(temp->right));
			while (temp_parent && temp == temp_parent->right)
			{
				temp = temp_parent;
				temp_parent = temp_parent->parent;
			}
			return (temp_parent);
		}

		search_tree_node* prev_node()
		{
			search_tree_node* temp = this;
			search_tree_node* temp_parent = temp->parent;

			if (temp->left)
				return (max_node(temp->left));
			while (temp_parent && temp == temp->left)
			{
				temp = temp_parent;
				temp_parent = temp_parent->parent;
			}
			return (temp_parent);
		}
	};
}

#endif
