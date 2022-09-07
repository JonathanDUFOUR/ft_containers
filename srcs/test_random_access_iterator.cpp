/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_random_access_iterator.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 04:19:40 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/08 00:46:52 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include "arrays.hpp"
#include "iterator/base/random_access_iterator.tpp"
#include "tester.hpp"

inline static int	__test_constructor(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Default constructor
		{
			ft::random_access_iterator<std::iostream>	it;
		}
		// Pointer constructor
		{
			for (idx = 0U ; idx < g_int_size ; ++idx)
			{
				ft::random_access_iterator<int>	it(&g_int[idx]);

				if (*it != g_int[idx])
					return EXIT_FAILURE;
			}
		}
		// Copy constructor
		{
			for (idx = 0U ; idx < g_int_size ; ++idx)
			{
				ft::random_access_iterator<int>	it0(&g_int[idx]);
				ft::random_access_iterator<int>	it1(it0);

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
	t_uint	idx;

	title(__func__);
	try
	{
		ft::random_access_iterator<std::string>	it0;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			ft::random_access_iterator<std::string>	it1(&g_string[idx]);

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
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			ft::random_access_iterator<int>	it0(&g_int[idx0]);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				ft::random_access_iterator<int const>	it1(&g_int[idx1]);

				if ((it0 == it1) != (idx0 == idx1))
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

inline static int	__test_operator_difference(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			ft::random_access_iterator<int>	it0(&g_int[idx0]);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				ft::random_access_iterator<int const>	it1(&g_int[idx1]);

				if ((it0 != it1) != (idx0 != idx1))
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

inline static int	__test_operator_dereference(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_hint_size ; ++idx)
		{
			ft::random_access_iterator<t_hint>	it(&g_hint[idx]);

			*it += 42;
			if (*it != g_hint[idx])
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
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_pair_size ; ++idx)
		{
			ft::random_access_iterator<std::pair<int, char> >	it(&g_pair[idx]);

			if (it->first != g_pair[idx].first || it->second != g_pair[idx].second)
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
	t_uint	idx;

	title(__func__);
	try
	{
		// Prefix incrementation
		{
			ft::random_access_iterator<t_luint>	it(&g_luint[0]);

			for (idx = 1U ; idx < g_luint_size ; ++idx)
				if (*++it != g_luint[idx])
					return EXIT_FAILURE;
		}
		// Postfix incrementation
		{
			ft::random_access_iterator<t_luint>	it(&g_luint[0]);

			for (idx = 1U ; idx < g_luint_size ; ++idx)
				if (*it++ != g_luint[idx - 1] || *it != g_luint[idx])
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

inline static int	__test_operator_decrement(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Prefix decrementation
		{
			ft::random_access_iterator<t_luint>	it(&g_luint[g_luint_size - 1]);

			for (idx = g_luint_size - 1 ; idx ; --idx)
				if (*--it != g_luint[idx - 1])
					return EXIT_FAILURE;
		}
		// Postfix decrementation
		{
			ft::random_access_iterator<t_luint>	it(&g_luint[g_luint_size - 1]);

			for (idx = g_luint_size - 1 ; idx ; --idx)
				if (*it-- != g_luint[idx] || *it != g_luint[idx - 1])
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

inline static int	__test_operator_add_assign(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_luint_size ; ++idx)
		{
			ft::random_access_iterator<t_luint>	it(&g_luint[0]);

			it = (it += idx);
			if (*it != g_luint[idx])
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
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_luint_size ; ++idx)
		{
			ft::random_access_iterator<t_luint>	it(&g_luint[g_luint_size - 1]);

			it = (it -= idx);
			if (*it != g_luint[g_luint_size - 1 - idx])
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
	t_uint	idx;

	title(__func__);
	try
	{
		ft::random_access_iterator<float>	it(&g_float[0]);

		for (idx = 0U ; idx < g_float_size ; ++idx)
			if (*(it + idx) != g_float[idx] || *(idx + it) != g_float[idx])
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
	t_uint	idx;

	title(__func__);
	try
	{
		ft::random_access_iterator<float>	it(&g_float[g_float_size - 1]);

		for (idx = 0U ; idx < g_float_size ; ++idx)
			if (*(it - idx) != g_float[g_float_size - 1 - idx])
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
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < g_string_size ; ++idx0)
		{
			ft::random_access_iterator<std::string>	it0(&g_string[idx0]);

			for (idx1 = 0U ; idx1 < g_string_size ; ++idx1)
			{
				ft::random_access_iterator<std::string>	it1(&g_string[idx1]);

				if (it0 - it1 != static_cast<std::ptrdiff_t>(idx0) - static_cast<std::ptrdiff_t>(idx1))
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
	t_uint	idx;

	title(__func__);
	try
	{
		ft::random_access_iterator<t_hhuint>	it(&g_hhuint[0]);

		for (idx = 0U ; idx < g_hhuint_size ; ++idx)
			if (it[idx] != g_hhuint[idx])
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
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			ft::random_access_iterator<int>	it0(&g_int[idx0]);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				ft::random_access_iterator<int const>	it1(&g_int[idx1]);

				if ((it0 < it1) != (idx0 < idx1))
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

inline static int	__test_operator_greater(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			ft::random_access_iterator<int>	it0(&g_int[idx0]);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				ft::random_access_iterator<int const>	it1(&g_int[idx1]);

				if ((it0 > it1) != (idx0 > idx1))
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

inline static int	__test_operator_lower_equal(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			ft::random_access_iterator<int>	it0(&g_int[idx0]);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				ft::random_access_iterator<int const>	it1(&g_int[idx1]);

				if ((it0 <= it1) != (idx0 <= idx1))
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

inline static int	__test_operator_greater_equal(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			ft::random_access_iterator<int>	it0(&g_int[idx0]);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				ft::random_access_iterator<int const>	it1(&g_int[idx1]);

				if ((it0 >= it1) != (idx0 >= idx1))
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

int	test_random_access_iterator(void)
{
	t_test const	tests[] = {
		__test_constructor,
		__test_operator_assign,
		__test_operator_equal,
		__test_operator_difference,
		__test_operator_dereference,
		__test_operator_maddress,
		__test_operator_increment,
		__test_operator_decrement,
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
	t_uint			koCount;
	t_uint			idx;


	std::cerr << "\033[38;2;0;173;255m";
	std::cout << "####################################################" << '\n';
	std::cout << "##             RANDOM ACCESS ITERATOR             ##" << '\n';
	std::cout << "####################################################" << '\n';
	std::cerr << "\033[0m";

	for (koCount = 0U, idx = 0U ; tests[idx] ; ++idx)
		switch (tests[idx]())
		{
			case EXIT_SUCCESS:
				std::cerr << "\033[38;2;0;255;0m";
				std::cout << "[OK]" << '\n';
				std::cerr << "\033[0m";
				break;

			case EXIT_FAILURE:
				std::cerr << "\033[38;2;255;0;0m";
				std::cout << "[KO]" << '\n';
				std::cerr << "\033[0m";
				++koCount;
				break;
		}
	std::cout << '\n';
	return koCount;
}
