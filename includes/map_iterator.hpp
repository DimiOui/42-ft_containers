#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	struct rbt
	{
		struct rbt*	parent;
		struct rbt*	left_child;
		struct rbt* right_child;
		void* val;
		std::size_t color;

		rbt() : parent(), left_child(), right_child(), val(), color(0) {}
	};

	template <class T, class Category = std::bidirectional_iterator_tag,
		class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class map_iterator
	{
		public:
			//	MEMBER TYPES
			typedef Category iterator_category;
			typedef T value_type;
			typedef Distance difference_type;
			typedef Pointer pointer;
			typedef Reference reference;

			//	MEMBER FUNCTIONS
			map_iterator() : _current_node() {}
			map_iterator(pointer rbt) : _current_node(rbt) {}
			map_iterator(const reference rbt) {_current_node = ref.get_node();}
			~map_iterator() {}

			operator map_iterator<const T>(void) const {}
			reference operator*() const {}
			map_iterator& operator++() {}
			map_iterator operator++ (int) {}
			map_iterator& operator--() {}
			map_iterator operator-- (int) {}
			pointer operator->() const {}

			map_iterator &operator= (const map_iterator<const T> &x) {}

			pointer get_node() const {return (_current_node);}

			//	COMPARISON
			bool operator== (const map_iterator<const T> &x) const {}
			bool operator!= (const map_iterator<const T> &x) const {}


		protected:
			rbt* _current_node;
	};
}

//	https://legacy.cplusplus.com/reference/iterator/iterator/

#endif
