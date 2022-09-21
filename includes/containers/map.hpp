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
		typedef binary_tree<value_type> node;
		typedef map_iterator<node, value_type> iterator;
		typedef map_iterator<node, const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;
		typedef typename allocator_type::template rebind<node>::other tree_allocator_type;

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
					 const allocator_type &alloc = allocator_type()) : _tree_alloc(std::allocator<node>()),
																	   _comp(comp), _size(0), _alloc(alloc),
																	   _root(NULL), _end(NULL), _rend(NULL)
		{
			//	Constructs an empty container, with no elements.
			_end = _tree_alloc.allocate(1);
			_tree_alloc.construct(_end, node());

			_rend = _tree_alloc.allocate(1);
			_tree_alloc.construct(_rend, node());
			_rend->parent = _end;
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : _tree_alloc(std::allocator<node>()),
															  _comp(comp), _size(0), _alloc(alloc),
															  _root(NULL), _end(NULL), _rend(NULL)
		{
			//	Constructs a container with as many elements as the range.
			_end = _tree_alloc.allocate(1);
			_tree_alloc.construct(_end, node());

			_rend = _tree_alloc.allocate(1);
			_tree_alloc.construct(_rend, node());
			_rend->parent = _end;
			this->insert(first, last);
		}

		map(const map &x) : _tree_alloc(std::allocator<node>()), _comp(x.key_comp()),
							_size(x._size), _alloc(x.get_allocator()),
							_root(NULL), _end(NULL), _rend(NULL)
		{
			//	Constructs a container with a copy of each of the elements in x.
			_end = _tree_alloc.allocate(1);
			_tree_alloc.construct(_end, node());

			_rend = _tree_alloc.allocate(1);
			_tree_alloc.construct(_rend, node());
			_rend->parent = _end;
			_root = NULL;
			*this = x;
		}

		~map()
		{
			this->clear();
			_tree_alloc.destroy(_end);
			_tree_alloc.deallocate(_end, 1);
			_tree_alloc.destroy(_rend);
			_tree_alloc.deallocate(_rend, 1);
		}

		map &operator=(const map &x)
		{
			if (this != &x)
			{
				try
				{
					this->clear();
					_comp = x._comp;
					_size = 0;
					_alloc = x._alloc;
					_tree_alloc = x._tree_alloc;
					this->insert(x.begin(), x.end());
				}
				catch (const std::exception &e)
				{
					std::cerr << e.what() << '\n';
				}
			}
			return (*this);
		}

		//	ITERATORS
		iterator begin() { return (iterator(this->_rend->parent)); }
		const_iterator begin() const { return (const_iterator(this->_rend->parent)); }
		iterator end() { return (iterator(this->_end)); }
		const_iterator end() const { return (const_iterator(this->_end)); }
		reverse_iterator rbegin() { return (reverse_iterator(this->_end)); }
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->_end)); }
		reverse_iterator rend() { return (reverse_iterator(this->_rend->parent)); }
		const_reverse_iterator rend() const { return (const_reverse_iterator(this->_rend->parent)); }

		//	CAPACITY
		bool empty() const
		{
			if (this->_size == 0)
				return true;
			else
				return false;
		}
		size_type size() const { return (this->_size); }
		size_type max_size() const { return (this->_alloc.max_size()); }

		//	ELEMENT ACCESS
		mapped_type &operator[](const key_type &k)
		{
			return ((this->insert(ft::make_pair(k, mapped_type())).first)->second);
		}

		//	MODIFIERS
		pair<iterator, bool> insert_root(const value_type &val)
		{
			if (_root == NULL)
			{
				_root = _tree_alloc.allocate(1);
				_tree_alloc.construct(_root, node(val));

				_root->left = _rend;
				_root->right = _end;
				_end->parent = _root;
				_rend->parent = _root;
				_size++;
			}
			return (ft::make_pair(iterator(_root), true));
		}

		node *insert_node(const value_type &val)
		{
			node *map_node = _root;
			node *new_map_node;

			while (map_node->right && map_node->right != _end && _comp(map_node->val.first,val.first))
				map_node = map_node->right;
			while (map_node->left && map_node->left != _rend && _comp(val.first, map_node->val.first))
				map_node = map_node->left;
			new_map_node = _tree_alloc.allocate(1);
			_tree_alloc.construct(new_map_node, node(val));
			new_map_node->parent = map_node;
			if (map_node->val.first < val.first)
			{
				new_map_node->right = map_node->right;
				if (new_map_node->right)
					new_map_node->right->parent = new_map_node;
				new_map_node->left = NULL;
				map_node->right = new_map_node;
			}
			else
			{
				new_map_node->left = map_node->left;
				if (new_map_node->left)
					new_map_node->left->parent = new_map_node;
				new_map_node->right = NULL;
				map_node->left = new_map_node;
			}
			_size++;
			return (new_map_node);
		}

		pair<iterator, bool> insert(const value_type &val)
		{
			iterator it;

			insert_root(val);
			it = this->find(val.first);
			if (it != this->end())
				return (ft::make_pair(it, false));
			return (ft::make_pair(insert_node(val), true));
		}

		iterator insert(iterator position, const value_type &val)
		{
			(void(position));
			return (this->insert(val).first);
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				this->insert(*first);
				first++;
			}
		}

		void erase(iterator position)
		{
			node *map_node = position.get_node();
			node *m_parent  = map_node->parent;
			node *m_left = map_node->left;
			node *m_right = map_node->right;
			node *next = map_node->next_node();

			if (!m_right && m_left)
			{
				if (m_parent->right == map_node)
					m_parent->right = m_left;
				else
					m_parent->left = m_left;
				m_left->parent = m_parent;
			}
			else if (m_right && !m_left)
			{
				if (m_parent->right == map_node)
					m_parent->right = m_right;
				else
					m_parent->left = m_right;
				m_right->parent = m_parent;
			}
			else if (!m_right && !m_left)
			{
				if (m_parent->right == map_node)
					m_parent->right = NULL;
				else
					m_parent->left = NULL;
			}
			else
			{
				if (next != map_node->left)
				{
					if (!m_parent)
						_root = next;
					else if (m_parent->right == map_node)
						m_parent->right = next;
					else
						m_parent->left = next;
					m_left->parent = next;
					next->parent = m_parent;
					next->left = m_left;
				}
				else
				{
					if (next->right)
					{
						next->parent->left = next->right;
						next->right->parent = next->parent;
					}
					if (!m_parent)
						_root = next;
					else if (m_parent->right == map_node)
						m_parent->right = next;
					else
						m_parent->left = next;
					if (next->parent->right == next)
						next->parent->right = NULL;
					else
						next->parent->left = NULL;
					next->parent = m_parent;
					next->right = m_right;
					next->left = m_left;
					m_left->parent = next;
					m_right->parent = next;
				}
			}
			_tree_alloc.destroy(map_node);
			_tree_alloc.deallocate(map_node, 1);
			_size--;
			if (_size == 0)
			{
				_root = NULL;
				_rend->right = NULL;
				_rend->left = NULL;
				_end->right = NULL;
				_end->left = NULL;
				_rend->parent = _end;
			}
		}

		size_type erase(const key_type& key)
		{
			return (find(key) != end() ? (erase(find(key)), true) : false);
		}

		void erase(iterator first, iterator last)
		{
			iterator it;

			if (first == last)
				return;
			it = first;
			erase(++first, last);
			erase(it);
		}

		void swap(map &x)
		{
			typename Alloc::template rebind<node>::other
				tmp_tree_alloc = this->_tree_alloc;
			Alloc tmp_alloc = this->_alloc;
			Compare tmp_comp = this->_comp;
			size_type tmp_size = this->_size;
			node *tmp_root = this->_root;
			node *tmp_end = this->_end;
			node *tmp_rend = this->_rend;

			if (x == *this)
				return;
			this->_tree_alloc = x._tree_alloc;
			this->_alloc = x._alloc;
			this->_comp = x._comp;
			this->_size = x._size;
			this->_root = x._root;
			this->_end = x._end;
			this->_rend = x._rend;

			x._tree_alloc = tmp_tree_alloc;
			x._alloc = tmp_alloc;
			x._comp = tmp_comp;
			x._size = tmp_size;
			x._root = tmp_root;
			x._end = tmp_end;
			x._rend = tmp_rend;
		}

		void clear()
		{
			this->erase(this->begin(), this->end());
		}

		//	OBSERVERS
		key_compare key_comp() const { return (key_compare()); }
		value_compare value_comp() const { return (value_compare(key_compare())); }

		//	OPERATIONS
		node *find_node(node *map_node, key_type k) const
		{
			if (!map_node)
				return (NULL);
			if (map_node->val.first == k)
				return (map_node);
			if (map_node->val.first > k)
				return (find_node(map_node->left, k));
			else
				return (find_node(map_node->right, k));
		}

		iterator find(const key_type &k)
		{
			node *map_node = find_node(_root, k);

			if (!map_node)
				return (this->end());
			return (iterator(map_node));
		}

		const_iterator find(const key_type &k) const
		{
			node *map_node = find_node(_root, k);

			if (!map_node)
				return (this->end());
			return (const_iterator(map_node));
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
		node *_root;
		node *_end;
		node *_rend;
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
