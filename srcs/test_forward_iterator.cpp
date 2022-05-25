/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_forward_iterator.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 03:26:05 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/25 08:55:54 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include "iterator/forward_iterator.tpp"
#include "tester.hpp"

inline static int	__test_construct_default(void)
{
	try
	{
		ft::forward_iterator<std::iostream>	it;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_construct_pointer(void)
{
	int	arr[] = {
		0,
		1,
		2,
		3,
		4,
		5,
		6,
		7,
		8,
		9,
	};
	int	idx;

	try
	{
		for (idx = 0 ; idx < 10 ; ++idx)
		{
			ft::forward_iterator<int>	it(arr + idx);

			if (*it != arr[idx])
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_construct_copy(void)
{
	char	arr[] = {
		'0',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
	};
	int		idx;

	try
	{
		for (idx = 0 ; idx < 10 ; ++idx)
		{
			ft::forward_iterator<char>	it0(arr + idx);
			ft::forward_iterator<char>	it1(it0);

			if (memcmp(&it0, &it1, sizeof(ft::forward_iterator<char>)))
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_assign(void)
{
	std::string	arr[] = {
		std::string("I"),
		std::string("wanna"),
		std::string("be"),
		std::string("the"),
		std::string("very"),
		std::string("best"),
		std::string("like"),
		std::string("no"),
		std::string("one"),
		std::string("ever"),
		std::string("was"),
	};
	int			idx;

	try
	{
		ft::forward_iterator<std::string>	it0;

		for (idx = 0 ; idx < 10 ; ++idx)
		{
			ft::forward_iterator<std::string>	it1(arr + idx);

			it0 = it1;
			if (memcmp(&it0, &it1, sizeof(ft::forward_iterator<std::string>)))
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_equal(void)
{
	int	arr[] = {
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
	int	idx0;
	int	idx1;

	try
	{
		for (idx0 = 0 ; idx0 < 10 ; ++idx0)
		{
			ft::forward_iterator<int>	it0(arr + idx0);

			for (idx1 = 0 ; idx1 < 10 ; ++idx1)
			{
				ft::forward_iterator<int>	it1(arr + idx1);

				if ((it0 == it1) != (idx0 == idx1))
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_difference(void)
{
	int	arr[] = {
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
	int	idx0;
	int	idx1;

	try
	{
		for (idx0 = 0 ; idx0 < 10 ; ++idx0)
		{
			ft::forward_iterator<int>	it0(arr + idx0);

			for (idx1 = 0 ; idx1 < 10 ; ++idx1)
			{
				ft::forward_iterator<int>	it1(arr + idx1);

				if ((it0 != it1) != (idx0 != idx1))
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_dereference(void)
{
	t_hint	arr[] = {
		-0,
		-1,
		-2,
		-3,
		-4,
		-5,
		-6,
		-7,
		-8,
		-9,
	};
	int		idx;

	try
	{
		for (idx = 0 ; idx < 10 ; ++idx)
		{
			ft::forward_iterator<t_hint>	it(arr + idx);

			*it += 42;
			if (*it != arr[idx])
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_maddress(void)
{
	int	arr[] = {
		0,
		1,
		2,
		3,
		4,
		5,
		6,
		7,
		8,
		9,
	};
	int	idx;

	try
	{
		for (idx = 0 ; idx < 10 ; ++idx)
		{
			ft::forward_iterator<int>	it(arr + idx);

			if (it.operator->() != arr + idx)
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_increment_prefix(void)
{
	t_luint	arr[] = {
		424242424242420,
		424242424242421,
		424242424242422,
		424242424242423,
		424242424242424,
		424242424242425,
		424242424242426,
		424242424242427,
		424242424242428,
		424242424242429,
	};
	int		idx;

	try
	{
		ft::forward_iterator<t_luint>	it(arr);

		for (idx = 0 ; idx < 9 ; ++idx)
			if (*++it != arr[idx + 1])
				return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_increment_postfix(void)
{
	int	arr[] = {
		0,
		1,
		2,
		3,
		4,
		5,
		6,
		7,
		8,
		9,
	};
	int	idx;

	try
	{
		ft::forward_iterator<int>	it(arr);

		for (idx = 0 ; idx < 9 ; ++idx)
			if (*it++ != arr[idx] || *it != arr[idx + 1])
				return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int	test_forward_iterator(void)
{
	t_test const	tests[] = {
		__test_construct_default,
		__test_construct_pointer,
		__test_construct_copy,
		__test_operator_assign,
		__test_operator_equal,
		__test_operator_difference,
		__test_operator_dereference,
		__test_operator_maddress,
		__test_operator_increment_prefix,
		__test_operator_increment_postfix,
		NULL
	};
	int				koCount;
	int				idx;

	std::cout << std::setw(PADDING) << "forward_iterator:";
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
	std::cout << std::endl;
	return koCount;
}
