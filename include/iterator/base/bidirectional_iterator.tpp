/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.tpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:18:24 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/12 14:23:31 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_TPP
# define BIDIRECTIONAL_ITERATOR_TPP

# include "forward_iterator.tpp"

namespace ft
{
/**
 * @par		This class is the implementation of the bidirectional_iterator.
 * 			According to the C++98 standard, a Bidirectional Iterator must conform to the following requirements:
 * 			- conform to the Forward Iterator requirements
 * 			- prefix decrementable (--it)
 * 			- postfix decrementable (it--)
 * 
 * @tparam	T The type of the value pointed by the iterator.
 * @tparam	Category One of the standard iterator tag to specify the iterator category.
 * @tparam	Diff The type of the difference between two iterators.
 * @tparam	Ptr The type of the pointer to the value pointed by the iterator.
 * @tparam	Ref The type of the reference to the value pointed by the iterator.
 */
template <
	typename T,
	typename Category = std::bidirectional_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class bidirectional_iterator : public forward_iterator<T, Category, Diff, Ptr, Ref>
{
public:
	// Member types
	using typename forward_iterator<T, Category, Diff, Ptr, Ref>::	iterator_category;
	using typename forward_iterator<T, Category, Diff, Ptr, Ref>::	value_type;
	using typename forward_iterator<T, Category, Diff, Ptr, Ref>::	pointer;
	using typename forward_iterator<T, Category, Diff, Ptr, Ref>::	reference;
	using typename forward_iterator<T, Category, Diff, Ptr, Ref>::	difference_type;

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new bidirectional_iterator object. (default constructor)
	 * 
	 * @param	ptr The pointer to wrap.
	 */
	bidirectional_iterator(pointer const ptr = NULL) :
		forward_iterator<value_type, iterator_category, difference_type, pointer, reference>(ptr) {}

	/**
	 * @brief	Construct a new bidirectional_iterator object.
	 * 			Allow mutable to constant bidirectional_iterator conversion. (copy constructor)
	 * 
	 * @tparam	U The type of the bidirectional_iterator to copy.
	 * 
	 * @param	src The bidirectional_iterator to copy.
	 */
	template <typename U>
	bidirectional_iterator(bidirectional_iterator<U> const &src) :
		forward_iterator<value_type, iterator_category, difference_type, pointer, reference>(src) {}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Check if two bidirectional_iterator are equivalent.
	 * 			Allow comparison between mutable and constant bidirectional_iterator.
	 * 
	 * @tparam	U The type of the bidirectional_iterator to compare with.
	 * 
	 * @param	rhs The bidirectional_iterator to compare with.
	 * 
	 * @return 	Either true if the two bidirectional_iterator are equivalent, or false if not.
	 */
	template <typename U>
	inline bool	operator==(bidirectional_iterator<U> const &rhs) const
	{
		return this->_ptr == rhs.base();
	}

	/**
	 * @brief	Check if two bidirectional_iterator are different.
	 * 			Allow comparison between mutable and constant bidirectional_iterator.
	 * 
	 * @tparam	U The type of the bidirectional_iterator to compare with.
	 * 
	 * @param	rhs The bidirectional_iterator to compare with.
	 * 
	 * @return	Either true if the two bidirectional_iterator are different, or false if not.
	 */
	template <typename U>
	inline bool	operator!=(bidirectional_iterator<U> const &rhs) const
	{
		return this->_ptr != rhs.base();
	}

	/**
	 * @brief	Decrement the wrapped pointer value by 1. (prefix decrementation)
	 * 
	 * @return	A reference to the decremented bidirectional_iterator.
	 */
	inline bidirectional_iterator	&operator--(void)
	{
		--this->_ptr;
		return *this;
	}

	/**
	 * @brief	Decrement the wrapped pointer value by 1. (postfix decrementation)
	 * 
	 * @return	A copy of the bidirectional_iterator before the decrementation.
	 */
	inline bidirectional_iterator	operator--(int)
	{
		bidirectional_iterator	original(*this);

		--this->_ptr;
		return original;
	}
};
}

#endif
