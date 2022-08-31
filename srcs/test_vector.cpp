/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:36:04 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/31 10:47:15 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>
#include "vector.hpp"
#include "utility.hpp"
#include "tester.hpp"

inline static int	__test_constructor(void)
{
	t_huint const		arr0[] = {
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
	std::string const	arr1[] = {
		std::string("Never gonna give you up"),
		std::string("Never gonna let you down"),
		std::string("Never gonna run around and desert you"),
		std::string("Never gonna make you cry"),
		std::string("Never gonna say goodbye"),
		std::string("Never gonna tell a lie and hurt you"),
		std::string("We've known each other for so long"),
		std::string("Your heart's been aching but you're too shy to say it"),
		std::string("Inside, we both know what's been going on"),
		std::string ("We know the game and we're gonna play it"),
	};
	title(__func__);
	try
	{
		// Default constructor
		{
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;

			if (sizeof(ft_vec) != sizeof(std_vec) || memcmp(&ft_vec, &std_vec, sizeof(ft_vec)))
				return EXIT_FAILURE;
		}
		// Fill constructor
		// Trivially copyable
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
		}
		// Fill constructor
		// Trivially copyable
		// Ambiguous
		{
			{
				ft::vector<char>	ft_vec(static_cast<char>(21LU), '$');
				std::vector<char>	std_vec(static_cast<char>(21LU), '$');

				if (sizeof(ft_vec) != sizeof(std_vec))
					return EXIT_FAILURE;
			}
			{
				ft::vector<char>	ft_vec(static_cast<char>(0LU), 'A');
				std::vector<char>	std_vec(static_cast<char>(0LU), 'A');

				if (sizeof(ft_vec) != sizeof(std_vec))
					return EXIT_FAILURE;
			}
			{
				ft::vector<char>	ft_vec(static_cast<char>(42LU), 42);
				std::vector<char>	std_vec(static_cast<char>(42LU), 42);

				if (sizeof(ft_vec) != sizeof(std_vec))
					return EXIT_FAILURE;
			}
		}
		// Fill constructor
		// Non-trivial copy required
		{
			{
				ft::vector<std::string>		ft_vec(21LU);
				std::vector<std::string>	std_vec(21LU);

				if (sizeof(ft_vec) != sizeof(std_vec))
					return EXIT_FAILURE;
			}
			{
				ft::vector<std::string>		ft_vec(0LU, std::string("pouic"));
				std::vector<std::string>	std_vec(0LU, std::string("pouic"));

				if (sizeof(ft_vec) != sizeof(std_vec))
					return EXIT_FAILURE;
			}
			{
				ft::vector<std::string>		ft_vec(42LU, std::string("Hello World !"));
				std::vector<std::string>	std_vec(42LU, std::string("Hello World !"));

				if (sizeof(ft_vec) != sizeof(std_vec))
					return EXIT_FAILURE;
			}
		}
		// Range constructor
		// Trivially copyable
		{
			{
				ft::input_iterator<t_huint const>	it0(arr0);
				ft::input_iterator<t_huint const>	it1(arr0);
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
				ft::random_access_iterator<t_huint const>	it0(arr0);
				ft::random_access_iterator<t_huint const>	it1(arr0 + 10);
				ft::vector<t_huint>							ft_vec(it0, it1);
				std::vector<t_huint>						std_vec(it0, it1);

				if (sizeof(ft_vec) != sizeof(std_vec))
					return EXIT_FAILURE;
			}
		}
		// Range constructor
		// Non-trivial copy required
		{
			{
				ft::input_iterator<std::string const>	it0(arr1);
				ft::input_iterator<std::string const>	it1(arr1);
				ft::vector<std::string>					ft_vec(it0, it1);
				std::vector<std::string>				std_vec(it0, it1);

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
				ft::random_access_iterator<std::string const>	it0(arr1);
				ft::random_access_iterator<std::string const>	it1(arr1 + 10);
				ft::vector<std::string>							ft_vec(it0, it1);
				std::vector<std::string>						std_vec(it0, it1);

				if (sizeof(ft_vec) != sizeof(std_vec))
					return EXIT_FAILURE;
			}
		}
		// Copy constructor
		// Trivially copyable
		{
			ft::forward_iterator<t_huint const>	it0(arr0);
			ft::forward_iterator<t_huint const>	it1(arr0 + 10);
			ft::vector<t_huint>					ft_vec0(it0, it1);
			ft::vector<t_huint>					ft_vec1(ft_vec0);
			std::vector<t_huint>				std_vec0(it0, it1);
			std::vector<t_huint>				std_vec1(std_vec0);

			if (sizeof(ft_vec1) != sizeof(std_vec1))
				return EXIT_FAILURE;
		}
		// Copy constructor
		// Non-trivial copy required
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

	title(__func__);
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

	title(__func__);
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

	title(__func__);
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
	title(__func__);
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

	title(__func__);
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
	size_t			n;

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::vector<t_lint>::iterator	ft_it;
			std::vector<t_lint>::iterator	std_it;

			for (n = 0LU ; n < 10LU ; ++n)
			{
				ft::vector<t_lint>	ft_vec(n, arr[n]);
				std::vector<t_lint>	std_vec(n, arr[n]);

				ft_it = ft_vec.begin();
				std_it = std_vec.begin();

				if (!!ft_it.base() != !!std_it.base() || (ft_it.base() && std_it.base() && *ft_it != *std_it))
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			ft::vector<t_lint>::const_iterator	ft_cit;
			std::vector<t_lint>::const_iterator	std_cit;

			for (n = 0LU ; n < 10LU ; ++n)
			{
				ft::vector<t_lint> const	ft_vec(n, arr[n]);
				std::vector<t_lint> const	std_vec(n, arr[n]);

				ft_cit = ft_vec.begin();
				std_cit = std_vec.begin();

				if (!!ft_cit.base() != !!std_cit.base() || (ft_cit.base() && std_cit.base() && *ft_cit != *std_cit))
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
	size_t			n;

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::vector<t_lint>::iterator	ft_it;
			std::vector<t_lint>::iterator	std_it;

			for (n = 0LU ; n < 10LU ; ++n)
			{
				ft::vector<t_lint>	ft_vec(n, arr[n]);
				std::vector<t_lint>	std_vec(n, arr[n]);

				ft_it = ft_vec.end();
				std_it = std_vec.end();

				if (!!ft_it.base() != !!std_it.base() || (ft_it.base() && std_it.base() && *--ft_it != *--std_it))
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			ft::vector<t_lint>::const_iterator	ft_cit;
			std::vector<t_lint>::const_iterator	std_cit;

			for (n = 0LU ; n < 10LU ; ++n)
			{
				ft::vector<t_lint> const	ft_vec(n, arr[n]);
				std::vector<t_lint> const	std_vec(n, arr[n]);

				ft_cit = ft_vec.end();
				std_cit = std_vec.end();

				if (!!ft_cit.base() != !!std_cit.base() || (ft_cit.base() && std_cit.base() && *--ft_cit != *--std_cit))
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
	size_t			n;

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::vector<t_lint>::reverse_iterator	ft_rit;
			std::vector<t_lint>::reverse_iterator	std_rit;

			for (n = 0LU ; n < 10LU ; ++n)
			{
				ft::vector<t_lint>	ft_vec(n, arr[n]);
				std::vector<t_lint>	std_vec(n, arr[n]);

				ft_rit = ft_vec.rbegin();
				std_rit = std_vec.rbegin();

				if (!!ft_rit.base().base() != !!std_rit.base().base() ||
					(ft_rit.base().base() && std_rit.base().base() && *ft_rit != *std_rit))
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			ft::vector<t_lint>::const_reverse_iterator	ft_crit;
			std::vector<t_lint>::const_reverse_iterator	std_crit;

			for (n = 0LU ; n < 10LU ; ++n)
			{
				ft::vector<t_lint> const	ft_vec(n, arr[n]);
				std::vector<t_lint> const	std_vec(n, arr[n]);

				ft_crit = ft_vec.rbegin();
				std_crit = std_vec.rbegin();

				if (!!ft_crit.base().base() != !!std_crit.base().base() ||
					(ft_crit.base().base() && std_crit.base().base() && *ft_crit != *std_crit))
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

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::vector<t_lint>::reverse_iterator	ft_rit;
			std::vector<t_lint>::reverse_iterator	std_rit;

			for (n = 0LU ; n < 10LU ; ++n)
			{
				ft::vector<t_lint>	ft_vec(n, arr[n]);
				std::vector<t_lint>	std_vec(n, arr[n]);

				ft_rit = ft_vec.rend();
				std_rit = std_vec.rend();

				if (!!ft_rit.base().base() != !!std_rit.base().base() ||
					(ft_rit.base().base() && std_rit.base().base() && *--ft_rit != *--std_rit))
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			ft::vector<t_lint>::const_reverse_iterator	ft_crit;
			std::vector<t_lint>::const_reverse_iterator	std_crit;

			for (n = 0LU ; n < 10LU ; ++n)
			{
				ft::vector<t_lint> const	ft_vec(n, arr[n]);
				std::vector<t_lint> const	std_vec(n, arr[n]);

				ft_crit = ft_vec.rend();
				std_crit = std_vec.rend();

				if (!!ft_crit.base().base() != !!std_crit.base().base() ||
					(ft_crit.base().base() && std_crit.base().base() && *--ft_crit != *--std_crit))
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

inline static int	__test_function_front(void)
{
	int const	arr[] = {
		5,
		10,
		20,
		40,
		80,
		160,
		320,
		640,
		1280,
		2560,
	};
	t_uint		idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft::vector<int>		ft_vec(&arr[idx], &arr[10]);
				std::vector<int>	std_vec(&arr[idx], &arr[10]);

				if (++ft_vec.front() != ++std_vec.front())
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft::vector<int> const	ft_vec(&arr[idx], &arr[10]);
				std::vector<int> const	std_vec(&arr[idx], &arr[10]);

				if (ft_vec.front() != std_vec.front())
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

inline static int	__test_function_back(void)
{
	int const	arr[] = {
		5,
		10,
		20,
		40,
		80,
		160,
		320,
		640,
		1280,
		2560,
	};
	t_uint		idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			for (idx = 1U ; idx < 11U ; ++idx)
			{
				ft::vector<int>		ft_vec(&arr[0], &arr[idx]);
				std::vector<int>	std_vec(&arr[0], &arr[idx]);

				if (--ft_vec.back() != --std_vec.back())
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			for (idx = 1U ; idx < 11U ; ++idx)
			{
				ft::vector<int> const	ft_vec(&arr[0], &arr[idx]);
				std::vector<int> const	std_vec(&arr[0], &arr[idx]);

				if (ft_vec.back() != std_vec.back())
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

inline static int	__test_function_at(void)
{
	int const	arr[] = {
		5,
		10,
		20,
		40,
		80,
		160,
		320,
		640,
		1280,
		2560,
	};
	t_uint		idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::vector<int>		ft_vec(&arr[0], &arr[10]);
			std::vector<int>	std_vec(&arr[0], &arr[10]);

			// Normal usage
			{
				for (idx = 0U ; idx < 10U ; ++idx)
					if (++ft_vec.at(idx) != ++std_vec.at(idx))
						return EXIT_FAILURE;
			}
			// Overlimits usage
			{
				try
				{
					++ft_vec.at(42LU);
				}
				catch (std::out_of_range const &e)
				{
					goto next0;
				}
				return EXIT_FAILURE;
				next0:;
			}
		}
		// Constant access
		{
			ft::vector<int> const	ft_vec(&arr[0], &arr[10]);
			std::vector<int> const	std_vec(&arr[0], &arr[10]);

			// Normal usage
			{
				for (idx = 0U ; idx < 10U ; ++idx)
					if (ft_vec.at(idx) != std_vec.at(idx))
						return EXIT_FAILURE;
			}
			// Overlimits usage
			{
				try
				{
					ft_vec.at(42LU);
				}
				catch (std::out_of_range const &e)
				{
					goto next1;
				}
				return EXIT_FAILURE;
				next1:;
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
	int const			arr1[] = {
		-1,
		-12,
		-123,
		-1234,
		-12345,
		-123456,
		-1234567,
		-12345678,
		-123456789,
		-1234567890
	};
	std::string const	arr2[] = {
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

	title(__func__);
	try
	{
		// Fill insertion
		// Trivially copyable
		{
			ft::vector<float>	ft_vec;
			std::vector<float>	std_vec;

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.insert(ft_vec.begin() + idx / 2, 10 - idx, arr0[idx]);
				std_vec.insert(std_vec.begin() + idx / 2, 10 - idx, arr0[idx]);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return EXIT_FAILURE;
			}
		}
		// Fill insertion
		// Trivially copyable
		// Ambiguous
		{
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.insert(ft_vec.begin() + idx / 2, static_cast<int>(10 - idx), arr1[idx]);
				std_vec.insert(std_vec.begin() + idx / 2, static_cast<int>(10 - idx), arr1[idx]);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return EXIT_FAILURE;
			}
		}
		// Fill insertion
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec;
			std::vector<std::string>	std_vec;

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.insert(ft_vec.end() - idx / 2, 10 - idx, arr2[idx]);
				std_vec.insert(std_vec.end() - idx / 2, 10 - idx, arr2[idx]);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return EXIT_FAILURE;
			}
		}
		// Range insertion
		// Trivially copyable
		{
			ft::vector<float>	ft_vec;
			std::vector<float>	std_vec;

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.insert(ft_vec.begin() + idx / 2, &arr0[0], &arr0[idx]);
				std_vec.insert(std_vec.begin() + idx / 2, &arr0[0], &arr0[idx]);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return EXIT_FAILURE;
			}
		}
		// Range insertion
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec;
			std::vector<std::string>	std_vec;

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.insert(ft_vec.end() - idx / 2, &arr2[0], &arr2[idx]);
				std_vec.insert(std_vec.end() - idx / 2, &arr2[0], &arr2[idx]);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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
				ft_cit = ft_vec.insert(ft_vec.begin() + idx / 2, arr0[idx]);
				std_cit = std_vec.insert(std_vec.begin() + idx / 2, arr0[idx]);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()) ||
					ft_cit - ft_vec.begin() != std_cit - std_vec.begin())
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
				ft_cit = ft_vec.insert(ft_vec.end() - idx / 2, arr2[idx]);
				std_cit = std_vec.insert(std_vec.end() - idx / 2, arr2[idx]);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()) ||
					ft_cit - ft_vec.begin() != std_cit - std_vec.begin())
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

inline static int	__test_function_erase(void)
{
	t_hhuint const	arr[] = {
		255U,
		254U,
		253U,
		252U,
		251U,
		250U,
		249U,
		248U,
		247U,
		246U,
	};
	t_uint			idx;

	title(__func__);
	try
	{
		// Range erase
		{
			ft::vector<t_hhuint>					ft_vec;
			std::vector<t_hhuint>					std_vec;
			ft::vector<t_hhuint>::const_iterator	ft_cit;
			std::vector<t_hhuint>::const_iterator	std_cit;

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.insert(ft_vec.end(), &arr[idx], &arr[10]);
				std_vec.insert(std_vec.end(), &arr[idx], &arr[10]);

				ft_cit = ft_vec.erase(ft_vec.begin() + idx, ft_vec.begin() + idx * 2);
				std_cit = std_vec.erase(std_vec.begin() + idx, std_vec.begin() + idx * 2);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()) ||
					ft_cit - ft_vec.begin() != std_cit - std_vec.begin())
					return EXIT_FAILURE;
			}
		}
		// Single erase
		{
			ft::vector<t_hhuint>					ft_vec;
			std::vector<t_hhuint>					std_vec;
			ft::vector<t_hhuint>::const_iterator	ft_cit;
			std::vector<t_hhuint>::const_iterator	std_cit;

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.insert(ft_vec.end(), &arr[idx], &arr[10]);
				std_vec.insert(std_vec.end(), &arr[idx], &arr[10]);

				ft_cit = ft_vec.erase(ft_vec.begin() + idx);
				std_cit = std_vec.erase(std_vec.begin() + idx);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()) ||
					ft_cit - ft_vec.begin() != std_cit - std_vec.begin())
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
	long double const	arr0[] = {
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
	std::string const	arr1[] = {
		std::string("Lorem"),
		std::string("ipsum"),
		std::string("dolor"),
		std::string("sit"),
		std::string("amet"),
		std::string("consectetur"),
		std::string("adipiscing"),
		std::string("elit"),
		std::string("Mauris"),
		std::string("lobortis"),
	};
	t_uint				idx;

	title(__func__);
	try
	{
		// Trivial copyable
		{
			ft::vector<long double>		ft_vec;
			std::vector<long double>	std_vec;

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.push_back(arr0[idx]);
				std_vec.push_back(arr0[idx]);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return EXIT_FAILURE;
			}
		}
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec;
			std::vector<std::string>	std_vec;

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.push_back(arr1[idx]);
				std_vec.push_back(arr1[idx]);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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

inline static int	__test_function_pop_back(void)
{
	int const	arr[] = {
		-1,
		-2,
		-3,
		-4,
		-5,
		-6,
		-7,
		-8,
		-9,
		-10,
	};
	t_uint		idx;

	title(__func__);
	try
	{
		ft::vector<int>		ft_vec(&arr[0], &arr[10]);
		std::vector<int>	std_vec(&arr[0], &arr[10]);

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft_vec.pop_back();
			std_vec.pop_back();

			if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
				!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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

	title(__func__);
	try
	{
		ft::vector<std::string>		ft_vec(&arr[0], &arr[10]);
		std::vector<std::string>	std_vec(&arr[0], &arr[10]);

		ft_vec.clear();
		std_vec.clear();

		if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity())
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_assign(void)
{
	double const		arr0[] = {
		0.0,
		1.9,
		2.8,
		3.7,
		4.6,
		5.5,
		6.4,
		7.3,
		8.2,
		9.1,
	};
	t_lint const		arr1[] = {
		2L,
		-5L,
		10L,
		-21L,
		42L,
		-85L,
		170L,
		-341L,
		682L,
		-1365L
	};
	std::string const	arr2[] = {
		std::string("There's a calm surrender"),
		std::string("to the rush of day"),
		std::string("when the heat of a rolling wind"),
		std::string("can be turned away"),
		std::string("An enchanted moment"),
		std::string("And it sees the me through"),
		std::string("It's enough for this restless warrior"),
		std::string("Just to be with you"),
		std::string("And can you feel the love tonight"),
		std::string("It is where we are"),
	};
	t_uint				idx;

	title(__func__);
	try
	{
		// Fill assignation
		// Trivially copyable
		{
			ft::vector<double>	ft_vec(7LU, NAN);
			std::vector<double>	std_vec(7LU, NAN);

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.assign(idx * idx, arr0[idx]);
				std_vec.assign(idx * idx, arr0[idx]);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return EXIT_FAILURE;
			}
		}
		// Fill assignation
		// Trivially copyable
		// Ambiguous
		{
			ft::vector<t_lint>	ft_vec(7LU, 42L);
			std::vector<t_lint>	std_vec(7LU, 42L);

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.assign(static_cast<t_lint>(idx * idx), arr1[idx]);
				std_vec.assign(static_cast<t_lint>(idx * idx), arr1[idx]);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return EXIT_FAILURE;
			}
		}
		// Fill assignation
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec(7LU, std::string("Koala"));
			std::vector<std::string>	std_vec(7LU, std::string("Koala"));

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.assign(idx * idx, arr2[idx]);
				std_vec.assign(idx * idx, arr2[idx]);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return EXIT_FAILURE;
			}
			
		}
		// Range assignation
		// Trivially copyable
		{
			ft::vector<double>	ft_vec(7LU, NAN);
			std::vector<double>	std_vec(7LU, NAN);

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.assign(&arr0[idx / 2 + (idx % 2)], &arr0[10 - idx / 2 - !(idx % 2)]);
				std_vec.assign(&arr0[idx / 2 + (idx % 2)], &arr0[10 - idx / 2 - !(idx % 2)]);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return EXIT_FAILURE;
			}
		}
		// Range assignation
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec(7LU, std::string("Koala"));
			std::vector<std::string>	std_vec(7LU, std::string("Koala"));

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft_vec.assign(&arr2[idx / 2 + (idx % 2)], &arr2[10 - idx / 2 - !(idx % 2)]);
				std_vec.assign(&arr2[idx / 2 + (idx % 2)], &arr2[10 - idx / 2 - !(idx % 2)]);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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

inline static int	__test_function_swap(void)
{
	t_uint const		arr0[] = {
		4294967295U,
		2147483647U,
		1073741823U,
		536870911U,
		268435455U,
		134217727U,
		67108863U,
		33554431U,
		16777215U,
		8388607U,
	};
	std::string const	arr1[] = {
		std::string("goat"),
		std::string("wolf"),
		std::string("elephant"),
		std::string("penguin"),
		std::string("worm"),
		std::string("bee"),
		std::string("dolphin"),
		std::string("wale"),
		std::string("eagle"),
		std::string("tiger"),
	};
	t_uint				idx;

	title(__func__);
	try
	{
		// Member function
		// Trivially copyable
		{
			ft::vector<t_uint>	ft_vec0(&arr0[0], &arr0[10]);
			std::vector<t_uint>	std_vec0(&arr0[0], &arr0[10]);
			ft::vector<t_uint>	ft_vec1;
			std::vector<t_uint>	std_vec1;

			for (idx = 0U ; idx < 20U ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin(), arr0[idx / 2]);
				std_vec1.insert(std_vec1.begin(), arr0[idx / 2]);
			}

			ft_vec0.swap(ft_vec1);
			std_vec0.swap(std_vec1);

			if (ft_vec0.size() != std_vec0.size() || ft_vec0.capacity() != std_vec0.capacity() ||
				ft_vec1.size() != std_vec1.size() || ft_vec1.capacity() != std_vec1.capacity() ||
				!std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()) ||
				!std::equal(ft_vec1.begin(), ft_vec1.end(), std_vec1.begin()))
				return EXIT_FAILURE;
		}
		// Member function
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec0(&arr1[0], &arr1[10]);
			std::vector<std::string>	std_vec0(&arr1[0], &arr1[10]);
			ft::vector<std::string>		ft_vec1;
			std::vector<std::string>	std_vec1;

			for (idx = 0U ; idx < 20U ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin(), arr1[idx / 2]);
				std_vec1.insert(std_vec1.begin(), arr1[idx / 2]);
			}
			
			ft_vec0.swap(ft_vec1);
			std_vec0.swap(std_vec1);

			if (ft_vec0.size() != std_vec0.size() || ft_vec0.capacity() != std_vec0.capacity() ||
				ft_vec1.size() != std_vec1.size() || ft_vec1.capacity() != std_vec1.capacity() ||
				!std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()) ||
				!std::equal(ft_vec1.begin(), ft_vec1.end(), std_vec1.begin()))
				return EXIT_FAILURE;
		}
		// Non-member function
		// Trivially copyable
		{
			ft::vector<t_uint>	ft_vec0(&arr0[0], &arr0[10]);
			std::vector<t_uint>	std_vec0(&arr0[0], &arr0[10]);
			ft::vector<t_uint>	ft_vec1;
			std::vector<t_uint>	std_vec1;

			for (idx = 0U ; idx < 20U ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin(), arr0[idx / 2]);
				std_vec1.insert(std_vec1.begin(), arr0[idx / 2]);
			}

			ft::swap(ft_vec0, ft_vec1);
			std::swap(std_vec0, std_vec1);

			if (ft_vec0.size() != std_vec0.size() || ft_vec0.capacity() != std_vec0.capacity() ||
				ft_vec1.size() != std_vec1.size() || ft_vec1.capacity() != std_vec1.capacity() ||
				!std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()) ||
				!std::equal(ft_vec1.begin(), ft_vec1.end(), std_vec1.begin()))
				return EXIT_FAILURE;
		}
		// Non-member function
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec0(&arr1[0], &arr1[10]);
			std::vector<std::string>	std_vec0(&arr1[0], &arr1[10]);
			ft::vector<std::string>		ft_vec1;
			std::vector<std::string>	std_vec1;

			for (idx = 0U ; idx < 20U ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin(), arr1[idx / 2]);
				std_vec1.insert(std_vec1.begin(), arr1[idx / 2]);
			}

			ft::swap(ft_vec0, ft_vec1);
			std::swap(std_vec0, std_vec1);

			if (ft_vec0.size() != std_vec0.size() || ft_vec0.capacity() != std_vec0.capacity() ||
				ft_vec1.size() != std_vec1.size() || ft_vec1.capacity() != std_vec1.capacity() ||
				!std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()) ||
				!std::equal(ft_vec1.begin(), ft_vec1.end(), std_vec1.begin()))
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
	size_t			n;

	title(__func__);
	try
	{
		ft::vector<t_huint>		ft_vec(&arr[0], &arr[10]);
		std::vector<t_huint>	std_vec(&arr[0], &arr[10]);

		// Normal usage
		{
			for (n = 0LU ; n < 100LU ; n += 10LU)
			{
				ft_vec.reserve(n);
				std_vec.reserve(n);

				if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
					!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return EXIT_FAILURE;
			}
		}
		// Overlimits usage
		{
			try
			{
				ft_vec.reserve(ft_vec.max_size() + 42LU);
			}
			catch (std::length_error const &e)
			{
				goto next;
			}
			return EXIT_FAILURE;
			next:

			if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
				!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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
	size_t		n;

	title(__func__);
	try
	{
		ft::vector<int>						ft_vec;
		std::vector<int>					std_vec;

		for (n = 0LU ; n < 10LU ; ++n)
		{
			ft_vec.resize(n * n, arr[n]);
			std_vec.resize(n * n, arr[n]);

			if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
				!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
				return EXIT_FAILURE;
		}
		for (--n ; n > 0LU ; --n)
		{
			ft_vec.resize(n * n);
			std_vec.resize(n * n);

			if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity() ||
				!std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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
	double const		arr0[] = {
		0.0,
		1.9,
		2.8,
		3.7,
		4.6,
		5.5,
		6.4,
		7.3,
		8.2,
		9.1,
	};
	std::string const	arr1[] = {
		std::string("There's a calm surrender"),
		std::string("to the rush of day"),
		std::string("when the heat of a rolling wind"),
		std::string("can be turned away"),
		std::string("An enchanted moment"),
		std::string("And it sees the me through"),
		std::string("It's enough for this restless warrior"),
		std::string("Just to be with you"),
		std::string("And can you feel the love tonight"),
		std::string("It is where we are"),
	};
	t_uint				idx;

	title(__func__);
	try
	{
		// Trivially copyable
		{
			ft::vector<double>	ft_vec0(&arr0[0], &arr0[10]);
			std::vector<double>	std_vec0(&arr0[0], &arr0[10]);
			ft::vector<double>	ft_vec1;
			std::vector<double>	std_vec1;

			for (idx = 0U ; idx < 20U ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin() + idx / 2, arr0[idx / 2]);
				std_vec1.insert(std_vec1.begin() + idx / 2, arr0[idx / 2]);
			}

			ft_vec0 = ft_vec1;
			std_vec0 = std_vec1;

			if (ft_vec0.size() != std_vec0.size() || ft_vec0.capacity() != std_vec0.capacity() ||
				!std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()))
				return EXIT_FAILURE;
		}
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec0(&arr1[0], &arr1[10]);
			std::vector<std::string>	std_vec0(&arr1[0], &arr1[10]);
			ft::vector<std::string>		ft_vec1;
			std::vector<std::string>	std_vec1;

			for (idx = 0U ; idx < 20U ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin() + idx / 2, arr1[idx / 2]);
				std_vec1.insert(std_vec1.begin() + idx / 2, arr1[idx / 2]);
			}

			ft_vec0 = ft_vec1;
			std_vec0 = std_vec1;

			if (ft_vec0.size() != std_vec0.size() || ft_vec0.capacity() != std_vec0.capacity() ||
				!std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()))
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

inline static int	__test_operator_access(void)
{
	t_lint const	arr[] = {
		1212121212121212L,
		-2323232323232323L,
		3434343434343434L,
		-4545454545454545L,
		5656456456456456L,
		-6767676767676767L,
		7878787878787878L,
		-8989898989898989L,
		9090909090909090L,
		-0101010101010101L,
	};
	t_uint			idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::vector<t_lint>	ft_vector(&arr[0], &arr[10]);
			std::vector<t_lint>	std_vector(&arr[0], &arr[10]);

			for (idx = 0U ; idx < 10U ; ++idx)
				if (++(ft_vector[idx]) != ++(std_vector[idx]))
					return EXIT_FAILURE;
		}
		// Constant access
		{
			ft::vector<t_lint> const	ft_vector(&arr[0], &arr[10]);
			std::vector<t_lint> const	std_vector(&arr[0], &arr[10]);

			for (idx = 0U ; idx < 10U ; ++idx)
				if (ft_vector[idx] != std_vector[idx])
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
	std::string const	arr[] = {
		std::string("Where is the moment we needed the most?"),
		std::string("You kick up the leaves, and the magic is lost"),
		std::string("They tell me your blue sky's faded to grey"),
		std::string("They tell me your passion's gone away"),
		std::string("And I don't need to carrying on"),
		std::string("You stand in the line just to hit a new low"),
		std::string("You're faking a smile with the coffee to go"),
		std::string("You tell me your life's been way off line"),
		std::string("You're falling to pieces every time"),
		std::string("And I don't need to carrying on"),
	};
	t_uint				idx;

	title(__func__);
	try
	{
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			if (ft::operator==(ft_vec0, ft_vec1) != std::operator==(std_vec0, std_vec1))
				return EXIT_FAILURE;
			ft_vec0.push_back(arr[idx]);
			std_vec0.push_back(arr[idx]);
			if (ft::operator==(ft_vec0, ft_vec1) != std::operator==(std_vec0, std_vec1))
				return EXIT_FAILURE;
			ft_vec1.push_back(arr[idx]);
			std_vec1.push_back(arr[idx]);
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
	std::string const	arr[] = {
		std::string("Where is the moment we needed the most?"),
		std::string("You kick up the leaves, and the magic is lost"),
		std::string("They tell me your blue sky's faded to grey"),
		std::string("They tell me your passion's gone away"),
		std::string("And I don't need to carrying on"),
		std::string("You stand in the line just to hit a new low"),
		std::string("You're faking a smile with the coffee to go"),
		std::string("You tell me your life's been way off line"),
		std::string("You're falling to pieces every time"),
		std::string("And I don't need to carrying on"),
	};
	t_uint				idx;

	title(__func__);
	try
	{
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			if (ft::operator!=(ft_vec0, ft_vec1) != std::operator!=(std_vec0, std_vec1))
				return EXIT_FAILURE;
			ft_vec0.push_back(arr[idx]);
			std_vec0.push_back(arr[idx]);
			if (ft::operator!=(ft_vec0, ft_vec1) != std::operator!=(std_vec0, std_vec1))
				return EXIT_FAILURE;
			ft_vec1.push_back(arr[idx]);
			std_vec1.push_back(arr[idx]);
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
	std::string const	arr[] = {
		std::string("Where is the moment we needed the most?"),
		std::string("You kick up the leaves, and the magic is lost"),
		std::string("They tell me your blue sky's faded to grey"),
		std::string("They tell me your passion's gone away"),
		std::string("And I don't need to carrying on"),
		std::string("You stand in the line just to hit a new low"),
		std::string("You're faking a smile with the coffee to go"),
		std::string("You tell me your life's been way off line"),
		std::string("You're falling to pieces every time"),
		std::string("And I don't need to carrying on"),
	};
	t_uint				idx;

	title(__func__);
	try
	{
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			if (ft::operator<(ft_vec0, ft_vec1) != std::operator<(std_vec0, std_vec1))
				return EXIT_FAILURE;
			ft_vec0.push_back(arr[idx]);
			std_vec0.push_back(arr[idx]);
			if (ft::operator<(ft_vec0, ft_vec1) != std::operator<(std_vec0, std_vec1))
				return EXIT_FAILURE;
			ft_vec1.push_back(arr[idx]);
			std_vec1.push_back(arr[idx]);
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
	std::string const	arr[] = {
		std::string("Where is the moment we needed the most?"),
		std::string("You kick up the leaves, and the magic is lost"),
		std::string("They tell me your blue sky's faded to grey"),
		std::string("They tell me your passion's gone away"),
		std::string("And I don't need to carrying on"),
		std::string("You stand in the line just to hit a new low"),
		std::string("You're faking a smile with the coffee to go"),
		std::string("You tell me your life's been way off line"),
		std::string("You're falling to pieces every time"),
		std::string("And I don't need to carrying on"),
	};
	t_uint				idx;

	title(__func__);
	try
	{
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			if (ft::operator>(ft_vec0, ft_vec1) != std::operator>(std_vec0, std_vec1))
				return EXIT_FAILURE;
			ft_vec0.push_back(arr[idx]);
			std_vec0.push_back(arr[idx]);
			if (ft::operator>(ft_vec0, ft_vec1) != std::operator>(std_vec0, std_vec1))
				return EXIT_FAILURE;
			ft_vec1.push_back(arr[idx]);
			std_vec1.push_back(arr[idx]);
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
	std::string const	arr[] = {
		std::string("Where is the moment we needed the most?"),
		std::string("You kick up the leaves, and the magic is lost"),
		std::string("They tell me your blue sky's faded to grey"),
		std::string("They tell me your passion's gone away"),
		std::string("And I don't need to carrying on"),
		std::string("You stand in the line just to hit a new low"),
		std::string("You're faking a smile with the coffee to go"),
		std::string("You tell me your life's been way off line"),
		std::string("You're falling to pieces every time"),
		std::string("And I don't need to carrying on"),
	};
	t_uint				idx;

	title(__func__);
	try
	{
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			if (ft::operator<=(ft_vec0, ft_vec1) != std::operator<=(std_vec0, std_vec1))
				return EXIT_FAILURE;
			ft_vec0.push_back(arr[idx]);
			std_vec0.push_back(arr[idx]);
			if (ft::operator<=(ft_vec0, ft_vec1) != std::operator<=(std_vec0, std_vec1))
				return EXIT_FAILURE;
			ft_vec1.push_back(arr[idx]);
			std_vec1.push_back(arr[idx]);
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
	std::string const	arr[] = {
		std::string("Where is the moment we needed the most?"),
		std::string("You kick up the leaves, and the magic is lost"),
		std::string("They tell me your blue sky's faded to grey"),
		std::string("They tell me your passion's gone away"),
		std::string("And I don't need to carrying on"),
		std::string("You stand in the line just to hit a new low"),
		std::string("You're faking a smile with the coffee to go"),
		std::string("You tell me your life's been way off line"),
		std::string("You're falling to pieces every time"),
		std::string("And I don't need to carrying on"),
	};
	t_uint				idx;

	title(__func__);
	try
	{
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			if (ft::operator>=(ft_vec0, ft_vec1) != std::operator>=(std_vec0, std_vec1))
				return EXIT_FAILURE;
			ft_vec0.push_back(arr[idx]);
			std_vec0.push_back(arr[idx]);
			if (ft::operator>=(ft_vec0, ft_vec1) != std::operator>=(std_vec0, std_vec1))
				return EXIT_FAILURE;
			ft_vec1.push_back(arr[idx]);
			std_vec1.push_back(arr[idx]);
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_type_iterator(void)
{
	int const	arr[] = {
		3,
		6,
		12,
		24,
		48,
		96,
		192,
		384,
		768,
		1536,
	};

	title(__func__);
	try
	{
		ft::vector<int>							ft_vec(&arr[0], &arr[10]);
		std::vector<int>						std_vec(&arr[0], &arr[10]);
		ft::vector<int>::iterator const			ft_end(ft_vec.end());
		std::vector<int>::iterator const		std_end(std_vec.end());
		ft::vector<int>::const_iterator const	ft_cend(ft_vec.end());
		std::vector<int>::const_iterator const	std_cend(std_vec.end());
		ft::vector<int>::iterator				ft_it;
		std::vector<int>::iterator				std_it;

		for (ft_it = ft_vec.begin(), std_it = std_vec.begin() ;
			ft_it != ft_vec.end() && std_it != std_vec.end() ;
			++ft_it, ++std_it)
		{
			ft_it = ++ft_it;
			ft_it = ft_it++;
			ft_it = --ft_it;
			ft_it = ft_it--;
			ft_it = (ft_it += 2);
			ft_it = (ft_it -= 2);
			ft_it = (ft_it + 3);
			ft_it = (ft_it - 3);
			ft_it = (4 + ft_it);
			ft_it -= 4;
			std_it = ++std_it;
			std_it = std_it++;
			std_it = --std_it;
			std_it = std_it--;
			std_it = (std_it += 2);
			std_it = (std_it -= 2);
			std_it = (std_it + 3);
			std_it = (std_it - 3);
			std_it = (4 + std_it);
			std_it -= 4;

			if (!!ft_it.base() != !!std_it.base() ||
				(ft_it - ft_end) != (std_it - std_end) || (ft_it - ft_cend) != (std_it - std_cend) ||
				(ft_it < ft_end) != (std_it < std_end) || (ft_it < ft_cend) != (std_it < std_cend) ||
				(ft_it > ft_end) != (std_it > std_end) || (ft_it > ft_cend) != (std_it > std_cend) ||
				(ft_it <= ft_end) != (std_it <= std_end) || (ft_it <= ft_cend) != (std_it <= std_cend) ||
				(ft_it >= ft_end) != (std_it >= std_end) || (ft_it >= ft_cend) != (std_it >= std_cend) ||
				(*ft_it)++ != (*std_it)++ || ++(ft_it[0]) != ++(std_it[0]) ||
				(*ft_it)-- != (*std_it)-- || --(ft_it[0]) != --(std_it[0]))
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

inline static int	__test_type_const_iterator(void)
{
	int const	arr[] = {
		3,
		6,
		12,
		24,
		48,
		96,
		192,
		384,
		768,
		1536,
	};

	title(__func__);
	try
	{
		ft::vector<int>							ft_vec(&arr[0], &arr[10]);
		std::vector<int>						std_vec(&arr[0], &arr[10]);
		ft::vector<int>::iterator const			ft_end(ft_vec.end());
		std::vector<int>::iterator const		std_end(std_vec.end());
		ft::vector<int>::const_iterator const	ft_cend(ft_vec.end());
		std::vector<int>::const_iterator const	std_cend(std_vec.end());
		ft::vector<int>::const_iterator			ft_cit;
		std::vector<int>::const_iterator		std_cit;

		for (ft_cit = ft_vec.begin(), std_cit = std_vec.begin() ;
			ft_cit != ft_vec.end() && std_cit != std_vec.end() ;
			++ft_cit, ++std_cit)
		{
			ft_cit = ++ft_cit;
			ft_cit = ft_cit++;
			ft_cit = --ft_cit;
			ft_cit = ft_cit--;
			ft_cit = (ft_cit += 2);
			ft_cit = (ft_cit -= 2);
			ft_cit = (ft_cit + 3);
			ft_cit = (ft_cit - 3);
			ft_cit = (4 + ft_cit);
			ft_cit -= 4;
			std_cit = ++std_cit;
			std_cit = std_cit++;
			std_cit = --std_cit;
			std_cit = std_cit--;
			std_cit = (std_cit += 2);
			std_cit = (std_cit -= 2);
			std_cit = (std_cit + 3);
			std_cit = (std_cit - 3);
			std_cit = (4 + std_cit);
			std_cit -= 4;

			if (!!ft_cit.base() != !!std_cit.base() ||
				(ft_cit - ft_end) != (std_cit - std_end) || (ft_cit - ft_cend) != (std_cit - std_cend) ||
				(ft_cit < ft_end) != (std_cit < std_end) || (ft_cit < ft_cend) != (std_cit < std_cend) ||
				(ft_cit > ft_end) != (std_cit > std_end) || (ft_cit > ft_cend) != (std_cit > std_cend) ||
				(ft_cit <= ft_end) != (std_cit <= std_end) || (ft_cit <= ft_cend) != (std_cit <= std_cend) ||
				(ft_cit >= ft_end) != (std_cit >= std_end) || (ft_cit >= ft_cend) != (std_cit >= std_cend) ||
				*ft_cit != *std_cit || ft_cit[0] != std_cit[0])
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

inline static int	__test_type_reverse_iterator(void)
{
	int const	arr[] = {
		3,
		6,
		12,
		24,
		48,
		96,
		192,
		384,
		768,
		1536,
	};

	title(__func__);
	try
	{
		ft::vector<int>									ft_vec(&arr[0], &arr[10]);
		std::vector<int>								std_vec(&arr[0], &arr[10]);
		ft::vector<int>::reverse_iterator const			ft_rend(ft_vec.rend());
		std::vector<int>::reverse_iterator const		std_rend(std_vec.rend());
		ft::vector<int>::const_reverse_iterator const	ft_crend(ft_vec.rend());
		std::vector<int>::const_reverse_iterator const	std_crend(std_vec.rend());
		ft::vector<int>::reverse_iterator				ft_rit;
		std::vector<int>::reverse_iterator				std_rit;

		for (ft_rit = ft_vec.rbegin(), std_rit = std_vec.rbegin() ;
			ft_rit != ft_vec.rend() && std_rit != std_vec.rend() ;
			++ft_rit, ++std_rit)
		{
			ft_rit = ++ft_rit;
			ft_rit = ft_rit++;
			ft_rit = --ft_rit;
			ft_rit = ft_rit--;
			ft_rit = (ft_rit += 2);
			ft_rit = (ft_rit -= 2);
			ft_rit = (ft_rit + 3);
			ft_rit = (ft_rit - 3);
			ft_rit = (4 + ft_rit);
			ft_rit -= 4;
			std_rit = ++std_rit;
			std_rit = std_rit++;
			std_rit = --std_rit;
			std_rit = std_rit--;
			std_rit = (std_rit += 2);
			std_rit = (std_rit -= 2);
			std_rit = (std_rit + 3);
			std_rit = (std_rit - 3);
			std_rit = (4 + std_rit);
			std_rit -= 4;

			if (!!ft_rit.base().base() != !!std_rit.base().base() ||
				(ft_rit - ft_rend) != (std_rit - std_rend) || (ft_rit - ft_crend) != (std_rit - std_crend) ||
				(ft_rit < ft_rend) != (std_rit < std_rend) || (ft_rit < ft_crend) != (std_rit < std_crend) ||
				(ft_rit > ft_rend) != (std_rit > std_rend) || (ft_rit > ft_crend) != (std_rit > std_crend) ||
				(ft_rit <= ft_rend) != (std_rit <= std_rend) || (ft_rit <= ft_crend) != (std_rit <= std_crend) ||
				(ft_rit >= ft_rend) != (std_rit >= std_rend) || (ft_rit >= ft_crend) != (std_rit >= std_crend) ||
				(*ft_rit)++ != (*std_rit)++ || ++(ft_rit[0]) != ++(std_rit[0]) ||
				(*ft_rit)-- != (*std_rit)-- || --(ft_rit[0]) != --(std_rit[0]))
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

inline static int	__test_type_const_reverse_iterator(void)
{
	int const	arr[] = {
		3,
		6,
		12,
		24,
		48,
		96,
		192,
		384,
		768,
		1536,
	};

	title(__func__);
	try
	{
		ft::vector<int> const						ft_vec(&arr[0], &arr[10]);
		std::vector<int> const						std_vec(&arr[0], &arr[10]);
		ft::vector<int>::const_reverse_iterator		ft_crit;
		std::vector<int>::const_reverse_iterator	std_crit;

		for (ft_crit = ft_vec.rbegin(), std_crit = std_vec.rbegin() ;
			ft_crit != ft_vec.rend() && std_crit != std_vec.rend() ;
			++ft_crit, ++std_crit)
		{
			ft_crit = ++ft_crit;
			ft_crit = ft_crit++;
			ft_crit = --ft_crit;
			ft_crit = ft_crit--;
			ft_crit = (ft_crit += 2);
			ft_crit = (ft_crit -= 2);
			ft_crit = (ft_crit + 3);
			ft_crit = (ft_crit - 3);
			ft_crit = (4 + ft_crit);
			ft_crit -= 4;
			std_crit = ++std_crit;
			std_crit = std_crit++;
			std_crit = --std_crit;
			std_crit = std_crit--;
			std_crit = (std_crit += 2);
			std_crit = (std_crit -= 2);
			std_crit = (std_crit + 3);
			std_crit = (std_crit - 3);
			std_crit = (4 + std_crit);
			std_crit -= 4;

			if (!!ft_crit.base().base() != !!std_crit.base().base() ||
				(ft_crit - ft_vec.rend()) != (std_crit - std_vec.rend()) ||
				(ft_crit < ft_vec.rend()) != (std_crit < std_vec.rend()) ||
				(ft_crit > ft_vec.rend()) != (std_crit > std_vec.rend()) ||
				(ft_crit <= ft_vec.rend()) != (std_crit <= std_vec.rend()) ||
				(ft_crit >= ft_vec.rend()) != (std_crit >= std_vec.rend()) ||
				*ft_crit != *std_crit || ft_crit[0] != std_crit[0])
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
		__test_constructor,
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
		__test_function_erase,
		__test_function_push_back,
		__test_function_pop_back,
		__test_function_clear,
		__test_function_assign,
		__test_function_swap,
		__test_function_reserve,
		__test_function_resize,
		__test_operator_assign,
		__test_operator_access,
		__test_operator_equal,
		__test_operator_difference,
		__test_operator_lower,
		__test_operator_greater,
		__test_operator_lower_equal,
		__test_operator_greater_equal,
		__test_type_iterator,
		__test_type_const_iterator,
		__test_type_reverse_iterator,
		__test_type_const_reverse_iterator,
		NULL
	};
	t_uint			koCount;
	t_uint			idx;

	std::cerr << "\033[38;2;0;173;255m";
	std::cout << "####################################################" << '\n';
	std::cout << "##                     VECTOR                     ##" << '\n';
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
