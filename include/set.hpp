/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:31:58 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/04 16:59:42 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include "rb_tree.tpp"

namespace ft
{
template <typename Key, typename Compare = std::less<Key>, typename Alloc = std::allocator<rb_node<Key> > >
class set
{
private:
	// Member types
	typedef rb_node<Key const>	_node_type;

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
	typedef rb_tree_iterator<value_type, _node_type>				iterator;

	typedef typename iterator_traits<iterator>::difference_type		difference_type;
	typedef size_t													size_type;

private:
	// Attributes
	rb_tree<value_type, value_compare, allocator_type>	_tree;

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
	 * @return	A value_compare default object.
	 */
	value_compare	value_comp(void) const
	{
		return value_compare();
	}
};
} // namespace ft


#endif
