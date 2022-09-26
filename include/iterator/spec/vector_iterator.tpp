/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.tpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:58:58 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/26 18:57:38 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_TPP
# define VECTOR_ITERATOR_TPP

# include "iterator/base/A_random_access_iterator.tpp"
# include "iterator.hpp"

namespace ft
{
template <typename Iterator>
class vector_iterator : public A_random_access_iterator<
	vector_iterator<Iterator>,
	typename iterator_traits<Iterator>::value_type,
	typename iterator_traits<Iterator>::iterator_category,
	typename iterator_traits<Iterator>::difference_type,
	typename iterator_traits<Iterator>::pointer,
	typename iterator_traits<Iterator>::reference>
{
private:
	// Member types
	typedef vector_iterator<Iterator>									_self_type;
	typedef A_random_access_iterator<
		_self_type,
		typename iterator_traits<Iterator>::value_type,
		typename iterator_traits<Iterator>::iterator_category,
		typename iterator_traits<Iterator>::difference_type,
		typename iterator_traits<Iterator>::pointer,
		typename iterator_traits<Iterator>::reference>					_base_type;

public:
	// Member types
	typedef Iterator													iterator_type;

	typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
	typedef typename iterator_traits<iterator_type>::value_type			value_type;
	typedef typename iterator_traits<iterator_type>::pointer			pointer;
	typedef typename iterator_traits<iterator_type>::reference			reference;
	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new vector_iterator object. (default constructor)
	 * 
	 * @param	ptr	The pointer to wrap.
	 */
	vector_iterator(pointer const ptr = NULL) :
		_base_type(ptr) {}

	/**
	 * @brief	Construct a new vector_iterator object from another one.
	 * 			Allow mutable to constant vector_iterator conversion. (copy constructor)
	 * 
	 * @tparam	_Iterator The type of the vector_iterator to copy.
	 * 
	 * @param	src The vector_iterator to copy.
	 */
	template <typename _Iterator>
	vector_iterator(vector_iterator<_Iterator> const &src) :
		_base_type(src.base()) {}

// ***************************************************************************************************************** //
//                                              Public Member Functions                                              //
// ***************************************************************************************************************** //

	/**
	 * @brief	Get a copy of the wrapped iterator.
	 * 
	 * @return	A copy of the wrapped iterator.
	 */
	inline iterator_type	base(void) const
	{
		return iterator_type(this->_ptr);
	}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Check if two vector_iterator are equivalent.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are equivalent, or false if not.
	 */
	inline bool	operator==(_self_type const &rhs) const
	{
		return this->base() == rhs.base();
	}

	/**
	 * @brief	Check if two vector_iterator are equivalent.
	 * 			Allow comparison between mutable and constant vector_iterator.
	 * 
	 * @tparam	_Iterator The type of the vector_iterator to compare with.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are equivalent, or false if not.
	 */
	template <typename _Iterator>
	inline bool	operator==(vector_iterator<_Iterator> const &rhs) const
	{
		return this->base() == rhs.base();
	}

	/**
	 * @brief	Check if two vector_iterator are different.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are different, or false if not.
	 */
	inline bool	operator!=(_self_type const &rhs) const
	{
		return this->base() != rhs.base();
	}

	/**
	 * @brief	Check if two vector_iterator are different.
	 * 			Allow comparison between mutable and constant vector_iterator.
	 * 
	 * @tparam	_Iterator The type of the vector_iterator to compare with.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are different, or false if not.
	 */
	template <typename _Iterator>
	inline bool	operator!=(vector_iterator<_Iterator> const &rhs) const
	{
		return this->base() != rhs.base();
	}

	/**
	 * @brief	Check if two vector_iterator are strictly ordered.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are strictly ordered, or false if not.
	 */
	inline bool	operator<(_self_type const &rhs) const
	{
		return this->base() < rhs.base();
	}

	/**
	 * @brief	Check if two vector_iterator are strictly ordered.
	 * 			Allow comparison between mutable and constant vector_iterator.
	 * 
	 * @tparam	_Iterator The type of the vector_iterator to compare with.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are strictly ordered, or false if not.
	 */
	template <typename _Iterator>
	inline bool	operator<(vector_iterator<_Iterator> const &rhs) const
	{
		return this->base() < rhs.base();
	}

	/**
	 * @brief	Check if two vector_iterator are strictly reverse ordered.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are strictly reverse ordered, or false if not.
	 */
	inline bool	operator>(_self_type const &rhs) const
	{
		return this->base() > rhs.base();
	}

	/**
	 * @brief	Check if two vector_iterator are strictly reverse ordered.
	 * 			Allow comparison between mutable and constant vector_iterator.
	 * 
	 * @tparam	_Iterator The type of the vector_iterator to compare with.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are strictly reverse ordered, or false if not.
	 */
	template <typename _Iterator>
	inline bool	operator>(vector_iterator<_Iterator> const &rhs) const
	{
		return this->base() > rhs.base();
	}

	/**
	 * @brief	Check if two vector_iterator are ordered or equivalent.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are ordered or equivalent, or false if not.
	 */
	inline bool	operator<=(_self_type const &rhs) const
	{
		return this->base() <= rhs.base();
	}

	/**
	 * @brief	Check if two vector_iterator are ordered or equivalent.
	 * 			Allow comparison between mutable and constant vector_iterator.
	 * 
	 * @tparam	_Iterator The type of the vector_iterator to compare with.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are ordered or equivalent, or false if not.
	 */
	template <typename _Iterator>
	inline bool	operator<=(vector_iterator<_Iterator> const &rhs) const
	{
		return this->base() <= rhs.base();
	}

	/**
	 * @brief	Check if two vector_iterator are reverse ordered or equivalent.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are reverse ordered or equivalent, or false if not.
	 */
	inline bool	operator>=(_self_type const &rhs) const
	{
		return this->base() >= rhs.base();
	}

	/**
	 * @brief	Check if two vector_iterator are reverse ordered or equivalent.
	 * 			Allow comparison between mutable and constant vector_iterator.
	 * 
	 * @tparam	_Iterator The type of the vector_iterator to compare with.
	 * 
	 * @param	rhs The vector_iterator to compare with.
	 * 
	 * @return	Either true if the two vector_iterator are reverse ordered or equivalent, or false if not.
	 */
	template <typename _Iterator>
	inline bool	operator>=(vector_iterator<_Iterator> const &rhs) const
	{
		return this->base() >= rhs.base();
	}

	/**
	 * @return	The element pointed by the wrapped pointer.
	 */
	inline reference	operator*(void) const
	{
		return *this->_ptr;
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
		return this->_ptr[idx];
	}

	/**
	 * @return	The wrapped pointer value.
	 */
	inline pointer	operator->(void) const
	{
		return this->_ptr;
	}

	/**
	 * @brief	Assign a new content to the vector_iterator from another one's. (copy assignation)
	 * 
	 * @param	rhs The right hand side vector_iterator to copy the content from.
	 * 
	 * @return	The assigned vector_iterator.
	 */
	inline _self_type	&operator=(_self_type const &rhs)
	{
		if (this != &rhs)
			this->_ptr = rhs._ptr;
		return *this;
	}

	/**
	 * @brief	Increase the wrapped pointer value by 1. (prefix incrementation)
	 * 
	 * @return 	A reference to the incremented vector_iterator.
	 */
	inline _self_type	&operator++(void)
	{
		++this->_ptr;
		return *this;
	}

	/**
	 * @brief	Increase the wrapped pointer value by 1. (postfix incrementation)
	 * 
	 * @return 	A copy of the vector_iterator before the incrementation.
	 */
	inline _self_type	operator++(int)
	{
		_self_type	original(*this);

		++this->_ptr;
		return original;
	}

	/**
	 * @brief	Decrease the wrapped pointer value by 1. (prefix decrementation)
	 * 
	 * @return	A reference to the decremented vector_iterator.
	 */
	inline _self_type	&operator--(void)
	{
		--this->_ptr;
		return *this;
	}

	/**
	 * @brief	Decrease the wrapped pointer value by 1. (postfix decrementation)
	 * 
	 * @return	A copy of the vector_iterator before the decrementation.
	 */
	inline _self_type	operator--(int)
	{
		_self_type	original(*this);

		--this->_ptr;
		return original;
	}

	/**
	 * @brief	Increase the wrapped pointer value by N.
	 * 
	 * @param	rhs The number to increase the pointer by.
	 * 
	 * @return	A reference to the increased vector_iterator.
	 */
	inline _self_type	&operator+=(difference_type const rhs)
	{
		this->_ptr += rhs;
		return *this;
	}

	/**
	 * @brief	Decrease the wrapped pointer value by N.
	 * 
	 * @param	rhs The number to decrease the pointer by.
	 * 
	 * @return	A reference to the decreased vector_iterator.
	 */
	inline _self_type	&operator-=(difference_type const rhs)
	{
		this->_ptr -= rhs;
		return *this;
	}

	/**
	 * @brief	Add N to the wrapped pointer value.
	 * 
	 * @param	rhs The number to add to the pointer.
	 * 
	 * @return	A vector_iterator pointing to the new position.
	 */
	inline _self_type	operator+(difference_type const rhs) const
	{
		_self_type	it(*this);

		it += rhs;
		return it;
	}

	/**
	 * @brief	Subtract N from the wrapped pointer value.
	 * 
	 * @param	rhs The number to subtract from the pointer.
	 * 
	 * @return   A vector_iterator pointing to the new position.
	 */
	inline _self_type	operator-(difference_type const rhs) const
	{
		_self_type	it(*this);

		it -= rhs;
		return it;
	}

	/**
	 * @brief	Calculate the distance between to another vector_iterator.
	 * 
	 * @param	rhs The vector_iterator to calculate the distance to.
	 * 
	 * @return	The distance between the two vector_iterator.
	 */
	inline difference_type operator-(_self_type const &rhs) const
	{
		return this->base() - rhs.base();
	}

	/**
	 * @brief	Calculate the distance between to another vector_iterator.
	 * 			Allow calculation between mutable and constant vector_iterator.
	 * 
	 * @tparam	_Iterator The type of the vector_iterator to calculate the distance to.
	 * 
	 * @param	rhs The vector_iterator to calculate the distance to.
	 * 
	 * @return	The distance between the two vector_iterator.
	 */
	template <typename _Iterator>
	inline difference_type operator-(vector_iterator<_Iterator> const &rhs) const
	{
		return this->base() - rhs.base();
	}
};

/**
 * @brief	Increment the wrapped pointer of a vector_iterator by N.
 * 
 * @param	lhs The number to increment the pointer with.
 * 
 * @return	A vector_iterator pointing to the new position.
 */
template <typename Iterator>
inline vector_iterator<Iterator>	operator+(
	typename vector_iterator<Iterator>::difference_type const lhs,
	vector_iterator<Iterator> const &rhs)
{
	return rhs + lhs;
}
}

#endif
