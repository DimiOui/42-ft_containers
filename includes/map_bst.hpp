#ifndef MAP_BST_HPP
# define MAP_BST_HPP

#pragma once

#include <cstdlib>
#include "pair.hpp"

namespace ft
{

	template <class Pair>
	struct BST_node
	{
		struct BST_node* parent;
		struct BST_node* left;
		struct BST_node* right;
		Pair val;

		explicit BST_node() : parent(NULL), left(NULL), right(NULL), val() {}
		explicit BST_node(const Pair& data) : parent(NULL), left(NULL), right(NULL),
											val(data) {}
		BST_node(const BST_node& x) : parent(x.parent), left(x.left),
									right(x.right), val(x.val) {}
		~BST_node() {}

		BST_node& operator= (const BST_node& x)
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

		BST_node* min_node(BST_node *node)
		{
			if (!node)
				return (NULL);
			while (node->left)
				node = node->left;
			return (node);
		}

		BST_node* max_node(BST_node *node)
		{
			if (!node)
				return (NULL);
			while (node->right)
				node = node->right;
			return (node);
		}

		BST_node* next_node()
		{
			BST_node* temp = this;
			BST_node* temp_parent = temp->parent;

			if (temp->right)
				return (min_node(temp->right));
			while (temp_parent && temp == temp_parent->right)
			{
				temp = temp_parent;
				temp_parent = temp_parent->parent;
			}
			return (temp_parent);
		}

		BST_node* prev_node()
		{
			BST_node* temp = this;
			BST_node* temp_parent = temp->parent;

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
