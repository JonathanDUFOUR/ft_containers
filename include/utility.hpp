/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:30:10 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/27 12:58:33 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{
template <typename T0, typename T1>
class pair
{
public:
	// Member types
	typedef T0	first_type;
	typedef T1	second_type;

	// Attributes
	first_type	first;
	second_type	second;

	// Constructors
	pair(
		first_type const &a = first_type(),
		second_type const &b = second_type()) :
		first(a),
		second(b) {}
	pair(pair const &src) :
		first(src.first),
		second(src.second) {}
	
	// Destructors
	~pair(void) {}

	// Operators
	pair	&operator=(pair const &rhs)
	{
		first = src.first;
		second = src.second;
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
