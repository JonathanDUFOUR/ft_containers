/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:42:59 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/31 17:56:40 by jodufour         ###   ########.fr       */
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

protected:
	// Attributes
	container_type	_ctnr;

public:
// ************************************************************************** //
//                                Constructors                                //
// ************************************************************************** //

	/**
	 * @brief	Construct a new stack object.
	 * 
	 * @param	ctnr An optional underlying container to use for instanciation.
	 */
	explicit stack(container_type const &ctnr = container_type()) :
		_ctnr(ctnr) {}

// ************************************************************************* //
//                                Destructors                                //
// ************************************************************************* //

	/**
	 * @brief	Destruct a stack object.
	 */
	~stack(void) {}

// ************************************************************************* //
//                          Public Member Functions                          //
// ************************************************************************* //

	/**
	 * @brief	Pop the element placed on the top of the stack.
	 */
	void	pop(void)
	{
		_ctnr.pop_back();
	}

	/**
	 * @brief	Push an element on the top of the stack.
	 * 
	 * @param	val The value to push.
	 */
	void	push(const_reference val)
	{
		_ctnr.push_back(val);
	}

	/**
	 * @brief	Check if the stack is empty.
	 * 
	 * @return	Either true if the stack is empty, or false if not.
	 */
	bool	empty(void) const
	{
		return _ctnr.empty();
	}

	/**
	 * @brief	Get access to the element on the top of the stack.
	 * 
	 * @return	A reference to the element on the top of the stack.
	 */
	reference	top(void)
	{
		return _ctnr.back();
	}

	/**
	 * @brief	Get access to the element on the top of the stack.
	 * 
	 * @return	A const_reference to the element on the top of the stack.
	 */
	const_reference	top(void) const
	{
		return _ctnr.back();
	}

	/**
	 * @brief	Get the size of the stack.
	 * 
	 * @return	The size of the stack.
	 */
	size_type	size(void) const
	{
		return _ctnr.size();
	}

// ************************************************************************* //
//                                 Operators                                 //
// ************************************************************************* //

	template <typename _T, typename _Container>
	friend bool	operator==(
		stack<_T, _Container> const &lhs,
		stack<_T, _Container> const &rhs);
	template <typename _T, typename _Container>
	friend bool	operator!=(
		stack<_T, _Container> const &lhs,
		stack<_T, _Container> const &rhs);
	template <typename _T, typename _Container>
	friend bool	operator<(
		stack<_T, _Container> const &lhs,
		stack<_T, _Container> const &rhs);
	template <typename _T, typename _Container>
	friend bool	operator>(
		stack<_T, _Container> const &lhs,
		stack<_T, _Container> const &rhs);
	template <typename _T, typename _Container>
	friend bool	operator<=(
		stack<_T, _Container> const &lhs,
		stack<_T, _Container> const &rhs);
	template <typename _T, typename _Container>
	friend bool	operator>=(
		stack<_T, _Container> const &lhs,
		stack<_T, _Container> const &rhs);
};

/**
 * @brief	Check if two stacks are equivalent.
 * 
 * @tparam	T The type of the elements of the stacks.
 * @tparam	Container The type of the underlying container of the stacks.
 * 
 * @param	lhs The left hand side stack.
 * @param	rhs The right hand side stack.
 * 
 * @return	Either true if the two stacks are equivalent, or false if not.
 */
template <typename T, typename Container>
bool	operator==(
			stack<T, Container> const &lhs,
			stack<T, Container> const &rhs)
{
	return lhs._ctnr == rhs._ctnr;
}

/**
 * @brief	Check if two stacks are different.
 * 
 * @tparam	T The type of the elements of the stacks.
 * @tparam	Container The type of the underlying container of the stacks.
 * 
 * @param	lhs The left hand side stack.
 * @param	rhs The right hand side stack.
 * 
 * @return	Either true if the two stacks are different, or false if not.
 */
template <typename T, typename Container>
bool	operator!=(
			stack<T, Container> const &lhs,
			stack<T, Container> const &rhs)
{
	return lhs._ctnr != rhs._ctnr;
}

/**
 * @brief	Check if the given stack `lhs` is lexicographicaly lower than
 * 			the given stack `rhs`.
 * 
 * @tparam	T The type of the elements of the stacks.
 * @tparam	Container The type of the underlying container of the stacks.
 * 
 * @param	lhs The left hand side stack.
 * @param	rhs The right hand side stack.
 * 
 * @return	Either true if the given stack `lhs` is lexicographicaly lower than
 * 			the given stack `rhs`, or false if not.
 */
template <typename T, typename Container>
bool	operator<(
			stack<T, Container> const &lhs,
			stack<T, Container> const &rhs)
{
	return lhs._ctnr < rhs._ctnr;
}

/**
 * @brief	Check if the given stack `lhs` is lexicographicaly greater than
 * 			the given stack `rhs`.
 * 
 * @tparam	T The type of the elements of the stacks.
 * @tparam	Container The type of the underlying container of the stacks.
 * 
 * @param	lhs The left hand side stack.
 * @param	rhs The right hand side stack.
 * 
 * @return	Either true if the given stack `lhs` is lexicographicaly greater than
 * 			the given stack `rhs`, or false if not.
 */
template <typename T, typename Container>
bool	operator>(
			stack<T, Container> const &lhs,
			stack<T, Container> const &rhs)
{
	return lhs._ctnr > rhs._ctnr;
}

/**
 * @brief	Check if the given stack `lhs` is lexicographicaly lower or equal than
 * 			the given stack `rhs`.
 * 
 * @tparam	T The type of the elements of the stacks.
 * @tparam	Container The type of the underlying container of the stacks.
 * 
 * @param	lhs The left hand side stack.
 * @param	rhs The right hand side stack.
 * 
 * @return	Either true if the given stack `lhs` lexicographicaly lower or equal than
 * 			the given stack `rhs`, or false if not.
 */
template <typename T, typename Container>
bool	operator<=(
			stack<T, Container> const &lhs,
			stack<T, Container> const &rhs)
{
	return lhs._ctnr <= rhs._ctnr;
}

/**
 * @brief	Check if the given stack `lhs` is lexicographicaly greater or equal than
 * 			the given stack `rhs`.
 * 
 * @tparam	T The type of the elements of the stacks.
 * @tparam	Container The type of the underlying container of the stacks.
 * 
 * @param	lhs The left hand side stack.
 * @param	rhs The right hand side stack.
 * 
 * @return	Either true if the given stack `lhs` is lexicographicaly greater or equal than
 * 			the given stack `rhs`, or false if not.
 */
template <typename T, typename Container>
bool	operator>=(
			stack<T, Container> const &lhs,
			stack<T, Container> const &rhs)
{
	return lhs._ctnr >= rhs._ctnr;
}
}

#endif
