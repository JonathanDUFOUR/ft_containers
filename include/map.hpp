/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:42:51 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/06 14:47:01 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "rb_tree.tpp"

namespace ft
{
template <
	typename Key,
	typename T,
	typename Compare = std::less<Key>,
	typename Alloc = std::allocator<pair<Key const, T> > >
class map
{
private:
	// Member types
	typedef rb_node<pair<Key const, T> >							_node_type;
	typedef typename Alloc::template rebind<_node_type>::other		_node_allocator_type;

public:
	// Member types
	typedef Key														key_type;
	typedef T														mapped_type;
	typedef Compare													key_compare;
	typedef Alloc													allocator_type;

	typedef pair<key_type const, mapped_type>						value_type;

	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::reference						reference;

	typedef typename allocator_type::const_pointer					const_pointer;
	typedef typename allocator_type::pointer						pointer;

	typedef rb_tree_iterator<value_type const, _node_type const>	const_iterator;
	typedef rb_tree_iterator<value_type, _node_type>				iterator;

	typedef reverse_iterator<const_iterator>						const_reverse_iterator;
	typedef reverse_iterator<iterator>								reverse_iterator;

	typedef typename iterator_traits<iterator>::difference_type		difference_type;
	typedef size_t													size_type;


	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
		friend class map;

	protected:
		// Attributes
		key_compare	_cmp;

	public:
		// Operators
		bool operator()(value_type const &lhs, value_type const &rhs) const
		{
			return this->_cmp(lhs.first, rhs.first);
		}

	}; // class value_compare

private:
	// Attributes
	rb_tree<value_type, value_compare, _node_allocator_type>	_tree;

public:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new empty map object. (default constructor)
	 */
	explicit map(key_compare const & = key_compare(), allocator_type const & = allocator_type()) :
		_tree() {}

	/**
	 * @brief	Construct a new map object using a range of iterators.
	 * 			The resulting map will contain elements from `first` included to `last` excluded.
	 * 			(range constructor)
	 * 
	 * @tparam	InputIterator The type of the iterators to use.
	 * 			(it must conform to the standard input iterator requirements)
	 * 
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 */
	template <typename InputIterator>
	map(
		InputIterator const first,
		InputIterator const last,
		key_compare const & = key_compare(),
		allocator_type const & = allocator_type()) :
		_tree(first, last) {}

	/**
	 * @brief	Construct a new map object as a copy of another one. (copy constructor)
	 * 
	 * @param	src The map to copy.
	 */
	map(map const &src) :
		_tree(src._tree) {}

// ***************************************************************************************************************** //
//                                                    Destructors                                                    //
// ***************************************************************************************************************** //

	/**
	 * @brief	Destroy the map object. (destructor)
	 */
	~map(void)
	{
		this->_tree.clear();
	}

// ***************************************************************************************************************** //
//                                              Public Member Functions                                              //
// ***************************************************************************************************************** //

	/**
	 * @return	An iterator to the first element of the map.
	 */
	iterator	begin(void)
	{
		return this->_tree.begin();
	}

	/**
	 * @return	A const_iterator to the first element of the map.
	 */
	const_iterator	begin(void) const
	{
		return this->_tree.begin();
	}

	/**
	 * @brief	Remove every elements of the map.
	 */
	void	clear(void)
	{
		this->_tree.clear();
	}

	/**
	 * @return	The number of matching elements with a given key in the map.
	 */
	size_type	count(key_type const &key) const
	{
		return this->_tree.find(value_type(key, mapped_type())) != this->_tree.getNil();
	}

	/**
	 * @return	Either true if the map is empty, or false if not.
	 */
	bool	empty(void) const
	{
		return !this->_tree.getSize();
	}

	/**
	 * @return	An iterator to the post-last element of the map.
	 */
	iterator	end(void)
	{
		return this->_tree.end();
	}

	/**
	 * @return	A const_iterator to the post-last element of the map.
	 */
	const_iterator	end(void) const
	{
		return this->_tree.end();
	}

	/**
	 * @brief	Search for elements matching a given key in the map.
	 * 			The resulting match is returned as a range of iterator,
	 * 			from the first element included to the last element excluded.
	 * 
	 * @param	key The key to search for.
	 * 
	 * @return	A pair containing an iterator to the first element of the matching range as `first` member,
	 * 			and an iterator to the last element of the matching range as `second` member.
	 */
	pair<iterator, iterator>	equal_range(key_type const &key)
	{
		return this->_tree.equal_range(value_type(key, mapped_type()));
	}

	/**
	 * @brief	Search for constant elements matching a given key in the map.
	 * 			The resulting match is returned as a range of const_iterator,
	 * 			from the first constant element included to the last constant element excluded.
	 * 
	 * @param	key The key to search for.
	 * 
	 * @return	A pair containing an iterator to the first constant element of the matching range as `first` member,
	 * 			and an iterator to the last constant element of the matching range as `second` member.
	 */
	pair<const_iterator, const_iterator>	equal_range(key_type const &key) const
	{
		return this->_tree.equal_range(value_type(key, mapped_type()));
	}

	/**
	 * @brief	Remove an element from the map. (single erase (position))
	 * 
	 * @param	pos The position of the element to remove.
	 */
	void	erase(iterator pos)
	{
		this->_tree.erase(pos.base());
	}

	/**
	 * @brief	Remove an element from the map. (single erase (key))
	 * 
	 * @param	key The key of the element to remove.
	 * 
	 * @return	The number of removed element(s).
	 */
	size_type	erase(key_type const &key)
	{
		return this->_tree.erase(value_type(key, mapped_type()));
	}

	/**
	 * @brief	Remove elements from the map, using a range of iterators,
	 * 			from `first` included to `last` excluded. (range erase)
	 * 
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 */
	void	erase(iterator first, iterator const last)
	{
		while (first != last)
			this->erase(first++);
	}

	/**
	 * @brief	Search for an element in the map.
	 * 
	 * @param	key The key of the element to search.
	 * 
	 * @return	An iterator to the element if found, or end() if not.
	 */
	iterator	find(key_type const &key)
	{
		return iterator(this->_tree.find(value_type(key, mapped_type())));
	}

	/**
	 * @brief	Search for a constant element in the map.
	 * 
	 * @param	key The key of the constant element to search.
	 * 
	 * @return	A const_iterator to the constant element if found, or end() if not.
	 */
	const_iterator	find(key_type const &key) const
	{
		return const_iterator(this->_tree.find(value_type(key, mapped_type())));
	}

	/**
	 * @brief	Insert elements in the map using a range of iterators,
	 * 			from `first` included to `last` excluded. (range insertion)
	 * 
	 * @tparam	InputIterator The type of the iterators to use.
	 * 			(it must conform to the standard input iterator requirements)
	 * 
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 */
	template <typename InputIterator>
	void	insert(InputIterator first, InputIterator const last)
	{
		for (; first != last ; ++first)
			this->insert(*first);
	}

	/**
	 * @brief	Insert an element in the map. (single insertion)
	 * 
	 * @param	val The value of the element to insert in the map.
	 * 
	 * @return	A pair containing an iterator to the element of the map with the given value as `first` member,
	 * 			and a boolean indicating whether a new element has been inserted as `second` member.
	 */
	pair<iterator, bool>	insert(value_type const &val)
	{
		return this->_tree.insert(val);
	}

	/**
	 * @brief	Insert an element in the map. (single insertion with hint)
	 * 
	 * @param	pos The position where to insert the element.
	 * @param	val The value of the element to insert in the map.
	 * 
	 * @return	An iterator to the element of the map with the given value.
	 */
	iterator	insert(iterator const pos, value_type const &val)
	{
		return this->_tree.insert(pos.base(), val);
	}

	/**
	 * @return	A key_compare default object.
	 */
	key_compare	key_comp(void) const
	{
		return key_compare();
	}

	/**
	 * @brief	Search for the first element in the map that should be after or at the given key.
	 * 
	 * @param	key The key of the virtual element preceding the searched one.
	 * 
	 * @return	An iterator to the element if found, or end() if not.
	 */
	iterator	lower_bound(key_type const &key)
	{
		return this->_tree.lower_bound(value_type(key, mapped_type()));
	}

	/**
	 * @brief	Search for the first constant element in the map that should be after or at the given key.
	 * 
	 * @param	key The key of the virtual element preceding the searched one.
	 * 
	 * @return	An iterator to the constant element if found, or end() if not.
	 */
	const_iterator	lower_bound(key_type const &key) const
	{
		return this->_tree.lower_bound(value_type(key, mapped_type()));
	}

	/**
	 * @return	The maximum number of elements that can be stored in the map.
	 */
	size_type	max_size(void) const
	{
		return this->_tree.max_size();
	}

	/**
	 * @return	A reverse_iterator to the last element of the map.
	 */
	reverse_iterator	rbegin(void)
	{
		return this->_tree.rbegin();
	}

	/**
	 * @return	A const_reverse_iterator to the last element of the map.
	 */
	const_reverse_iterator	rbegin(void) const
	{
		return this->_tree.rbegin();
	}

	/**
	 * @return	A reverse_iterator to the pre-first element of the map.
	 */
	reverse_iterator	rend(void)
	{
		return this->_tree.rend();
	}

	/**
	 * @return	A const_reverse_iterator to the pre-first element of the map.
	 */
	const_reverse_iterator	rend(void) const
	{
		return this->_tree.rend();
	}

	/**
	 * @return	The number of stored elements in the map.
	 */
	size_type	size(void) const
	{
		return this->_tree.getSize();
	}

	/**
	 * @brief	Swap the content of the given map with the content of the current map.
	 * 
	 * @param	other The map to swap with.
	 */
	void	swap(map &other)
	{
		this->_tree.swap(other._tree);
	}

	/**
	 * @brief	Search for the first element in the map that should be strictly after the given key.
	 * 
	 * @param	key The key of the virtual element preceding the searched one.
	 * 
	 * @return	An iterator to the element if found, or end() if not.
	 */
	iterator	upper_bound(key_type const &key)
	{
		return this->_tree.upper_bound(value_type(key, mapped_type()));
	}

	/**
	 * @brief	Search for the first constant element in the map that should be strictly after the given key.
	 * 
	 * @param	key The key of the virtual element preceding the searched one.
	 * 
	 * @return	A const_iterator to the element if found, or end() if not.
	 */
	const_iterator	upper_bound(key_type const &key) const
	{
		return this->_tree.upper_bound(value_type(key, mapped_type()));
	}

	/**
	 * @return	A value_compare default object.
	 */
	value_compare	value_comp(void) const
	{
		return value_compare();
	}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Assign a new content to the map from another one's. (copy assignation)
	 * 
	 * @param	rhs The right hand side map to copy the content from.
	 * 
	 * @return	The assigned map.
	 */
	map	&operator=(map const &rhs)
	{
		if (this != &rhs)
			this->_tree = rhs._tree;
		return *this;
	}

	/**
	 * @brief	Look for an element in the map, inserting it if not found.
	 * 
	 * @param	key The key of the element to get.
	 * 
	 * @return	The element matching the given key.
	 */
	mapped_type	&operator[](key_type const &key)
	{
		iterator	it;
		key_compare	cmp;

		if (!this->_tree.getSize())
			return this->_tree.insert(value_type(key, mapped_type())).first->second;
		it = this->lower_bound(key);
		if (it == this->end())
			return this->_tree.insert(this->_tree.getNil()->child[MAX], value_type(key, mapped_type()))->second;
		if (cmp(it->first, key) || cmp(key, it->first))
			return this->_tree.insert(it.base(), value_type(key, mapped_type()))->second;
		return it->second;
	}

}; // class map

/**
 * @brief	Check if two map are equivalent.
 * 
 * @tparam	Key The key type of both of the map.
 * @tparam	T The mapped type of both of the map.
 * @tparam	Compare The functor to use to compare the keys.
 * @tparam	Alloc The allocator type used in both of the map.
 * 
 * @param	lhs The left hand side map to compare.
 * @param	rhs The right hand side map to compare.
 * 
 * @return	Either true if the two map are equivalent, or false if not.
 */
template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator==(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs)
{
	return &lhs == &rhs || (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

/**
 * @brief	Check if two map are different.
 * 
 * @tparam	Key The key type of both of the map.
 * @tparam	T The mapped type of both of the map.
 * @tparam	Compare The functor to use to compare the keys.
 * @tparam	Alloc The allocator type used in both of the map.
 * 
 * @param	lhs The left hand side map to compare.
 * @param	rhs The right hand side map to compare.
 * 
 * @return	Either true if the two map are different, or false if not.
 */
template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator!=(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs)
{
	return !(lhs == rhs);
}

/**
 * @brief	Check if two map are strictly lexiographicaly ordered.
 * 
 * @tparam	Key The key type of both of the map.
 * @tparam	T The mapped type of both of the map.
 * @tparam	Compare The functor to use to compare the keys.
 * @tparam	Alloc The allocator type used in both of the map.
 * 
 * @param	lhs The left hand side map to compare.
 * @param	rhs The right hand side map to compare.
 * 
 * @return	Either true if the two map are strictly lexiographicaly ordered, or false if not.
 */
template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator<(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/**
 * @brief	Check if two map are strictly lexiographicaly reverse-ordered.
 * 
 * @tparam	Key The key type of both of the map.
 * @tparam	T The mapped type of both of the map.
 * @tparam	Compare The functor to use to compare the keys.
 * @tparam	Alloc The allocator type used in both of the map.
 * 
 * @param	lhs The left hand side map to compare.
 * @param	rhs The right hand side map to compare.
 * 
 * @return	Either true if the two map are strictly lexiographicaly reverse-ordered, or false if not.
 */
template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator>(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs)
{
	return rhs < lhs;
}

/**
 * @brief	Check if two map are lexiographicaly ordered or equivalent.
 * 
 * @tparam	Key The key type of both of the map.
 * @tparam	T The mapped type of both of the map.
 * @tparam	Compare The functor to use to compare the keys.
 * @tparam	Alloc The allocator type used in both of the map.
 * 
 * @param	lhs The left hand side map to compare.
 * @param	rhs The right hand side map to compare.
 * 
 * @return	Either true if the two map are lexiographicaly ordered or equivalent, or false if not.
 */
template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator<=(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs)
{
	return !(rhs < lhs);
}

/**
 * @brief	Check if two map are lexiographicaly reverse-ordered or equivalent.
 * 
 * @tparam	Key The key type of both of the map.
 * @tparam	T The mapped type of both of the map.
 * @tparam	Compare The functor to use to compare the keys.
 * @tparam	Alloc The allocator type used in both of the map.
 * 
 * @param	lhs The left hand side map to compare.
 * @param	rhs The right hand side map to compare.
 * 
 * @return	Either true if the two map are lexiographicaly reverse-ordered or equivalent, or false if not.
 */
template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator>=(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs)
{
	return !(lhs < rhs);
}

// ***************************************************************************************************************** //
//                                               Specialized Functions                                               //
// ***************************************************************************************************************** //

/**
 * @brief	Swap the contents of two given map.
 * 
 * @tparam	Key The key type of both of the map.
 * @tparam	T The mapped type of both of the map.
 * @tparam	Compare The functor to use to compare the keys.
 * @tparam	Alloc The allocator type used in both of the map.
 * 
 * @param	a The first map to swap.
 * @param	b The second map to swap.
 */
template <typename Key, typename T, typename Compare, typename Alloc>
void	swap(map<Key, T, Compare, Alloc> &a, map<Key, T, Compare, Alloc> &b)
{
	a.swap(b);
}

} // namespace ft

#endif
