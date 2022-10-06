/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:31:58 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/06 12:39:37 by jodufour         ###   ########.fr       */
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
	typedef rb_tree_iterator<value_type const, _node_type>			iterator;

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
		this->_tree.erase(pos.base());
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
	 * @return	The maximum number of elements that can be stored in the set.
	 */
	size_type	max_size(void) const
	{
		return allocator_type().max_size();
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
	 * @return	The number of stored elements in the set.
	 */
	size_type	size(void) const
	{
		return this->_tree.getSize();
	}

	/**
	 * @return	A value_compare default object.
	 */
	value_compare	value_comp(void) const
	{
		return value_compare();
	}
};
} // namespace ft


#endif
