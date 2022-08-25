/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_input_iterator.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:10:24 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/25 22:26:08 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include "iterator/base/input_iterator.tpp"
#include "tester.hpp"

inline static int	__test_constructor(void)
{
	int		arr[] = {
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
	t_uint	idx;

	title(__func__);
	try
	{
		// Pointer constructor
		{
			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft::input_iterator<int>	it(arr + idx);

				if (*it != arr[idx])
					return EXIT_FAILURE;
			}
		}
		// Copy constructor
		{
			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft::input_iterator<int>	it0(arr + idx);
				ft::input_iterator<int>	it1(it0);

				if (memcmp(&it0, &it1, sizeof(it0)))
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
	t_uint		idx;

	title(__func__);
	try
	{
		ft::input_iterator<std::string>	it0(NULL);

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft::input_iterator<std::string>	it1(arr + idx);

			it0 = it1;
			if (memcmp(&it0, &it1, sizeof(it0)))
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
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < 10U ; ++idx0)
		{
			ft::input_iterator<int>	it0(arr + idx0);

			for (idx1 = 0U ; idx1 < 10U ; ++idx1)
			{
				ft::input_iterator<int>	it1(arr + idx1);

				if ((it0 == it1) != (idx0 == idx1))
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
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
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < 10U ; ++idx0)
		{
			ft::input_iterator<int>	it0(arr + idx0);

			for (idx1 = 0U ; idx1 < 10U ; ++idx1)
			{
				ft::input_iterator<int>	it1(arr + idx1);

				if ((it0 != it1) != (idx0 != idx1))
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
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
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft::input_iterator<t_hint>	it(arr + idx);

			*it += 42;
			if (*it != arr[idx])
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

inline static int	__test_operator_maddress(void)
{
	std::pair<int, char>	arr[] = {
		std::pair<int, char>(0, 'A'),
		std::pair<int, char>(1, 'B'),
		std::pair<int, char>(2, 'C'),
		std::pair<int, char>(3, 'D'),
		std::pair<int, char>(4, 'E'),
		std::pair<int, char>(5, 'F'),
		std::pair<int, char>(6, 'G'),
		std::pair<int, char>(7, 'H'),
		std::pair<int, char>(8, 'I'),
		std::pair<int, char>(9, 'J'),
	};
	t_uint					idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft::input_iterator<std::pair<int, char> >	it(arr + idx);

			if (it->first != arr[idx].first
				|| it->second != arr[idx].second)
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

inline static int	__test_operator_increment(void)
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
	t_uint	idx;

	title(__func__);
	try
	{
		// Prefix incrementation
		{
			ft::input_iterator<t_luint>	it(arr);

			for (idx = 0U ; idx < 9U ; ++idx)
				if (*++it != arr[idx + 1])
					return EXIT_FAILURE;
		}
		// Postfix incrementation
		{
			ft::input_iterator<t_luint>	it(arr);

			for (idx = 0U ; idx < 9U ; ++idx)
				if (*it++ != arr[idx] || *it != arr[idx + 1])
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

int	test_input_iterator(void)
{
	t_test const	tests[] = {
		__test_constructor,
		__test_operator_assign,
		__test_operator_equal,
		__test_operator_difference,
		__test_operator_dereference,
		__test_operator_maddress,
		__test_operator_increment,
		NULL
	};
	t_uint			koCount;
	t_uint			idx;

	std::cerr << "\033[38;2;0;173;255m";
	std::cout << "####################################################" << '\n';
	std::cout << "##                 INPUT ITERATOR                 ##" << '\n';
	std::cout << "####################################################" << '\n';
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
