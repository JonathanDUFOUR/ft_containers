/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:13:27 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/18 23:38:19 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include "arrays.hpp"
#include "iterator/restrictor/random_access_iterator_restrictor.tpp"
#include "map.hpp"
#include "tester.hpp"
#include "e_ret.hpp"

inline static int	__test_constructor(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Default constructor
		{
			ft::map<int, int>	ft_map;
			std::map<int, int>	std_map;

			if (sizeof(ft_map) != sizeof(std_map) || memcmp(&ft_map, &std_map, sizeof(ft_map)))
				ret = ISO_OK;
		}
		// Range constructor
		{
			// Range of input_iterator_restrictor
			{
				std::vector<ft::pair<int, t_hhuint> >	ft_vec;
				std::vector<std::pair<int, t_hhuint> >	std_vec;

				for (idx = 0U ; idx < g_int_size && idx < g_hhuint_size ; ++idx)
				{
					ft_vec.push_back(ft::pair<int, t_hhuint>(g_int[idx], g_hhuint[idx]));
					std_vec.push_back(std::pair<int, t_hhuint>(g_int[idx], g_hhuint[idx]));
				}

				ft::input_iterator_restrictor<std::vector<ft::pair<int, t_hhuint> >::iterator>	ft_it0(ft_vec.begin());
				ft::input_iterator_restrictor<std::vector<ft::pair<int, t_hhuint> >::iterator>	ft_it1(ft_vec.end());
				ft::input_iterator_restrictor<std::vector<std::pair<int, t_hhuint> >::iterator>	std_it0(std_vec.begin());
				ft::input_iterator_restrictor<std::vector<std::pair<int, t_hhuint> >::iterator>	std_it1(std_vec.end());
				std::map<int, t_hhuint>															std_map(std_it0, std_it1);
				ft::map<int, t_hhuint>															ft_map(ft_it0, ft_it1);

				if (sizeof(ft_map) != sizeof(std_map))
					ret = ISO_OK;
			}
			// Range of forward_iterator
			{
				ft::forward_iterator<ft::pair<int, void *> >	ft_it;
				ft::forward_iterator<std::pair<int, void *> >	std_it;
				ft::map<int, void *>							ft_map(ft_it, ft_it);
				std::map<int, void *>							std_map(std_it, std_it);

				if (sizeof(ft_map) != sizeof(std_map))
					ret = ISO_OK;
			}
			// Range of random_access_iterator_restrictor
			{
				std::vector<ft::pair<t_uint, t_lint> >	ft_vec;
				std::vector<std::pair<t_uint, t_lint> >	std_vec;

				for (idx = 0U ; idx < g_uint_size && idx < g_lint_size ; ++idx)
				{
					ft_vec.push_back(ft::pair<t_uint, t_lint>(g_uint[idx], g_lint[idx]));
					std_vec.push_back(std::pair<t_uint, t_lint>(g_uint[idx], g_lint[idx]));
				}

				ft::random_access_iterator_restrictor<std::vector<ft::pair<t_uint, t_lint> >::iterator>		ft_it0(ft_vec.begin());
				ft::random_access_iterator_restrictor<std::vector<ft::pair<t_uint, t_lint> >::iterator>		ft_it1(ft_vec.end());
				ft::random_access_iterator_restrictor<std::vector<std::pair<t_uint, t_lint> >::iterator>	std_it0(std_vec.begin());
				ft::random_access_iterator_restrictor<std::vector<std::pair<t_uint, t_lint> >::iterator>	std_it1(std_vec.end());
				ft::map<t_uint, t_lint>																		ft_map(ft_it0, ft_it1);
				std::map<t_uint, t_lint>																	std_map(std_it0, std_it1);

				if (sizeof(ft_map) != sizeof(std_map))
					ret = ISO_OK;
			}
			// Range of pair *
			{
				std::vector<ft::pair<char, int> >	ft_vec;
				std::vector<std::pair<char, int> >	std_vec;

				for (idx = 0U ; idx < g_char_size && idx < g_int_size ; ++idx)
				{
					ft_vec.push_back(ft::pair<char, int>(g_char[idx], g_int[idx]));
					std_vec.push_back(std::pair<char, int>(g_char[idx], g_int[idx]));
				}

				ft::map<int, char>	ft_map(ft_vec.begin().base(), &*ft_vec.end().base());
				std::map<int, char>	std_map(std_vec.begin().base(), &*std_vec.end().base());

				if (sizeof(ft_map) != sizeof(std_map))
					ret = ISO_OK;
			}
		}
		// Copy constructor
		{
			std::vector<ft::pair<float, std::string> >	ft_vec;
			std::vector<std::pair<float, std::string> >	std_vec;

			for (idx = 0U ; idx < g_float_size && idx < g_string_size ; ++idx)
			{
				ft_vec.push_back(ft::pair<float, std::string>(g_float[idx], g_string[idx]));
				std_vec.push_back(std::pair<float, std::string>(g_float[idx], g_string[idx]));
			}

			ft::map<float, std::string>		ft_map0(ft_vec.begin(), ft_vec.end());
			ft::map<float, std::string>		ft_map1(ft_map0);
			std::map<float, std::string>	std_map0(std_vec.begin(), std_vec.end());
			std::map<float, std::string>	std_map1(std_map0);

			if (sizeof(ft_map1) != sizeof(std_map1))
				ret = ISO_OK;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_function_get_allocator(void)
{
	title(__func__);
	try
	{
		ft::map<char, float> const	ft_map;
		std::map<char, float> const	std_map;

		if (ft_map.get_allocator() != std_map.get_allocator())
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_max_size(void)
{
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::map<t_hhuint, t_hhint> const			ft_map0;
		ft::map<t_lint, t_luint> const				ft_map1;
		ft::map<long double, std::string> const		ft_map2;
		std::map<t_hhuint, t_hhint> const			std_map0;
		std::map<t_lint, t_luint> const				std_map1;
		std::map<long double, std::string> const	std_map2;

		if (ft_map0.max_size() != std_map0.max_size() || ft_map1.max_size() != std_map1.max_size() ||
			ft_map2.max_size() != std_map2.max_size())
			ret = ISO_OK;
		if ((ft_map0.max_size() < ft_map1.max_size()) != (std_map0.max_size() < std_map1.max_size()) ||
			(ft_map0.max_size() < ft_map2.max_size()) != (std_map0.max_size() < std_map2.max_size()) ||
			(ft_map1.max_size() < ft_map2.max_size()) != (std_map1.max_size() < std_map2.max_size()))
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_function_size(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		std::list<ft::pair<t_huint, double> >	ft_lst;
		std::list<std::pair<t_huint, double> >	std_lst;

		for (idx = 0U ; idx < g_huint_size && idx < g_double_size ; ++idx)
		{
			ft::map<t_huint, double>	ft_map(ft_lst.begin(), ft_lst.end());
			std::map<t_huint, double>	std_map(std_lst.begin(), std_lst.end());

			if (ft_map.size() != std_map.size())
				return KO;

			ft_lst.push_back(ft::pair<t_huint, double>(g_huint[idx], g_double[idx]));
			std_lst.push_back(std::pair<t_huint, double>(g_huint[idx], g_double[idx]));
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
		std::vector<ft::pair<t_uint, std::string> >		ft_vec;
		std::vector<std::pair<t_uint, std::string> >	std_vec;

		for (idx = 0U ; idx < g_uint_size && idx < g_string_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<t_uint, std::string>(g_uint[idx], g_string[idx]));
			std_vec.push_back(std::pair<t_uint, std::string>(g_uint[idx], g_string[idx]));
		}
		for (idx = 0U ; idx < g_uint_size && idx < g_string_size ; ++idx)
		{
			ft::map<t_uint, std::string>	ft_map(&ft_vec[idx * (idx % 2)], &ft_vec[idx]);
			std::map<t_uint, std::string>	std_map(&std_vec[idx * (idx % 2)], &std_vec[idx]);

			if (ft_map.empty() != std_map.empty())
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

int	test_map(void)
{
	t_test const	tests[] = {
		__test_constructor,
		__test_function_get_allocator,
		__test_function_max_size,
		__test_function_size,
		__test_function_empty,
		NULL
	};
	t_uint			koCount;
	t_uint			idx;

	std::cerr << "\033[38;2;0;173;255m";
	std::cout << "###################################################" << '\n';
	std::cout << "##                      MAP                      ##" << '\n';
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
