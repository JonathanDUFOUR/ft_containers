/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseIterator.tpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 06:00:52 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/24 10:38:57 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSEITERATOR_TPP
# define REVERSEITERATOR_TPP

# include "BidirectionalIterator.tpp"

namespace ft
{
template <typename Iterator>
class ReverseIterator : public BidirectionalIterator<
	typename Iterator::value_type,
	typename Iterator::iterator_category,
	typename Iterator::difference_type,
	typename Iterator::pointer,
	typename Iterator::reference>
{
public:
	// Member types
	using typename Iterator::iterator_category;
	using typename Iterator::value_type;
	using typename Iterator::difference_type;
	using typename Iterator::pointer;
	using typename Iterator::reference;

	typedef Iterator	iterator_type;

private:
	// Attributes
	iterator_type	_it;

protected:
public:
	// Constructors
	ReverseIterator(void) : _it() {};
	explicit ReverseIterator(iterator_type const &it) : _it(it) {};
	ReverseIterator(ReverseIterator const &src) : _it(src._it) {};

	// Destructors
	~ReverseIterator(void) {};

	// Member functions
	iterator_type	base(void) const
	{
		return --this->_it;
	};

	// Operators
	inline ReverseIterator	&operator++(void) // ++it
	{
		--this->_it;
		return *this;
	}

	inline ReverseIterator	operator++(int) // it++
	{
		ReverseIterator	original(*this);

		--this->_it;
		return original;
	}

	inline ReverseIterator	&operator--(void) // --it
	{
		++this->_it;
		return *this;
	}

	inline ReverseIterator	operator--(int) // it--
	{
		ReverseIterator	original(*this);

		++this->_it;
		return original;
	}

	inline ReverseIterator	&operator+=(difference_type n) // it += n
	{
		this->_it -= n;
		return *this;
	}

	inline ReverseIterator	&operator-=(difference_type n) // it -= n
	{
		this->_it += n;
		return *this;
	}

	inline ReverseIterator operator+(difference_type n) const // it + n
	{
		ReverseIterator<iterator_type>	it(*this);

		it -= n;
		return it;
	}

	inline ReverseIterator operator-(difference_type n) const // it - n
	{
		ReverseIterator<iterator_type>	it(*this);

		it += n;
		return it;
	}

	inline reference	operator[](difference_type idx) const // it[idx]
	{
		return *(this->_it - idx);
	}

	inline bool	operator<(ReverseIterator const &rhs) const // it0 < it1
	{
		return this->_it > rhs._it;
	}

	inline bool	operator>(ReverseIterator const &rhs) const // it0 > it1
	{
		return this->_it < rhs._it;
	}

	inline bool	operator<=(ReverseIterator const &rhs) const // it0 <= it1
	{
		return this->_it >= rhs._it;
	}

	inline bool	operator>=(ReverseIterator const &rhs) const // it0 >= it1
	{
		return this->_it <= rhs._it;
	}
};
}

#endif
