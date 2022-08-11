/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 09:48:18 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/11 18:53:06 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{

template <bool Cond, typename T = void>
class enable_if;

template <typename T>
class enable_if<true, T>
{
public:
	typedef T	type;
};

template <typename T, T v>
class integral_constant
{
public:
	// Member types
	typedef T						value_type;
	typedef integral_constant<T, v>	type;

	// Attributes
	static value_type const	value = v;

	// Operators
	operator value_type(void) const
	{
		return value;
	}
};

typedef integral_constant<bool, true>	true_type;
typedef integral_constant<bool, false>	false_type;

template <typename T>
class is_integral : public false_type {};

template<>
class is_integral<bool> : public true_type {};

template<>
class is_integral<wchar_t> : public true_type {};

template<>
class is_integral<signed char> : public true_type {};

template<>
class is_integral<signed short> : public true_type {};

template<>
class is_integral<signed int> : public true_type {};

template<>
class is_integral<signed long> : public true_type {};

template<>
class is_integral<unsigned char> : public true_type {};

template<>
class is_integral<unsigned short> : public true_type {};

template<>
class is_integral<unsigned int> : public true_type {};

template<>
class is_integral<unsigned long> : public true_type {};
}

#endif
