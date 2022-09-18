/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator_restrictor.tpp              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 07:30:16 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/18 07:36:44 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_RESTRICTOR_TPP
# define BIDIRECTIONAL_ITERATOR_RESTRICTOR_TPP

# include "forward_iterator_restrictor.tpp"

namespace ft
{
/**
 * @par		This class is the implementation of the bidirectional_iterator_restrictor.
 * 			It is designed to restrict any type of iterator to the Bidirectional Iterator requirements only.
 * 			According to the C++98 standard, a Bidirectional Iterator must conform to the following requirements:
 * 			- conform to the Forward Iterator requirements
 * 			- prefix decrementable (--it)
 * 			- postfix decrementable (it--)
 * 
 * @tparam	Iterator The type of the iterator to restrict.
 */
template <typename Iterator>
class bidirectional_iterator_restrictor : public forward_iterator_restrictor<Iterator>
{
public:
	// Member types
	using typename forward_iterator_restrictor<Iterator>::		iterator_type;

	using typename forward_iterator_restrictor<iterator_type>::	iterator_category;
	using typename forward_iterator_restrictor<iterator_type>::	value_type;
	using typename forward_iterator_restrictor<iterator_type>::	pointer;
	using typename forward_iterator_restrictor<iterator_type>::	reference;
	using typename forward_iterator_restrictor<iterator_type>::	difference_type;

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new bidirectional_iterator_restrictor object. (default constructor)
	 * 
	 * @param	it The iterator to wrap.
	 */
	bidirectional_iterator_restrictor(iterator_type const &it = iterator_type()) :
		forward_iterator_restrictor<iterator_type>(it) {}

	/**
	 * @brief	Construct a new bidirectional_iterator_restrictor object.
	 * 			Allow mutable to constant bidirectional_iterator_restrictor conversion. (copy constructor)
	 * 
	 * @tparam	U The type of the bidirectional_iterator_restrictor to copy.
	 * 
	 * @param	src The bidirectional_iterator_restrictor to copy.
	 */
	template <typename U>
	bidirectional_iterator_restrictor(bidirectional_iterator_restrictor<U> const &src) :
		forward_iterator_restrictor<iterator_type>(src) {}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Check if two bidirectional_iterator_restrictor are equivalent.
	 * 			Allow comparison between mutable and constant bidirectional_iterator_restrictor.
	 * 
	 * @tparam	U The type of the bidirectional_iterator_restrictor to compare with.
	 * 
	 * @param	rhs The bidirectional_iterator_restrictor to compare with.
	 * 
	 * @return 	Either true if the two bidirectional_iterator_restrictor are equivalent, or false if not.
	 */
	template <typename U>
	inline bool	operator==(bidirectional_iterator_restrictor<U> const &rhs) const
	{
		return this->_it == rhs.base();
	}

	/**
	 * @brief	Check if two bidirectional_iterator_restrictor are different.
	 * 			Allow comparison between mutable and constant bidirectional_iterator_restrictor.
	 * 
	 * @tparam	U The type of the bidirectional_iterator_restrictor to compare with.
	 * 
	 * @param	rhs The bidirectional_iterator_restrictor to compare with.
	 * 
	 * @return	Either true if the two bidirectional_iterator_restrictor are different, or false if not.
	 */
	template <typename U>
	inline bool	operator!=(bidirectional_iterator_restrictor<U> const &rhs) const
	{
		return this->_it != rhs.base();
	}

	/**
	 * @brief	Decrement the wrapped pointer value by 1. (prefix decrementation)
	 * 
	 * @return	A reference to the decremented bidirectional_iterator_restrictor.
	 */
	inline bidirectional_iterator_restrictor	&operator--(void)
	{
		--this->_it;
		return *this;
	}

	/**
	 * @brief	Decrement the wrapped pointer value by 1. (postfix decrementation)
	 * 
	 * @return	A copy of the bidirectional_iterator_restrictor before the decrementation.
	 */
	inline bidirectional_iterator_restrictor	operator--(int)
	{
		return bidirectional_iterator_restrictor(this->_it--);
	}
};
}

#endif
