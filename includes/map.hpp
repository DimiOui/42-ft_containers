#ifndef MAP_HPP
# define MAP_HPP

#pragma once

#include "map_iterator.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "map_bst.hpp"
#include "lexicographical_compare.hpp"

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
			typedef BST_node<value_type> node;
			typedef map_iterator<node, value_type> iterator; //not done
			typedef map_iterator<const node, value_type> const_iterator; // not done
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef std::ptrdiff_t difference_type;
			typedef std::size_t size_type;
			typedef typename Alloc::template rebind<node>::other bst_allocator_type;

			//	VALUE COMPARE
			class value_compare
			{
				friend class map;

				protected:
					Compare	_comp;
					value_compare(Compare c) : _comp(c) {}

				public:
					typedef bool result_type;
					typedef value_type first_arg_type;
					typedef value_type second_arg_type;

					bool operator() (const value_type& x, const value_type& y) const
					{
						return (_comp(x.first, y.first));
					}
			};

			//	MEMBER FUNCTIONS
			explicit map(const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()) :
					_bst_alloc(std::allocator<node>()), _comp(comp), _size(0), _alloc(alloc),
					_root(NULL), _end(NULL), _rend(NULL)
			{
				//	Constructs an empty container, with no elements.
				_end = _bst_alloc.allocate(1);
				_bst_alloc.construct(_end, node());

				_rend = _bst_alloc.allocate(1);
				_bst_alloc.construct(_rend, node());
				_rend->parent = _end;
			}

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) :
				_bst_alloc(std::allocator<node>()), _comp(comp), _size(0), _alloc(alloc),
				_root(NULL), _end(NULL), _rend(NULL)
			{
				//	Constructs a container with as many elements as the range.
			}

			map(const map& x) : _bst_alloc(std::allocator<node>()), _comp(x.key_comp()),
								_size(x._size), _alloc(x.get_allocator()),
								_root(NULL), _end(NULL), _rend(NULL)
			{
				//	Constructs a container with a copy of each of the elements in x.
				_end = _bst_alloc.allocate(1);
				_bst_alloc.construct(_end, node());

				_rend = _bst_alloc.allocate(1);
				_bst_alloc.construct(_rend, node());
				_rend->parent = _end;
				_root = NULL;
				*this = x;
			}

			~map()
			{
				this->clear();
				_bst_alloc.destroy(_end);
				_bst_alloc.deallocate(_end, 1);
				_bst_alloc.destroy(_rend);
				_bst_alloc.deallocate(_rend, 1);
			}

			map& operator= (const map& x)
			{
				this->clear();
				_comp = x._comp;
				_size = 0;
				_alloc = x._alloc;
				_bst_alloc = x._bst_alloc;
				this->insert(x.begin(), x.end());
				return (*this);
			}

			//	ITERATORS
			iterator begin() {return (iterator(_rend->parent));}
			const_iterator begin() const {return (const_iterator(_rend->parent));}
			iterator end() {return (iterator(_end));}
			const_iterator end() const {return (const_iterator(_end));}
			reverse_iterator rbegin() {return (reverse_iterator(_end));}
			const_reverse_iterator rbegin() const {return (const_reverse_iterator(_end));}
			reverse_iterator rend() {return (reverse_iterator(_rend->parent));}
			const_reverse_iterator rend() const {return (const_reverse_iterator(_rend->parent));}

			//	CAPACITY
			bool empty() const
			{if (_size == 0) return true; else return false;}

			size_type size() const {return (_size);}
			size_type max_size() const {return (_alloc.max_size());}

			//	ELEMENT ACCESS
			mapped_type& operator[] (const key_type& k)
			{
				return (*(this->insert(value_type(k, mapped_type())).first)).second;
			}

			//	MODIFIERS
			pair<iterator,bool> insert(const value_type& val)
			{
				iterator	it;
				node		*map_node;
				node		*new_mnode;

				if (!_root)
				{
					_root = _bst_alloc.allocate(1);
					_bst_alloc.construct(_root, node(val));

					_root->left = _rend;
					_root->right = _end;
					_end->parent = _root;
					_rend->parent = _root;
					_size = 1;

					return (ft::make_pair(iterator(_root), true));
				}
				it = this->find(val.first);
				if (it != this->end())
					return (ft::make_pair(it, false));
				map_node = _root;
				while (map_node->right || map_node->left)
				{
					if (_comp(map_node->val.first, val.first))
					{
						if (map_node->right && map_node->right != _end)
							map_node = map_node->right;
						else
							break;
					}
					else
					{
						if (map_node->left && map_node->left != _rend)
							map_node = map_node->left;
						else
							break;
					}
				}
				new_mnode = _bst_alloc.allocate(1);
				_bst_alloc.construct(new_mnode, node(val));
				new_mnode->parent = map_node;
				if (_comp(map_node->val.first, val.first))
				{
					new_mnode->right = map_node->right;
					if (new_mnode->right)
						new_mnode->right->parent = new_mnode;
					new_mnode->left = NULL;
					map_node->right = new_mnode;
				}
				else
				{
					new_mnode->left = map_node->left;
					if (new_mnode->left)
						new_mnode->left->parent = new_mnode;
					new_mnode->right = NULL;
					map_node->left = new_mnode;
				}
				_size++;
				return (ft::make_pair(new_mnode, true));
			}

			iterator insert (iterator position, const value_type& val)
			{
				//void (position);
				return (this->insert(val).first);
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					this->insert(*first);
					first++;
				}
			}

			void erase (iterator position)
			{
				node	*map_node;
				node	*right;
				node	*left;
				node	*parent;
				node	*next;

			map_node = position.get_node();
			right = map_node->right;
			left = map_node->left;
			parent = map_node->parent;
            next = map_node->next_node();
			if (!right && !left)
			{
				if (parent->right == map_node)
					parent->right = NULL;
				else
					parent->left = NULL;
			}
			else if (!right && left)
			{
				if (parent->right == map_node)
					parent->right = left;
				else
					parent->left = left;
				left->parent = parent;
			}
			else if (right && !left)
			{
				if (parent->right == map_node)
					parent->right = right;
				else
					parent->left = right;
				right->parent = parent;
			}
			else
			{
				if (next != map_node->right)
				{
					if (next->right)
					{
						next->parent->left = next->right;
						next->right->parent = next->parent;
					}
					if (!parent)
						_root = next;
					else if (parent->right == map_node)
						parent->right = next;
					else
						parent->left = next;
                    if (next->parent->right == next)
                        next->parent->right = NULL;
                    else
                        next->parent->left = NULL;
					next->parent = parent;
					next->right = right;
					next->left = left;
					left->parent = next;
					right->parent = next;
				}
				else
				{
					if (!parent)
						_root = next;
					else if (parent->right == map_node)
						parent->right = next;
					else
						parent->left = next;
					left->parent = next;
					next->parent = parent;
					next->left = left;
				}
			}
			_bst_alloc.destroy(map_node);
			_bst_alloc.deallocate(map_node, 1);
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

			size_type erase (const key_type& k)
			{
				iterator it;

				if ((it = this->find(k)) == this->end())
					return (false);
				erase(it);
				return (true);
			}

			void erase (iterator first, iterator last)
			{
				iterator temp;

				if (first == last)
					return;
				temp = first;
				erase(++first, last);
				erase(temp);
			}

			void swap (map& x)
			{
				 typename Alloc::template rebind<node>::other
							tmp_bst_alloc = this->_bst_alloc;
				Alloc		tmp_alloc = this->_alloc;
				pointer		tmp_root = this->_root;
				pointer		tmp_end = this->_end;
				pointer		tmp_rend = this->_rend;
				Compare		tmp_comp = this->_comp;
				size_type	tmp_size = this->_size;

				if (x == *this)
					return;
				this->_bst_alloc = x._bst_alloc;
				this->_alloc = x._alloc;
				this->_size = x._size;
				this->_comp = x._comp;
				this->_root = x._root;
				this->_end = x._end;
				this->_rend = x._rend;

				x._bst_alloc = tmp_bst_alloc;
				x._alloc = tmp_alloc;
				x._size = tmp_size;
				x._comp = tmp_comp;
				x._root = tmp_root;
				x._end = tmp_end;
				x._rend = tmp_rend;
			}

			void clear()
			{
				this->erase(this->begin(), this->end());
			}

			//	OBSERVERS
			key_compare key_comp() const {return (key_compare());}
			value_compare value_comp() const {return (value_compare(key_compare()));}

			//	OPERATIONS
			iterator find (const key_type& k)
			{
				node* map_node;

				map_node = _root;
				while (map_node && map_node != _end && map_node != _rend &&
				(_comp(map_node->val.first, k) || _comp(k, map_node->val.first)))
				{
					if (_comp(map_node->val.first, k))
						map_node = map_node->right;
					else
						map_node = map_node->left;
				}
				if (map_node && map_node != _end && map_node != _rend &&
				(!_comp(map_node->val.first, k) || !_comp(k, map_node->val.first)))
					return (iterator(map_node));
				else
					return (map::end());
			}
			const_iterator find (const key_type &k) const
			{
				node* map_node;

				map_node = _root;
				while (map_node && map_node != _end && map_node != _rend &&
				(_comp(map_node->val.first, k) || _comp(k, map_node->val.first)))
				{
					if (_comp(map_node->val.first, k))
						map_node = map_node->right;
					else
						map_node = map_node->left;
				}
				if (map_node && map_node != _end && map_node != _rend &&
				(!_comp(map_node->val.first, k) || !_comp(k, map_node->val.first)))
					return (const_iterator(map_node));
				else
					return (const_iterator(_end));
			}

			size_type count (const key_type& k) const
			{
				//can exchange find and count smh
				if (this->find(k) == this->end())
					return (false);
				return (true);
			}

			iterator lower_bound (const key_type& k) {}
			const_iterator lower_bound (const key_type& k) const {}
			iterator upper_bound (const key_type& k) {}
			const_iterator upper_bound (const key_type& k) const {}
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const {}
			pair<iterator,iterator> equal_range (const key_type& k) {}

			//	ALLOCATOR
			allocator_type get_allocator() const {return (this->_alloc);}

		private:
			bst_allocator_type _bst_alloc;
			key_compare _comp;
			size_type _size;
			allocator_type _alloc;
			node* _root;
			node* _end;
			node* _rend;

	};

	//	NON-MEMBER FUNCTIONS
	template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
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
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator< ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator> ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}
}
//	https://legacy.cplusplus.com/reference/map/map/
//	https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/

#endif
