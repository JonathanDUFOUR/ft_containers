/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:42:59 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/27 18:08:23 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <vector>

namespace ft
{
template <typename T, typename Container = std::vector<T> >
class stack
{
public:
	// Member types
	typedef Container									container_type;
	typedef typename container_type::value_type			value_type;
	typedef typename container_type::reference			reference;
	typedef typename container_type::const_reference	const_reference;
	typedef typename container_type::size_type			size_type;

private:
protected:
	// Attributes
	container_type	_ctnr;

public:
	// Constructors
	explicit stack(container_type const &ctnr = container_type()) :
		_ctnr(ctnr) {}
	
	// Destructor
	~stack(void) {}

	// Member functions
	void	pop(void)
	{
		_ctnr.pop_back();
	}

	void	push(const_reference val)
	{
		_ctnr.push_back(val);
	}

	bool	empty(void) const
	{
		return _ctnr.empty();
	}

	reference	top(void)
	{
		return _ctnr.back();
	}

	const_reference	top(void) const
	{
		return _ctnr.back();
	}

	size_type	size(void) const
	{
		return _ctnr.size();
	}
};

template <typename T, typename Container>
bool	operator==(
			stack<T, Container> const &lhs,
			stack<T, Container> const &rhs)
{
	return lhs._ctnr == rhs._ctnr;
}

template <typename T, typename Container>
bool	operator!=(
			stack<T, Container> const &lhs,
			stack<T, Container> const &rhs)
{
	return lhs._ctnr != rhs._ctnr;
}

template <typename T, typename Container>
bool	operator<(
			stack<T, Container> const &lhs,
			stack<T, Container> const &rhs)
{
	return lhs._ctnr < rhs._ctnr;
}

template <typename T, typename Container>
bool	operator>(
			stack<T, Container> const &lhs,
			stack<T, Container> const &rhs)
{
	return lhs._ctnr > rhs._ctnr;
}

template <typename T, typename Container>
bool	operator<=(
			stack<T, Container> const &lhs,
			stack<T, Container> const &rhs)
{
	return lhs._ctnr <= rhs._ctnr;
}

template <typename T, typename Container>
bool	operator>=(
			stack<T, Container> const &lhs,
			stack<T, Container> const &rhs)
{
	return lhs._ctnr >= rhs._ctnr;
}
}

#endif
