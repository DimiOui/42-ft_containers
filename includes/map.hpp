#ifndef MAP_HPP
# define MAP_HPP

#pragma once

#include "map_iterator.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
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
			typedef allocator_type::reference reference;
			typedef allocator_type::const_reference const_reference;
			typedef allocator_type::pointer pointer;
			typedef allocator_type::const_pointer const_pointer;
			typedef map_iterator<value_type> iterator; //not done
			typedef map_iterator<const value_type> const_iterator; // not done
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef std::ptrdiff_t difference_type;
			typedef std::size_t size_type;

			//	MEMBER FUNCTIONS
			explicit map(const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
			{
				//	Constructs an empty container, with no elements.
			}

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			{
				//	Constructs a container with as many elements as the range.
			}

			map(const map& x)
			{
				//	Constructs a container with a copy of each of the elements in x.
			}

			~map() {}

			map& operator= (const map& x) {}

			//	ITERATORS
			iterator begin() {}
			const_iterator begin() const {}
			iterator end() {}
			const_iterator end() const {}
			reverse_iterator rbegin() {}
			const_reverse_iterator rbegin() const {}
			reverse_iterator rend() {}
			const_reverse_iterator rend() const {}

			//	CAPACITY
			bool empty() const {}
			size_type size() const {}
			size_type max_size() const {}

			//	ELEMENT ACCESS
			mapped_type& operator[] (const key_type& k) {}

			//	MODIFIERS
			pair<iterator,bool> insert(const value_type& val) {}
			iterator insert (iterator position, const value_type& val) {}
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last) {}
			void erase (iterator position) {}
			size_type erase (const key_type& k) {}
			void erase (iterator first, iterator last) {}
			void swap (map& x) {}
			void clear() {}

			//	OBSERVERS
			key_compare key_comp() const {}
			value_compare value_comp() const {}

			//	OPERATIONS
			iterator find (const key_type& k) {}
			const_iterator find (const key_type &k) const {}
			size_type count (const key_type& k) const {}
			iterator lower_bound (const key_type& k) {}
			const_iterator lower_bound (const key_type& k) const {}
			iterator upper_bound (const key_type& k) {}
			const_iterator upper_bound (const key_type& k) const {}
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const {}
			pair<iterator,iterator> equal_range (const key_type& k) {}

			//	ALLOCATOR
			allocator_type get_allocator() const {}

		private:
			typename Alloc::template rebind<Rbt>::other _rbt_alloc;
			key_compare _comp;
			size_type _size;
			allocator_type _alloc;
			Rbt* _root;
			Rbt* _child;

	};

	//	NON-MEMBER FUNCTIONS
	template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{}

	template <class Key, class T, class Compare, class Alloc>
	bool operator< ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{}

	template <class Key, class T, class Compare, class Alloc>
	bool operator> ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{}

	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{}
}
//	https://legacy.cplusplus.com/reference/map/map/

#endif
