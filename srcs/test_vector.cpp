/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:36:04 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/28 18:56:14 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>
#include "vector.hpp"
#include "tester.hpp"

inline static int	__test_construct_default(void)
{
	try
	{
		ft::vector<int>		ft_vec;
		std::vector<int>	std_vec;

		if (sizeof(ft_vec) != sizeof(std_vec))
		{
			std::cout << '\n';
			std::cout << " sizeof(ft_vec): " << sizeof(ft_vec) << '\n';
			std::cout << "sizeof(std_vec): " << sizeof(std_vec) << '\n';
			return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
	}
	return EXIT_SUCCESS;
}

int	test_vector(void)
{
	t_test const	tests[] = {
		__test_construct_default,
		NULL
	};
	int				koCount;
	int				idx;

	std::cout << std::setw(PADDING) << "vector:";
	for (koCount = 0, idx = 0 ; tests[idx] ; ++idx)
	{
		if (tests[idx]())
		{
			std::cerr << "\033[38;2;255;0;0m";
			std::cout << " [KO]";
			std::cerr << "\033[0m";
			++koCount;
		}
		else
		{
			std::cerr << "\033[38;2;0;255;0m";
			std::cout << " [OK]";
			std::cerr << "\033[0m";
			
		}
	}
	std::cout << '\n';
	return koCount;
}
