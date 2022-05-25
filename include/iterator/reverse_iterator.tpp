/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 06:00:52 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/25 21:42:42 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_TPP
# define REVERSE_ITERATOR_TPP

# include "bidirectional_iterator.tpp"

namespace ft
{
template <typename Iterator>
class reverse_iterator : public bidirectional_iterator<
	typename Iterator::value_type,
	typename Iterator::iterator_category,
	typename Iterator::difference_type,
	typename Iterator::pointer,
	typename Iterator::reference>
{
public:
	// Member types
	using typename bidirectional_iterator<
		typename Iterator::value_type,
		typename Iterator::iterator_category,
		typename Iterator::difference_type,
		typename Iterator::pointer,
		typename Iterator::reference>::iterator_category;
	using typename bidirectional_iterator<
		typename Iterator::value_type,
		typename Iterator::iterator_category,
		typename Iterator::difference_type,
		typename Iterator::pointer,
		typename Iterator::reference>::value_type;
	using typename bidirectional_iterator<
		typename Iterator::value_type,
		typename Iterator::iterator_category,
		typename Iterator::difference_type,
		typename Iterator::pointer,
		typename Iterator::reference>::difference_type;
	using typename bidirectional_iterator<
		typename Iterator::value_type,
		typename Iterator::iterator_category,
		typename Iterator::difference_type,
		typename Iterator::pointer,
		typename Iterator::reference>::pointer;
	using typename bidirectional_iterator<
		typename Iterator::value_type,
		typename Iterator::iterator_category,
		typename Iterator::difference_type,
		typename Iterator::pointer,
		typename Iterator::reference>::reference;

	typedef Iterator	iterator_type;

private:
	// Attributes
	iterator_type	_it;

protected:
public:
	// Constructors
	reverse_iterator(void) : _it() {};
	explicit reverse_iterator(iterator_type const &it) : _it(it) {};
	reverse_iterator(reverse_iterator const &src) : _it(src._it) {};

	// Destructors
	~reverse_iterator(void) {};

	// Member functions
	iterator_type	base(void) const
	{
		return this->_it - 1;
	};

	// Operators
	inline reverse_iterator	&operator++(void) // ++rit
	{
		--this->_it;
		return *this;
	}

	inline reverse_iterator	operator++(int) // rit++
	{
		reverse_iterator	original(*this);

		--this->_it;
		return original;
	}

	inline reverse_iterator	&operator--(void) // --rit
	{
		++this->_it;
		return *this;
	}

	inline reverse_iterator	operator--(int) // rit--
	{
		reverse_iterator	original(*this);

		++this->_it;
		return original;
	}

	inline reverse_iterator	&operator+=(difference_type n) // rit += n
	{
		this->_it -= n;
		return *this;
	}

	inline reverse_iterator	&operator-=(difference_type n) // rit -= n
	{
		this->_it += n;
		return *this;
	}

	inline reverse_iterator operator+(difference_type n) const // rit + n
	{
		reverse_iterator<iterator_type>	it(*this);

		it -= n;
		return it;
	}

	inline reverse_iterator operator-(difference_type n) const // rit - n
	{
		reverse_iterator<iterator_type>	it(*this);

		it += n;
		return it;
	}

	inline reference	operator[](difference_type idx) const // rit[idx]
	{
		return *(this->_it - idx);
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
	return lhs.base() - rhs.base();
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
