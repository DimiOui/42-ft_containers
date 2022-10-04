#ifndef MAP_HPP
#define MAP_HPP

#pragma once

#include "../iterators/map_iterator.hpp"
#include "../utils/map_binary_tree.hpp"
#include "../utils/lexicographical_compare.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
			  class Alloc = std::allocator<pair<const Key, T> > >
	class map
	{
	public:
		//	MEMBER TYPES
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef map_iterator<tree_node, value_type> iterator;
		typedef const_map_iterator<tree_node, const value_type, iterator> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;
		typedef typename allocator_type::template rebind<tree_node>::other tree_allocator_type;

		//	VALUE COMPARE
		class value_compare
		{
			friend class map;

		protected:
			Compare _comp;
			value_compare(Compare c) : _comp(c) {}

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return (_comp(x.first, y.first));
			}
		};

		//	MEMBER FUNCTIONS
		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type()) : _comp(comp), _size(0), _alloc(alloc),
																	   _root(NULL)
		{
			//	Constructs an empty container, with no elements.
			_leaf = _tree_alloc.allocate(1);
			_tree_alloc.construct(_leaf, tree_node());
			_leaf->color = 2;
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : _comp(comp), _size(0), _alloc(alloc),
															  _root(NULL)
		{
			//	Constructs a container with as many elements as the range.
			_leaf = _tree_alloc.allocate(1);
			_tree_alloc.construct(_leaf, tree_node());
			_leaf->color = 2;
			insert(first, last);
			_leaf->right = min_node(_root);
			_leaf->left = max_node(_root);
			min_node(_root)->left = _leaf;
			max_node(_root)->right = _leaf;
		}

		map(const map &x) : _comp(x.key_comp()), _size(0), _alloc(x.get_allocator()),
							_root(NULL)
		{
			//	Constructs a container with a copy of each of the elements in x.
			_leaf = _tree_alloc.allocate(1);
			_tree_alloc.construct(_leaf, tree_node());
			_leaf->color = 2;
			insert(x.begin(), x.end());
			_leaf->right = min_node(_root);
			_leaf->left = max_node(_root);
			min_node(_root)->left = _leaf;
			max_node(_root)->right = _leaf;
		}

		~map()
		{
			clear();
			_tree_alloc.destroy(_leaf);
			_tree_alloc.deallocate(_leaf, 1);
		}

		map &operator=(const map &x)
		{
			if (this != &x)
			{
				try
				{
					clear();
					_comp = x.key_comp();
					_size = 0;
					_alloc = x.get_allocator();
					_tree_alloc = x._tree_alloc;
					insert(x.begin(), x.end());
				}
				catch (const std::exception &e)
				{
					std::cerr << e.what() << '\n';
				}
			}
			return (*this);
		}

		//	ITERATORS
		iterator begin()
		{
			if (!_size)
				return (end());
			return (iterator(_leaf->right));
		}
		const_iterator begin() const
		{
			if (!_size)
				return (end());
			return (const_iterator(_leaf->right));
		}
		iterator end() { return (iterator(_leaf)); }
		const_iterator end() const { return (const_iterator(_leaf)); }
		reverse_iterator rbegin() { return (reverse_iterator(end())); }
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }
		reverse_iterator rend() { return (reverse_iterator(begin())); }
		const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

		//	CAPACITY
		bool empty() const { return (!_root); }
		size_type size() const { return (this->_size); }
		size_type max_size() const { return (this->_tree_alloc.max_size()); }

		//	ELEMENT ACCESS
		mapped_type &operator[](const key_type &k)
		{
			return ((this->insert(ft::make_pair(k, mapped_type())).first)->second);
		}

		//	MODIFIERS
		pair<iterator, bool> insert(const value_type &val)
		{
			iterator it = find(val.first);
			;
			bool ret;

			if (it == end())
			{
				insert_node(val);
				ret = true;
				it = find(val.first);
			}
			else
				ret = false;
			return (ft::make_pair(it, ret));
		}

		iterator insert(iterator position, const value_type &val)
		{
			(void(position));
			return (this->insert(val).first);
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (InputIterator it = first; it != last; it++)
				insert(*it);
		}

		void erase(iterator position)
		{
			delete_node(search_tree(_root, position->first));
		}

		size_type erase(const key_type &key)
		{
			return (find(key) != end() ? (erase(find(key)), true) : false);
		}

		void erase(iterator first, iterator last)
		{
			iterator it = first++;

			while (it != last)
			{
				delete_node(search_tree(_root, it->first));
				it = first++;
			}
		}

		void swap(map &x)
		{
			typename Alloc::template rebind<tree_node>::other
				tmp_tree_alloc = this->_tree_alloc;
			Alloc tmp_alloc = this->_alloc;
			Compare tmp_comp = this->_comp;
			size_type tmp_size = this->_size;
			tree_node *tmp_root = this->_root;
			tree_node *tmp_leaf = this->_leaf;

			if (x == *this)
				return;
			this->_tree_alloc = x._tree_alloc;
			this->_alloc = x._alloc;
			this->_comp = x._comp;
			this->_size = x._size;
			this->_root = x._root;
			this->_leaf = x._leaf;

			x._tree_alloc = tmp_tree_alloc;
			x._alloc = tmp_alloc;
			x._comp = tmp_comp;
			x._size = tmp_size;
			x._root = tmp_root;
			x._leaf = tmp_leaf;
		}

		void clear()
		{
			clear_tree(_root);
			_size = 0;
			_root = NULL;
		}

		//	OBSERVERS
		key_compare key_comp() const { return (key_compare()); }
		value_compare value_comp() const { return (value_compare(key_compare())); }

		//	OPERATIONS
		iterator find(const key_type &k)
		{
			tree_node *node = search_tree(_root, k);

			if (!node)
				return (end());
			return (iterator(node));
		}

		const_iterator find(const key_type &k) const
		{
			tree_node *node = search_tree(_root, k);

			if (!node)
				return (end());
			return (const_iterator(node));
		}

		size_type count(const key_type &k) const
		{
			if (this->find(k) == this->end())
				return (false);
			return (true);
		}

		iterator lower_bound(const key_type &k)
		{
			iterator it = this->begin();

			while (it != this->end() && _comp(it->first, k))
				it++;
			return (it);
		}

		const_iterator lower_bound(const key_type &k) const
		{
			const_iterator it = this->begin();

			while (it != this->end() && _comp(it->first, k))
				it++;
			return (it);
		}

		iterator upper_bound(const key_type &k)
		{
			reverse_iterator it = this->rbegin();

			while (it != this->rend() && _comp(k, it->first))
				it++;
			return (it.base());
		}

		const_iterator upper_bound(const key_type &k) const
		{
			const_reverse_iterator it = this->rbegin();

			while (it != this->rend() && _comp(k, it->first))
				it++;
			return (it.base());
		}

		pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
		}

		pair<iterator, iterator> equal_range(const key_type &k)
		{
			return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
		}

		//	ALLOCATOR
		allocator_type get_allocator() const { return (this->_alloc); }

	private:
		tree_allocator_type _tree_alloc;
		key_compare _comp;
		size_type _size;
		allocator_type _alloc;
		tree_node *_root;
		tree_node *_leaf;

		//	RED_BLACK_TREE FUNCTIONS
		void clear_tree(tree_node *node)
		{
			_size--;
			if (node && node != _leaf)
			{
				if (node->left && node->left != _leaf)
					clear_tree(node->left);
				if (node->right && node->right != _leaf)
					clear_tree(node->right);
				_alloc.destroy(static_cast<pair<const Key, T> *>(node->val));
				_alloc.deallocate(static_cast<pair<const Key, T> *>(node->val), 1);
				_tree_alloc.destroy(node);
				_tree_alloc.deallocate(node, 1);
			}
		}

		tree_node *min_node(tree_node *node) const
		{
			while (node->left && node->left != _leaf)
				node = node->left;
			return (node);
		}

		tree_node *max_node(tree_node *node) const
		{
			while (node->right && node->right != _leaf)
				node = node->right;
			return (node);
		}

		tree_node *search_tree(tree_node *root, Key key) const
		{
			if (root == NULL || root == _leaf ||
				static_cast<value_type *>(root->val)->first == key)
				return (root);
			if (_comp(static_cast<value_type *>(root->val)->first, key))
				return (search_tree(root->right, key));
			return (search_tree(root->left, key));
		}

		void left_rotate(tree_node *P)
		{
			tree_node *N = P->right;
			tree_node *temp;

			if (N->left && N->left != _leaf)
				N->left->parent = P;
			N->parent = P->parent;
			if (!P->parent)
				_root = N;
			else if (P == P->parent->right)
				P->parent->right = N;
			else
				P->parent->left = N;
			P->parent = N;
			temp = N->left;
			N->left = P;
			P->right = temp;
		}

		void right_rotate(tree_node *P)
		{
			tree_node *N = P->left;
			tree_node *temp;

			if (N->right && N->right != _leaf)
				N->right->parent = P;
			N->parent = P->parent;
			if (!P->parent)
				_root = N;
			else if (P == P->parent->right)
				P->parent->right = N;
			else
				P->parent->left = N;
			P->parent = N;
			temp = N->right;
			N->right = P;
			P->left = temp;
		}

		void swap_val(tree_node *node1, tree_node *node2)
		{
			tree_node *temp = node1->parent;
			tree_node *temp2 = node2->parent;
			std::size_t temp_color;

			node2->parent = temp;
			node1->parent = temp2;
			if (!temp)
				_root = node2;
			else if (temp->right == node1)
				temp->right = node2;
			else
				temp->left = node2;
			if (!temp2)
				_root = node1;
			else if (temp2->right == node2)
				temp2->right = node1;
			else
				temp2->left = node1;

			temp = node1->left;
			temp2 = node1->right;

			node1->left = node2->left;
			node1->right = node2->right;
			node2->left = temp;
			node2->right = temp2;
			if (node1->left && node1->left != _leaf)
				node1->left->parent = node1;
			if (node1->right && node1->right != _leaf)
				node1->right->parent = node1;
			if (node2->left && node2->left != _leaf)
				node2->left->parent = node2;
			if (node2->right && node2->right != _leaf)
				node2->right->parent = node2;
			temp_color = node1->color;
			node1->color = node2->color;
			node2->color = temp_color;
		}

		void delete_tree(tree_node *P, tree_node *child)
		{
			tree_node *child_left;
			tree_node *child_right;
			bool child_l_color;
			bool child_r_color;

			while (P)
			{
				if (child && child != _leaf)
				{
					child_left = child->left;
					child_right = child->right;
				}
				child_l_color = (!child || child == _leaf || !child_left ||
								 child_left == _leaf || child_left->color == 1);
				child_r_color = (!child || child == _leaf || !child_right ||
								 child_right == _leaf || child_right->color == 1);

				if (P->color == 1 && child && child->color == 0 &&
					child_l_color == 1 && child_r_color == 1)
				{
					P->color = 0;
					child->color = 1;
					if (child == P->left)
					{
						child = child->right;
						right_rotate(P);
					}
					else
					{
						child = child->left;
						left_rotate(P);
					}
				}

				else if (P->color == 1 && (!child || child->color != 0)
						&& (child_l_color == 1 && child_r_color == 1))
				{
					if (child)
						child->color = 0;
					if (P->parent)
						child = (P->parent->right == P)
									? P->parent->left
									: P->parent->right;
					P = P->parent;
				}

				else if (P->color == 0 && (!child || child->color != 0)
						&& (child_l_color == 1 && child_r_color == 1))
				{
					P->color = 1;
					if (child)
						child->color = 0;
					break;
				}

				else if ((!child || child->color != 0) &&
						 ((child == P->right && child_l_color == 0 && child_r_color != 0)
						 || (child == P->left && child_r_color == 0 && child_l_color != 0)))
				{
					if (child && child != _leaf)
						child->color = 0;
					if (child_right->color == 0)
					{
						child_right->color = 1;
						left_rotate(child);
					}
					else
					{
						child_left->color = 1;
						right_rotate(child);
					}
					if (child && child != _leaf)
						child = child->parent;
				}

				else
				{
					if (child == P->left)
					{
						child_left->color = 1;
						right_rotate(P);
					}
					else
					{
						child_right->color = 1;
						left_rotate(P);
					}
					break;
				}
			}
		}

		void delete_node(tree_node *node)
		{
			tree_node *P;
			tree_node *child;

			_size--;
			if (node->left && node->right && node->left != _leaf && node->right != _leaf)
				swap_val(node, min_node(node->right));
			P = node->parent;
			if (P)
				child = (P->left == node) ? P->right : P->left;
			if (node->right && node->right != _leaf)
			{
				swap_val(node, node->right);
				node->parent->right = NULL;
			}
			else if (node->left && node->left != _leaf)
			{
				swap_val(node, node->left);
				node->parent->left = NULL;
			}
			else
			{
				if (node == _root)
				{
					_root = NULL;
					_leaf->right = NULL;
					_leaf->left = NULL;
				}
				else
				{
					if (node->parent->right == node)
						node->parent->right = NULL;
					else
						node->parent->left = NULL;
				}
			}
			if (node->color == 1 && _root)
				delete_tree(P, child);
			if (_root)
			{
				while (_root->parent)
					_root = _root->parent;
				tree_node *temp_min = min_node(_root);
				tree_node *temp_max = max_node(_root);
				temp_min->left = _leaf;
				temp_max->right = _leaf;
				_leaf->right = temp_min;
				_leaf->left = temp_max;
			}
			_alloc.destroy(static_cast<value_type *>(node->val));
			_alloc.deallocate(static_cast<value_type *>(node->val), 1);
			_tree_alloc.destroy(node);
			_tree_alloc.deallocate(node, 1);
		}

		tree_node *tree_insert(tree_node *root, tree_node *prev, pair<const Key, T> val)
		{
			if (!root || root == _leaf)
			{
				root = _tree_alloc.allocate(1);
				_tree_alloc.construct(root, tree_node());
				root->val = _alloc.allocate(1);
				_alloc.construct(static_cast<value_type *>(root->val), val);
				root->parent = prev;
				if (!_root)
					_root = root;
			}
			else if (!_comp(val.first, static_cast<value_type *>(root->val)->first))
				root->right = tree_insert(root->right, root, val);
			else if (_comp(val.first, static_cast<value_type *>(root->val)->first))
				root->left = tree_insert(root->left, root, val);
			return (root);
		}

		void tree_insert_fix(tree_node *node)
		{
			tree_node *P = node->parent;
			tree_node *grandparent;
			tree_node *uncle;

			while (P)
			{
				if (P->color == 1)
					return;
				if ((grandparent = P->parent) == NULL)
				{
					P->color = 1;
					return;
				}
				uncle = (grandparent->right == P) ? grandparent->left : grandparent->right;
				if (!uncle || uncle->color > 0)
				{
					if (node == P->right && P == grandparent->left)
					{
						left_rotate(P);
						node = P;
						P = grandparent->left;
					}
					else if (node == P->left && P == grandparent->right)
					{
						right_rotate(P);
						node = P;
						P = grandparent->right;
					}
					if (node == P->left)
						right_rotate(grandparent);
					else
						left_rotate(grandparent);
					P->color = 1;
					grandparent->color = 0;
					return;
				}
				P->color = 1;
				uncle->color = 1;
				grandparent->color = 0;
				node = grandparent;
				P = node->parent;
			}
			_root->color = 1;
		}

		void insert_node(const pair<const Key, T> &val)
		{
			_size++;
			tree_insert(_root, NULL, val);
			if (_size > 1)
				tree_insert_fix(search_tree(_root, val.first));
			while (_root && _root->parent)
				_root = _root->parent;

			tree_node *temp_min = min_node(_root);
			tree_node *temp_max = max_node(_root);

			temp_min->left = _leaf;
			temp_max->right = _leaf;
			_leaf->right = temp_min;
			_leaf->left = temp_max;
		}
	};

	//	NON-MEMBER FUNCTIONS
	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		typename map<Key, T>::const_iterator rit = rhs.begin();
		typename map<Key, T>::const_iterator lit = lhs.begin();

		if (lhs.size() != rhs.size())
			return (false);
		while (rit != rhs.end() && lit != lhs.end())
		{
			if (*rit != *lit)
				return (false);
			rit++;
			lit++;
		}
		return (true);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
	{
		x.swap(y);
	}
}
//	https://legacy.cplusplus.com/reference/map/map/
//	https://algorithmtutor.com/Data-Structures/Tree/Binary-Search-Trees/
//	https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/

#endif
