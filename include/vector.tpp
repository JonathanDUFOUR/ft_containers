/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 06:04:04 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/22 17:37:28 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

// ************************************************************************** //
//                                Constructors                                //
// ************************************************************************** //

template < typename T, typename Alloc >
ft::vector< T, Alloc >::vector(allocator_type const &alloc) :
	_alloc(alloc),
	_content(NULL),
	_capacity(0),
	_size(0) {}

template < typename T, typename Alloc >
ft::vector< T, Alloc >::vector(
	size_type n,
	value_type const &val,
	allocator_type const &alloc) :
	_alloc(alloc)
{
	size_type	i;

	this->reserve(n);
	this->_size = n;
	for (i = 0 ; i < n ; ++i)
		this->_content[i] = val;
}

template < typename T, typename Alloc, typename InputIterator >
ft::vector< T, Alloc >::vector(
	InputIterator first,
	InputIterator last,
	allocator_type const &alloc) :
	_alloc(alloc)
{
	size_type	i;

	this->reserve(std::distance(first, last));
	this->_size = std::distance(first, last);
	for (i = 0 ; first != last ; ++first, ++i)
		this->_content[i] = *first;
}
