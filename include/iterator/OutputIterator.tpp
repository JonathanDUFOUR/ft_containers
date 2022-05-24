/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OutputIterator.tpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:50:41 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/24 10:34:42 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUTITERATOR_TPP
# define OUTPUTITERATOR_TPP

# include <iterator>

namespace ft
{
template <
	typename T,
	typename Category = std::output_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class OutputIterator
{
public:
	// Member types
	typedef Category	iterator_category;
	typedef T			value_type;
	typedef Ptr			pointer;
	typedef Ref			reference;
	typedef Diff		difference_type;

private:
	// Attributes
	pointer	_ptr;

public:
	// Constructors
	OutputIterator(OutputIterator const &src) : _ptr(src._ptr) {}

	// Destructors
	~OutputIterator(void) {}

	// Operators
	inline OutputIterator	&operator=(OutputIterator const &rhs)
	{
		this->_ptr = rhs._ptr;
		return *this;
	}

	inline reference	operator*(void)
	{
		return *this->_ptr;
	}

	inline OutputIterator	&operator++(void) // ++it
	{
		++this->_ptr;
		return *this;
	}

	inline OutputIterator	operator++(int) // it++
	{
		OutputIterator	original(*this);

		++this->_ptr;
		return original;
	}
};
}

#endif
