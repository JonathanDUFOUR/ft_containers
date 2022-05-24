/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputIterator.tpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:49:20 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/24 12:03:57 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTITERATOR_TPP
# define INPUTITERATOR_TPP

# include <iterator>

namespace ft
{
template <
	typename T,
	typename Category = std::input_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class InputIterator
{
public:
	// Member types
	typedef Category	iterator_category;
	typedef T			value_type;
	typedef Ptr			pointer;
	typedef Ref			reference;
	typedef Diff		difference_type;

protected:
	// Attributes
	pointer	_ptr;

	// Constructors
	InputIterator(void) : _ptr(NULL) {}

public:
	// Constructors
	InputIterator(pointer const ptr) : _ptr(ptr) {}

	InputIterator(InputIterator const &src) : _ptr(src._ptr) {}

	// Destructors
	~InputIterator(void) {}

	// Operators
	inline InputIterator &operator=(InputIterator const &rhs) // it0 = it1
	{
		this->_ptr = rhs._ptr;
		return *this;
	}

	inline bool	operator==(InputIterator const &rhs) const // it0 == it1
	{
		return this->_ptr == rhs._ptr;
	}

	inline bool	operator!=(InputIterator const &rhs) const // it0 != it1
	{
		return this->_ptr != rhs._ptr;
	}

	inline reference	operator*(void) const // *it
	{
		return *this->_ptr;
	}

	inline pointer	operator->(void) const // it->member
	{
		return this->_ptr;
	}

	inline /* virtual */ InputIterator	&operator++(void) // ++it
	{
		++this->_ptr;
		return *this;
	}

	inline /* virtual */ InputIterator	operator++(int) // it++
	{
		InputIterator	original(*this);

		++this->_ptr;
		return original;
	}
};
}

#endif
