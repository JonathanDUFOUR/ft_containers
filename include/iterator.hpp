/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 10:25:41 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/27 15:51:55 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iterator>

namespace ft
{
template <typename Iterator>
class iterator_traits
{
public:
	// Member types
	typedef typename Iterator::iterator_category	iterator_category;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::difference_type		difference_type;

}; // class iterator_traits

template <typename T>
class iterator_traits <T *>
{
public:
	// Member types
	typedef std::random_access_iterator_tag	iterator_category;
	typedef T								value_type;
	typedef T *								pointer;
	typedef T &								reference;
	typedef std::ptrdiff_t					difference_type;

}; // class iterator_traits

template <typename T>
class iterator_traits <T const *>
{
public:
	// Member types
	typedef std::random_access_iterator_tag	iterator_category;
	typedef T								value_type;
	typedef T const *						pointer;
	typedef T const &						reference;
	typedef std::ptrdiff_t					difference_type;

}; // class iterator_traits

}

#endif
