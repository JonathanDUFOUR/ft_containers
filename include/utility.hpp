/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:30:10 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/17 05:40:55 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{
template <typename T0, typename T1>
struct pair
{
	// Member types
	typedef T0	first_type;
	typedef T1	second_type;

	// Attributes
	first_type	first;
	second_type	second;

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new pair object. (Default constructor)
	 * 
	 * @param	a The first value of the pair.
	 * @param	b The second value of the pair.
	 */
	pair(first_type const &a = first_type(), second_type const &b = second_type()) :
		first(a),
		second(b) {}
	
	/**
	 * @brief	Construct a new pair object from another one.
	 * 			Allow mutable to constant pair conversion. (copy constructor)
	 * 
	 * @tparam	U0 The first type of the pair to copy.
	 * @tparam	U1 The second type of the pair to copy.
	 * 
	 * @param	src The pair to copy.
	 */
	template <typename U0, typename U1>
	pair(pair<U0, U1> const &src) :
		first(src.first),
		second(src.second) {}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Assign a new content to the pair.
	 * 			Allow mutable to constant pair conversion.
	 * 
	 * @tparam	U0 The first type of the pair to copy.
	 * @tparam	U1 The second type of the pair to copy.
	 * 
	 * @param	rhs The pair to copy the content from.
	 * 
	 * @return	A reference to the assigned pair.
	 */
	template <typename U0, typename U1>
	pair	&operator=(pair<U0, U1> const &rhs)
	{
		if (this != &rhs)
		{
			first = rhs.first;
			second = rhs.second;
		}
		return *this;
	}
};

template <typename T0, typename T1>
pair<T0, T1>	make_pair(T0 const &a, T1 const &b)
{
	return pair<T0, T1>(a, b);
}

template <typename T0, typename T1>
inline bool	operator==(pair<T0, T1> const &lhs, pair<T0, T1> const &rhs)
{
	return (lhs.first == rhs.first) && (lhs.second == rhs.second);
}

template <typename T0, typename T1>
inline bool	operator!=(pair<T0, T1> const &lhs, pair<T0, T1> const &rhs)
{
	return (!lhs.first != rhs.first) || (!lhs.second != rhs.second);
}

template <typename T0, typename T1>
inline bool	operator<(pair<T0, T1> const &lhs, pair<T0, T1> const &rhs)
{
	return (lhs.first < rhs.first) || (lhs.second < rhs.second);
}

template <typename T0, typename T1>
inline bool	operator>(pair<T0, T1> const &lhs, pair<T0, T1> const &rhs)
{
	return (lhs.first > rhs.first) || (lhs.second > rhs.second);
}

template <typename T0, typename T1>
inline bool	operator<=(pair<T0, T1> const &lhs, pair<T0, T1> const &rhs)
{
	return (lhs.first <= rhs.first) || (lhs.second <= rhs.second);
}

template <typename T0, typename T1>
inline bool	operator>=(pair<T0, T1> const &lhs, pair<T0, T1> const &rhs)
{
	return (lhs.first >= rhs.first) || (lhs.second >= rhs.second);
}
}
#endif
