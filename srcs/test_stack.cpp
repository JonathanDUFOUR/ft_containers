/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:28:16 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/04 17:43:28 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>
#include "arrays.hpp"
#include "stack.hpp"
#include "tester.hpp"
#include "e_ret.hpp"

inline static int	__test_constructor(void)
{
	int					ret;
	std::vector<t_uint>	vec;
	t_uint				idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Default constructor
		{
			ft::stack<int, std::vector<int> >	ft_sta;
			std::stack<int, std::vector<int> >	std_sta;

			if (sizeof(ft_sta) != sizeof(std_sta)
				|| memcmp(&ft_sta, &std_sta, sizeof(ft_sta)))
				ret = ISO_OK;
		}
		// Wrap constructor
		{
			// Empty underlying container
			{
				ft::stack<t_uint, std::vector<t_uint> >		ft_sta(vec);
				std::stack<t_uint, std::vector<t_uint> >	std_sta(vec);
				if (sizeof(ft_sta) != sizeof(std_sta)
					|| memcmp(&ft_sta, &std_sta, sizeof(ft_sta)))
					ret = ISO_OK;
			}
			// Non-empty underlying container
			{
				for (idx = 0U ; idx < g_uint_size ; ++idx)
				{
					vec.push_back(g_uint[idx]);

					ft::stack<t_uint, std::vector<t_uint> >		ft_sta(vec);
					std::stack<t_uint, std::vector<t_uint> >	std_sta(vec);

					if (sizeof(ft_sta) != sizeof(std_sta))
						ret = ISO_OK;
				}
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

inline static int	__test_type_value_type(void)
{
	title(__func__);
	try
	{
		typedef ft::stack<t_lint, std::vector<t_lint> >		ft_sta_type;
		typedef std::stack<t_lint, std::vector<t_lint> >	std_sta_type;

		if (!ft::is_same<ft_sta_type::value_type, std_sta_type::value_type>::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_size_type(void)
{
	title(__func__);
	try
	{
		typedef ft::stack<t_lint, std::vector<t_lint> >		ft_sta_type;
		typedef std::stack<t_lint, std::vector<t_lint> >	std_sta_type;

		if (!ft::is_same<ft_sta_type::size_type, std_sta_type::size_type>::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_container_type(void)
{
	title(__func__);
	try
	{
		typedef ft::stack<t_lint, std::vector<t_lint> >		ft_sta_type;
		typedef std::stack<t_lint, std::vector<t_lint> >	std_sta_type;

		if (!ft::is_same<ft_sta_type::container_type, std_sta_type::container_type>::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_top(void)
{
	std::vector<char>	vec;
	t_uint				idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_char_size ; ++idx)
		{
			vec.push_back(g_char[idx]);

			ft::stack<char, std::vector<char> >		ft_sta(vec);
			std::stack<char, std::vector<char> >	std_sta(vec);

			if (ft_sta.top() != std_sta.top())
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

inline static int	__test_function_push(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<std::string, std::vector<std::string> >	ft_sta;
		std::stack<std::string, std::vector<std::string> >	std_sta;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			ft_sta.push(g_string[idx]);
			std_sta.push(g_string[idx]);

			if (ft_sta.top() != std_sta.top())
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

inline static int	__test_function_pop(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<float, std::vector<float> >	ft_sta;
		std::stack<float, std::vector<float> >	std_sta;

		for (idx = 0U ; idx < g_float_size ; ++idx)
		{
			ft_sta.push(g_float[idx]);
			std_sta.push(g_float[idx]);
		}
		for (idx = 0U ; idx < g_float_size ; ++idx)
		{
			if (ft_sta.top() != std_sta.top())
				return KO;
			ft_sta.pop();
			std_sta.pop();
		}
		for (idx = 0U ; idx < g_float_size ; ++idx)
		{
			ft_sta.pop();
			std_sta.pop();
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_empty(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<t_lint, std::vector<t_lint> >		ft_sta;
		std::stack<t_lint, std::vector<t_lint> >	std_sta;

		for (idx = 0U ; idx < g_lint_size ; ++idx)
		{
			if (ft_sta.empty() != std_sta.empty())
				return KO;
			ft_sta.push(g_lint[idx]);
			std_sta.push(g_lint[idx]);
		}
		if (ft_sta.empty() != std_sta.empty())
			return KO;
		for (idx = 0U ; idx < g_lint_size ; ++idx)
		{
			ft_sta.pop();
			std_sta.pop();
			if (ft_sta.empty() != std_sta.empty())
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

inline static int	__test_function_size(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<t_uint, std::vector<t_uint> >		ft_sta;
		std::stack<t_uint, std::vector<t_uint> >	std_sta;

		for (idx = 0U ; idx < g_uint_size ; ++idx)
		{
			if (ft_sta.size() != std_sta.size())
				return KO;
			ft_sta.push(g_uint[idx]);
			std_sta.push(g_uint[idx]);
		}
		if (ft_sta.size() != std_sta.size())
			return KO;
		for (idx = 0U ; idx < g_uint_size ; ++idx)
		{
			ft_sta.pop();
			std_sta.pop();
			if (ft_sta.size() != std_sta.size())
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
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<int, std::vector<int> >	ft_sta0;
		ft::stack<int, std::vector<int> >	ft_sta1;
		std::stack<int, std::vector<int> >	std_sta0;
		std::stack<int, std::vector<int> >	std_sta1;

		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			if (ft::operator==(ft_sta0, ft_sta1) != std::operator==(std_sta0, std_sta1))
				return KO;
			ft_sta0.push(g_int[idx]);
			std_sta0.push(g_int[idx]);
			if (ft::operator==(ft_sta0, ft_sta1) != std::operator==(std_sta0, std_sta1))
				return KO;
			ft_sta1.push(g_int[idx]);
			std_sta1.push(g_int[idx]);
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
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<int, std::vector<int> >	ft_sta0;
		ft::stack<int, std::vector<int> >	ft_sta1;
		std::stack<int, std::vector<int> >	std_sta0;
		std::stack<int, std::vector<int> >	std_sta1;

		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			if (ft::operator!=(ft_sta0, ft_sta1) != std::operator!=(std_sta0, std_sta1))
				return KO;
			ft_sta0.push(g_int[idx]);
			std_sta0.push(g_int[idx]);
			if (ft::operator!=(ft_sta0, ft_sta1) != std::operator!=(std_sta0, std_sta1))
				return KO;
			ft_sta1.push(g_int[idx]);
			std_sta1.push(g_int[idx]);
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
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<int, std::vector<int> >	ft_sta0;
		ft::stack<int, std::vector<int> >	ft_sta1;
		std::stack<int, std::vector<int> >	std_sta0;
		std::stack<int, std::vector<int> >	std_sta1;

		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			if (ft::operator<(ft_sta0, ft_sta1) != std::operator<(std_sta0, std_sta1))
				return KO;
			ft_sta0.push(g_int[idx]);
			std_sta0.push(g_int[idx]);
			if (ft::operator<(ft_sta0, ft_sta1) != std::operator<(std_sta0, std_sta1))
				return KO;
			ft_sta1.push(g_int[idx]);
			std_sta1.push(g_int[idx]);
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
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<int, std::vector<int> >	ft_sta0;
		ft::stack<int, std::vector<int> >	ft_sta1;
		std::stack<int, std::vector<int> >	std_sta0;
		std::stack<int, std::vector<int> >	std_sta1;

		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			if (ft::operator>(ft_sta0, ft_sta1) != std::operator>(std_sta0, std_sta1))
				return KO;
			ft_sta0.push(g_int[idx]);
			std_sta0.push(g_int[idx]);
			if (ft::operator>(ft_sta0, ft_sta1) != std::operator>(std_sta0, std_sta1))
				return KO;
			ft_sta1.push(g_int[idx]);
			std_sta1.push(g_int[idx]);
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
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<int, std::vector<int> >	ft_sta0;
		ft::stack<int, std::vector<int> >	ft_sta1;
		std::stack<int, std::vector<int> >	std_sta0;
		std::stack<int, std::vector<int> >	std_sta1;

		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			if (ft::operator<=(ft_sta0, ft_sta1) != std::operator<=(std_sta0, std_sta1))
				return KO;
			ft_sta0.push(g_int[idx]);
			std_sta0.push(g_int[idx]);
			if (ft::operator<=(ft_sta0, ft_sta1) != std::operator<=(std_sta0, std_sta1))
				return KO;
			ft_sta1.push(g_int[idx]);
			std_sta1.push(g_int[idx]);
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
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<int, std::vector<int> >	ft_sta0;
		ft::stack<int, std::vector<int> >	ft_sta1;
		std::stack<int, std::vector<int> >	std_sta0;
		std::stack<int, std::vector<int> >	std_sta1;

		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			if (ft::operator>=(ft_sta0, ft_sta1) != std::operator>=(std_sta0, std_sta1))
				return KO;
			ft_sta0.push(g_int[idx]);
			std_sta0.push(g_int[idx]);
			if (ft::operator>=(ft_sta0, ft_sta1) != std::operator>=(std_sta0, std_sta1))
				return KO;
			ft_sta1.push(g_int[idx]);
			std_sta1.push(g_int[idx]);
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

int	test_stack(void)
{
	t_test const	tests[] = {
		__test_constructor,
		__test_type_value_type,
		__test_type_size_type,
		__test_type_container_type,
		__test_function_top,
		__test_function_push,
		__test_function_pop,
		__test_function_empty,
		__test_function_size,
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
	std::cout << "###################################################" << '\n';
	std::cout << "##                     STACK                     ##" << '\n';
	std::cout << "###################################################" << '\n';
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
