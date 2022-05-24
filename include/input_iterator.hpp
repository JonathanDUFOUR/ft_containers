/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:49:20 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/24 05:16:30 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_ITERATOR_HPP
# define INPUT_ITERATOR_HPP

# include <iterator>

namespace ft
{
template <
	typename T,
	typename Category = std::input_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class input_iterator
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
	input_iterator(void) : _ptr(NULL) {}

public:
	// Constructors
	input_iterator(input_iterator const &src) : _ptr(src._ptr) {}

	// Destructors
	~input_iterator(void) {}

	// Operators
	inline input_iterator &operator=(input_iterator const &rhs) // it0 = it1
	{
		this->_ptr = rhs._ptr;
		return *this;
	}

	inline bool	operator==(input_iterator const &rhs) const // it0 == it1
	{
		return this->_ptr == rhs._ptr;
	}

	inline bool	operator!=(input_iterator const &rhs) const // it0 != it1
	{
		return this->_ptr != rhs._ptr;
	}

	inline reference	operator*(void) const // *it
	{
		return *this->_ptr;
	}

	inline input_iterator	&operator++(void) // ++it
	{
		++this->_ptr;
		return *this;
	}

	inline input_iterator	operator++(int) // it++
	{
		input_iterator	original(*this);

		++this->_ptr;
		return original;
	}
};
}

#endif
