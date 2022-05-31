/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:36:04 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/31 18:51:57 by jodufour         ###   ########.fr       */
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

		if (sizeof(ft_vec) != sizeof(std_vec)
			|| memcmp(&ft_vec, &std_vec, sizeof(ft_vec)))
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_construct_fill(void)
{
	try
	{
		{
			ft::vector<char>	ft_vec(21);
			std::vector<char>	std_vec(21);

			if (sizeof(ft_vec) != sizeof(std_vec))
				return EXIT_FAILURE;
		}
		{
			ft::vector<char>	ft_vec(0, 'A');
			std::vector<char>	std_vec(0, 'A');

			if (sizeof(ft_vec) != sizeof(std_vec))
				return EXIT_FAILURE;
		}
		{
			ft::vector<char>	ft_vec(42, 42);
			std::vector<char>	std_vec(42, 42);

			if (sizeof(ft_vec) != sizeof(std_vec))
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

inline static int	__test_construct_range(void)
{
	t_huint	arr[] = {
		0U,
		42U,
		84U,
		126U,
		168U,
		210U,
		252U,
		294U,
		336U,
		378U,
	};

	try
	{
		{
			ft::input_iterator<t_huint>	it0(arr);
			ft::input_iterator<t_huint>	it1(arr);
			ft::vector<t_huint>			ft_vec(it0, it1);
			std::vector<t_huint>		std_vec(it0, it1);

			if (sizeof(ft_vec) != sizeof(std_vec))
				return EXIT_FAILURE;
		}
		{
			ft::forward_iterator<void *>	it0;
			ft::forward_iterator<void *>	it1;
			ft::vector<void *>				ft_vec(it0, it1);
			std::vector<void *>				std_vec(it0, it1);

			if (sizeof(ft_vec) != sizeof(std_vec))
				return EXIT_FAILURE;
		}
		{
			ft::random_access_iterator<t_huint>	it0(arr);
			ft::random_access_iterator<t_huint>	it1(arr + 10);
			ft::vector<t_huint>					ft_vec(it0, it1);
			std::vector<t_huint>				std_vec(it0, it1);

			if (sizeof(ft_vec) != sizeof(std_vec))
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

inline static int	__test_construct_copy(void)
{
	t_lint	arr[] = {
		112233445566778899L,
		122334455667788991L,
		223344556677889911L,
		233445566778899112L,
		334455667788991122L,
		344556677889911223L,
		445566778899112233L,
		455667788991122334L,
		556677889911223344L,
		566778899112233445L,
	};

	try
	{
		ft::forward_iterator<t_lint>	it0(arr);
		ft::forward_iterator<t_lint>	it1(arr + 10);
		ft::vector<t_lint>				ft_vec0(it0, it1);
		ft::vector<t_lint>				ft_vec1(ft_vec0);
		std::vector<t_lint>				std_vec0(it0, it1);
		std::vector<t_lint>				std_vec1(std_vec0);

		if (sizeof(ft_vec1) != sizeof(std_vec1))
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_size(void)
{
	int	n;

	try
	{
		for (n = 0 ; n < 10 ; ++n)
		{
			ft::vector<t_hhuint>	ft_vec(n, 42U);
			std::vector<t_hhuint>	std_vec(n, 42U);

			if (ft_vec.size() != std_vec.size())
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

inline static int	__test_function_capacity(void)
{
	int	n;

	try
	{
		for (n = 0 ; n < 10 ; ++n)
		{
			ft::vector<float>	ft_vec(n, 3.14f);
			std::vector<float>	std_vec(n, 3.14f);

			if (ft_vec.capacity() != std_vec.capacity())
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

inline static int	__test_function_empty(void)
{
	int	n;

	try
	{
		for (n = 0 ; n < 10 ; ++n)
		{
			ft::vector<std::string>		ft_vec(n * (n % 2), std::string("Hello World"));
			std::vector<std::string>	std_vec(n * (n % 2), std::string("Hello World"));

			if (ft_vec.empty() != std_vec.empty())
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

inline static int	__test_function_begin(void)
{
	t_lint	arr[] = {
		0,
		11,
		222,
		3333,
		44444,
		555555,
		6666666,
		77777777,
		888888888,
		9999999999,
	};
	int		n;

	try
	{
		for (n = 0 ; n < 10 ; ++n)
		{
			ft::vector<t_lint>					ft_vec(n, arr[n]);
			std::vector<t_lint>					std_vec(n, arr[n]);
			ft::vector<t_lint>::iterator		ft_it = ft_vec.begin();
			std::vector<t_lint>::iterator		std_it = std_vec.begin();
			ft::vector<t_lint>::const_iterator	ft_cit = ft_vec.begin();
			std::vector<t_lint>::const_iterator	std_cit = std_vec.begin();

			if (!!ft_it.operator->() != !!std_it.operator->()
				|| (ft_it.operator->() && std_it.operator->()
					&& *ft_it.operator->() != *std_it.operator->())
				|| !!ft_cit.operator->() != !!std_cit.operator->()
				|| (ft_cit.operator->() && std_cit.operator->()
					&& *ft_cit.operator->() != *std_cit.operator->()))
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_end(void)
{
	t_lint	arr[] = {
		0,
		11,
		222,
		3333,
		44444,
		555555,
		6666666,
		77777777,
		888888888,
		9999999999,
	};
	int		n;

	try
	{
		for (n = 0 ; n < 10 ; ++n)
		{
			ft::vector<t_lint>					ft_vec(n, arr[n]);
			std::vector<t_lint>					std_vec(n, arr[n]);
			ft::vector<t_lint>::iterator		ft_it = ft_vec.end();
			std::vector<t_lint>::iterator		std_it = std_vec.end();
			ft::vector<t_lint>::const_iterator	ft_cit = ft_vec.end();
			std::vector<t_lint>::const_iterator	std_cit = std_vec.end();

			if (!!ft_it.operator->() != !!std_it.operator->()
				|| (ft_it.operator->() && std_it.operator->()
					&& *ft_it.operator->() != *std_it.operator->())
				|| !!ft_cit.operator->() != !!std_cit.operator->()
				|| (ft_cit.operator->() && std_cit.operator->()
					&& *ft_cit.operator->() != *std_cit.operator->()))
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_rbegin(void)
{
	t_lint	arr[] = {
		0,
		11,
		222,
		3333,
		44444,
		555555,
		6666666,
		77777777,
		888888888,
		9999999999,
	};
	int		n;

	try
	{
		for (n = 0 ; n < 10 ; ++n)
		{
			ft::vector<t_lint>							ft_vec(n, arr[n]);
			std::vector<t_lint>							std_vec(n, arr[n]);
			ft::vector<t_lint>::reverse_iterator		ft_rit = ft_vec.rbegin();
			std::vector<t_lint>::reverse_iterator		std_rit = std_vec.rbegin();
			ft::vector<t_lint>::const_reverse_iterator	ft_crit = ft_vec.rbegin();
			std::vector<t_lint>::const_reverse_iterator	std_crit = std_vec.rbegin();

			if (!!ft_rit.operator->() != !!std_rit.operator->()
				|| (ft_rit.operator->() && std_rit.operator->()
					&& *ft_rit.operator->() != *std_rit.operator->())
				|| !!ft_crit.operator->() != !!std_crit.operator->()
				|| (ft_crit.operator->() && std_crit.operator->()
					&& *ft_crit.operator->() != *std_crit.operator->()))
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_rend(void)
{
	t_lint	arr[] = {
		0,
		11,
		222,
		3333,
		44444,
		555555,
		6666666,
		77777777,
		888888888,
		9999999999,
	};
	int		n;

	try
	{
		for (n = 0 ; n < 10 ; ++n)
		{
			ft::vector<t_lint>							ft_vec(n, arr[n]);
			std::vector<t_lint>							std_vec(n, arr[n]);
			ft::vector<t_lint>::reverse_iterator		ft_rit = ft_vec.rend();
			std::vector<t_lint>::reverse_iterator		std_rit = std_vec.rend();
			ft::vector<t_lint>::const_reverse_iterator	ft_crit = ft_vec.rend();
			std::vector<t_lint>::const_reverse_iterator	std_crit = std_vec.rend();

			if (!!ft_rit.operator->() != !!std_rit.operator->()
				|| (ft_rit.operator->() && std_rit.operator->()
					&& *ft_rit.operator->() != *std_rit.operator->())
				|| !!ft_crit.operator->() != !!std_crit.operator->()
				|| (ft_crit.operator->() && std_crit.operator->()
					&& *ft_crit.operator->() != *std_crit.operator->()))
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
		__test_construct_fill,
		__test_construct_range,
		__test_construct_copy,
		__test_function_size,
		__test_function_capacity,
		__test_function_empty,
		__test_function_begin,
		__test_function_end,
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
