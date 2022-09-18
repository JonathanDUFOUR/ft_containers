/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward_iterator_restrictor.tpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:54:37 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/18 07:15:28 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORWARD_ITERATOR_RESTRICTOR_TPP
# define FORWARD_ITERATOR_RESTRICTOR_TPP

# include "input_iterator_restrictor.tpp"

namespace ft
{
/**
 * @par		This class is the implementation of the forward_iterator_restrictor.
 * 			It is designed to restrict any type of iterator to the Forward Iterator requirements only.
 * 			According to the C++98 standard, a Forward Iterator must conform to the following requirements:
 * 			- conform to the Input Iterator requirements
 * 			- default constructible (it) (it())
 * 
 * @tparam	Iterator The type of the iterator to restrict.
 */
template <typename Iterator>
class forward_iterator_restrictor : public input_iterator_restrictor<Iterator>
{
public:
	// Member types
	using typename input_iterator_restrictor<Iterator>::		iterator_type;

	using typename input_iterator_restrictor<iterator_type>::	iterator_category;
	using typename input_iterator_restrictor<iterator_type>::	value_type;
	using typename input_iterator_restrictor<iterator_type>::	pointer;
	using typename input_iterator_restrictor<iterator_type>::	reference;
	using typename input_iterator_restrictor<iterator_type>::	difference_type;

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new forward_iterator_restrictor object. (default constructor)
	 * 
	 * @param	it The iterator to wrap.
	 */
	forward_iterator_restrictor(iterator_type const &it = iterator_type()) :
		input_iterator_restrictor<iterator_type>(it) {}

	/**
	 * @brief	Construct a new forward_iterator_restrictor object from another one.
	 * 			Allow mutable to constant forward_iterator_restrictor conversion. (copy constructor)
	 * 
	 * @tparam	U The type of the forward_iterator_restrictor to copy.
	 * 
	 * @param	src The forward_iterator_restrictor to copy.
	 */
	template <typename U>
	forward_iterator_restrictor(forward_iterator_restrictor<U> const &src) :
		input_iterator_restrictor<iterator_type>(src) {}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Check if two forward_iterator_restrictor are equivalent.
	 * 			Allow comparison between mutable and constant forward_iterator_restrictor.
	 * 
	 * @tparam	U The type of the forward_iterator_restrictor to compare with.
	 * 
	 * @param	rhs The forward_iterator_restrictor to compare with.
	 * 
	 * @return 	Either true if the two forward_iterator_restrictor are equivalent, or false if not.
	 */
	template <typename U>
	inline bool	operator==(forward_iterator_restrictor<U> const &rhs) const
	{
		return this->_it == rhs.base();
	}

	/**
	 * @brief	Check if two forward_iterator_restrictor are different.
	 * 			Allow comparison between mutable and constant forward_iterator_restrictor.
	 * 
	 * @tparam	U The type of the forward_iterator_restrictor to compare with.
	 * 
	 * @param	rhs The forward_iterator_restrictor to compare with.
	 * 
	 * @return	Either true if the two forward_iterator_restrictor are different, or false if not.
	 */
	template <typename U>
	inline bool	operator!=(forward_iterator_restrictor<U> const &rhs) const
	{
		return this->_it != rhs.base();
	}
};
}

#endif
