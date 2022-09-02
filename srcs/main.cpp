/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 06:00:18 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/01 22:03:44 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "tester.hpp"
#include "t_int.hpp"

int	main(void)
{
	t_test const	tests[] = {
		test_input_iterator,
		test_output_iterator,
		test_forward_iterator,
		test_bidirectional_iterator,
		test_random_access_iterator,
		test_reverse_iterator,
		test_is_integral,
		test_algorithm,
		test_stack,
		test_vector,
		NULL
	};
	t_uint	koCount;
	t_uint	idx;

	for (koCount = 0, idx = 0 ; tests[idx] ; ++idx)
		koCount += tests[idx]();
	return !!koCount;
}
