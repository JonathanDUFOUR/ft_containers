/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.tpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:58:58 by jodufour          #+#    #+#             */
/*   Updated: 2022/06/01 12:45:31 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_TPP
# define VECTOR_ITERATOR_TPP

# include "iterator/base/random_access_iterator.tpp"
# include "iterator/iterator_traits.hpp"

namespace ft
{
template <typename Iterator>
class vector_iterator : public random_access_iterator<
	typename iterator_traits<Iterator>::value_type,
	typename iterator_traits<Iterator>::iterator_category,
	typename iterator_traits<Iterator>::difference_type,
	typename iterator_traits<Iterator>::pointer,
	typename iterator_traits<Iterator>::reference>
{
public:
	// Member types
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;

// ************************************************************************** //
//                                Constructors                                //
// ************************************************************************** //

	/**
	 * @brief	Construct a new vector_iterator object.
	 * 			(default constructor)
	 * 
	 * @param	ptr	The pointer to wrap.
	 */
	vector_iterator(pointer const ptr = NULL) :
		random_access_iterator<
			value_type,
			iterator_category,
			difference_type,
			pointer,
			reference>(ptr) {}

	/**
	 * @brief	Construct a new vector_iterator object from another one.
	 * 			Allow iterator to constant iterator conversion.
	 * 			(copy constructor)
	 * 
	 * @tparam	_Iterator The type of the iterator to copy.
	 * 
	 * @param	src The iterator to copy.
	 */
	template <typename _Iterator>
	vector_iterator(vector_iterator<_Iterator> const &src) :
		random_access_iterator<
			value_type,
			iterator_category,
			difference_type,
			pointer,
			reference>(src.operator->()) {}

// ************************************************************************* //
//                                Destructors                                //
// ************************************************************************* //

	/**
	 * @brief	Destroy the vector_iterator object.
	 */
	~vector_iterator(void) {}
};
}

#endif
