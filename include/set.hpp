/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:31:58 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/06 16:56:23 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include "rb_tree.tpp"

namespace ft
{
template <typename Key, typename Compare = std::less<Key>, typename Alloc = std::allocator<Key> >
class set
{
private:
	// Member types
	typedef rb_node<Key const>										_node_type;
	typedef typename Alloc::template rebind<_node_type>::other		_node_allocator_type;

public:
	//Member types
	typedef Key														key_type;
	typedef Key														value_type;
	typedef Compare													key_compare;
	typedef Compare													value_compare;
	typedef Alloc													allocator_type;

	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::reference						reference;

	typedef typename allocator_type::const_pointer					const_pointer;
	typedef typename allocator_type::pointer						pointer;

	typedef rb_tree_iterator<value_type const, _node_type const>	const_iterator;
	typedef const_iterator											iterator;

	typedef reverse_iterator<const_iterator>						const_reverse_iterator;
	typedef reverse_iterator<iterator>								reverse_iterator;

	typedef typename iterator_traits<iterator>::difference_type		difference_type;
	typedef size_t													size_type;

private:
	// Attributes
	rb_tree<value_type const, value_compare, _node_allocator_type>	_tree;

public:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new empty set object. (default constructor)
	 */
	explicit set(key_compare const & = key_compare(), allocator_type const & = allocator_type()) :
		_tree() {}

	/**
	 * @brief	Construct a new set object using a range of iterators.
	 * 			The resulting set will contain elements from `first` included to `last` excluded.
	 * 			(range constructor)
	 * 
	 * @tparam	InputIterator The type of the iterators to use.
	 * 			(it must conform to the standard input iterator requirements)
	 * 
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 */
	template <typename InputIterator>
	set(
		InputIterator const first,
		InputIterator last,
		key_compare const & = key_compare(),
		allocator_type const & = allocator_type()) :
		_tree(first, last) {}

	/**
	 * @brief	Construct a new set object as a copy of another one. (copy constructor)
	 * 
	 * @param	src The set to copy.
	 */
	set(set const &src) :
		_tree(src._tree) {}

// ***************************************************************************************************************** //
//                                              Public Member Functions                                              //
// ***************************************************************************************************************** //

	/**
	 * @return	An iterator to the first element of the set.
	 */
	iterator	begin(void)
	{
		return this->_tree.begin();
	}

	/**
	 * @return	A const_iterator to the first element of the set.
	 */
	const_iterator	begin(void) const
	{
		return this->_tree.begin();
	}

	/**
	 * @brief	Remove every elements of the set.
	 */
	void	clear(void)
	{
		this->_tree.clear();
	}

	/**
	 * @return	The number of matching elements with a given key in the set.
	 */
	size_type	count(key_type const &key) const
	{
		return this->_tree.find(key) != this->_tree.getNil();
	}

	/**
	 * @return	Either true if the set is empty, or false if not.
	 */
	bool	empty(void) const
	{
		return !this->_tree.getSize();
	}

	/**
	 * @return	An iterator to the post-last element of the set.
	 */
	iterator	end(void)
	{
		return this->_tree.end();
	}

	/**
	 * @return	A const_iterator to the post-last element of the set.
	 */
	const_iterator	end(void) const
	{
		return this->_tree.end();
	}

	/**
	 * @brief	Remove an element from the set. (single erase (position))
	 * 
	 * @param	pos The position of the element to remove.
	 */
	void	erase(iterator pos)
	{
		this->_tree.erase(const_cast<_node_type *>(pos.base()));
	}

	/**
	 * @brief	Remove an element from the set. (single erase (key))
	 * 
	 * @param	key The key of the element to remove.
	 * 
	 * @return	The number of removed element(s).
	 */
	size_type	erase(key_type const &key)
	{
		return this->_tree.erase(key);
	}

	/**
	 * @brief	Remove elements from the set, using a range of iterators,
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
	 * @brief	Search for elements matching a given key in the set.
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
		return this->_tree.equal_range(key);
	}

	/**
	 * @brief	Search for constant elements matching a given key in the set.
	 * 			The resulting match is returned as a range of const_iterator,
	 * 			from the first constant element included to the last constant element excluded.
	 * 
	 * @param	key The key to search for.
	 * 
	 * @return	A pair containing a const_iterator to the first element of the matching range as `first` member,
	 * 			and a const_iterator to the last element of the matching range as `second` member.
	 */
	pair<const_iterator, const_iterator>	equal_range(key_type const &key) const
	{
		return this->_tree.equal_range(key);
	}

	/**
	 * @brief	Search for an element in the set.
	 * 
	 * @param	key The key of the element to search.
	 * 
	 * @return	An iterator to the element if found, or end() if not.
	 */
	iterator	find(key_type const &key)
	{
		return iterator(this->_tree.find(key));
	}

	/**
	 * @brief	Search for a constant element in the set.
	 * 
	 * @param	key The key of the constant element to search.
	 * 
	 * @return	A const_iterator to the constant element if found, or end() if not.
	 */
	const_iterator	find(key_type const &key) const
	{
		return const_iterator(this->_tree.find(key));
	}

	/**
	 * @brief	Insert elements in the set using a range of iterators,
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
		while (first != last)
			this->insert(*first++);
	}

	/**
	 * @brief	Insert an element in the set. (single insertion)
	 * 
	 * @param	val The value of the element to insert in the set.
	 * 
	 * @return	A pair containing an iterator to the element of the set with the given value as `first` member,
	 * 			and a boolean indicating whether a new element has been inserted as `second` member.
	 */
	pair<iterator, bool>	insert(value_type const &val)
	{
		return this->_tree.insert(val);
	}

	/**
	 * @brief	Insert an element in the set. (single insertion with hint)
	 * 
	 * @param	pos The position where to insert the element.
	 * @param	val The value of the element to insert in the set.
	 * 
	 * @return	An iterator to the element of the set with the given value.
	 */
	iterator	insert(iterator const pos, value_type const &val)
	{
		return this->_tree.insert(const_cast<_node_type *>(pos.base()), val);
	}

	/**
	 * @return	A key_compare default object.
	 */
	key_compare	key_comp(void) const
	{
		return key_compare();
	}

	/**
	 * @brief	Search for the first element in the set that should be after or at the given key.
	 * 
	 * @param	key The key of the virtual element preceding the searched one.
	 * 
	 * @return	An iterator to the element if found, or end() if not.
	 */
	iterator	lower_bound(key_type const &key)
	{
		return this->_tree.lower_bound(key);
	}

	/**
	 * @brief	Search for the first constant element in the set that should be after or at the given key.
	 * 
	 * @param	key The key of the virtual element preceding the searched one.
	 * 
	 * @return	A const_iterator to the element if found, or end() if not.
	 */
	const_iterator	lower_bound(key_type const &key) const
	{
		return this->_tree.lower_bound(key);
	}

	/**
	 * @return	The maximum number of elements that can be stored in the set.
	 */
	size_type	max_size(void) const
	{
		return this->_tree.max_size();
	}

	/**
	 * @return	A reverse_iterator to the last element of the set.
	 */
	reverse_iterator	rbegin(void)
	{
		return this->_tree.rbegin();
	}

	/**
	 * @return	A const_reverse_iterator to the last element of the set.
	 */
	const_reverse_iterator	rbegin(void) const
	{
		return this->_tree.rbegin();
	}

	/**
	 * @return	A reverse_iterator to the pre-first element of the set.
	 */
	reverse_iterator	rend(void)
	{
		return this->_tree.rend();
	}

	/**
	 * @return	A const_reverse_iterator to the pre-first element of the set.
	 */
	const_reverse_iterator	rend(void) const
	{
		return this->_tree.rend();
	}

	/**
	 * @return	The number of stored elements in the set.
	 */
	size_type	size(void) const
	{
		return this->_tree.getSize();
	}

	/**
	 * @brief	Swap the content of the given set with the content of the current set.
	 * 
	 * @param	other The set to swap with.
	 */
	void	swap(set &other)
	{
		this->_tree.swap(other._tree);
	}

	/**
	 * @brief	Search for the first element in the set that should be strictly after the given key.
	 * 
	 * @param	key The key of the virtual element preceding the searched one.
	 * 
	 * @return	An iterator to the element if found, or end() if not.
	 */
	iterator	upper_bound(key_type const &key)
	{
		return this->_tree.upper_bound(key);
	}

	/**
	 * @brief	Search for the first constant element in the set that should be strictly after the given key.
	 * 
	 * @param	key The key of the virtual element preceding the searched one.
	 * 
	 * @return	A const_iterator to the element if found, or end() if not.
	 */
	const_iterator	upper_bound(key_type const &key) const
	{
		return this->_tree.upper_bound(key);
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
	 * @brief	Assign a new content to the set from another one's. (copy assignation)
	 * 
	 * @param	rhs The right hand side set to copy the content from.
	 * 
	 * @return	The assigned set.
	 */
	set	&operator=(set const &rhs)
	{
		if (this != &rhs)
			this->_tree = rhs._tree;
		return *this;
	}

}; // class set

/**
 * @brief	Check if two set are equivalent.
 * 
 * @tparam	Key The key type of both of the set.
 * @tparam	Compare The functor to use to compare the keys.
 * @tparam	Alloc The allocator type used in both of the set.
 * 
 * @param	lhs The left hand side set to compare.
 * @param	rhs The right hand side set to compare.
 * 
 * @return	Either true if the two set are equivalent, or false if not.
 */
template <typename Key, typename Compare, typename Alloc>
bool	operator==(set<Key, Compare, Alloc> const &lhs, set<Key, Compare, Alloc> const &rhs)
{
	return &lhs == &rhs || (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

/**
 * @brief	Check if two set are different.
 * 
 * @tparam	Key The key type of both of the set.
 * @tparam	Compare The functor to use to compare the keys.
 * @tparam	Alloc The allocator type used in both of the set.
 * 
 * @param	lhs The left hand side set to compare.
 * @param	rhs The right hand side set to compare.
 * 
 * @return	Either true if the two set are different, or false if not.
 */
template <typename Key, typename Compare, typename Alloc>
bool	operator!=(set<Key, Compare, Alloc> const &lhs, set<Key, Compare, Alloc> const &rhs)
{
	return !(lhs == rhs);
}

/**
 * @brief	Check if two set are strictly lexiographicaly ordered.
 * 
 * @tparam	Key The key type of both of the set.
 * @tparam	Compare The functor to use to compare the keys.
 * @tparam	Alloc The allocator type used in both of the set.
 * 
 * @param	lhs The left hand side set to compare.
 * @param	rhs The right hand side set to compare.
 * 
 * @return	Either true if the two set are strictly lexiographicaly ordered, or false if not.
 */
template <typename Key, typename Compare, typename Alloc>
bool	operator<(set<Key, Compare, Alloc> const &lhs, set<Key, Compare, Alloc> const &rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/**
 * @brief	Check if two set are strictly lexiographicaly reverse-ordered.
 * 
 * @tparam	Key The key type of both of the set.
 * @tparam	Compare The functor to use to compare the keys.
 * @tparam	Alloc The allocator type used in both of the set.
 * 
 * @param	lhs The left hand side set to compare.
 * @param	rhs The right hand side set to compare.
 * 
 * @return	Either true if the two set are strictly lexiographicaly reverse-ordered, or false if not.
 */
template <typename Key, typename Compare, typename Alloc>
bool	operator>(set<Key, Compare, Alloc> const &lhs, set<Key, Compare, Alloc> const &rhs)
{
	return rhs < lhs;
}

/**
 * @brief	Check if two set are lexiographicaly ordered or equivalent.
 * 
 * @tparam	Key The key type of both of the set.
 * @tparam	Compare The functor to use to compare the keys.
 * @tparam	Alloc The allocator type used in both of the set.
 * 
 * @param	lhs The left hand side set to compare.
 * @param	rhs The right hand side set to compare.
 * 
 * @return	Either true if the two set are lexiographicaly ordered or equivalent, or false if not.
 */
template <typename Key, typename Compare, typename Alloc>
bool	operator<=(set<Key, Compare, Alloc> const &lhs, set<Key, Compare, Alloc> const &rhs)
{
	return !(rhs < lhs);
}

/**
 * @brief	Check if two set are lexiographicaly reverse-ordered or equivalent.
 * 
 * @tparam	Key The key type of both of the set.
 * @tparam	Compare The functor to use to compare the keys.
 * @tparam	Alloc The allocator type used in both of the set.
 * 
 * @param	lhs The left hand side set to compare.
 * @param	rhs The right hand side set to compare.
 * 
 * @return	Either true if the two set are lexiographicaly reverse-ordered or equivalent, or false if not.
 */
template <typename Key, typename Compare, typename Alloc>
bool	operator>=(set<Key, Compare, Alloc> const &lhs, set<Key, Compare, Alloc> const &rhs)
{
	return !(lhs < rhs);
}

// ***************************************************************************************************************** //
//                                               Specialized Functions                                               //
// ***************************************************************************************************************** //

/**
 * @brief	Swap the contents of two given set.
 * 
 * @tparam	Key The key type of both of the set.
 * @tparam	Compare The functor to use to compare the keys.
 * @tparam	Alloc The allocator type used in both of the set.
 * 
 * @param	a The first set to swap.
 * @param	b The second set to swap.
 */
template <typename Key, typename Compare, typename Alloc>
void	swap(set<Key, Compare, Alloc> &a, set<Key, Compare, Alloc> &b)
{
	a.swap(b);
}

} // namespace ft


#endif
