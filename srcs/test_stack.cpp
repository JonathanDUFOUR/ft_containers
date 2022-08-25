/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:28:16 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/25 22:30:56 by jodufour         ###   ########.fr       */
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

inline static int	__test_constructor(void)
{
	std::vector<t_uint>	vec;
	t_uint				idx;

	title(__func__);
	try
	{
		// Default constructor
		{
			ft::stack<int, std::vector<int> >	ft_sta;
			std::stack<int, std::vector<int> >	std_sta;

			if (sizeof(ft_sta) != sizeof(std_sta)
				|| memcmp(&ft_sta, &std_sta, sizeof(ft_sta)))
				return EXIT_FAILURE;
		}
		// Wrap constructor
		{
			{
				ft::stack<t_uint, std::vector<t_uint> >		ft_sta(vec);
				std::stack<t_uint, std::vector<t_uint> >	std_sta(vec);
				if (sizeof(ft_sta) != sizeof(std_sta)
					|| memcmp(&ft_sta, &std_sta, sizeof(ft_sta)))
					return EXIT_FAILURE;
			}
			for (idx = 0U ; idx < 10U ; ++idx)
			{
				vec.push_back(idx);

				ft::stack<t_uint, std::vector<t_uint> >		ft_sta(vec);
				std::stack<t_uint, std::vector<t_uint> >	std_sta(vec);

				if (sizeof(ft_sta) != sizeof(std_sta))
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

inline static int	__test_function_top(void)
{
	char				arr[] = {
		'H',
		'e',
		'l',
		'l',
		'o',
		' ',
		'y',
		'o',
		'u',
		'!',
	};
	std::vector<char>	vec;
	t_uint					idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < 10U ; ++idx)
		{
			vec.push_back(arr[idx]);

			ft::stack<char, std::vector<char> >		ft_sta(vec);
			std::stack<char, std::vector<char> >	std_sta(vec);

			if (ft_sta.top() != std_sta.top())
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

inline static int	__test_function_push(void)
{
	std::string	arr[] = {
		std::string("Une"),
		std::string("souris"),
		std::string("verte"),
		std::string("qui"),
		std::string("courait"),
		std::string("dans"),
		std::string("l'herbe"),
		std::string("je"),
		std::string("l'attrape"),
		std::string("par"),
	};
	t_uint		idx;

	title(__func__);
	try
	{
		ft::stack<std::string, std::vector<std::string> >	ft_sta;
		std::stack<std::string, std::vector<std::string> >	std_sta;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft_sta.push(arr[idx]);
			std_sta.push(arr[idx]);

			if (ft_sta.top() != std_sta.top())
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

inline static int	__test_function_pop(void)
{
	float	arr[] = {
		0.0f,
		1.0f,
		10.0f,
		11.0f,
		100.0f,
		101.0f,
		110.0f,
		111.0f,
		1000.0f,
		1001.0f,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<float, std::vector<float> >	ft_sta;
		std::stack<float, std::vector<float> >	std_sta;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft_sta.push(arr[idx]);
			std_sta.push(arr[idx]);
		}
		for (idx = 0U ; idx < 10U ; ++idx)
		{
			if (ft_sta.top() != std_sta.top())
				return EXIT_FAILURE;
			ft_sta.pop();
			std_sta.pop();
		}
		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft_sta.pop();
			std_sta.pop();
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_empty(void)
{
	t_lint	arr[] = {
		0x0000000000000000L,
		0x000000000000000fL,
		0x00000000000000ffL,
		0x0000000000000fffL,
		0x000000000000ffffL,
		0x00000000000fffffL,
		0x0000000000ffffffL,
		0x000000000fffffffL,
		0x00000000ffffffffL,
		0x0000000fffffffffL,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<t_lint, std::vector<t_lint> >		ft_sta;
		std::stack<t_lint, std::vector<t_lint> >	std_sta;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			if (ft_sta.empty() != std_sta.empty())
				return EXIT_FAILURE;
			ft_sta.push(arr[idx]);
			std_sta.push(arr[idx]);
		}
		if (ft_sta.empty() != std_sta.empty())
			return EXIT_FAILURE;
		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft_sta.pop();
			std_sta.pop();
			if (ft_sta.empty() != std_sta.empty())
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return EXIT_SUCCESS;
}

inline static int	__test_function_size(void)
{
	t_uint	arr[] = {
		0x01234567U,
		0xf0123456U,
		0xef012345U,
		0xdef01234U,
		0xcdef0123U,
		0xbcdef012U,
		0xabcdef01U,
		0x9abcdef0U,
		0x89abcdefU,
		0x789abcdeU,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<t_uint, std::vector<t_uint> >		ft_sta;
		std::stack<t_uint, std::vector<t_uint> >	std_sta;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			if (ft_sta.size() != std_sta.size())
				return EXIT_FAILURE;
			ft_sta.push(arr[idx]);
			std_sta.push(arr[idx]);
		}
		if (ft_sta.size() != std_sta.size())
			return EXIT_FAILURE;
		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft_sta.pop();
			std_sta.pop();
			if (ft_sta.size() != std_sta.size())
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return EXIT_SUCCESS;
}

inline static int	__test_operator_equal(void)
{
	int		arr[] = {
		1,
		2,
		4,
		8,
		16,
		32,
		64,
		128,
		256,
		512,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<int, std::vector<int> >	ft_sta0;
		ft::stack<int, std::vector<int> >	ft_sta1;
		std::stack<int, std::vector<int> >	std_sta0;
		std::stack<int, std::vector<int> >	std_sta1;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			if (ft::operator==(ft_sta0, ft_sta1) != std::operator==(std_sta0, std_sta1))
				return EXIT_FAILURE;
			ft_sta0.push(arr[idx]);
			std_sta0.push(arr[idx]);
			if (ft::operator==(ft_sta0, ft_sta1) != std::operator==(std_sta0, std_sta1))
				return EXIT_FAILURE;
			ft_sta1.push(arr[idx]);
			std_sta1.push(arr[idx]);
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_difference(void)
{
	int		arr[] = {
		1,
		2,
		4,
		8,
		16,
		32,
		64,
		128,
		256,
		512,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<int, std::vector<int> >	ft_sta0;
		ft::stack<int, std::vector<int> >	ft_sta1;
		std::stack<int, std::vector<int> >	std_sta0;
		std::stack<int, std::vector<int> >	std_sta1;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			if (ft::operator!=(ft_sta0, ft_sta1) != std::operator!=(std_sta0, std_sta1))
				return EXIT_FAILURE;
			ft_sta0.push(arr[idx]);
			std_sta0.push(arr[idx]);
			if (ft::operator!=(ft_sta0, ft_sta1) != std::operator!=(std_sta0, std_sta1))
				return EXIT_FAILURE;
			ft_sta1.push(arr[idx]);
			std_sta1.push(arr[idx]);
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_lower(void)
{
	int		arr[] = {
		1,
		2,
		4,
		8,
		16,
		32,
		64,
		128,
		256,
		512,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<int, std::vector<int> >	ft_sta0;
		ft::stack<int, std::vector<int> >	ft_sta1;
		std::stack<int, std::vector<int> >	std_sta0;
		std::stack<int, std::vector<int> >	std_sta1;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			if (ft::operator<(ft_sta0, ft_sta1) != std::operator<(std_sta0, std_sta1))
				return EXIT_FAILURE;
			ft_sta0.push(arr[idx]);
			std_sta0.push(arr[idx]);
			if (ft::operator<(ft_sta0, ft_sta1) != std::operator<(std_sta0, std_sta1))
				return EXIT_FAILURE;
			ft_sta1.push(arr[idx]);
			std_sta1.push(arr[idx]);
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_greater(void)
{
	int		arr[] = {
		1,
		2,
		4,
		8,
		16,
		32,
		64,
		128,
		256,
		512,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<int, std::vector<int> >	ft_sta0;
		ft::stack<int, std::vector<int> >	ft_sta1;
		std::stack<int, std::vector<int> >	std_sta0;
		std::stack<int, std::vector<int> >	std_sta1;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			if (ft::operator>(ft_sta0, ft_sta1) != std::operator>(std_sta0, std_sta1))
				return EXIT_FAILURE;
			ft_sta0.push(arr[idx]);
			std_sta0.push(arr[idx]);
			if (ft::operator>(ft_sta0, ft_sta1) != std::operator>(std_sta0, std_sta1))
				return EXIT_FAILURE;
			ft_sta1.push(arr[idx]);
			std_sta1.push(arr[idx]);
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_lower_equal(void)
{
	int		arr[] = {
		1,
		2,
		4,
		8,
		16,
		32,
		64,
		128,
		256,
		512,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<int, std::vector<int> >	ft_sta0;
		ft::stack<int, std::vector<int> >	ft_sta1;
		std::stack<int, std::vector<int> >	std_sta0;
		std::stack<int, std::vector<int> >	std_sta1;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			if (ft::operator<=(ft_sta0, ft_sta1) != std::operator<=(std_sta0, std_sta1))
				return EXIT_FAILURE;
			ft_sta0.push(arr[idx]);
			std_sta0.push(arr[idx]);
			if (ft::operator<=(ft_sta0, ft_sta1) != std::operator<=(std_sta0, std_sta1))
				return EXIT_FAILURE;
			ft_sta1.push(arr[idx]);
			std_sta1.push(arr[idx]);
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_greater_equal(void)
{
	int		arr[] = {
		1,
		2,
		4,
		8,
		16,
		32,
		64,
		128,
		256,
		512,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<int, std::vector<int> >	ft_sta0;
		ft::stack<int, std::vector<int> >	ft_sta1;
		std::stack<int, std::vector<int> >	std_sta0;
		std::stack<int, std::vector<int> >	std_sta1;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			if (ft::operator>=(ft_sta0, ft_sta1) != std::operator>=(std_sta0, std_sta1))
				return EXIT_FAILURE;
			ft_sta0.push(arr[idx]);
			std_sta0.push(arr[idx]);
			if (ft::operator>=(ft_sta0, ft_sta1) != std::operator>=(std_sta0, std_sta1))
				return EXIT_FAILURE;
			ft_sta1.push(arr[idx]);
			std_sta1.push(arr[idx]);
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int	test_stack(void)
{
	t_test const	tests[] = {
		__test_constructor,
		__test_function_top,
		__test_function_push,
		__test_function_pop,
		__test_function_empty,
		__test_function_size,
		__test_operator_equal,
		__test_operator_difference,
		__test_operator_lower,
		__test_operator_greater,
		__test_operator_lower_equal,
		__test_operator_greater_equal,
		NULL
	};
	t_uint			koCount;
	t_uint			idx;

	std::cerr << "\033[38;2;0;173;255m";
	std::cout << "###################################################" << '\n';
	std::cout << "##                     STACK                     ##" << '\n';
	std::cout << "###################################################" << '\n';
	std::cerr << "\033[0m";

	for (koCount = 0U, idx = 0U ; tests[idx] ; ++idx)
	{
		if (tests[idx]())
		{
			std::cerr << "\033[38;2;255;0;0m";
			std::cout << "[KO]" << '\n';
			std::cerr << "\033[0m";
			++koCount;
		}
		else
		{
			std::cerr << "\033[38;2;0;255;0m";
			std::cout << "[OK]" << '\n';
			std::cerr << "\033[0m";
		}
	}
	std::cout << '\n';
	return koCount;
}
