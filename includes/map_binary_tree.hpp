#ifndef MAP_BINARY_TREE_HPP
#define MAP_BINARY_TREE_HPP

#pragma once

#include <cstdlib>
#include "pair.hpp"

namespace ft
{

	template <class Pair>
	struct binary_tree
	{
		struct binary_tree *parent;
		struct binary_tree *left;
		struct binary_tree *right;
		Pair val;

		explicit binary_tree() : parent(NULL), left(NULL), right(NULL), val() {}
		explicit binary_tree(const Pair &value) : parent(NULL), left(NULL), right(NULL),
												  val(value) {}
		binary_tree(const binary_tree &x) : parent(x.parent), left(x.left),
											right(x.right), val(x.val) {}
		~binary_tree() {}

		binary_tree &operator=(const binary_tree &x)
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

		binary_tree *min_node(binary_tree *node)
		{
			if (!node)
				return (NULL);
			while (node->left)
				node = node->left;
			return (node);
		}

		binary_tree *max_node(binary_tree *node)
		{
			if (!node)
				return (NULL);
			while (node->right)
				node = node->right;
			return (node);
		}

		binary_tree *next_node()
		{
			binary_tree *temp = this;
			binary_tree *temp_parent = temp->parent;

			if (temp->right)
				return (min_node(temp->right));
			while (temp_parent && temp == temp_parent->right)
			{
				temp = temp_parent;
				temp_parent = temp_parent->parent;
			}
			return (temp_parent);
		}

		binary_tree *prev_node()
		{
			binary_tree *temp = this;
			binary_tree *temp_parent = temp->parent;

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
