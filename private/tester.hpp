/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:15:58 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/06 17:15:50 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
# define TESTER_HPP

# include <cstddef>

# define PADDING	33

typedef int	(*t_test)(void);

template <typename T, T v>
struct integral_constant
{
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

}; // struct integral_constant

typedef integral_constant<bool, true>	true_type;
typedef integral_constant<bool, false>	false_type;

template <typename T0, typename T1> class is_same : public false_type {};
template <typename T> class is_same<T, T> : public true_type {};

int	test_algorithm(void);
int	test_is_integral(void);
int	test_map(void);
int	test_pair(void);
int	test_rb_tree(void);
int	test_reverse_iterator(void);
int	test_set(void);
int	test_stack(void);
int	test_vector(void);

void	title(char const *const funcName);

#endif
