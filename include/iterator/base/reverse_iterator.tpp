/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 06:00:52 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/31 11:01:35 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_TPP
# define REVERSE_ITERATOR_TPP

# include "bidirectional_iterator.tpp"
# include "iterator.hpp"

namespace ft
{
template <typename Iterator>
class reverse_iterator : public bidirectional_iterator<
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

	typedef Iterator												iterator_type;

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new reverse_iterator object. (default constructor)
	 * 
	 * @param	it The iterator to wrap.
	 */
	explicit reverse_iterator(iterator_type const &it = iterator_type()) :
		bidirectional_iterator<value_type, iterator_category, difference_type, pointer, reference>(it) {};

	/**
	 * @brief	Construct a new reverse_iterator object from another one.
	 * 			Allow iterator to constant iterator conversion. (copy constructor)
	 * 
	 * @tparam	_Iterator The type of the iterator to copy.
	 * 
	 * @param	src The reverse_iterator to copy.
	 */
	template <typename _Iterator>
	reverse_iterator(reverse_iterator<_Iterator> const &src) :
		bidirectional_iterator<value_type, iterator_category, difference_type, pointer, reference>(src.base().base()) {};

// ***************************************************************************************************************** //
//                                              Public Member Functions                                              //
// ***************************************************************************************************************** //

	/**
	 * @brief	Get a copy of the wrapped iterator.
	 * 
	 * @return	A copy of the wrapped iterator.
	 */
	iterator_type	base(void) const
	{
		return iterator_type(this->_ptr);
	};

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Dereference the pointer right before the wrapped one.
	 * 
	 * @return	The element pointed by the pointer right before the wrapped one.
	 */
	inline reference	operator*(void) const
	{
		return *(this->_ptr - 1);
	}

	/**
	 * @brief	Get the value of the pointer right before the wrapped one.
	 * 
	 * @return	The value of the pointer right before the wrapped one.
	 */
	inline pointer	operator->(void) const
	{
		return this->_ptr - 1;
	}

	/**
	 * @brief	Decrease the wrapped pointer value by 1. (prefix incrementation)
	 * 
	 * @return	A reference to the incremented reverse_iterator.
	 */
	inline reverse_iterator	&operator++(void)
	{
		--this->_ptr;
		return *this;
	}

	/**
	 * @brief	Decrease the wrapped pointer value by 1. (postfix incrementation)
	 * 
	 * @return	A copy of the reverse_iterator before the incrementation.
	 */
	inline reverse_iterator	operator++(int)
	{
		reverse_iterator	original(*this);

		--this->_ptr;
		return original;
	}

	/**
	 * @brief	Increase the wrapped pointer value by 1. (prefix decrementation)
	 * 
	 * @return	A reference to the decremented reverse_iterator.
	 */
	inline reverse_iterator	&operator--(void)
	{
		++this->_ptr;
		return *this;
	}

	/**
	 * @brief	Increase the wrapped pointer value by 1. (postfix decrementation)
	 * 
	 * @return	A copy of the reverse_iterator before the decrementation.
	 */
	inline reverse_iterator	operator--(int)
	{
		reverse_iterator	original(*this);

		++this->_ptr;
		return original;
	}

	/**
	 * @brief	Decrease the wrapped pointer value by N.
	 * 
	 * @param	rhs The number to decrease the pointer by.
	 * 
	 * @return	A reference to the decreased random_access_iterator.
	 */
	inline reverse_iterator	&operator+=(difference_type const rhs)
	{
		this->_ptr -= rhs;
		return *this;
	}

	/**
	 * @brief	Increase the wrapped pointer value by N.
	 * 
	 * @param	rhs The number to increase the pointer by.
	 * 
	 * @return	A reference to the increased random_access_iterator.
	 */
	inline reverse_iterator	&operator-=(difference_type const rhs)
	{
		this->_ptr += rhs;
		return *this;
	}

	/**
	 * @brief	Subtract N from the wrapped pointer value.
	 * 
	 * @param	rhs The number to subtract from the pointer.
	 * 
	 * @return	A random_access_iterator pointing to the new position.
	 */
	inline reverse_iterator operator+(difference_type const n) const
	{
		reverse_iterator<iterator_type>	rit(*this);

		rit += n;
		return rit;
	}

	/**
	 * @brief	Add N to the wrapped pointer value.
	 * 
	 * @param	rhs The number to add to the pointer.
	 * 
	 * @return	A random_access_iterator pointing to the new position.
	 */
	inline reverse_iterator operator-(difference_type const n) const
	{
		reverse_iterator<iterator_type>	rit(*this);

		rit -= n;
		return rit;
	}

	/**
	 * @brief	Access to a distant element from the pointed one.
	 * 
	 * @param	idx The index of the element to access.
	 * 
	 * @return	A reference to the distant element.
	 */
	inline reference	operator[](difference_type idx) const
	{
		return *(this->_ptr - idx - 1);
	}

	template <typename Iterator0, typename Iterator1>
	friend inline bool	operator==(reverse_iterator<Iterator0> const &lhs, reverse_iterator<Iterator1> const &rhs);
	template <typename Iterator0, typename Iterator1>
	friend inline bool	operator!=(reverse_iterator<Iterator0> const &lhs, reverse_iterator<Iterator1> const &rhs);
	template <typename Iterator0, typename Iterator1>
	friend inline bool	operator<(reverse_iterator<Iterator0> const &lhs, reverse_iterator<Iterator1> const &rhs);
	template <typename Iterator0, typename Iterator1>
	friend inline bool	operator>(reverse_iterator<Iterator0> const &lhs, reverse_iterator<Iterator1> const &rhs);
	template <typename Iterator0, typename Iterator1>
	friend inline bool	operator<=(reverse_iterator<Iterator0> const &lhs, reverse_iterator<Iterator1> const &rhs);
	template <typename Iterator0, typename Iterator1>
	friend inline bool	operator>=(reverse_iterator<Iterator0> const &lhs, reverse_iterator<Iterator1> const &rhs);
};

/**
 * @brief	Check if two reverse_iterator are equivalent.
 * 			Allow comparison between mutable and constant reverse_iterator.
 * 
 * @tparam	Iterator0 The type of the left hand side reverse_iterator to compare with.
 * @tparam	Iterator1 The type of the right hand side reverse_iterator to compare with.
 * 
 * @param	lhs The left hand side reverse_iterator to compare.
 * @param	rhs The right hand side reverse_iterator to compare.
 * 
 * @return	Either true if the two reverse_iterator are equivalent, or false if not.
 */
template <typename Iterator0, typename Iterator1>
inline bool	operator==(reverse_iterator<Iterator0> const &lhs, reverse_iterator<Iterator1> const &rhs)
{
	return lhs.base() == rhs.base();
}

/**
 * @brief	Check if two reverse_iterator are different.
 * 			Allow comparison between mutable and constant reverse_iterator.
 * 
 * @tparam	Iterator0 The type of the left hand side reverse_iterator to compare with.
 * @tparam	Iterator1 The type of the right hand side reverse_iterator to compare with.
 * 
 * @param	lhs The left hand side reverse_iterator to compare.
 * @param	rhs The right hand side reverse_iterator to compare.
 * 
 * @return	Either true if the two reverse_iterator are different, or false if not.
 */
template <typename Iterator0, typename Iterator1>
inline bool	operator!=(reverse_iterator<Iterator0> const &lhs, reverse_iterator<Iterator1> const &rhs)
{
	return lhs.base() != rhs.base();
}

/**
 * @brief	Check if two reverse_iterator are strictly ordered.
 * 			Allow comparison between mutable and constant reverse_iterator.
 * 
 * @tparam	Iterator0 The type of the left hand side reverse_iterator to compare with.
 * @tparam	Iterator1 The type of the right hand side reverse_iterator to compare with.
 * 
 * @param	lhs The left hand side reverse_iterator to compare.
 * @param	rhs The right hand side reverse_iterator to compare.
 * 
 * @return	Either true if the two reverse_iterator are strictly ordered, or false if not.
 */
template <typename Iterator0, typename Iterator1>
inline bool	operator<(reverse_iterator<Iterator0> const &lhs, reverse_iterator<Iterator1> const &rhs)
{
	return lhs.base() > rhs.base();
}

/**
 * @brief	Check if two reverse_iterator are strictly reverse ordered.
 * 			Allow comparison between mutable and constant reverse_iterator.
 * 
 * @tparam	Iterator0 The type of the left hand side reverse_iterator to compare with.
 * @tparam	Iterator1 The type of the right hand side reverse_iterator to compare with.
 * 
 * @param	lhs The left hand side reverse_iterator to compare.
 * @param	rhs The right hand side reverse_iterator to compare.
 * 
 * @return	Either true if the two reverse_iterator are strictly reverse ordered, or false if not.
 */
template <typename Iterator0, typename Iterator1>
inline bool	operator>(reverse_iterator<Iterator0> const &lhs, reverse_iterator<Iterator1> const &rhs)
{
	return lhs.base() < rhs.base();
}

/**
 * @brief	Check if two reverse_iterator are ordered or equivalent.
 * 			Allow comparison between mutable and constant reverse_iterator.
 * 
 * @tparam	Iterator0 The type of the left hand side reverse_iterator to compare with.
 * @tparam	Iterator1 The type of the right hand side reverse_iterator to compare with.
 * 
 * @param	lhs The left hand side reverse_iterator to compare.
 * @param	rhs The right hand side reverse_iterator to compare.
 * 
 * @return	Either true if the two reverse_iterator are ordered or equivalent, or false if not.
 */
template <typename Iterator0, typename Iterator1>
inline bool	operator<=(reverse_iterator<Iterator0> const &lhs, reverse_iterator<Iterator1> const &rhs)
{
	return lhs.base() >= rhs.base();
}

/**
 * @brief	Check if two reverse_iterator are reverse ordered or equivalent.
 * 			Allow comparison between mutable and constant reverse_iterator.
 * 
 * @tparam	Iterator0 The type of the left hand side reverse_iterator to compare with.
 * @tparam	Iterator1 The type of the right hand side reverse_iterator to compare with.
 * 
 * @param	lhs The left hand side reverse_iterator to compare.
 * @param	rhs The right hand side reverse_iterator to compare.
 * 
 * @return	Either true if the two reverse_iterator are reverse ordered or equivalent, or false if not.
 */
template <typename Iterator0, typename Iterator1>
inline bool	operator>=(reverse_iterator<Iterator0> const &lhs, reverse_iterator<Iterator1> const &rhs)
{
	return lhs.base() <= rhs.base();
}

/**
 * @brief	Subtract N from the wrapped pointer value of a reverse_iterator.
 * 
 * @tparam	Iterator The type of the iterator to wrap.
 * 
 * @param	lhs The reverse_iterator to apply the substraction.
 * @param	rhs The number to subtract from the pointer.
 * 
 * @return	A random_access_iterator pointing to the new position.
 */
template <typename Iterator>
inline reverse_iterator<Iterator>	operator+(
	typename reverse_iterator<Iterator>::difference_type lhs,
	reverse_iterator<Iterator> const &rhs)
{
	return rhs + lhs;
}

/**
 * @brief	Calculate the distance between two reverse_iterator.
 * 			Allow calculation between mutable and constant reverse_iterator.
 * 
 * @tparam	Iterator0 The type of the left hand side reverse_iterator.
 * @tparam	Iterator1 The type of the right hand side reverse_iterator.
 * 
 * @param	lhs The left hand side reverse_iterator to calculate the distance from.
 * @param	rhs The right hand side reverse_iterator to calculate the distance to.
 * 
 * @return	The distance between the two reverse_iterator.
 */
template <typename Iterator0, typename Iterator1>
inline typename reverse_iterator<Iterator0>::difference_type	operator-(
	reverse_iterator<Iterator0> const &lhs,
	reverse_iterator<Iterator1> const &rhs)
{
	return rhs.base() - lhs.base();
}
}

#endif
