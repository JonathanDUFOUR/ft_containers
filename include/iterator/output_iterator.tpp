/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_iterator.tpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:50:41 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/25 10:00:31 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_ITERATOR_TPP
# define OUTPUT_ITERATOR_TPP

# include <iterator>

namespace ft
{
template <
	typename T,
	typename Category = std::output_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class output_iterator
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
	output_iterator(pointer const ptr) : _ptr(ptr) {}
	output_iterator(output_iterator const &src) : _ptr(src._ptr) {}

	// Destructors
	~output_iterator(void) {}

	// Operators
	inline output_iterator	&operator=(output_iterator const &rhs) // it0 = it1
	{
		this->_ptr = rhs._ptr;
		return *this;
	}

	inline reference	operator*(void) // *it
	{
		return *this->_ptr;
	}

	inline output_iterator	&operator++(void) // ++it
	{
		++this->_ptr;
		return *this;
	}

	inline output_iterator	operator++(int) // it++
	{
		output_iterator	original(*this);

		++this->_ptr;
		return original;
	}
};
}

#endif
