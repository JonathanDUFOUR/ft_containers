/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_InputIterator.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:10:24 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/24 13:06:40 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include "iterator/InputIterator.tpp"
#include "tester.hpp"

inline static int	__test_construct_pointer(void)
{
	int	arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int	idx;

	try
	{
		for (idx = 0 ; idx < 10 ; ++idx)
		{
			ft::InputIterator<int>	it(arr + idx);
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
	int	arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int	idx;

	try
	{
		for (idx = 0 ; idx < 10 ; ++idx)
		{
			ft::InputIterator<int>	it0(arr + idx);
			ft::InputIterator<int>	it1(it0);
			if (it0 != it1)
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

inline static int	__test_operator_assignation(void)
{
	int						arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int						idx;
	ft::InputIterator<int>	it0(NULL);

	try
	{
		for (idx = 0 ; idx < 10 ; ++idx)
		{
			ft::InputIterator<int>	it1(arr + idx);
			it0 = it1;
			if (it0 != it1)
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

inline static int	__test_operator_equality(void)
{
	int						arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int						idx;
	ft::InputIterator<int>	it0(NULL);

	try
	{
		for (idx = 0 ; idx < 10 ; ++idx)
		{
			ft::InputIterator<int>	it1(arr + idx);
			if (it0 == it1)
				return EXIT_FAILURE;
			it0 = it1;
			if (it0 != it1)
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

inline static int	__test_operator_dereference(void)
{
	int	arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int	idx;

	try
	{
		for (idx = 0 ; idx < 10 ; ++idx)
		{
			ft::InputIterator<int>	it(arr + idx);
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
	int	arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int	idx;

	try
	{
		for (idx = 0 ; idx < 10 ; ++idx)
		{
			ft::InputIterator<int>	it(arr + idx);
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
	int	arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int	idx;

	try
	{
		for (idx = 0 ; idx < 9 ; ++idx)
		{
			ft::InputIterator<int>	it(arr + idx);
			if (*it != arr[idx])
				return EXIT_FAILURE;
			if (*++it != arr[idx + 1])
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

inline static int	__test_operator_increment_postfix(void)
{
	int	arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int	idx;

	try
	{
		for (idx = 0 ; idx < 9 ; ++idx)
		{
			ft::InputIterator<int>	it(arr + idx);
			if (*it != arr[idx])
				return EXIT_FAILURE;
			if (*it++ != arr[idx])
				return EXIT_FAILURE;
			if (*it != arr[idx + 1])
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

int	test_InputIterator(void)
{
	t_test const	tests[] = {
		__test_construct_pointer,
		__test_construct_copy,
		__test_operator_assignation,
		__test_operator_equality,
		__test_operator_dereference,
		__test_operator_maddress,
		__test_operator_increment_prefix,
		__test_operator_increment_postfix,
		NULL
	};
	int				koCount;
	int				idx;

	std::cout << "InputIterator:";
	for (koCount = 0, idx = 0 ; tests[idx] ; ++idx)
	{
		if (tests[idx]())
		{
			std::cout << " \033[38;2;255;0;0m[KO]\033[0m";
			++koCount;
		}
		else
			std::cout << " \033[38;2;0;255;0m[OK]\033[0m";
	}
	std::cout << std::endl;
	return koCount;
}
