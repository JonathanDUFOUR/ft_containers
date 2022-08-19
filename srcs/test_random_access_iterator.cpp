/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_random_access_iterator.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 04:19:40 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/19 17:56:03 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include "iterator/base/random_access_iterator.tpp"
#include "tester.hpp"

inline static int	__test_construct_default(void)
{
	title(__func__);
	try
	{
		ft::random_access_iterator<std::iostream>	it;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_construct_pointer(void)
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
		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft::random_access_iterator<int>	it(arr + idx);

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
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft::random_access_iterator<char>	it0(arr + idx);
			ft::random_access_iterator<char>	it1(it0);

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
		ft::random_access_iterator<std::string>	it0;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft::random_access_iterator<std::string>	it1(arr + idx);

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
			ft::random_access_iterator<int>	it0(arr + idx0);

			for (idx1 = 0U ; idx1 < 10U ; ++idx1)
			{
				ft::random_access_iterator<int>	it1(arr + idx1);

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
			ft::random_access_iterator<int>	it0(arr + idx0);

			for (idx1 = 0U ; idx1 < 10U ; ++idx1)
			{
				ft::random_access_iterator<int>	it1(arr + idx1);

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
			ft::random_access_iterator<t_hint>	it(arr + idx);

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
			ft::random_access_iterator<std::pair<int, char> >	it(arr + idx);

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

inline static int	__test_operator_increment_prefix(void)
{
	t_luint	arr[] = {
		424242424242420LU,
		424242424242421LU,
		424242424242422LU,
		424242424242423LU,
		424242424242424LU,
		424242424242425LU,
		424242424242426LU,
		424242424242427LU,
		424242424242428LU,
		424242424242429LU,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		ft::random_access_iterator<t_luint>	it(arr);

		for (idx = 0U ; idx < 9U ; ++idx)
			if (*++it != arr[idx + 1])
				return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_increment_postfix(void)
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
		ft::random_access_iterator<int>	it(arr);

		for (idx = 0U ; idx < 9U ; ++idx)
			if (*it++ != arr[idx] || *it != arr[idx + 1])
				return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_decrement_prefix(void)
{
	t_luint	arr[] = {
		424242424242420LU,
		424242424242421LU,
		424242424242422LU,
		424242424242423LU,
		424242424242424LU,
		424242424242425LU,
		424242424242426LU,
		424242424242427LU,
		424242424242428LU,
		424242424242429LU,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		ft::random_access_iterator<t_luint>	it(arr + 9);

		for (idx = 9U ; idx > 0U ; --idx)
			if (*--it != arr[idx - 1])
				return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_decrement_postfix(void)
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
		ft::random_access_iterator<int>	it(arr + 9);

		for (idx = 9U ; idx > 0U ; --idx)
			if (*it-- != arr[idx] || *it != arr[idx - 1])
				return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_add_assign(void)
{
	t_luint	arr[] = {
		0LU,
		1LU,
		10LU,
		11LU,
		100LU,
		101LU,
		110LU,
		111LU,
		1000LU,
		1001LU,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft::random_access_iterator<t_luint>	it(arr);

			it += idx;
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

inline static int	__test_operator_sub_assign(void)
{
	t_luint	arr[] = {
		0LU,
		1LU,
		10LU,
		11LU,
		100LU,
		101LU,
		110LU,
		111LU,
		1000LU,
		1001LU,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft::random_access_iterator<t_luint>	it(arr + 9);

			it -= idx;
			if (*it != arr[9 - idx])
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

inline static int	__test_operator_add(void)
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
		ft::random_access_iterator<float>	it(arr);

		for (idx = 0U ; idx < 10U ; ++idx)
			if (*(it + idx) != arr[idx])
				return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_sub(void)
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
		ft::random_access_iterator<float>	it(arr + 9);

		for (idx = 0U ; idx < 10U ; ++idx)
			if (*(it - idx) != arr[9 - idx])
				return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_distance(void)
{
	std::string	arr[] = {
		std::string("Un"),
		std::string("elephant"),
		std::string("qui"),
		std::string("se"),
		std::string("balancait"),
		std::string("sur"),
		std::string("une"),
		std::string("toile"),
		std::string("d'"),
		std::string("araignee"),
	};
	ptrdiff_t	idx0;
	ptrdiff_t	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0L ; idx0 < 10L ; ++idx0)
		{
			ft::random_access_iterator<std::string>	it0(arr + idx0);

			for (idx1 = 0L ; idx1 < 10L ; ++idx1)
			{
				ft::random_access_iterator<std::string>	it1(arr + idx1);

				if (it0 - it1 != idx0 - idx1)
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

inline static int	__test_operator_access(void)
{
	t_hhuint	arr[] = {
		0xff,
		0xfe,
		0xfd,
		0xfc,
		0xfb,
		0xfa,
		0xf9,
		0xf8,
		0xf7,
		0xf6,
	};
	t_uint		idx;

	title(__func__);
	try
	{
		ft::random_access_iterator<t_hhuint>	it(arr);

		for (idx = 0U ; idx < 10U ; ++idx)
			if (it[idx] != arr[idx])
				return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_SUCCESS;
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
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < 10U ; ++idx0)
		{
			ft::random_access_iterator<int>	it0(arr + idx0);

			for (idx1 = 0U ; idx1 < 10U ; ++idx1)
			{
				ft::random_access_iterator<int>	it1(arr + idx1);

				if ((it0 < it1) != (idx0 < idx1))
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
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < 10U ; ++idx0)
		{
			ft::random_access_iterator<int>	it0(arr + idx0);

			for (idx1 = 0U ; idx1 < 10U ; ++idx1)
			{
				ft::random_access_iterator<int>	it1(arr + idx1);

				if ((it0 > it1) != (idx0 > idx1))
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
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < 10U ; ++idx0)
		{
			ft::random_access_iterator<int>	it0(arr + idx0);

			for (idx1 = 0U ; idx1 < 10U ; ++idx1)
			{
				ft::random_access_iterator<int>	it1(arr + idx1);

				if ((it0 <= it1) != (idx0 <= idx1))
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
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < 10U ; ++idx0)
		{
			ft::random_access_iterator<int>	it0(arr + idx0);

			for (idx1 = 0U ; idx1 < 10U ; ++idx1)
			{
				ft::random_access_iterator<int>	it1(arr + idx1);

				if ((it0 >= it1) != (idx0 >= idx1))
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

int	test_random_access_iterator(void)
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
		__test_operator_decrement_prefix,
		__test_operator_decrement_postfix,
		__test_operator_add_assign,
		__test_operator_sub_assign,
		__test_operator_add,
		__test_operator_sub,
		__test_operator_distance,
		__test_operator_access,
		__test_operator_lower,
		__test_operator_greater,
		__test_operator_lower_equal,
		__test_operator_greater_equal,
		NULL,
	};
	int				koCount;
	int				idx;


	std::cerr << "\033[38;2;0;173;255m";
	std::cout << "####################################################" << '\n';
	std::cout << "##             RANDOM ACCESS ITERATOR             ##" << '\n';
	std::cout << "####################################################" << '\n';
	std::cerr << "\033[0m";

	for (koCount = 0, idx = 0 ; tests[idx] ; ++idx)
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
