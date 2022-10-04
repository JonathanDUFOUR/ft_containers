/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:06:05 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/04 17:19:14 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <set>
#include "arrays.hpp"
#include "tester.hpp"
#include "set.hpp"
#include "iterator/restrictor/random_access_iterator_restrictor.tpp"
#include "e_ret.hpp"

static inline int	__test_constructor(void)
{
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Default constructor
		{
			ft::set<int>	ft_set;
			std::set<int>	std_set;

			if (sizeof(ft_set) != sizeof(std_set) || memcmp(&ft_set, &std_set, sizeof(ft_set)))
				ret = ISO_OK;
		}
		// Range constructor
		{
			// Range of input_iterator_restrictor
			{
				ft::input_iterator_restrictor<t_huint const *> const	it0(&g_huint[0]);
				ft::input_iterator_restrictor<t_huint const *> const	it1(&g_huint[0]);
				ft::set<t_huint> const									ft_set(it0, it1);
				std::set<t_huint> const									std_set(it0, it1);

				if (sizeof(ft_set) != sizeof(std_set) || memcmp(&ft_set, &std_set, sizeof(ft_set)))
					ret = ISO_OK;
			}
			// Range of forward_iterator_restrictor
			{
				ft::forward_iterator_restrictor<void *const *> const	it;
				ft::set<void *> const									ft_set(it, it);
				std::set<void *> const									std_set(it, it);

				if (sizeof(ft_set) != sizeof(std_set) || memcmp(&ft_set, &std_set, sizeof(ft_set)))
					ret = ISO_OK;
			}
			// Range of random_access_iterator
			{
				ft::random_access_iterator_restrictor<t_huint const *> const	it0(&g_huint[0]);
				ft::random_access_iterator_restrictor<t_huint const *> const	it1(&g_huint[g_huint_size]);
				ft::set<t_huint> const											ft_set(it0, it1);
				std::set<t_huint> const											std_set(it0, it1);

				if (sizeof(ft_set) != sizeof(std_set) || memcmp(&ft_set, &std_set, sizeof(ft_set)))
					ret = ISO_OK;
			}
			// Range of char const *
			{
				ft::set<char> const		ft_set(&g_char[0], &g_char[g_char_size]);
				std::set<char> const	std_set(&g_char[0], &g_char[g_char_size]);

				if (sizeof(ft_set) != sizeof(std_set) || memcmp(&ft_set, &std_set, sizeof(ft_set)))
					ret = ISO_OK;
			}
		}
		// Copy constructor
		{
			// Default set
			{
				ft::set<int> const	ft_set0;
				ft::set<int> const	ft_set1(ft_set0);
				std::set<int> const	std_set0;
				std::set<int> const	std_set1(std_set0);

				if (sizeof(ft_set1) != sizeof(std_set1) || memcmp(&ft_set1, &std_set1, sizeof(ft_set1)))
					ret = ISO_OK;
			}
			// Filled set
			{
				ft::set<int> const	ft_set0(&g_int[0], &g_int[g_int_size]);
				ft::set<int> const	ft_set1(ft_set0);
				std::set<int> const	std_set0(&g_int[0], &g_int[g_int_size]);
				std::set<int> const	std_set1(std_set0);

				if (sizeof(ft_set1) != sizeof(std_set1) || memcmp(&ft_set1, &std_set1, sizeof(ft_set1)))
					ret = ISO_OK;
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

inline static int	__test_function_max_size(void)
{
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::set<t_hhuint> const		ft_set0;
		ft::set<std::string> const	ft_set1;
		ft::set<long double> const	ft_set2;
		std::set<t_hhuint> const	std_set0;
		std::set<std::string> const	std_set1;
		std::set<long double> const	std_set2;

		if (ft_set0.max_size() != std_set0.max_size() || ft_set1.max_size() != std_set1.max_size() ||
			ft_set2.max_size() != std_set2.max_size())
			ret = ISO_OK;
		if ((ft_set0.max_size() < ft_set1.max_size()) != (std_set0.max_size() < std_set1.max_size()) ||
			(ft_set0.max_size() < ft_set2.max_size()) != (std_set0.max_size() < std_set2.max_size()) ||
			(ft_set1.max_size() < ft_set2.max_size()) != (std_set1.max_size() < std_set2.max_size()))
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_function_key_comp(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// std::less
		{
			ft::set<char, std::less<char> > const				ft_set;
			std::set<char, std::less<char> > const				std_set;
			ft::set<char, std::less<char> >::key_compare const	ft_key_cmp = ft_set.key_comp();
			std::set<char, std::less<char> >::key_compare const	std_key_cmp = std_set.key_comp();

			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_key_cmp(g_char[idx - 1], g_char[idx]) != std_key_cmp(g_char[idx - 1], g_char[idx]))
					return KO;
		}
		// std::less_equal
		{
			ft::set<char, std::less_equal<char> > const					ft_set;
			std::set<char, std::less_equal<char> > const				std_set;
			ft::set<char, std::less_equal<char> >::key_compare const	ft_key_cmp = ft_set.key_comp();
			std::set<char, std::less_equal<char> >::key_compare const	std_key_cmp = std_set.key_comp();

			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_key_cmp(g_char[idx - 1], g_char[idx]) != std_key_cmp(g_char[idx - 1], g_char[idx]))
					return KO;
		}
		// std::greater
		{
			ft::set<char, std::greater<char> > const				ft_set;
			std::set<char, std::greater<char> > const				std_set;
			ft::set<char, std::greater<char> >::key_compare const	ft_key_cmp = ft_set.key_comp();
			std::set<char, std::greater<char> >::key_compare const	std_key_cmp = std_set.key_comp();

			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_key_cmp(g_char[idx - 1], g_char[idx]) != std_key_cmp(g_char[idx - 1], g_char[idx]))
					return KO;
		}
		// std::greater_equal
		{
			ft::set<char, std::greater_equal<char> > const					ft_set;
			std::set<char, std::greater_equal<char> > const					std_set;
			ft::set<char, std::greater_equal<char> >::key_compare const		ft_key_cmp = ft_set.key_comp();
			std::set<char, std::greater_equal<char> >::key_compare const	std_key_cmp = std_set.key_comp();

			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_key_cmp(g_char[idx - 1], g_char[idx]) != std_key_cmp(g_char[idx - 1], g_char[idx]))
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

inline static int	__test_function_value_comp(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// std::less
		{
			ft::set<char, std::less<char> > const					ft_set;
			std::set<char, std::less<char> > const					std_set;
			ft::set<char, std::less<char> >::value_compare const	ft_val_cmp = ft_set.value_comp();
			std::set<char, std::less<char> >::value_compare const	std_val_cmp = std_set.value_comp();

			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_val_cmp(g_char[idx - 1], g_char[idx]) != std_val_cmp(g_char[idx - 1], g_char[idx]))
					return KO;
		}
		// std::less_equal
		{
			ft::set<char, std::less_equal<char> > const					ft_set;
			std::set<char, std::less_equal<char> > const				std_set;
			ft::set<char, std::less_equal<char> >::value_compare const	ft_val_cmp = ft_set.value_comp();
			std::set<char, std::less_equal<char> >::value_compare const	std_val_cmp = std_set.value_comp();

			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_val_cmp(g_char[idx - 1], g_char[idx]) != std_val_cmp(g_char[idx - 1], g_char[idx]))
					return KO;
		}
		// std::greater
		{
			ft::set<char, std::greater<char> > const					ft_set;
			std::set<char, std::greater<char> > const					std_set;
			ft::set<char, std::greater<char> >::value_compare const		ft_val_cmp = ft_set.value_comp();
			std::set<char, std::greater<char> >::value_compare const	std_val_cmp = std_set.value_comp();

			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_val_cmp(g_char[idx - 1], g_char[idx]) != std_val_cmp(g_char[idx - 1], g_char[idx]))
					return KO;
		}
		// std::greater_equal
		{
			ft::set<char, std::greater_equal<char> > const					ft_set;
			std::set<char, std::greater_equal<char> > const					std_set;
			ft::set<char, std::greater_equal<char> >::value_compare const	ft_val_cmp = ft_set.value_comp();
			std::set<char, std::greater_equal<char> >::value_compare const	std_val_cmp = std_set.value_comp();

			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_val_cmp(g_char[idx - 1], g_char[idx]) != std_val_cmp(g_char[idx - 1], g_char[idx]))
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

int	test_set(void)
{
	t_test const	tests[] = {
		__test_constructor,
		__test_function_max_size,
		__test_function_key_comp,
		__test_function_value_comp,
		NULL
	};
	t_uint			koCount;
	t_uint			idx;

	std::cerr << "\033[38;2;0;173;255m";
	std::cout << "###################################################" << '\n';
	std::cout << "##                      SET                      ##" << '\n';
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
