/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:15:58 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/25 10:15:19 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
# define TESTER_HPP

# include <cstddef>

# define PADDING	23

typedef int	(*t_test)(void);

typedef signed char			t_hhint;
typedef signed short		t_hint;
typedef signed int			t_int;
typedef signed long			t_lint;

typedef unsigned char		t_hhuint;
typedef unsigned short		t_huint;
typedef unsigned int		t_uint;
typedef unsigned long		t_luint;

int	test_bidirectional_iterator(void);
int	test_forward_iterator(void);
int	test_input_iterator(void);
int	test_output_iterator(void);
int	test_random_access_iterator(void);
int	test_reverse_iterator(void);

static t_test const	g_test[] = {
	test_input_iterator,
	test_output_iterator,
	test_forward_iterator,
	test_bidirectional_iterator,
	test_random_access_iterator,
	test_reverse_iterator,
	NULL
};

#endif
