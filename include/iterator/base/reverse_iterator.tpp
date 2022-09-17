/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 06:00:52 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/17 06:16:57 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_TPP
# define REVERSE_ITERATOR_TPP

# include "iterator.hpp"

namespace ft
{
/**
 * @par		This class is the implementation of the reverse_iterator.
 * 			Reverse iterators iterate backwards: increasing them moves them towards the beginning of the range.
 * 			They are implemented as a wrapper around a normal iterator.
 * 
 * @tparam	BidirectionalIterator The type of the iterator to wrap.
 * 			(it must conform to the standard bidirectional iterator requirements)
 */
template <typename BidirectionalIterator>
class reverse_iterator
{
public:
	// Member types
	typedef BidirectionalIterator										iterator_type;

	typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
	typedef typename iterator_traits<iterator_type>::value_type			value_type;
	typedef typename iterator_traits<iterator_type>::pointer			pointer;
	typedef typename iterator_traits<iterator_type>::reference			reference;
	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;


private:
	// Attributes
	iterator_type	_it;

public:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new reverse_iterator object. (default constructor)
	 * 
	 * @param	it The iterator to wrap.
	 */
	explicit reverse_iterator(iterator_type const &it = iterator_type()) :
		_it(it) {};

	/**
	 * @brief	Construct a new reverse_iterator object from another one.
	 * 			Allow iterator to constant iterator conversion. (copy constructor)
	 * 
	 * @tparam	_BidirectionalIterator The type of the iterator to copy.
	 * 			(it must conform to the standard bidirectional iterator requirements)
	 * 
	 * @param	src The reverse_iterator to copy.
	 */
	template <typename _BidirectionalIterator>
	reverse_iterator(reverse_iterator<_BidirectionalIterator> const &src) :
		_it(src.base()) {};

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
		return this->_it;
	};

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Dereference the iterator right before the wrapped one.
	 * 
	 * @return	The element pointed by the iterator right before the wrapped one.
	 */
	inline reference	operator*(void) const
	{
		iterator_type	tmp(this->_it);

		return *--tmp;
	}

	/**
	 * @brief	Get the value of the pointer stored in the iterator right before the wrapped one.
	 * 
	 * @return	The value of the pointer stored in the iterator right before the wrapped one.
	 */
	inline pointer	operator->(void) const
	{
		return &**this;
	}

	/**
	 * @brief	Decrement the wrapped iterator by 1. (prefix incrementation)
	 * 
	 * @return	A reference to the incremented reverse_iterator.
	 */
	inline reverse_iterator	&operator++(void)
	{
		--this->_it;
		return *this;
	}

	/**
	 * @brief	Decrement the wrapped iterator by 1. (postfix incrementation)
	 * 
	 * @return	A copy of the reverse_iterator before the incrementation.
	 */
	inline reverse_iterator	operator++(int)
	{
		reverse_iterator	original(*this);

		--this->_it;
		return original;
	}

	/**
	 * @brief	Increment the wrapped iterator by 1. (prefix decrementation)
	 * 
	 * @return	A reference to the decremented reverse_iterator.
	 */
	inline reverse_iterator	&operator--(void)
	{
		++this->_it;
		return *this;
	}

	/**
	 * @brief	Increment the wrapped iterator by 1. (postfix decrementation)
	 * 
	 * @return	A copy of the reverse_iterator before the decrementation.
	 */
	inline reverse_iterator	operator--(int)
	{
		reverse_iterator	original(*this);

		++this->_it;
		return original;
	}

	/**
	 * @brief	Decrement the wrapped iterator by N.
	 * 
	 * @param	rhs The number to decrement the wrapped iterator by.
	 * 
	 * @return	A reference to the updated random_access_iterator.
	 */
	inline reverse_iterator	&operator+=(difference_type const rhs)
	{
		this->_it -= rhs;
		return *this;
	}

	/**
	 * @brief	Increment the wrapped iterator by N.
	 * 
	 * @param	rhs The number to increment the wrapped iterator by.
	 * 
	 * @return	A reference to the updated random_access_iterator.
	 */
	inline reverse_iterator	&operator-=(difference_type const rhs)
	{
		this->_it += rhs;
		return *this;
	}

	/**
	 * @brief	Get a reverse_iterator placed at a N distance ahead of the current one.
	 * 
	 * @param	rhs The distance between the wanted current and the wanted position.
	 * 
	 * @return	A random_access_iterator pointing to the new position.
	 */
	inline reverse_iterator operator+(difference_type const n) const
	{
		reverse_iterator	rit(*this);

		rit += n;
		return rit;
	}

	/**
	 * @brief	Get a reverse_iterator placed at a N distance before the current one.
	 * 
	 * @param	rhs The distance between the wanted current and the wanted position.
	 * 
	 * @return	A random_access_iterator pointing to the new position.
	 */
	inline reverse_iterator operator-(difference_type const n) const
	{
		reverse_iterator	rit(*this);

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
		return this->_it[-idx - 1];
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
