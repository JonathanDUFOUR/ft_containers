/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:36:04 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/12 02:15:07 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>
#include "vector.hpp"
#include "utility.hpp"
#include "tester.hpp"

inline static int	__test_construct_default(void)
{
	try
	{
		ft::vector<int>		ft_vec;
		std::vector<int>	std_vec;

		if (sizeof(ft_vec) != sizeof(std_vec) ||
			memcmp(&ft_vec, &std_vec, sizeof(ft_vec)))
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
			ft::vector<char>	ft_vec(21LU);
			std::vector<char>	std_vec(21LU);

			if (sizeof(ft_vec) != sizeof(std_vec))
				return EXIT_FAILURE;
		}
		{
			ft::vector<char>	ft_vec(0LU, 'A');
			std::vector<char>	std_vec(0LU, 'A');

			if (sizeof(ft_vec) != sizeof(std_vec))
				return EXIT_FAILURE;
		}
		{
			ft::vector<char>	ft_vec(42LU, 42);
			std::vector<char>	std_vec(42LU, 42);

			if (sizeof(ft_vec) != sizeof(std_vec))
				return EXIT_FAILURE;
		}
		{
			ft::vector<std::string>		ft_vec(42LU, std::string("How are you ?"));
			std::vector<std::string>	std_vec(42LU, std::string("How are you ?"));

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
	t_huint const		arr[] = {
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
			ft::input_iterator<t_huint const>	it0(arr);
			ft::input_iterator<t_huint const>	it1(arr);
			ft::vector<t_huint>					ft_vec(it0, it1);
			std::vector<t_huint>				std_vec(it0, it1);

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
			ft::random_access_iterator<t_huint const>	it0(arr);
			ft::random_access_iterator<t_huint const>	it1(arr + 10);
			ft::vector<t_huint>							ft_vec(it0, it1);
			std::vector<t_huint>						std_vec(it0, it1);

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
	t_lint const		arr0[] = {
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
	std::string const	arr1[] = {
		std::string("Gilbert"),
		std::string("Bernard"),
		std::string("Jack"),
		std::string("Odette"),
		std::string("Alphonse"),
		std::string("Georgette"),
		std::string("Anne"),
		std::string("Gaston"),
		std::string("Yves"),
		std::string("Rose"),
	};

	try
	{
		{
			ft::forward_iterator<t_lint const>	it0(arr0);
			ft::forward_iterator<t_lint const>	it1(arr0 + 10);
			ft::vector<t_lint>					ft_vec0(it0, it1);
			ft::vector<t_lint>					ft_vec1(ft_vec0);
			std::vector<t_lint>					std_vec0(it0, it1);
			std::vector<t_lint>					std_vec1(std_vec0);

			if (sizeof(ft_vec1) != sizeof(std_vec1))
				return EXIT_FAILURE;
		}
		{
			ft::forward_iterator<std::string const>	it0(arr1);
			ft::forward_iterator<std::string const>	it1(arr1 + 10);
			ft::vector<std::string>					ft_vec0(it0, it1);
			ft::vector<std::string>					ft_vec1(ft_vec0);
			std::vector<std::string>				std_vec0(it0, it1);
			std::vector<std::string>				std_vec1(std_vec0);

			if (sizeof(ft_vec1) != sizeof(std_vec1))
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

inline static int	__test_function_size(void)
{
	size_t	n;

	try
	{
		for (n = 0LU ; n < 10LU ; ++n)
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

inline static int	__test_function_max_size(void)
{
	size_t	n;

	try
	{
		for (n = 0LU ; n < 10LU ; ++n)
		{
			ft::vector<ft::pair<char, int> >	ft_vec(n, ft::pair<char, int>('F', 0));
			std::vector<std::pair<char, int> >	std_vec(n, std::pair<char, int>('F', 0));

			if (ft_vec.max_size() != std_vec.max_size())
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
	size_t	n;

	try
	{
		for (n = 0LU ; n < 10LU ; ++n)
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

inline static int	__test_function_get_allocator(void)
{
	try
	{
		ft::vector<char, std::allocator<char> >		ft_vec;
		std::vector<char, std::allocator<char> >	std_vec;

		if (ft_vec.get_allocator() != std_vec.get_allocator())
			return EXIT_FAILURE;
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
	size_t	n;

	try
	{
		for (n = 0LU ; n < 10LU ; ++n)
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
	t_lint const	arr[] = {
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
	size_t		n;

	try
	{
		for (n = 0LU ; n < 10LU ; ++n)
		{
			ft::vector<t_lint>					ft_vec(n, arr[n]);
			std::vector<t_lint>					std_vec(n, arr[n]);
			ft::vector<t_lint>::iterator		ft_it = ft_vec.begin();
			std::vector<t_lint>::iterator		std_it = std_vec.begin();
			ft::vector<t_lint>::const_iterator	ft_cit = ft_vec.begin();
			std::vector<t_lint>::const_iterator	std_cit = std_vec.begin();

			if (!!ft_it.base() != !!std_it.base() || (
					ft_it.base() &&
					std_it.base() &&
					*ft_it != *std_it) ||
				!!ft_cit.base() != !!std_cit.base() || (
					ft_cit.base() &&
					std_cit.base() &&
					*ft_cit != *std_cit))
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

inline static int	__test_function_end(void)
{
	t_lint const	arr[] = {
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
	size_t		n;

	try
	{
		for (n = 0LU ; n < 10LU ; ++n)
		{
			ft::vector<t_lint>					ft_vec(n, arr[n]);
			std::vector<t_lint>					std_vec(n, arr[n]);
			ft::vector<t_lint>::iterator		ft_it = ft_vec.end();
			std::vector<t_lint>::iterator		std_it = std_vec.end();
			ft::vector<t_lint>::const_iterator	ft_cit = ft_vec.end();
			std::vector<t_lint>::const_iterator	std_cit = std_vec.end();

			if (!!ft_it.base() != !!std_it.base() || (
					ft_it.base() &&
					std_it.base() &&
					*(ft_it - 1) != *(std_it - 1)) ||
				!!ft_cit.base() != !!std_cit.base() || (
					ft_cit.base() &&
					std_cit.base() &&
					*(ft_cit - 1) != *(std_cit - 1)))
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

inline static int	__test_function_rbegin(void)
{
	t_lint const	arr[] = {
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
	size_t		n;

	try
	{
		for (n = 0LU ; n < 10LU ; ++n)
		{
			ft::vector<t_lint>							ft_vec(n, arr[n]);
			std::vector<t_lint>							std_vec(n, arr[n]);
			ft::vector<t_lint>::reverse_iterator		ft_rit = ft_vec.rbegin();
			std::vector<t_lint>::reverse_iterator		std_rit = std_vec.rbegin();
			ft::vector<t_lint>::const_reverse_iterator	ft_crit = ft_vec.rbegin();
			std::vector<t_lint>::const_reverse_iterator	std_crit = std_vec.rbegin();

			if (!!ft_rit.base().base() != !!std_rit.base().base() || (
					ft_rit.base().base() &&
					std_rit.base().base() &&
					*std_rit != *ft_rit) ||
				!!ft_crit.base().base() != !!std_crit.base().base() || (
					ft_crit.base().base() &&
					std_crit.base().base() &&
					*ft_crit != *std_crit))
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

inline static int	__test_function_rend(void)
{
	t_lint const	arr[] = {
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
	size_t			n;

	try
	{
		for (n = 0LU ; n < 10LU ; ++n)
		{
			ft::vector<t_lint>							ft_vec(n, arr[n]);
			std::vector<t_lint>							std_vec(n, arr[n]);
			ft::vector<t_lint>::reverse_iterator		ft_rit = ft_vec.rend();
			std::vector<t_lint>::reverse_iterator		std_rit = std_vec.rend();
			ft::vector<t_lint>::const_reverse_iterator	ft_crit = ft_vec.rend();
			std::vector<t_lint>::const_reverse_iterator	std_crit = std_vec.rend();

			if (!!ft_rit.base().base() != !!std_rit.base().base() || (
					ft_rit.base().base() &&
					std_rit.base().base() &&
					*(std_rit - 1) != *(ft_rit - 1)) ||
				!!ft_crit.base().base() != !!std_crit.base().base() || (
					ft_crit.base().base() &&
					std_crit.base().base() &&
					*(ft_crit - 1) != *(std_crit - 1)))
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_front(void)
{
	std::string const	arr[] = {
		std::string("ab"),
		std::string("cd"),
		std::string("ef"),
		std::string("gh"),
		std::string("ij"),
		std::string("kl"),
		std::string("mn"),
		std::string("op"),
		std::string("qr"),
		std::string("st"),
	};
	t_uint				idx;

	try
	{
		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft::vector<std::string>		ft_vec(&arr[idx], &arr[10]);
			std::vector<std::string>	std_vec(&arr[idx], &arr[10]);

			if (ft_vec.front() != std_vec.front())
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

inline static int	__test_function_back(void)
{
	std::string const	arr[] = {
		std::string("ts"),
		std::string("rq"),
		std::string("po"),
		std::string("nm"),
		std::string("lk"),
		std::string("ji"),
		std::string("hg"),
		std::string("fe"),
		std::string("dc"),
		std::string("ba"),
	};
	t_uint				idx;

	try
	{
		for (idx = 1U ; idx < 11U ; ++idx)
		{
			ft::vector<std::string>		ft_vec(&arr[0], &arr[idx]);
			std::vector<std::string>	std_vec(&arr[0], &arr[idx]);

			if (ft_vec.back() != std_vec.back())
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

inline static int	__test_function_at(void)
{
	std::pair<t_hhuint, long double> const	arr[] = {
		std::pair<t_huint, long double>(0, 0.0),
		std::pair<t_huint, long double>(2, -2.0),
		std::pair<t_huint, long double>(4, -4.0),
		std::pair<t_huint, long double>(8, -8.0),
		std::pair<t_huint, long double>(16, -16.0),
		std::pair<t_huint, long double>(32, -32.0),
		std::pair<t_huint, long double>(64, -64.0),
		std::pair<t_huint, long double>(128, -128.0),
		std::pair<t_huint, long double>(256, -256.0),
		std::pair<t_huint, long double>(512, -512.0),
	};
	t_uint									idx;

	try
	{
		ft::vector<std::pair<t_hhuint, long double> >	ft_vec(&arr[0], &arr[10]);
		std::vector<std::pair<t_hhuint, long double> >	std_vec(&arr[0], &arr[10]);

		for (idx = 0U ; idx < 10U ; ++idx)
			if (ft_vec.at(idx) != std_vec.at(idx))
				return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_insert(void)
{
	float const			arr0[] = {
		0.0f,
		1.1f,
		2.2f,
		3.3f,
		4.4f,
		5.5f,
		6.6f,
		7.7f,
		8.8f,
		9.9f,
	};
	std::string const	arr1[] = {
		std::string("Un"),
		std::string("jour"),
		std::string("je"),
		std::string("serai"),
		std::string("hokage"),
		std::string("tel"),
		std::string("est"),
		std::string("mon"),
		std::string("nindo"),
		std::string("!!!"),
	};
	t_uint				idx;

	try
	{
		// Range insertion
		// Trivially copyable
		{
			ft::vector<float>					ft_vec;
			std::vector<float>					std_vec;
			ft::vector<float>::const_iterator	ft_cit;
			std::vector<float>::const_iterator	std_cit;

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.insert(ft_vec.begin() + idx / 2, &arr0[0], &arr0[idx]);
				std_vec.insert(std_vec.begin() + idx / 2, &arr0[0], &arr0[idx]);

				if (ft_vec.size() != std_vec.size() ||
					ft_vec.capacity() != std_vec.capacity())
					return EXIT_FAILURE;
				for (ft_cit = ft_vec.begin(), std_cit = std_vec.begin() ;
					ft_cit != ft_vec.end() && std_cit != std_vec.end() ;
					++ft_cit, ++std_cit)
					if (*ft_cit != *std_cit)
						return EXIT_FAILURE;
			}
		}
		// Range insertion
		// Non-trivial copy required
		{
			ft::vector<std::string>						ft_vec;
			std::vector<std::string>					std_vec;
			ft::vector<std::string>::const_iterator		ft_cit;
			std::vector<std::string>::const_iterator	std_cit;

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.insert(ft_vec.end() - idx / 2, &arr1[0], &arr1[idx]);
				std_vec.insert(std_vec.end() - idx / 2, &arr1[0], &arr1[idx]);

				if (ft_vec.size() != std_vec.size() ||
					ft_vec.capacity() != std_vec.capacity())
					return EXIT_FAILURE;
				for (ft_cit = ft_vec.begin(), std_cit = std_vec.begin() ;
					ft_cit != ft_vec.end() && std_cit != std_vec.end() ;
					++ft_cit, ++std_cit)
					if (*ft_cit != *std_cit)
						return EXIT_FAILURE;
			}
		}
		// Fill insertion
		// Trivially copyable
		{
			ft::vector<float>					ft_vec;
			std::vector<float>					std_vec;
			ft::vector<float>::const_iterator	ft_cit;
			std::vector<float>::const_iterator	std_cit;

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.insert(ft_vec.begin() + idx / 2, 10 - idx, arr0[idx]);
				std_vec.insert(std_vec.begin() + idx / 2, 10 - idx, arr0[idx]);

				if (ft_vec.size() != std_vec.size() ||
					ft_vec.capacity() != std_vec.capacity())
					return EXIT_FAILURE;
				for (ft_cit = ft_vec.begin(), std_cit = std_vec.begin() ;
					ft_cit != ft_vec.end() && std_cit != std_vec.end() ;
					++ft_cit, ++std_cit)
					if (*ft_cit != *std_cit)
						return EXIT_FAILURE;
			}
		}
		// Fill insertion
		// Non-trivial copy required
		{
			ft::vector<std::string>						ft_vec;
			std::vector<std::string>					std_vec;
			ft::vector<std::string>::const_iterator		ft_cit;
			std::vector<std::string>::const_iterator	std_cit;

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.insert(ft_vec.end() - idx / 2, 10 - idx, arr1[idx]);
				std_vec.insert(std_vec.end() - idx / 2, 10 - idx, arr1[idx]);

				if (ft_vec.size() != std_vec.size() ||
					ft_vec.capacity() != std_vec.capacity())
					return EXIT_FAILURE;
				for (ft_cit = ft_vec.begin(), std_cit = std_vec.begin() ;
					ft_cit != ft_vec.end() && std_cit != std_vec.end() ;
					++ft_cit, ++std_cit)
					if (*ft_cit != *std_cit)
						return EXIT_FAILURE;
			}
		}
		// Single insertion
		// Trivially copyable
		{
			ft::vector<float>					ft_vec;
			std::vector<float>					std_vec;
			ft::vector<float>::const_iterator	ft_cit;
			std::vector<float>::const_iterator	std_cit;

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.insert(ft_vec.begin() + idx / 2, arr0[idx]);
				std_vec.insert(std_vec.begin() + idx / 2, arr0[idx]);

				if (ft_vec.size() != std_vec.size() ||
					ft_vec.capacity() != std_vec.capacity())
					return EXIT_FAILURE;
				for (ft_cit = ft_vec.begin(), std_cit = std_vec.begin() ;
					ft_cit != ft_vec.end() && std_cit != std_vec.end() ;
					++ft_cit, ++std_cit)
					if (*ft_cit != *std_cit)
						return EXIT_FAILURE;
			}
		}
		// Single insertion
		// Non-trivial copy required
		{
			ft::vector<std::string>						ft_vec;
			std::vector<std::string>					std_vec;
			ft::vector<std::string>::const_iterator		ft_cit;
			std::vector<std::string>::const_iterator	std_cit;

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_cit = ft_vec.insert(ft_vec.end() - idx / 2, arr1[idx]);
				std_cit = std_vec.insert(std_vec.end() - idx / 2, arr1[idx]);

				if (ft_vec.size() != std_vec.size() ||
					ft_vec.capacity() != std_vec.capacity() ||
					ft_cit - ft_vec.begin() != std_cit - std_vec.begin())
					return EXIT_FAILURE;
				for (ft_cit = ft_vec.begin(), std_cit = std_vec.begin() ;
					ft_cit != ft_vec.end() && std_cit != std_vec.end() ;
					++ft_cit, ++std_cit)
					if (*ft_cit != *std_cit)
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

inline static int	__test_function_push_back(void)
{
	int	const arr[] = {
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

	try
	{
		ft::vector<int>						ft_vec;
		std::vector<int>					std_vec;
		ft::vector<int>::const_iterator		ft_cit;
		std::vector<int>::const_iterator	std_cit;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft_vec.push_back(arr[idx]);
			std_vec.push_back(arr[idx]);

			if (ft_vec.size() != std_vec.size() ||
				ft_vec.capacity() != std_vec.capacity())
				return EXIT_FAILURE;
			for (ft_cit = ft_vec.begin(), std_cit = std_vec.begin() ;
				ft_cit != ft_vec.end() && std_cit != std_vec.end() ;
				++ft_cit, ++std_cit)
				if (*ft_cit != *std_cit)
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

inline static int	__test_function_pop_back(void)
{
	double const	arr[] = {
		0.0,
		1.0,
		2.0,
		3.0,
		4.0,
		5.0,
		6.0,
		7.0,
		8.0,
		9.0,
	};
	t_uint	idx;

	try
	{
		ft::vector<double>					ft_vec(&arr[0], &arr[10]);
		std::vector<double>					std_vec(&arr[0], &arr[10]);
		ft::vector<double>::const_iterator	ft_cit;
		std::vector<double>::const_iterator	std_cit;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft_vec.pop_back();
			std_vec.pop_back();

			if (ft_vec.size() != std_vec.size() ||
				ft_vec.capacity() != std_vec.capacity())
				return EXIT_FAILURE;
			for (ft_cit = ft_vec.begin(), std_cit = std_vec.begin() ;
				ft_cit != ft_vec.end() && std_cit != std_vec.end() ;
				++ft_cit, ++std_cit)
				if (*ft_cit != *std_cit)
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

inline static int	__test_function_clear(void)
{
	std::string const	arr[] = {
		std::string("0123456789"),
		std::string("1234567890"),
		std::string("2345678901"),
		std::string("3456789012"),
		std::string("4567890123"),
		std::string("5678901234"),
		std::string("6789012345"),
		std::string("7890123456"),
		std::string("8901234567"),
		std::string("9012345678"),
	};

	try
	{
		ft::vector<std::string>		ft_vec(&arr[0], &arr[10]);
		std::vector<std::string>	std_vec(&arr[0], &arr[10]);

		ft_vec.clear();
		std_vec.clear();

		if (ft_vec.size() != std_vec.size() ||
			ft_vec.capacity() != std_vec.capacity())
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_reserve(void)
{
	t_huint const	arr[] = {
		2U,
		5U,
		7U,
		11U,
		13U,
		17U,
		19U,
		23U,
		29U,
		31U,
	};
	size_t	n;

	try
	{
		ft::vector<t_huint>						ft_vec(&arr[0], &arr[10]);
		std::vector<t_huint>					std_vec(&arr[0], &arr[10]);
		ft::vector<t_huint>::const_iterator		ft_cit;
		std::vector<t_huint>::const_iterator	std_cit;

		for (n = 0LU ; n < 100LU ; n += 10LU)
		{
			ft_vec.reserve(n);
			std_vec.reserve(n);

			if (ft_vec.size() != std_vec.size() ||
				ft_vec.capacity() != std_vec.capacity())
				return EXIT_FAILURE;
			for (ft_cit = ft_vec.begin(), std_cit = std_vec.begin() ;
				ft_cit != ft_vec.end() && std_cit != std_vec.end() ;
				++ft_cit, ++std_cit)
				if (*ft_cit != *std_cit)
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

inline static int	__test_function_resize(void)
{
	int const	arr[] = {
		9,
		8,
		7,
		6,
		5,
		4,
		3,
		2,
		1,
		0,
	};
	size_t	n;

	try
	{
		ft::vector<int>						ft_vec;
		std::vector<int>					std_vec;
		ft::vector<int>::const_iterator		ft_cit;
		std::vector<int>::const_iterator	std_cit;

		for (n = 0LU ; n < 10LU ; ++n)
		{
			ft_vec.resize(n * n, arr[n]);
			std_vec.resize(n * n, arr[n]);

			if (ft_vec.size() != std_vec.size()
				|| ft_vec.capacity() != std_vec.capacity())
				return EXIT_FAILURE;
			for (ft_cit = ft_vec.begin(), std_cit = std_vec.begin() ;
				ft_cit != ft_vec.end() && std_cit != std_vec.end() ;
				++ft_cit, ++std_cit)
				if (*ft_cit != *std_cit)
					return EXIT_FAILURE;
		}
		for (--n ; n > 0LU ; --n)
		{
			ft_vec.resize(n * n);
			std_vec.resize(n * n);

			if (ft_vec.size() != std_vec.size()
				|| ft_vec.capacity() != std_vec.capacity())
				return EXIT_FAILURE;
			for (ft_cit = ft_vec.begin(), std_cit = std_vec.begin() ;
				ft_cit != ft_vec.end() && std_cit != std_vec.end() ;
				++ft_cit, ++std_cit)
				if (*ft_cit != *std_cit)
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

int	test_vector(void)
{
	t_test const	tests[] = {
		__test_construct_default,
		__test_construct_fill,
		__test_construct_range,
		__test_construct_copy,
		__test_function_size,
		__test_function_max_size,
		__test_function_capacity,
		__test_function_get_allocator,
		__test_function_empty,
		__test_function_begin,
		__test_function_end,
		__test_function_rbegin,
		__test_function_rend,
		__test_function_front,
		__test_function_back,
		__test_function_at,
		__test_function_insert,
		__test_function_push_back,
		__test_function_pop_back,
		__test_function_clear,
		__test_function_reserve,
		__test_function_resize,
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
