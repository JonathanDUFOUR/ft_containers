/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator_restrictor.tpp              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 07:37:34 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/18 07:47:16 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_RESTRICTOR_TPP
# define RANDOM_ACCESS_ITERATOR_RESTRICTOR_TPP

# include "bidirectional_iterator_restrictor.tpp"

namespace ft
{
/**
 * @par		This class is the implementation of the radom_access_iterator_restrictor.
 * 			It is designed to restrict any type of iterator to the Random Access Iterator requirements only.
 * 			According to the C++98 standard, a Random Access Iterator must conform to the following requirements:
 * 			- conform to the Bidirectional Iterator requirements
 * 			- distance incrementable (it += n)
 * 			- distance decrementable (it -= n)
 * 			- distance addable (it + n || n + it)
 * 			- distance subtractable (it - n)
 * 			- distance calculable (it0 - it1)
 * 			- subscriptable (it[n])
 * 			- lower comparable (it0 < it1)
 * 			- greater comparable (it0 > it1)
 * 			- lower or equal comparable (it0 <= it1)
 * 			- greater or equal comparable (it0 >= it1)
 * 
 * @tparam	Iterator The type of the iterator to restrict.
 */
template <typename Iterator>
class random_access_iterator_restrictor : public bidirectional_iterator_restrictor<Iterator>
{
public:
	// Member types
	using typename bidirectional_iterator_restrictor<Iterator>::		iterator_type;

	using typename bidirectional_iterator_restrictor<iterator_type>::	iterator_category;
	using typename bidirectional_iterator_restrictor<iterator_type>::	value_type;
	using typename bidirectional_iterator_restrictor<iterator_type>::	pointer;
	using typename bidirectional_iterator_restrictor<iterator_type>::	reference;
	using typename bidirectional_iterator_restrictor<iterator_type>::	difference_type;

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new random_access_iterator_restrictor object. (default constructor)
	 * 
	 * @param	it	The iterator to wrap.
	 */
	random_access_iterator_restrictor(iterator_type const &it = iterator_type()) :
		bidirectional_iterator_restrictor<iterator_type>(it) {}

	/**
	 * @brief	Construct a new random_access_iterator_restrictor object.
	 * 			Allow mutable to constant random_access_iterator_restrictor conversion. (copy constructor)
	 * 
	 * @tparam	U The type of the random_access_iterator_restrictor to copy.
	 * 
	 * @param	src The random_access_iterator_restrictor to copy.
	 */
	template <typename U>
	random_access_iterator_restrictor(random_access_iterator_restrictor<U> const &src) :
		bidirectional_iterator_restrictor<iterator_type>(src) {}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Check if two random_access_iterator_restrictor are equivalent.
	 * 			Allow comparison between mutable and constant random_access_iterator_restrictor.
	 * 
	 * @tparam	U The type of the random_access_iterator_restrictor to compare with.
	 * 
	 * @param	rhs The random_access_iterator_restrictor to compare with.
	 * 
	 * @return 	Either true if the two random_access_iterator_restrictor are equivalent, or false if not.
	 */
	template <typename U>
	inline bool	operator==(random_access_iterator_restrictor<U> const &rhs) const
	{
		return this->_it == rhs.base();
	}

	/**
	 * @brief	Check if two random_access_iterator_restrictor are different.
	 * 			Allow comparison between mutable and constant random_access_iterator_restrictor.
	 * 
	 * @tparam	U The type of the random_access_iterator_restrictor to compare with.
	 * 
	 * @param	rhs The random_access_iterator_restrictor to compare with.
	 * 
	 * @return	Either true if the two random_access_iterator_restrictor are different, or false if not.
	 */
	template <typename U>
	inline bool	operator!=(random_access_iterator_restrictor<U> const &rhs) const
	{
		return this->_it != rhs.base();
	}

	/**
	 * @brief	Check if two random_access_iterator_restrictor are strictly ordered.
	 * 			Allow comparison between mutable and constant random_access_iterator_restrictor.
	 * 
	 * @tparam	U The type of the random_access_iterator_restrictor to compare with.
	 * 
	 * @param	rhs The random_access_iterator_restrictor to compare with.
	 * 
	 * @return	Either true if the two random_access_iterator_restrictor are strictly ordered, or false if not.
	 */
	template <typename U>
	inline bool	operator<(random_access_iterator_restrictor<U> const &rhs) const
	{
		return this->_it < rhs.base();
	}

	/**
	 * @brief	Check if two random_access_iterator_restrictor are strictly reverse ordered.
	 * 			Allow comparison between mutable and constant random_access_iterator_restrictor.
	 * 
	 * @tparam	U The type of the random_access_iterator_restrictor to compare with.
	 * 
	 * @param	rhs The random_access_iterator_restrictor to compare with.
	 * 
	 * @return	Either true if the two random_access_iterator_restrictor are strictly reverse ordered, or false if not.
	 */
	template <typename U>
	inline bool	operator>(random_access_iterator_restrictor<U> const &rhs) const
	{
		return this->_it > rhs.base();
	}

	/**
	 * @brief	Check if two random_access_iterator_restrictor are ordered or equivalent.
	 * 			Allow comparison between mutable and constant random_access_iterator_restrictor.
	 * 
	 * @tparam	U The type of the random_access_iterator_restrictor to compare with.
	 * 
	 * @param	rhs The random_access_iterator_restrictor to compare with.
	 * 
	 * @return	Either true if the two random_access_iterator_restrictor are ordered or equivalent, or false if not.
	 */
	template <typename U>
	inline bool	operator<=(random_access_iterator_restrictor<U> const &rhs) const
	{
		return this->_it <= rhs.base();
	}

	/**
	 * @brief	Check if two random_access_iterator_restrictor are reverse ordered or equivalent.
	 * 			Allow comparison between mutable and constant random_access_iterator_restrictor.
	 * 
	 * @tparam	U The type of the random_access_iterator_restrictor to compare with.
	 * 
	 * @param	rhs The random_access_iterator_restrictor to compare with.
	 * 
	 * @return	Either true if the two random_access_iterator_restrictor are reverse ordered or equivalent, or false if not.
	 */
	template <typename U>
	inline bool	operator>=(random_access_iterator_restrictor<U> const &rhs) const
	{
		return this->_it >= rhs.base();
	}

	/**
	 * @brief	Increase the wrapped pointer value by N.
	 * 
	 * @param	rhs The number to increase the pointer by.
	 * 
	 * @return	A reference to the increased random_access_iterator_restrictor.
	 */
	inline random_access_iterator_restrictor	&operator+=(difference_type const rhs)
	{
		this->_it += rhs;
		return *this;
	}

	/**
	 * @brief	Decrease the wrapped pointer value by N.
	 * 
	 * @param	rhs The number to decrease the pointer by.
	 * 
	 * @return	A reference to the decreased random_access_iterator_restrictor.
	 */
	inline random_access_iterator_restrictor	&operator-=(difference_type const rhs)
	{
		this->_it -= rhs;
		return *this;
	}

	/**
	 * @brief	Add N to the wrapped pointer value.
	 * 
	 * @param	rhs The number to add to the pointer.
	 * 
	 * @return	A random_access_iterator_restrictor pointing to the new position.
	 */
	inline random_access_iterator_restrictor	operator+(difference_type const rhs) const
	{
		return random_access_iterator_restrictor<iterator_type>(this->_it + rhs);
	}

	/**
	 * @brief	Subtract N from the wrapped pointer value.
	 * 
	 * @param	rhs The number to subtract from the pointer.
	 * 
	 * @return   A random_access_iterator_restrictor pointing to the new position.
	 */
	inline random_access_iterator_restrictor	operator-(difference_type const rhs) const
	{
		return random_access_iterator_restrictor<iterator_type>(this->_it - rhs);
	}

	/**
	 * @brief	Calculate the distance between two random_access_iterator_restrictor.
	 * 
	 * @param	rhs The random_access_iterator_restrictor to calculate the distance to.
	 * 
	 * @return	The distance between the two random_access_iterator_restrictor.
	 */
	inline difference_type operator-(random_access_iterator_restrictor const &rhs) const
	{
		return this->_it - rhs.base();
	}

	/**
	 * @brief	Access to a distant element from the pointed one.
	 * 
	 * @param	idx The index of the element to access.
	 * 
	 * @return	A reference to the distant element.
	 */
	inline reference	operator[](difference_type const idx) const
	{
		return this->_it[idx];
	}
};

/**
 * @brief	Increment the wrapped pointer of a random_access_iterator_restrictor by N.
 * 
 * @param	lhs The number to increment the pointer with.
 * @param	rhs The random_access_iterator_restrictor to increment.
 * 
 * @return	A random_access_iterator_restrictor pointing to the new position.
 */
template<typename Iterator>
inline random_access_iterator_restrictor<Iterator>	operator+(
	typename random_access_iterator_restrictor<Iterator>::difference_type const lhs,
	random_access_iterator_restrictor<Iterator> const &rhs)
{
	return rhs + lhs;
}
}

#endif
