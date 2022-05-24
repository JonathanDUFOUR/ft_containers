/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:15:58 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/24 12:19:20 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
# define TESTER_HPP

# include <cstddef>

typedef int	(*t_test)(void);

int	test_InputIterator(void);

static t_test const	g_test[] = {
	test_InputIterator,
	NULL
};

#endif
