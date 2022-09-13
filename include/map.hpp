/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:42:51 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/12 15:25:55 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "rb_tree.tpp"
# include <map>

namespace ft
{
template <
	typename Key,
	typename T,
	typename Compare = std::less<pair<Key, T> >,
	typename Alloc = std::allocator<pair<Key const, T> > >
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

	struct value_compare
	{
		bool	operator()(value_type const &a, value_type const &b) const
		{
			return key_compare(a.first, b.first);
		}
	};

private:
	// Attributes
	rb_tree<value_type, value_compare, allocator_type>	tree;
};
}

#endif
