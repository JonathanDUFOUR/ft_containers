/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:42:51 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/17 05:28:02 by jodufour         ###   ########.fr       */
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
	typename Compare = std::less<pair<Key, T> >,
	typename Alloc = std::allocator<rb_node<pair<Key const, T> > > >
class map
{
public:
	// Member types
	typedef Key													key_type;
	typedef T													mapped_type;
	typedef pair<key_type const, mapped_type>					value_type;
	typedef Compare												key_compare;
	typedef Alloc												allocator_type;

	typedef typename allocator_type::const_reference			const_reference;
	typedef typename allocator_type::reference					reference;

	typedef typename allocator_type::const_pointer				const_pointer;
	typedef typename allocator_type::pointer					pointer;

	typedef rb_tree_iterator<const_pointer>						const_iterator;
	typedef rb_tree_iterator<pointer>							iterator;

	typedef reverse_iterator<const_iterator>					const_reverse_iterator;
	typedef reverse_iterator<iterator>							reverse_iterator;

	typedef typename iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t												size_type;

	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
	private:
		// Attributes
		key_compare	_cmp;

		friend class map<Key, T, Compare, Alloc>;

	public:
		// Operators
		bool operator()(value_type const &lhs, value_type const &rhs) const
		{
			return this->_cmp(lhs, rhs);
		}
	};

private:
	// Attributes
	rb_tree<value_type, value_compare, allocator_type>	_tree;

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
	map(InputIterator const &first,
		InputIterator const &last,
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
};
}

#endif
