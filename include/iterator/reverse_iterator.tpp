/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 06:00:52 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/30 12:32:15 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_TPP
# define REVERSE_ITERATOR_TPP

# include "bidirectional_iterator.tpp"
# include "iterator_traits.hpp"

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

	typedef Iterator	iterator_type;

	// Constructors
	reverse_iterator(void) :
		bidirectional_iterator<
			value_type,
			iterator_category,
			difference_type,
			pointer,
			reference>() {};
	explicit reverse_iterator(iterator_type const &it) :
		bidirectional_iterator<
			value_type,
			iterator_category,
			difference_type,
			pointer,
			reference>(it) {};
	reverse_iterator(reverse_iterator const &src) :
		bidirectional_iterator<
			value_type,
			iterator_category,
			difference_type,
			pointer,
			reference>(src._ptr) {};

	// Destructors
	~reverse_iterator(void) {};

	// Member functions
	iterator_type	base(void) const
	{
		return iterator_type(this->_ptr);
	};

	// Operators
	inline reference	operator*(void) const // *it
	{
		return *(this->_ptr - 1);
	}

	inline pointer	operator->(void) const // it->member
	{
		return this->_ptr - 1;
	}

	inline reverse_iterator	&operator++(void) // ++rit
	{
		--this->_ptr;
		return *this;
	}

	inline reverse_iterator	operator++(int) // rit++
	{
		reverse_iterator	original(*this);

		--this->_ptr;
		return original;
	}

	inline reverse_iterator	&operator--(void) // --rit
	{
		++this->_ptr;
		return *this;
	}

	inline reverse_iterator	operator--(int) // rit--
	{
		reverse_iterator	original(*this);

		++this->_ptr;
		return original;
	}

	inline reverse_iterator	&operator+=(difference_type n) // rit += n
	{
		this->_ptr -= n;
		return *this;
	}

	inline reverse_iterator	&operator-=(difference_type n) // rit -= n
	{
		this->_ptr += n;
		return *this;
	}

	inline reverse_iterator operator+(difference_type n) const // rit + n
	{
		reverse_iterator<iterator_type>	rit(*this);

		rit += n;
		return rit;
	}

	inline reverse_iterator operator-(difference_type n) const // rit - n
	{
		reverse_iterator<iterator_type>	rit(*this);

		rit -= n;
		return rit;
	}

	inline reference	operator[](difference_type idx) const // rit[idx]
	{
		return *(this->_ptr - idx - 1);
	}
};

template <typename Iterator>
inline reverse_iterator<Iterator>	operator+(
	typename reverse_iterator<Iterator>::difference_type lhs,
	reverse_iterator<Iterator> const &rhs) // n + rit
{
	return rhs + lhs;
}

template <typename Iterator>
inline typename reverse_iterator<Iterator>::difference_type	operator-(
	reverse_iterator<Iterator> const &lhs,
	reverse_iterator<Iterator> const &rhs) // rit0 - rit1
{
	return rhs.base() - lhs.base();
}

template <typename Iterator>
inline bool	operator==(
	reverse_iterator<Iterator> const &lhs,
	reverse_iterator<Iterator> const &rhs) // rit0 == rit1
{
	return lhs.base() == rhs.base();
}

template <typename Iterator>
inline bool	operator!=(
	reverse_iterator<Iterator> const &lhs,
	reverse_iterator<Iterator> const &rhs) // rit0 != rit1
{
	return lhs.base() != rhs.base();
}

template <typename Iterator>
inline bool	operator<(
	reverse_iterator<Iterator> const &lhs,
	reverse_iterator<Iterator> const &rhs) // rit0 < rit1
{
	return lhs.base() > rhs.base();
}

template <typename Iterator>
inline bool	operator>(
	reverse_iterator<Iterator> const &lhs,
	reverse_iterator<Iterator> const &rhs) // rit0 > rit1
{
	return lhs.base() < rhs.base();
}

template <typename Iterator>
inline bool	operator<=(
	reverse_iterator<Iterator> const &lhs,
	reverse_iterator<Iterator> const &rhs) // rit0 <= rit1
{
	return lhs.base() >= rhs.base();
}

template <typename Iterator>
inline bool	operator>=(
	reverse_iterator<Iterator> const &lhs,
	reverse_iterator<Iterator> const &rhs) // rit0 >= rit1
{
	return lhs.base() <= rhs.base();
}
}

#endif
