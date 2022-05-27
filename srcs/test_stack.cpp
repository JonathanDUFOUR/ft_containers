/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:28:16 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/27 18:48:35 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>
#include "stack.hpp"
#include "tester.hpp"

inline static int	__test_construct_default(void)
{
	try
	{
		ft::stack<int, std::vector<int> >	ft_sta;
		std::stack<int, std::vector<int> >	std_sta;

		if (sizeof(ft_sta)  !=  sizeof(std_sta)
			|| memcmp(&ft_sta, &std_sta, sizeof(ft_sta)))
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_construct_container(void) // TODO rework ce test
{
	std::vector<char>	vec;
	int					idx;

	try
	{
		{
			ft::stack<char, std::vector<char> >	ft_sta(vec);
			std::stack<char, std::vector<char> >	std_sta(vec);

			if (sizeof(ft_sta)  !=  sizeof(std_sta))
				return EXIT_FAILURE;
			if (memcmp(&ft_sta, &std_sta, sizeof(ft_sta))) // ON NE REUTILISE PAS MEMCMP !!!! (C'est une deep copy)
				return EXIT_FAILURE;
		}
		for (idx = 0 ; idx < 10 ; ++idx)
		{
			vec.push_back(idx);
			ft::stack<char, std::vector<char> >		ft_sta(vec);
			std::stack<char, std::vector<char> >	std_sta(vec);

			if (sizeof(ft_sta)  !=  sizeof(std_sta))
				return EXIT_FAILURE;
			if (memcmp(&ft_sta, &std_sta, sizeof(ft_sta)))
			{
				std::cout << '\n';
				std::cout << " ft_sta.top(): " << ft_sta.top() << '\n';
				std::cout << "std_sta.top(): " << std_sta.top() << '\n';
				ft_sta.pop();
				std_sta.pop();
				std::cout << " ft_sta.top(): " << ft_sta.top() << '\n';
				std::cout << "std_sta.top(): " << std_sta.top() << '\n';
				ft_sta.pop();
				std_sta.pop();
				std::cout << " ft_sta.top(): " << ft_sta.top() << '\n';
				std::cout << "std_sta.top(): " << std_sta.top() << '\n';
				ft_sta.pop();
				std_sta.pop();
				std::cout << " ft_sta.top(): " << ft_sta.top() << '\n';
				std::cout << "std_sta.top(): " << std_sta.top() << '\n';
				ft_sta.pop();
				std_sta.pop();
				std::cout << " ft_sta.top(): " << ft_sta.top() << '\n';
				std::cout << "std_sta.top(): " << std_sta.top() << '\n';
				return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_pop(void)
{
	std::vector<int>	vec;
	int					i;

	for (i = 0 ; i < 10 ; ++i)
		vec.push_back(i);
	try
	{
		ft::stack<int, std::vector<int> >	ft_sta(vec);
		std::stack<int, std::vector<int> >	std_sta(vec);

		for (i = 0 ; i < 10 ; ++i)
		{
			ft_sta.pop();
			std_sta.pop();
			if ((sizeof(ft_sta) != sizeof(std_sta))
				|| memcmp(&ft_sta, &std_sta, sizeof(ft_sta)))
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

// inline static int	__test_function_push(void)
// {
// 	int	i;
// }

int	test_stack(void)
{
	t_test const	tests[] = {
		__test_construct_default,
		__test_construct_container,
		__test_function_pop,
		NULL
	};
	int				koCount;
	int				idx;

	std::cout << std::setw(PADDING) << "stack:";
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
