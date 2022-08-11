/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.tpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:58:58 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/11 17:33:46 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_TPP
# define VECTOR_ITERATOR_TPP

# include "iterator/base/random_access_iterator.tpp"
# include "iterator.hpp"

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
	 * 			Allow mutable to constant vector_iterator conversion.
	 * 			(copy constructor)
	 * 
	 * @tparam	_Iterator The type of the vector_iterator to copy.
	 * 
	 * @param	src The vector_iterator to copy.
	 */
	template <typename _Iterator>
	vector_iterator(vector_iterator<_Iterator> const &src) :
		random_access_iterator<
			value_type,
			iterator_category,
			difference_type,
			pointer,
			reference>(src.base()) {}

// ************************************************************************* //
//                                Destructors                                //
// ************************************************************************* //

	/**
	 * @brief	Destroy the vector_iterator object.
	 */
	~vector_iterator(void) {}

// ************************************************************************* //
//                          Public Member Functions                          //
// ************************************************************************* //

	/**
	 * @brief	Get a copy of the wrapped pointer.
	 * 
	 * @return	A copy of the wrapped pointer.
	 */
	inline pointer	base(void) const
	{
		return this->_ptr;
	}

// ************************************************************************* //
//                                 Operators                                 //
// ************************************************************************* //

	/**
	 * @brief	Check if two vector_iterator are equivalent.
	 * 			Allow comparison between mutable and constant vector_iterator.
	 * 
	 * @tparam	_Iterator The type of the vector_iterator to compare with.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are equivalent,
	 * 			or false if not.
	 */
	template <typename _Iterator>
	inline bool	operator==(vector_iterator<_Iterator> const &rhs) const
	{
		return this->base() == rhs.base();
	}

	/**
	 * @brief	Check if two vector_iterator are different.
	 * 			Allow comparison between mutable and constant vector_iterator.
	 * 
	 * @tparam	_Iterator The type of the vector_iterator to compare with.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are different,
	 * 			or false if not.
	 */
	template <typename _Iterator>
	inline bool	operator!=(vector_iterator<_Iterator> const &rhs) const
	{
		return this->base() != rhs.base();
	}

	/**
	 * @brief	Check if two vector_iterator are strictly ordered.
	 * 			Allow comparison between mutable and constant vector_iterator.
	 * 
	 * @tparam	_Iterator The type of the vector_iterator to compare with.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are strictly ordered,
	 * 			or false if not.
	 */
	template <typename _Iterator>
	inline bool	operator<(vector_iterator<_Iterator> const &rhs) const
	{
		return this->base() < rhs.base();
	}

	/**
	 * @brief	Check if two vector_iterator are strictly reverse ordered.
	 * 			Allow comparison between mutable and constant vector_iterator.
	 * 
	 * @tparam	_Iterator The type of the vector_iterator to compare with.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are strictly reverse ordered,
	 * 			or false if not.
	 */
	template <typename _Iterator>
	inline bool	operator>(vector_iterator<_Iterator> const &rhs) const
	{
		return this->base() > rhs.base();
	}

	/**
	 * @brief	Check if two vector_iterator are ordered or equivalent.
	 * 			Allow comparison between mutable and constant vector_iterator.
	 * 
	 * @tparam	_Iterator The type of the vector_iterator to compare with.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are ordered or equivalent,
	 * 			or false if not.
	 */
	template <typename _Iterator>
	inline bool	operator<=(vector_iterator<_Iterator> const &rhs) const
	{
		return this->base() <= rhs.base();
	}

	/**
	 * @brief	Check if two vector_iterator are reverse ordered or equivalent.
	 * 			Allow comparison between mutable and constant vector_iterator.
	 * 
	 * @tparam	_Iterator The type of the vector_iterator to compare with.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are reverse ordered or equivalent,
	 * 			or false if not.
	 */
	template <typename _Iterator>
	inline bool	operator>=(vector_iterator<_Iterator> const &rhs) const
	{
		return this->base() >= rhs.base();
	}

	// REMIND: See if it is possible to use the random_access_iterator member functions instead of overload them (with using keyword)
};

}

#endif
