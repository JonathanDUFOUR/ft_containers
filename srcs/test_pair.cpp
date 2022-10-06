/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pair.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:56:47 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/06 10:04:59 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <iostream>
#include "arrays.hpp"
#include "tester.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include "e_ret.hpp"

inline static int	__test_constructor(void)
{
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Default constructor
		{
			ft::pair<int, t_uint> const		ft_pair;
			std::pair<int, t_uint> const	std_pair;

			if (sizeof(ft_pair) != sizeof(std_pair) || memcmp(&ft_pair, &std_pair, sizeof(ft_pair)))
				ret = ISO_OK;
			if (ft_pair.first != std_pair.first || ft_pair.second != std_pair.second)
				return KO;
		}
		// Parameters constructor
		{
			ft::pair<t_uint, int> const		ft_pair(42U, -42);
			std::pair<t_uint, int> const	std_pair(42U, -42);

			if (sizeof(ft_pair) != sizeof(std_pair) || memcmp(&ft_pair, &std_pair, sizeof(ft_pair)))
				ret = ISO_OK;
			if (ft_pair.first != std_pair.first || ft_pair.second != std_pair.second)
				return KO;
		}
		// Copy constructor
		{
			// Default pair
			{
				ft::pair<char const, char const> const	ft_pair0;
				ft::pair<char const, char const> const	ft_pair1(ft_pair0);
				std::pair<char const, char const> const	std_pair0;
				std::pair<char const, char const> const	std_pair1(std_pair0);

				if (sizeof(ft_pair1) != sizeof(std_pair1) || memcmp(&ft_pair1, &std_pair1, sizeof(ft_pair1)))
					ret = ISO_OK;
				if (ft_pair1.first != std_pair1.first || ft_pair1.second != std_pair1.second)
					return KO;
			}
			// Filled pair
			{
				ft::pair<char const, char const> const	ft_pair0('!', '?');
				ft::pair<char, char> const				ft_pair1(ft_pair0);
				std::pair<char const, char const> const	std_pair0('!', '?');
				std::pair<char, char> const				std_pair1(std_pair0);

				if (sizeof(ft_pair1) != sizeof(std_pair1) || memcmp(&ft_pair1, &std_pair1, sizeof(ft_pair1)))
					ret = ISO_OK;
				if (ft_pair1.first != std_pair1.first || ft_pair1.second != std_pair1.second)
					return KO;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_type_first_type(void)
{
	title(__func__);
	try
	{
		typedef ft::pair<long double, char>	pair_type;

		if (!is_same<pair_type::first_type, long double>::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_second_type(void)
{
	title(__func__);
	try
	{
		typedef ft::pair<long double, char>	pair_type;

		if (!is_same<pair_type::second_type, char>::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_make_pair(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::pair<t_luint, std::string>	ft_pair;
		std::pair<t_luint, std::string>	std_pair;

		for (idx = 0U ; idx < g_luint_size && idx < g_string_size ; ++idx)
		{
			ft_pair = ft::make_pair(g_luint[idx], g_string[idx]);
			std_pair = std::make_pair(g_luint[idx], g_string[idx]);

			if (ft_pair.first != std_pair.first || ft_pair.second != std_pair.second)
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_operator_assign(void)
{
	title(__func__);
	try
	{
		// Assigning mutable -> mutable
		{
			ft::pair<t_hhint, std::string>			ft_pair0(-1, "Hello World");
			ft::pair<t_hhint, std::string> const	ft_pair1(55, "How are you today ?");
			std::pair<t_hhint, std::string>			std_pair0(-1, "Hello World");
			std::pair<t_hhint, std::string> const	std_pair1(55, "How are you today ?");

			ft_pair0 = ft_pair1;
			std_pair0 = std_pair1;

			if (ft_pair0.first != std_pair0.first || ft_pair0.second != std_pair0.second)
				return KO;
		}
		// Assigning constant -> mutable
		{
			ft::pair<t_hhint, std::string>						ft_pair0(-1, "Hello World");
			ft::pair<t_hhint const, std::string const> const	ft_pair1(55, "How are you today ?");
			std::pair<t_hhint, std::string>						std_pair0(-1, "Hello World");
			std::pair<t_hhint const, std::string const> const	std_pair1(55, "How are you today ?");

			ft_pair0 = ft_pair1;
			std_pair0 = std_pair1;

			if (ft_pair0.first != std_pair0.first || ft_pair0.second != std_pair0.second)
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_operator_equivalent(void)
{
	title(__func__);
	try
	{
		// first == first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator==(ft_pair0, ft_pair1) != std::operator==(std_pair0, std_pair1))
				return KO;
		}
		// first == first | second != second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 209U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 209U);

			if (ft::operator==(ft_pair0, ft_pair1) != std::operator==(std_pair0, std_pair1))
				return KO;
		}
		// first != first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.22f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.22f, 210U);

			if (ft::operator==(ft_pair0, ft_pair1) != std::operator==(std_pair0, std_pair1))
				return KO;
		}
		// first != first | second != second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.22f, 209U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.22f, 209U);

			if (ft::operator==(ft_pair0, ft_pair1) != std::operator==(std_pair0, std_pair1))
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_operator_different(void)
{
	title(__func__);
	try
	{
		// first == first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator!=(ft_pair0, ft_pair1) != std::operator!=(std_pair0, std_pair1))
				return KO;
		}
		// first == first | second != second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 209U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 209U);

			if (ft::operator!=(ft_pair0, ft_pair1) != std::operator!=(std_pair0, std_pair1))
				return KO;
		}
		// first != first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.22f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.22f, 210U);

			if (ft::operator!=(ft_pair0, ft_pair1) != std::operator!=(std_pair0, std_pair1))
				return KO;
		}
		// first != first | second != second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.22f, 209U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.22f, 209U);

			if (ft::operator!=(ft_pair0, ft_pair1) != std::operator!=(std_pair0, std_pair1))
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_operator_lower(void)
{
	title(__func__);
	try
	{
		// first < first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);

			if (ft::operator<(ft_pair0, ft_pair1) != std::operator<(std_pair0, std_pair1))
				return KO;
		}
		// first < first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);

			if (ft::operator<(ft_pair0, ft_pair1) != std::operator<(std_pair0, std_pair1))
				return KO;
		}
		// first < first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);

			if (ft::operator<(ft_pair0, ft_pair1) != std::operator<(std_pair0, std_pair1))
				return KO;
		}
		// first > first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator<(ft_pair0, ft_pair1) != std::operator<(std_pair0, std_pair1))
				return KO;
		}
		// first > first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 201U);

			if (ft::operator<(ft_pair0, ft_pair1) != std::operator<(std_pair0, std_pair1))
				return KO;
		}
		// first > first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator<(ft_pair0, ft_pair1) != std::operator<(std_pair0, std_pair1))
				return KO;
		}
		// first == first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator<(ft_pair0, ft_pair1) != std::operator<(std_pair0, std_pair1))
				return KO;
		}
		// first == first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 201U);

			if (ft::operator<(ft_pair0, ft_pair1) != std::operator<(std_pair0, std_pair1))
				return KO;
		}
		// first == first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator<(ft_pair0, ft_pair1) != std::operator<(std_pair0, std_pair1))
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_operator_greater(void)
{
	title(__func__);
	try
	{
		// first < first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);

			if (ft::operator>(ft_pair0, ft_pair1) != std::operator>(std_pair0, std_pair1))
				return KO;
		}
		// first < first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);

			if (ft::operator>(ft_pair0, ft_pair1) != std::operator>(std_pair0, std_pair1))
				return KO;
		}
		// first < first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);

			if (ft::operator>(ft_pair0, ft_pair1) != std::operator>(std_pair0, std_pair1))
				return KO;
		}
		// first > first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator>(ft_pair0, ft_pair1) != std::operator>(std_pair0, std_pair1))
				return KO;
		}
		// first > first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 201U);

			if (ft::operator>(ft_pair0, ft_pair1) != std::operator>(std_pair0, std_pair1))
				return KO;
		}
		// first > first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator>(ft_pair0, ft_pair1) != std::operator>(std_pair0, std_pair1))
				return KO;
		}
		// first == first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator>(ft_pair0, ft_pair1) != std::operator>(std_pair0, std_pair1))
				return KO;
		}
		// first == first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 201U);

			if (ft::operator>(ft_pair0, ft_pair1) != std::operator>(std_pair0, std_pair1))
				return KO;
		}
		// first == first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator>(ft_pair0, ft_pair1) != std::operator>(std_pair0, std_pair1))
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_operator_lower_or_equivalent(void)
{
	title(__func__);
	try
	{
		// first < first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);

			if (ft::operator<=(ft_pair0, ft_pair1) != std::operator<=(std_pair0, std_pair1))
				return KO;
		}
		// first < first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);

			if (ft::operator<=(ft_pair0, ft_pair1) != std::operator<=(std_pair0, std_pair1))
				return KO;
		}
		// first < first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);

			if (ft::operator<=(ft_pair0, ft_pair1) != std::operator<=(std_pair0, std_pair1))
				return KO;
		}
		// first > first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator<=(ft_pair0, ft_pair1) != std::operator<=(std_pair0, std_pair1))
				return KO;
		}
		// first > first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 201U);

			if (ft::operator<=(ft_pair0, ft_pair1) != std::operator<=(std_pair0, std_pair1))
				return KO;
		}
		// first > first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator<=(ft_pair0, ft_pair1) != std::operator<=(std_pair0, std_pair1))
				return KO;
		}
		// first == first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator<=(ft_pair0, ft_pair1) != std::operator<=(std_pair0, std_pair1))
				return KO;
		}
		// first == first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 201U);

			if (ft::operator<=(ft_pair0, ft_pair1) != std::operator<=(std_pair0, std_pair1))
				return KO;
		}
		// first == first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator<=(ft_pair0, ft_pair1) != std::operator<=(std_pair0, std_pair1))
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_operator_greater_or_equivalent(void)
{
	title(__func__);
	try
	{
		// first < first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);

			if (ft::operator>=(ft_pair0, ft_pair1) != std::operator>=(std_pair0, std_pair1))
				return KO;
		}
		// first < first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);

			if (ft::operator>=(ft_pair0, ft_pair1) != std::operator>=(std_pair0, std_pair1))
				return KO;
		}
		// first < first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);

			if (ft::operator>=(ft_pair0, ft_pair1) != std::operator>=(std_pair0, std_pair1))
				return KO;
		}
		// first > first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator>=(ft_pair0, ft_pair1) != std::operator>=(std_pair0, std_pair1))
				return KO;
		}
		// first > first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 201U);

			if (ft::operator>=(ft_pair0, ft_pair1) != std::operator>=(std_pair0, std_pair1))
				return KO;
		}
		// first > first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator>=(ft_pair0, ft_pair1) != std::operator>=(std_pair0, std_pair1))
				return KO;
		}
		// first == first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator>=(ft_pair0, ft_pair1) != std::operator>=(std_pair0, std_pair1))
				return KO;
		}
		// first == first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 201U);

			if (ft::operator>=(ft_pair0, ft_pair1) != std::operator>=(std_pair0, std_pair1))
				return KO;
		}
		// first == first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);

			if (ft::operator>=(ft_pair0, ft_pair1) != std::operator>=(std_pair0, std_pair1))
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

int	test_pair(void)
{
	t_test const	tests[] = {
		__test_constructor,
		__test_type_first_type,
		__test_type_second_type,
		__test_function_make_pair,
		__test_operator_assign,
		__test_operator_equivalent,
		__test_operator_different,
		__test_operator_lower,
		__test_operator_greater,
		__test_operator_lower_or_equivalent,
		__test_operator_greater_or_equivalent,
		NULL
	};
	t_uint			koCount;
	t_uint			idx;

	std::cerr << "\033[38;2;0;173;255m";
	std::cout << "####################################################" << '\n';
	std::cout << "##                      PAIR                      ##" << '\n';
	std::cout << "####################################################" << '\n';
	std::cerr << "\033[0m";
	for (koCount = 0U, idx = 0U ; tests[idx] ; ++idx)
		switch (tests[idx]())
		{
			case IMP_OK:
				std::cerr << "\033[38;2;0;255;0m";
				std::cout << "[OK]" << '\n';
				std::cerr << "\033[0m";
				break;

			case ISO_OK:
				std::cerr << "\033[38;2;255;255;0m";
				std::cout << "[OK]" << '\n';
				std::cerr << "\033[0m";
				break;

			case KO:
				std::cerr << "\033[38;2;255;0;0m";
				std::cout << "[KO]" << '\n';
				std::cerr << "\033[0m";
				++koCount;
				break;
		}
	std::cout << '\n';
	return koCount;
}
