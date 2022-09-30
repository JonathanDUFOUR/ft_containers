/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:13:27 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/30 19:53:56 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <vector>
#include "arrays.hpp"
#include "iteratorCheck.tpp"
#include "iterator/restrictor/random_access_iterator_restrictor.tpp"
#include "map.hpp"
#include "tester.hpp"
#include "e_ret.hpp"

template <typename T0, typename T1>
inline static bool	__cmp(ft::pair<T0, T1> const &a, std::pair<T0, T1> const &b)
{
	return a.first == b.first && a.second == b.second;
}

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
			// Range of forward_iterator_restrictor
			{
				ft::forward_iterator_restrictor<ft::pair<int, void *> const *>	ft_it;
				ft::forward_iterator_restrictor<std::pair<int, void *> const *>	std_it;
				ft::map<int, void *>											ft_map(ft_it, ft_it);
				std::map<int, void *>											std_map(std_it, std_it);

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

inline static int	__test_function_key_comp(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// std::less
		{
			ft::map<char, t_lint, std::less<char> > const	ft_map;
			std::map<char, t_lint, std::less<char> > const	std_map;
			std::less<char> const							ft_key_cmp = ft_map.key_comp();
			std::less<char> const							std_key_cmp = std_map.key_comp();

			if (sizeof(ft_key_cmp) != sizeof(std_key_cmp))
				return KO;
			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_key_cmp(g_char[idx - 1], g_char[idx]) != std_key_cmp(g_char[idx - 1], g_char[idx]))
					return KO;
		}
		// std::less_equal
		{
			ft::map<char, t_lint, std::less_equal<char> > const		ft_map;
			std::map<char, t_lint, std::less_equal<char> > const	std_map;
			std::less_equal<char> const								ft_key_cmp = ft_map.key_comp();
			std::less_equal<char> const								std_key_cmp = std_map.key_comp();

			if (sizeof(ft_key_cmp) != sizeof(std_key_cmp))
				return KO;
			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_key_cmp(g_char[idx - 1], g_char[idx]) != std_key_cmp(g_char[idx - 1], g_char[idx]))
					return KO;
		}
		// std::greater
		{
			ft::map<char, t_lint, std::greater<char> > const	ft_map;
			std::map<char, t_lint, std::greater<char> > const	std_map;
			std::greater<char> const							ft_key_cmp = ft_map.key_comp();
			std::greater<char> const							std_key_cmp = std_map.key_comp();

			if (sizeof(ft_key_cmp) != sizeof(std_key_cmp))
				return KO;
			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_key_cmp(g_char[idx - 1], g_char[idx]) != std_key_cmp(g_char[idx - 1], g_char[idx]))
					return KO;
		}
		// std::greater_equal
		{
			ft::map<char, t_lint, std::greater_equal<char> > const	ft_map;
			std::map<char, t_lint, std::greater_equal<char> > const	std_map;
			std::greater_equal<char> const							ft_key_cmp = ft_map.key_comp();
			std::greater_equal<char> const							std_key_cmp = std_map.key_comp();

			if (sizeof(ft_key_cmp) != sizeof(std_key_cmp))
				return KO;
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
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// std::less
		{
			ft::map<char, t_lint, std::less<char> > const					ft_map;
			std::map<char, t_lint, std::less<char> > const					std_map;
			ft::map<char, t_lint, std::less<char> >::value_compare const	ft_val_cmp = ft_map.value_comp();
			std::map<char, t_lint, std::less<char> >::value_compare const	std_val_cmp = std_map.value_comp();

			if (sizeof(ft_val_cmp) != sizeof(std_val_cmp))
				return ret = ISO_OK;
			for (idx = 1U ; idx < g_char_size && idx < g_lint_size ; ++idx)
			{
				ft::map<char, t_lint, std::less<char> >::value_type const	ft_val0(g_char[idx - 1], g_lint[idx - 1]);
				ft::map<char, t_lint, std::less<char> >::value_type const	ft_val1(g_char[idx], g_lint[idx]);
				std::map<char, t_lint, std::less<char> >::value_type const	std_val0(g_char[idx - 1], g_lint[idx - 1]);
				std::map<char, t_lint, std::less<char> >::value_type const	std_val1(g_char[idx], g_lint[idx]);

				if (ft_val_cmp(ft_val0, ft_val1) != std_val_cmp(std_val0, std_val1))
					return KO;
			}
		}
		// std::less_equal
		{
			ft::map<char, t_lint, std::less_equal<char> > const					ft_map;
			std::map<char, t_lint, std::less_equal<char> > const				std_map;
			ft::map<char, t_lint, std::less_equal<char> >::value_compare const	ft_val_cmp = ft_map.value_comp();
			std::map<char, t_lint, std::less_equal<char> >::value_compare const	std_val_cmp = std_map.value_comp();

			if (sizeof(ft_val_cmp) != sizeof(std_val_cmp))
				return ret = ISO_OK;
			for (idx = 1U ; idx < g_char_size && idx < g_lint_size ; ++idx)
			{
				ft::map<char, t_lint, std::less_equal<char> >::value_type const		ft_val0(g_char[idx - 1], g_lint[idx - 1]);
				ft::map<char, t_lint, std::less_equal<char> >::value_type const		ft_val1(g_char[idx], g_lint[idx]);
				std::map<char, t_lint, std::less_equal<char> >::value_type const	std_val0(g_char[idx - 1], g_lint[idx - 1]);
				std::map<char, t_lint, std::less_equal<char> >::value_type const	std_val1(g_char[idx], g_lint[idx]);

				if (ft_val_cmp(ft_val0, ft_val1) != std_val_cmp(std_val0, std_val1))
					return KO;
			}
		}
		// std::greater
		{
			ft::map<char, t_lint, std::greater<char> > const					ft_map;
			std::map<char, t_lint, std::greater<char> > const					std_map;
			ft::map<char, t_lint, std::greater<char> >::value_compare const		ft_val_cmp = ft_map.value_comp();
			std::map<char, t_lint, std::greater<char> >::value_compare const	std_val_cmp = std_map.value_comp();

			if (sizeof(ft_val_cmp) != sizeof(std_val_cmp))
				return ret = ISO_OK;
			for (idx = 1U ; idx < g_char_size && idx < g_lint_size ; ++idx)
			{
				ft::map<char, t_lint, std::greater<char> >::value_type const	ft_val0(g_char[idx - 1], g_lint[idx - 1]);
				ft::map<char, t_lint, std::greater<char> >::value_type const	ft_val1(g_char[idx], g_lint[idx]);
				std::map<char, t_lint, std::greater<char> >::value_type const	std_val0(g_char[idx - 1], g_lint[idx - 1]);
				std::map<char, t_lint, std::greater<char> >::value_type const	std_val1(g_char[idx], g_lint[idx]);

				if (ft_val_cmp(ft_val0, ft_val1) != std_val_cmp(std_val0, std_val1))
					return KO;
			}
		}
		// std::greater_equal
		{
			ft::map<char, t_lint, std::greater_equal<char> > const					ft_map;
			std::map<char, t_lint, std::greater_equal<char> > const					std_map;
			ft::map<char, t_lint, std::greater_equal<char> >::value_compare const	ft_val_cmp = ft_map.value_comp();
			std::map<char, t_lint, std::greater_equal<char> >::value_compare const	std_val_cmp = std_map.value_comp();

			if (sizeof(ft_val_cmp) != sizeof(std_val_cmp))
				return ret = ISO_OK;
			for (idx = 1U ; idx < g_char_size && idx < g_lint_size ; ++idx)
			{
				ft::map<char, t_lint, std::greater_equal<char> >::value_type const	ft_val0(g_char[idx - 1], g_lint[idx - 1]);
				ft::map<char, t_lint, std::greater_equal<char> >::value_type const	ft_val1(g_char[idx], g_lint[idx]);
				std::map<char, t_lint, std::greater_equal<char> >::value_type const	std_val0(g_char[idx - 1], g_lint[idx - 1]);
				std::map<char, t_lint, std::greater_equal<char> >::value_type const	std_val1(g_char[idx], g_lint[idx]);

				if (ft_val_cmp(ft_val0, ft_val1) != std_val_cmp(std_val0, std_val1))
					return KO;
			}
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

inline static int	__test_function_begin(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		std::vector<ft::pair<char, int> >	ft_vec;
		std::vector<std::pair<char, int> >	std_vec;

		for (idx = 0U ; idx < g_char_size && idx < g_int_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<char, int>(g_char[idx], g_int[idx]));
			std_vec.push_back(std::pair<char, int>(g_char[idx], g_int[idx]));
		}

		// Mutable access
		{
			ft::map<char, int>::iterator	ft_it;
			std::map<char, int>::iterator	std_it;

			for (idx = 1U ; idx < g_char_size && idx < g_int_size ; ++idx)
			{
				ft::map<char, int>	ft_map(&ft_vec[idx - 1], &*ft_vec.end());
				std::map<char, int>	std_map(&std_vec[idx - 1], &*std_vec.end());

				ft_it = ft_map.begin();
				std_it = std_map.begin();

				if (!!ft_it.getCurr() != !!std_it._M_node)
					ret = ISO_OK;
				if (ft_it->first != std_it->first || ft_it->second != std_it->second)
					return KO;
			}

			ft::map<char, int>	ft_map;
			std::map<char, int>	std_map;

			ft_it = ft_map.begin();
			std_it = std_map.begin();

			if (!!ft_it.getCurr() != !!std_it._M_node)
				ret = ISO_OK;
		}
		// Constant access
		{
			ft::map<char, int>::const_iterator	ft_cit;
			std::map<char, int>::const_iterator	std_cit;

			for (idx = 1U ; idx < g_char_size && idx < g_int_size ; ++idx)
			{
				ft::map<char, int> const	ft_map(&ft_vec[idx - 1], &*ft_vec.end());
				std::map<char, int> const	std_map(&std_vec[idx - 1], &*std_vec.end());

				ft_cit = ft_map.begin();
				std_cit = std_map.begin();

				if (!!ft_cit.getCurr() != !!std_cit._M_node)
					ret = ISO_OK;
				if (ft_cit->first != std_cit->first || ft_cit->second != std_cit->second)
					return KO;
			}

			ft::map<char, int> const	ft_map;
			std::map<char, int> const	std_map;

			ft_cit = ft_map.begin();
			std_cit = std_map.begin();

			if (!!ft_cit.getCurr() != !!std_cit._M_node)
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

inline static int	__test_function_end(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		std::vector<ft::pair<char, int> >	ft_vec;
		std::vector<std::pair<char, int> >	std_vec;

		for (idx = 0U ; idx < g_char_size && idx < g_int_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<char, int>(g_char[idx], g_int[idx]));
			std_vec.push_back(std::pair<char, int>(g_char[idx], g_int[idx]));
		}

		// Mutable access
		{
			ft::map<char, int>::iterator	ft_it;
			std::map<char, int>::iterator	std_it;

			for (idx = 1U ; idx < g_char_size && idx < g_int_size ; ++idx)
			{
				ft::map<char, int>	ft_map(&ft_vec[0], &ft_vec[idx]);
				std::map<char, int>	std_map(&std_vec[0], &std_vec[idx]);

				ft_it = ft_map.end();
				std_it = std_map.end();

				if (!!ft_it.getCurr() != !!std_it._M_node)
					ret =  ISO_OK;

				--ft_it;
				--std_it;

				if (ft_it->first != std_it->first || ft_it->second != std_it->second)
					return KO;
			}

			ft::map<char, int>	ft_map;
			std::map<char, int>	std_map;

			ft_it = ft_map.end();
			std_it = std_map.end();

			if (!!ft_it.getCurr() != !!std_it._M_node)
				ret = ISO_OK;
		}
		// Constant access
		{
			ft::map<char, int>::const_iterator	ft_cit;
			std::map<char, int>::const_iterator	std_cit;

			for (idx = 1U ; idx < g_char_size && idx < g_int_size ; ++idx)
			{
				ft::map<char, int> const	ft_map(&ft_vec[0], &ft_vec[idx]);
				std::map<char, int> const	std_map(&std_vec[0], &std_vec[idx]);

				ft_cit = ft_map.end();
				std_cit = std_map.end();

				if (!!ft_cit.getCurr() != !!std_cit._M_node)
					ret = ISO_OK;

				--ft_cit;
				--std_cit;

				if (ft_cit->first != std_cit->first || ft_cit->second != std_cit->second)
					return KO;
			}

			ft::map<char, int> const	ft_map;
			std::map<char, int> const	std_map;

			ft_cit = ft_map.end();
			std_cit = std_map.end();

			if (!!ft_cit.getCurr() != !!std_cit._M_node)
				ret = ISO_OK;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_rbegin(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		std::vector<ft::pair<char, int> >	ft_vec;
		std::vector<std::pair<char, int> >	std_vec;

		for (idx = 0U ; idx < g_char_size && idx < g_int_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<char, int>(g_char[idx], g_int[idx]));
			std_vec.push_back(std::pair<char, int>(g_char[idx], g_int[idx]));
		}

		// Mutable access
		{
			ft::map<char, int>::reverse_iterator	ft_rit;
			std::map<char, int>::reverse_iterator	std_rit;

			for (idx = 1U ; idx < g_char_size && idx < g_int_size ; ++idx)
			{
				ft::map<char, int>	ft_map(&ft_vec[idx - 1], &*ft_vec.end());
				std::map<char, int>	std_map(&std_vec[idx - 1], &*std_vec.end());

				ft_rit = ft_map.rbegin();
				std_rit = std_map.rbegin();

				if (!!ft_rit.base().getCurr() != !!std_rit.base()._M_node)
					ret = ISO_OK;
				if (ft_rit->first != std_rit->first || ft_rit->second != std_rit->second)
					return KO;
			}

			ft::map<char, int>	ft_map;
			std::map<char, int>	std_map;

			ft_rit = ft_map.rbegin();
			std_rit = std_map.rbegin();

			if (!!ft_rit.base().getCurr() != !!std_rit.base()._M_node)
				ret = ISO_OK;
		}
		// Constant access
		{
			ft::map<char, int>::const_reverse_iterator	ft_crit;
			std::map<char, int>::const_reverse_iterator	std_crit;

			for (idx = 1U ; idx < g_char_size && idx < g_int_size ; ++idx)
			{
				ft::map<char, int> const	ft_map(&ft_vec[idx - 1], &*ft_vec.end());
				std::map<char, int> const	std_map(&std_vec[idx - 1], &*std_vec.end());

				ft_crit = ft_map.rbegin();
				std_crit = std_map.rbegin();

				if (!!ft_crit.base().getCurr() != !!std_crit.base()._M_node)
					ret = ISO_OK;
				if (ft_crit->first != std_crit->first || ft_crit->second != std_crit->second)
					return KO;
			}

			ft::map<char, int> const	ft_map;
			std::map<char, int> const	std_map;

			ft_crit = ft_map.rbegin();
			std_crit = std_map.rbegin();

			if (!!ft_crit.base().getCurr() != !!std_crit.base()._M_node)
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

inline static int	__test_function_rend(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		std::vector<ft::pair<char, int> >	ft_vec;
		std::vector<std::pair<char, int> >	std_vec;

		for (idx = 0U ; idx < g_char_size && idx < g_int_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<char, int>(g_char[idx], g_int[idx]));
			std_vec.push_back(std::pair<char, int>(g_char[idx], g_int[idx]));
		}

		// Mutable access
		{
			ft::map<char, int>::reverse_iterator	ft_rit;
			std::map<char, int>::reverse_iterator	std_rit;

			for (idx = 1U ; idx < g_char_size && idx < g_int_size ; ++idx)
			{
				ft::map<char, int>	ft_map(&ft_vec[0], &ft_vec[idx]);
				std::map<char, int>	std_map(&std_vec[0], &std_vec[idx]);

				ft_rit = ft_map.rend();
				std_rit = std_map.rend();

				if (!!ft_rit.base().getCurr() != !!std_rit.base()._M_node)
					ret = ISO_OK;

				--ft_rit;
				--std_rit;

				if (ft_rit->first != std_rit->first || ft_rit->second != std_rit->second)
					return KO;
			}

			ft::map<char, int>	ft_map;
			std::map<char, int>	std_map;

			ft_rit = ft_map.rend();
			std_rit = std_map.rend();

			if (!!ft_rit.base().getCurr() != !!std_rit.base()._M_node)
				ret = ISO_OK;
		}
		// Constant access
		{
			ft::map<char, int>::const_reverse_iterator	ft_crit;
			std::map<char, int>::const_reverse_iterator	std_crit;

			for (idx = 1U ; idx < g_char_size && idx < g_int_size ; ++idx)
			{
				ft::map<char, int> const	ft_map(&ft_vec[0], &ft_vec[idx]);
				std::map<char, int> const	std_map(&std_vec[0], &std_vec[idx]);

				ft_crit = ft_map.rend();
				std_crit = std_map.rend();

				if (!!ft_crit.base().getCurr() != !!std_crit.base()._M_node)
					ret = ISO_OK;

				--ft_crit;
				--std_crit;

				if (ft_crit->first != std_crit->first || ft_crit->second != std_crit->second)
					return KO;
			}

			ft::map<char, int> const	ft_map;
			std::map<char, int> const	std_map;

			ft_crit = ft_map.rend();
			std_crit = std_map.rend();

			if (!!ft_crit.base().getCurr() != !!std_crit.base()._M_node)
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

inline static int	__test_type_iterator(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		std::vector<ft::pair<float, t_hhint> >	ft_vec;
		std::vector<std::pair<float, t_hhint> >	std_vec;

		for (idx = 0U ; idx < g_float_size && idx < g_hhint_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<float, t_hhint>(g_float[idx], g_hhint[idx]));
			std_vec.push_back(std::pair<float, t_hhint>(g_float[idx], g_hhint[idx]));
		}

		ft::map<float, t_hhint>				ft_map(ft_vec.begin(), ft_vec.end());
		std::map<float, t_hhint>			std_map(std_vec.begin(), std_vec.end());
		ft::map<float, t_hhint>::iterator	ft_it;
		std::map<float, t_hhint>::iterator	std_it;

		if (sizeof(ft_it) != sizeof(std_it))
			ret = ISO_OK;

		for (ft_it = ft_map.begin(), std_it = std_map.begin(), idx = 0U ;
			ft_it != ft_map.end() && std_it != std_map.end() ;
			++ft_it, ++std_it, ++idx)
		{
			if (idx)
			{
				BidirectionalIteratorCheck(ft_it);
				BidirectionalIteratorCheck(std_it);
			}

			if ((ft_it->first != std_it->first) ||
				(ft_it->second)++ != (std_it->second)++ || ++(ft_it->second) != ++(std_it->second) ||
				(ft_it->second)-- != (std_it->second)-- || --(ft_it->second) != --(std_it->second))
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_type_const_iterator(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		std::vector<ft::pair<float, t_hhint> >	ft_vec;
		std::vector<std::pair<float, t_hhint> >	std_vec;

		for (idx = 0U ; idx < g_float_size && idx < g_hhint_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<float, t_hhint>(g_float[idx], g_hhint[idx]));
			std_vec.push_back(std::pair<float, t_hhint>(g_float[idx], g_hhint[idx]));
		}

		ft::map<float, t_hhint>						ft_map(ft_vec.begin(), ft_vec.end());
		std::map<float, t_hhint>					std_map(std_vec.begin(), std_vec.end());
		ft::map<float, t_hhint>::const_iterator		ft_it;
		std::map<float, t_hhint>::const_iterator	std_it;

		if (sizeof(ft_it) != sizeof(std_it))
			ret = ISO_OK;

		for (ft_it = ft_map.begin(), std_it = std_map.begin(), idx = 0U ;
			ft_it != ft_map.end() && std_it != std_map.end() ;
			++ft_it, ++std_it)
		{
			if (idx)
			{
				BidirectionalIteratorCheck(ft_it);
				BidirectionalIteratorCheck(std_it);
			}

			if (ft_it->first != std_it->first || ft_it->second != std_it->second)
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_type_reverse_iterator(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		std::vector<ft::pair<float, t_hhint> >	ft_vec;
		std::vector<std::pair<float, t_hhint> >	std_vec;

		for (idx = 0U ; idx < g_float_size && idx < g_hhint_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<float, t_hhint>(g_float[idx], g_hhint[idx]));
			std_vec.push_back(std::pair<float, t_hhint>(g_float[idx], g_hhint[idx]));
		}

		ft::map<float, t_hhint>						ft_map(ft_vec.begin(), ft_vec.end());
		std::map<float, t_hhint>					std_map(std_vec.begin(), std_vec.end());
		ft::map<float, t_hhint>::reverse_iterator	ft_rit;
		std::map<float, t_hhint>::reverse_iterator	std_it;

		if (sizeof(ft_rit) != sizeof(std_it))
			ret = ISO_OK;

		for (ft_rit = ft_map.rbegin(), std_it = std_map.rbegin(), idx = 0U ;
			ft_rit != ft_map.rend() && std_it != std_map.rend() ;
			++ft_rit, ++std_it, ++idx)
		{
			if (idx)
			{
				BidirectionalIteratorCheck(ft_rit);
				BidirectionalIteratorCheck(std_it);
			}

			if ((ft_rit->first != std_it->first) ||
				(ft_rit->second)++ != (std_it->second)++ || ++(ft_rit->second) != ++(std_it->second) ||
				(ft_rit->second)-- != (std_it->second)-- || --(ft_rit->second) != --(std_it->second))
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_type_const_reverse_iterator(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		std::vector<ft::pair<float, t_hhint> >	ft_vec;
		std::vector<std::pair<float, t_hhint> >	std_vec;

		for (idx = 0U ; idx < g_float_size && idx < g_hhint_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<float, t_hhint>(g_float[idx], g_hhint[idx]));
			std_vec.push_back(std::pair<float, t_hhint>(g_float[idx], g_hhint[idx]));
		}

		ft::map<float, t_hhint>								ft_map(ft_vec.begin(), ft_vec.end());
		std::map<float, t_hhint>							std_map(std_vec.begin(), std_vec.end());
		ft::map<float, t_hhint>::const_reverse_iterator		ft_crit;
		std::map<float, t_hhint>::const_reverse_iterator	std_crit;

		if (sizeof(ft_crit) != sizeof(std_crit))
			ret = ISO_OK;

		for (ft_crit = ft_map.rbegin(), std_crit = std_map.rbegin(), idx = 0U ;
			ft_crit != ft_map.rend() && std_crit != std_map.rend() ;
			++ft_crit, ++std_crit)
		{
			if (idx)
			{
				BidirectionalIteratorCheck(ft_crit);
				BidirectionalIteratorCheck(std_crit);
			}

			if (ft_crit->first != std_crit->first || ft_crit->second != std_crit->second)
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_function_insert(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		std::vector<ft::pair<std::string, t_luint> >	ft_vec;
		std::vector<std::pair<std::string, t_luint> >	std_vec;

		for (idx = 0U ; idx < g_string_size && idx < g_luint_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<std::string, t_luint>(g_string[idx], g_luint[idx]));
			std_vec.push_back(std::pair<std::string, t_luint>(g_string[idx], g_luint[idx]));
		}

		// Range insertion
		{
			ft::map<std::string, t_luint>	ft_map;
			std::map<std::string, t_luint>	std_map;

			for (idx = 1U ; idx < g_string_size && idx < g_luint_size ; ++idx)
			{
				ft_map.insert(&ft_vec[idx - 1], &ft_vec[idx + 1]);
				std_map.insert(&std_vec[idx - 1], &std_vec[idx + 1]);

				if (ft_map.size() != std_map.size() ||
					!std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), __cmp<std::string, t_luint>))
					return KO;
			}
		}
		// Single insertion
		{
			ft::map<std::string, t_luint>								ft_map;
			std::map<std::string, t_luint>								std_map;
			ft::pair<ft::map<std::string, t_luint>::iterator, bool>		ft_ret;
			std::pair<std::map<std::string, t_luint>::iterator, bool>	std_ret;

			for (idx = 0U ; idx < ft_vec.size() && idx < std_vec.size() ; ++idx)
			{
				ft_ret = ft_map.insert(ft_vec[idx]);
				std_ret = std_map.insert(std_vec[idx]);

				if (ft_ret.first->first != std_ret.first->first ||
					ft_ret.first->second != std_ret.first->second ||
					ft_ret.second != std_ret.second ||
					ft_map.size() != std_map.size() ||
					!std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), __cmp<std::string, t_luint>))
					return KO;
			}
		}
		// Single insertion with hint
		{
			ft::map<std::string, t_luint>				ft_map;
			std::map<std::string, t_luint>				std_map;
			ft::map<std::string, t_luint>::iterator		ft_it;
			std::map<std::string, t_luint>::iterator	std_it;

			ft_map.insert(ft::pair<std::string, t_luint>(std::string("dedicated to lmartin"), 42LU));
			std_map.insert(std::pair<std::string, t_luint>(std::string("dedicated to lmartin"), 42LU));
			ft_it = ft_map.begin();
			std_it = std_map.begin();
			for (idx = 0U ; idx < ft_vec.size() * 3 && idx < std_vec.size() * 3 ; ++idx)
			{
				switch (idx % 3)
				{
					case 0:
						ft_it = ft_map.insert(ft_it, ft_vec[idx / 3]);
						std_it = std_map.insert(std_it, std_vec[idx / 3]);
						break;
				
					case 1:
						ft_it = ft_map.insert(ft_map.begin(), *++ft_map.begin());
						std_it = std_map.insert(std_map.begin(), *++std_map.begin());
						break;

					case 2:
						ft_it = ft_map.insert(ft_map.end(), *++ft_map.rbegin());
						std_it = std_map.insert(std_map.end(), *++std_map.rbegin());
						break;
				}

				if (ft_it->first != std_it->first ||
					ft_it->second != std_it->second ||
					ft_map.size() != std_map.size() ||
					!std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), __cmp<std::string, t_luint>))
					return KO;
			}
			ft_it = ft_map.insert(ft_map.end(), ft::make_pair(std::string("What else ?"), 11223344556677889900LU));
			std_it = std_map.insert(std_map.end(), std::make_pair(std::string("What else ?"), 11223344556677889900LU));

			if (ft_it->first != std_it->first ||
				ft_it->second != std_it->second ||
				ft_map.size() != std_map.size() ||
				!std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), __cmp<std::string, t_luint>))
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

inline static int	__test_function_erase(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		std::vector<ft::pair<char, t_lint> >	ft_vec;
		std::vector<std::pair<char, t_lint> >	std_vec;

		for (idx = 0U ; idx < g_char_size && idx < g_lint_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<char, t_lint>(g_char[idx], g_lint[idx]));
			std_vec.push_back(std::pair<char, t_lint>(g_char[idx], g_lint[idx]));
		}

		// Single erase (position)
		{
			ft::map<char, t_lint>	ft_map(ft_vec.begin(), ft_vec.end());
			std::map<char, t_lint>	std_map(std_vec.begin(), std_vec.end());

			for (idx = 0U ; idx < g_char_size && idx < g_lint_size ; ++idx)
			{
				ft_map.erase(ft_map.begin());
				std_map.erase(std_map.begin());

				if (ft_map.size() != std_map.size() ||
					!std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), __cmp<char, t_lint>))
					return KO;
			}
		}
		// Single erase (key)
		{
			ft::map<char, t_lint>	ft_map(ft_vec.begin(), ft_vec.end());
			std::map<char, t_lint>	std_map(std_vec.begin(), std_vec.end());
			size_t					ft_ret;
			size_t					std_ret;

			for (idx = 0U ; idx < g_char_size * 2 && idx < g_lint_size * 2 ; ++idx)
			{
				ft_ret = ft_map.erase(g_char[idx / 2]);
				std_ret = std_map.erase(g_char[idx / 2]);

				if (ft_ret != std_ret || ft_map.size() != std_map.size() ||
					!std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), __cmp<char, t_lint>))
					return KO;
			}
		}
		// Range erase
		{
			ft::map<char, t_lint>				ft_map(ft_vec.begin(), ft_vec.end());
			std::map<char, t_lint>				std_map(std_vec.begin(), std_vec.end());
			ft::map<char, t_lint>::iterator		ft_it0;
			ft::map<char, t_lint>::iterator		ft_it1;
			std::map<char, t_lint>::iterator	std_it0;
			std::map<char, t_lint>::iterator	std_it1;
			
			for (idx = 0U ; idx < g_char_size && idx < g_lint_size ; idx += 2)
			{
				ft_it0 = ft_map.begin();
				std_it0 = std_map.begin();
				std::advance(ft_it0, ft_map.size() / 2 - 1);
				std::advance(std_it0, std_map.size() / 2 - 1);
				ft_it1 = ft_it0;
				std_it1 = std_it0;
				std::advance(ft_it1, 2U);
				std::advance(std_it1, 2U);
				ft_map.erase(ft_it0, ft_it1);
				std_map.erase(std_it0, std_it1);

				if (ft_map.size() != std_map.size() ||
					!std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), __cmp<char, t_lint>))
					return KO;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_clear(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		std::vector<ft::pair<int, t_hhuint> >	ft_vec;
		std::vector<std::pair<int, t_hhuint> >	std_vec;

		for (idx = 0U ; idx < g_int_size && idx < g_hhuint_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<int, t_hhuint>(g_int[idx], g_hhuint[idx]));
			std_vec.push_back(std::pair<int, t_hhuint>(g_int[idx], g_hhuint[idx]));
		}

		for (idx = 0U ; idx < g_int_size && idx < g_hhuint_size ; ++idx)
		{
			ft::map<int, t_hhuint>	ft_map(ft_vec.begin(), ft_vec.end());
			std::map<int, t_hhuint>	std_map(std_vec.begin(), std_vec.end());

			ft_map.clear();
			std_map.clear();

			if (ft_map.size() != std_map.size() ||
				!std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), __cmp<int, t_hhuint>))
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

inline static int	__test_function_find(void)
{
	t_uint	idx;
	float	nb;

	title(__func__);
	try
	{
		std::vector<ft::pair<float, std::string> >	ft_vec;
		std::vector<std::pair<float, std::string> >	std_vec;

		for (idx = 0U ; idx < g_float_size && idx < g_string_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<float, std::string>(g_float[idx], g_string[idx]));
			std_vec.push_back(std::pair<float, std::string>(g_float[idx], g_string[idx]));
		}

		// Mutable access
		{
			ft::map<float, std::string>				ft_map(ft_vec.begin(), ft_vec.end());
			std::map<float, std::string>			std_map(std_vec.begin(), std_vec.end());
			ft::map<float, std::string>::iterator	ft_it;
			std::map<float, std::string>::iterator	std_it;

			for (idx = 0U ; idx < g_float_size * 2 && idx < g_string_size * 2 ; ++idx)
			{
				if (idx % 2)
				{
					nb = static_cast<float>(rand());
					while (std::find(&g_float[0], &g_float[g_float_size], nb) != &g_float[g_float_size])
						nb = static_cast<float>(rand());
				}
				else
					nb = g_float[idx / 2];

				ft_it = ft_map.find(nb);
				std_it = std_map.find(nb);

				if ((ft_it == ft_map.end()) != (std_it == std_map.end()) ||
					(ft_it != ft_map.end() && (ft_it->first != std_it->first ||
					ft_it->second.append("42") != std_it->second.append("42"))))
					return KO;
			}
		}
		// Constant access
		{
			ft::map<float, std::string> const				ft_map(ft_vec.begin(), ft_vec.end());
			std::map<float, std::string> const				std_map(std_vec.begin(), std_vec.end());
			ft::map<float, std::string>::const_iterator		ft_cit;
			std::map<float, std::string>::const_iterator	std_cit;

			for (idx = 0U ; idx < g_float_size * 2 && idx < g_string_size * 2 ; ++idx)
			{
				if (idx % 2)
				{
					nb = static_cast<float>(rand());
					while (std::find(&g_float[0], &g_float[g_float_size], nb) != &g_float[g_float_size])
						nb = static_cast<float>(rand());
				}
				else
					nb = g_float[idx / 2];

				ft_cit = ft_map.find(nb);
				std_cit = std_map.find(nb);

				if ((ft_cit == ft_map.end()) != (std_cit == std_map.end()) ||
					(ft_cit != ft_map.end() && (ft_cit->first != std_cit->first || ft_cit->second != std_cit->second)))
					return KO;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_count(void)
{
	t_uint	idx;
	float	nb;

	title(__func__);
	try
	{
		std::vector<ft::pair<float, std::string> >	ft_vec;
		std::vector<std::pair<float, std::string> >	std_vec;

		for (idx = 0U ; idx < g_float_size && idx < g_string_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<float, std::string>(g_float[idx], g_string[idx]));
			std_vec.push_back(std::pair<float, std::string>(g_float[idx], g_string[idx]));
		}

		ft::map<float, std::string> const		ft_map(ft_vec.begin(), ft_vec.end());
		std::map<float, std::string> const		std_map(std_vec.begin(), std_vec.end());

		for (idx = 0U ; idx < g_float_size * 2 && idx < g_string_size * 2 ; ++idx)
		{
			if (idx % 2)
			{
				nb = static_cast<float>(rand());
				while (std::find(&g_float[0], &g_float[g_float_size], nb) != &g_float[g_float_size])
					nb = static_cast<float>(rand());
			}
			else
				nb = g_float[idx / 2];

			if (ft_map.count(nb) != std_map.count(nb))
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

inline static int	__test_function_lower_bound(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		std::vector<ft::pair<t_lint, long double> >		ft_vec;
		std::vector<std::pair<t_lint, long double> >	std_vec;

		for (idx = 0U ; idx < g_lint_size && idx < g_long_double_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<t_lint, long double>(g_lint[idx], g_long_double[idx]));
			std_vec.push_back(std::pair<t_lint, long double>(g_lint[idx], g_long_double[idx]));
		}

		// Mutable access
		{
			ft::map<t_lint, long double>			ft_map(ft_vec.begin(), ft_vec.end());
			std::map<t_lint, long double>			std_map(std_vec.begin(), std_vec.end());
			ft::map<t_lint, long double>::iterator	ft_it;
			std::map<t_lint, long double>::iterator	std_it;

			for (idx = 0U ; idx < g_lint_size && idx < g_long_double_size ; ++idx)
			{
				ft_it = ft_map.lower_bound(g_lint[idx]);
				std_it = std_map.lower_bound(g_lint[idx]);

				if ((ft_it == ft_map.end()) != (std_it == std_map.end()) ||
					(ft_it != ft_map.end() && (ft_it->first != std_it->first || --ft_it->second != --std_it->second)))
					return KO;
			}
		}
		// Constant access
		{
			ft::map<t_lint, long double> const				ft_map(ft_vec.begin(), ft_vec.end());
			std::map<t_lint, long double> const				std_map(std_vec.begin(), std_vec.end());
			ft::map<t_lint, long double>::const_iterator	ft_cit;
			std::map<t_lint, long double>::const_iterator	std_cit;

			for (idx = 0U ; idx < g_lint_size && idx < g_long_double_size ; ++idx)
			{
				ft_cit = ft_map.lower_bound(g_lint[idx]);
				std_cit = std_map.lower_bound(g_lint[idx]);

				if ((ft_cit == ft_map.end()) != (std_cit == std_map.end()) ||
					(ft_cit != ft_map.end() && (ft_cit->first != std_cit->first || ft_cit->second != std_cit->second)))
					return KO;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_upper_bound(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		std::vector<ft::pair<t_lint, long double> >		ft_vec;
		std::vector<std::pair<t_lint, long double> >	std_vec;

		for (idx = 0U ; idx < g_lint_size && idx < g_long_double_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<t_lint, long double>(g_lint[idx], g_long_double[idx]));
			std_vec.push_back(std::pair<t_lint, long double>(g_lint[idx], g_long_double[idx]));
		}

		// Mutable access
		{
			ft::map<t_lint, long double>			ft_map(ft_vec.begin(), ft_vec.end());
			std::map<t_lint, long double>			std_map(std_vec.begin(), std_vec.end());
			ft::map<t_lint, long double>::iterator	ft_it;
			std::map<t_lint, long double>::iterator	std_it;

			for (idx = 0U ; idx < g_lint_size && idx < g_long_double_size ; ++idx)
			{
				ft_it = ft_map.upper_bound(g_lint[idx]);
				std_it = std_map.upper_bound(g_lint[idx]);

				if ((ft_it == ft_map.end()) != (std_it == std_map.end()) ||
					(ft_it != ft_map.end() && (ft_it->first != std_it->first || --ft_it->second != --std_it->second)))
					return KO;
			}
		}
		// Constant access
		{
			ft::map<t_lint, long double> const				ft_map(ft_vec.begin(), ft_vec.end());
			std::map<t_lint, long double> const				std_map(std_vec.begin(), std_vec.end());
			ft::map<t_lint, long double>::const_iterator	ft_cit;
			std::map<t_lint, long double>::const_iterator	std_cit;

			for (idx = 0U ; idx < g_lint_size && idx < g_long_double_size ; ++idx)
			{
				ft_cit = ft_map.upper_bound(g_lint[idx]);
				std_cit = std_map.upper_bound(g_lint[idx]);

				if ((ft_cit == ft_map.end()) != (std_cit == std_map.end()) ||
					(ft_cit != ft_map.end() && (ft_cit->first != std_cit->first || ft_cit->second != std_cit->second)))
					return KO;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_equal_range(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		std::vector<ft::pair<t_hint, t_uint> >	ft_vec;
		std::vector<std::pair<t_hint, t_uint> >	std_vec;

		for (idx = 0U ; idx < g_hint_size && idx < g_uint_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<t_hint, t_uint>(g_hint[idx], g_uint[idx]));
			std_vec.push_back(std::pair<t_hint, t_uint>(g_hint[idx], g_uint[idx]));
		}

		// Mutable access
		{
			ft::map<t_hint, t_uint>					ft_map(ft_vec.begin(), ft_vec.end());
			std::map<t_hint, t_uint>				std_map(std_vec.begin(), std_vec.end());
			ft::pair<
				ft::map<t_hint, t_uint>::iterator,
				ft::map<t_hint, t_uint>::iterator>	ft_ret;
			std::pair<
				std::map<t_hint, t_uint>::iterator,
				std::map<t_hint, t_uint>::iterator>	std_ret;

			for (idx = 0U ; idx < g_hint_size && idx < g_uint_size ; ++idx)
			{
				ft_ret = ft_map.equal_range(g_hint[idx]);
				std_ret = std_map.equal_range(g_hint[idx]);

				if ((ft_ret.first == ft_map.end()) != (std_ret.first == std_map.end()) ||
					(ft_ret.first != ft_map.end() && (
						--ft_ret.first->second != --std_ret.first->second ||
						!std::equal(ft_ret.first, ft_ret.second, std_ret.first, __cmp<t_hint, t_uint>))))
					return KO;
			}
		}
		// Constant access
		{
			ft::map<t_hint, t_uint> const					ft_map(ft_vec.begin(), ft_vec.end());
			std::map<t_hint, t_uint> const					std_map(std_vec.begin(), std_vec.end());
			ft::pair<
				ft::map<t_hint, t_uint>::const_iterator,
				ft::map<t_hint, t_uint>::const_iterator>	ft_ret;
			std::pair<
				std::map<t_hint, t_uint>::const_iterator,
				std::map<t_hint, t_uint>::const_iterator>	std_ret;

			for (idx = 0U ; idx < g_hint_size && idx < g_uint_size ; ++idx)
			{
				ft_ret = ft_map.equal_range(g_hint[idx]);
				std_ret = std_map.equal_range(g_hint[idx]);

				if ((ft_ret.first == ft_map.end()) != (std_ret.first == std_map.end()) ||
					(ft_ret.first != ft_map.end() && (
						!std::equal(ft_ret.first, ft_ret.second, std_ret.first, __cmp<t_hint, t_uint>))))
					return KO;
			}
			
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_swap(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		std::vector<ft::pair<char, float> >		ft_vec;
		std::vector<std::pair<char, float> >	std_vec;

		for (idx = 0U ; idx < g_char_size && idx < g_float_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<char, float>(g_char[idx], g_float[idx]));
			std_vec.push_back(std::pair<char, float>(g_char[idx], g_float[idx]));
		}

		// Member function
		{
			// Swapping empty | empty
			{
				ft::map<char, float>					ft_map0;
				ft::map<char, float>					ft_map1;
				std::map<char, float>					std_map0;
				std::map<char, float>					std_map1;
				ft::map<char, float>::const_iterator	ft_cit0(ft_map0.begin());
				ft::map<char, float>::const_iterator	ft_cit1(ft_map1.begin());
				std::map<char, float>::const_iterator	std_cit0(std_map0.begin());
				std::map<char, float>::const_iterator	std_cit1(std_map1.begin());
				ft::map<char, float>::const_iterator	ft_cend0;
				ft::map<char, float>::const_iterator	ft_cend1;

				ft_map0.swap(ft_map1);
				std_map0.swap(std_map1);

				ft_cend0 = ft_map0.end();
				ft_cend1 = ft_map1.end();

				if (ft_map0.size() != std_map0.size() || ft_map1.size() != std_map1.size() ||
					!std::equal(ft_cit0, ft_cend1, std_cit0, __cmp<char, float>) ||
					!std::equal(ft_cit1, ft_cend0, std_cit1, __cmp<char, float>))
					return KO;
			}
			// Swapping empty | non-empty
			{
				ft::map<char, float>					ft_map0;
				ft::map<char, float>					ft_map1(&ft_vec[ft_vec.size() / 2], &ft_vec[ft_vec.size()]);
				std::map<char, float>					std_map0;
				std::map<char, float>					std_map1(&std_vec[std_vec.size() / 2], &std_vec[std_vec.size()]);
				ft::map<char, float>::const_iterator	ft_cit0(ft_map0.begin());
				ft::map<char, float>::const_iterator	ft_cit1(ft_map1.begin());
				std::map<char, float>::const_iterator	std_cit0(std_map0.begin());
				std::map<char, float>::const_iterator	std_cit1(std_map1.begin());
				ft::map<char, float>::const_iterator	ft_cend0;
				ft::map<char, float>::const_iterator	ft_cend1;

				ft_map0.swap(ft_map1);
				std_map0.swap(std_map1);

				ft_cend0 = ft_map0.end();
				ft_cend1 = ft_map1.end();

				if (ft_map0.size() != std_map0.size() || ft_map1.size() != std_map1.size() ||
					!std::equal(ft_cit0, ft_cend1, std_cit0, __cmp<char, float>) ||
					!std::equal(ft_cit1, ft_cend0, std_cit1, __cmp<char, float>))
					return KO;
			}
			// Swapping non-empty | empty
			{
				ft::map<char, float>					ft_map0(&ft_vec[0], &ft_vec[ft_vec.size() / 2]);
				ft::map<char, float>					ft_map1;
				std::map<char, float>					std_map0(&std_vec[0], &std_vec[std_vec.size() / 2]);
				std::map<char, float>					std_map1;
				ft::map<char, float>::const_iterator	ft_cit0(ft_map0.begin());
				ft::map<char, float>::const_iterator	ft_cit1(ft_map1.begin());
				std::map<char, float>::const_iterator	std_cit0(std_map0.begin());
				std::map<char, float>::const_iterator	std_cit1(std_map1.begin());
				ft::map<char, float>::const_iterator	ft_cend0;
				ft::map<char, float>::const_iterator	ft_cend1;

				ft_map0.swap(ft_map1);
				std_map0.swap(std_map1);

				ft_cend0 = ft_map0.end();
				ft_cend1 = ft_map1.end();

				if (ft_map0.size() != std_map0.size() || ft_map1.size() != std_map1.size() ||
					!std::equal(ft_cit0, ft_cend1, std_cit0, __cmp<char, float>) ||
					!std::equal(ft_cit1, ft_cend0, std_cit1, __cmp<char, float>))
					return KO;
			}
			// Swapping non-empty | non-empty
			{
				ft::map<char, float>					ft_map0(&ft_vec[0], &ft_vec[ft_vec.size() / 2]);
				ft::map<char, float>					ft_map1(&ft_vec[ft_vec.size() / 2], &ft_vec[ft_vec.size()]);
				std::map<char, float>					std_map0(&std_vec[0], &std_vec[std_vec.size() / 2]);
				std::map<char, float>					std_map1(&std_vec[std_vec.size() / 2], &std_vec[std_vec.size()]);
				ft::map<char, float>::const_iterator	ft_cit0(ft_map0.begin());
				ft::map<char, float>::const_iterator	ft_cit1(ft_map1.begin());
				std::map<char, float>::const_iterator	std_cit0(std_map0.begin());
				std::map<char, float>::const_iterator	std_cit1(std_map1.begin());
				ft::map<char, float>::const_iterator	ft_cend0;
				ft::map<char, float>::const_iterator	ft_cend1;

				ft_map0.swap(ft_map1);
				std_map0.swap(std_map1);

				ft_cend0 = ft_map0.end();
				ft_cend1 = ft_map1.end();

				if (ft_map0.size() != std_map0.size() || ft_map1.size() != std_map1.size() ||
					!std::equal(ft_cit0, ft_cend1, std_cit0, __cmp<char, float>) ||
					!std::equal(ft_cit1, ft_cend0, std_cit1, __cmp<char, float>))
					return KO;
			}
		}
		// Non-member function
		{
			// Swapping empty | empty
			{
				ft::map<char, float>					ft_map0;
				ft::map<char, float>					ft_map1;
				std::map<char, float>					std_map0;
				std::map<char, float>					std_map1;
				ft::map<char, float>::const_iterator	ft_cit0(ft_map0.begin());
				ft::map<char, float>::const_iterator	ft_cit1(ft_map1.begin());
				std::map<char, float>::const_iterator	std_cit0(std_map0.begin());
				std::map<char, float>::const_iterator	std_cit1(std_map1.begin());
				ft::map<char, float>::const_iterator	ft_cend0;
				ft::map<char, float>::const_iterator	ft_cend1;

				ft::swap(ft_map0, ft_map1);
				std::swap(std_map0, std_map1);

				ft_cend0 = ft_map0.end();
				ft_cend1 = ft_map1.end();

				if (ft_map0.size() != std_map0.size() || ft_map1.size() != std_map1.size() ||
					!std::equal(ft_cit0, ft_cend1, std_cit0, __cmp<char, float>) ||
					!std::equal(ft_cit1, ft_cend0, std_cit1, __cmp<char, float>))
					return KO;
			}
			// Swapping empty | non-empty
			{
				ft::map<char, float>					ft_map0;
				ft::map<char, float>					ft_map1(&ft_vec[ft_vec.size() / 2], &ft_vec[ft_vec.size()]);
				std::map<char, float>					std_map0;
				std::map<char, float>					std_map1(&std_vec[std_vec.size() / 2], &std_vec[std_vec.size()]);
				ft::map<char, float>::const_iterator	ft_cit0(ft_map0.begin());
				ft::map<char, float>::const_iterator	ft_cit1(ft_map1.begin());
				std::map<char, float>::const_iterator	std_cit0(std_map0.begin());
				std::map<char, float>::const_iterator	std_cit1(std_map1.begin());
				ft::map<char, float>::const_iterator	ft_cend0;
				ft::map<char, float>::const_iterator	ft_cend1;

				ft::swap(ft_map0, ft_map1);
				std::swap(std_map0, std_map1);

				ft_cend0 = ft_map0.end();
				ft_cend1 = ft_map1.end();

				if (ft_map0.size() != std_map0.size() || ft_map1.size() != std_map1.size() ||
					!std::equal(ft_cit0, ft_cend1, std_cit0, __cmp<char, float>) ||
					!std::equal(ft_cit1, ft_cend0, std_cit1, __cmp<char, float>))
					return KO;
			}
			// Swapping non-empty | empty
			{
				ft::map<char, float>					ft_map0(&ft_vec[0], &ft_vec[ft_vec.size() / 2]);
				ft::map<char, float>					ft_map1;
				std::map<char, float>					std_map0(&std_vec[0], &std_vec[std_vec.size() / 2]);
				std::map<char, float>					std_map1;
				ft::map<char, float>::const_iterator	ft_cit0(ft_map0.begin());
				ft::map<char, float>::const_iterator	ft_cit1(ft_map1.begin());
				std::map<char, float>::const_iterator	std_cit0(std_map0.begin());
				std::map<char, float>::const_iterator	std_cit1(std_map1.begin());
				ft::map<char, float>::const_iterator	ft_cend0;
				ft::map<char, float>::const_iterator	ft_cend1;

				ft::swap(ft_map0, ft_map1);
				std::swap(std_map0, std_map1);

				ft_cend0 = ft_map0.end();
				ft_cend1 = ft_map1.end();

				if (ft_map0.size() != std_map0.size() || ft_map1.size() != std_map1.size() ||
					!std::equal(ft_cit0, ft_cend1, std_cit0, __cmp<char, float>) ||
					!std::equal(ft_cit1, ft_cend0, std_cit1, __cmp<char, float>))
					return KO;
			}
			// Swapping non-empty | non-empty
			{
				ft::map<char, float>					ft_map0(&ft_vec[0], &ft_vec[ft_vec.size() / 2]);
				ft::map<char, float>					ft_map1(&ft_vec[ft_vec.size() / 2], &ft_vec[ft_vec.size()]);
				std::map<char, float>					std_map0(&std_vec[0], &std_vec[std_vec.size() / 2]);
				std::map<char, float>					std_map1(&std_vec[std_vec.size() / 2], &std_vec[std_vec.size()]);
				ft::map<char, float>::const_iterator	ft_cit0(ft_map0.begin());
				ft::map<char, float>::const_iterator	ft_cit1(ft_map1.begin());
				std::map<char, float>::const_iterator	std_cit0(std_map0.begin());
				std::map<char, float>::const_iterator	std_cit1(std_map1.begin());
				ft::map<char, float>::const_iterator	ft_cend0;
				ft::map<char, float>::const_iterator	ft_cend1;

				ft::swap(ft_map0, ft_map1);
				std::swap(std_map0, std_map1);

				ft_cend0 = ft_map0.end();
				ft_cend1 = ft_map1.end();

				if (ft_map0.size() != std_map0.size() || ft_map1.size() != std_map1.size() ||
					!std::equal(ft_cit0, ft_cend1, std_cit0, __cmp<char, float>) ||
					!std::equal(ft_cit1, ft_cend0, std_cit1, __cmp<char, float>))
					return KO;
			}
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
	t_uint	idx;

	title(__func__);
	try
	{
		std::vector<ft::pair<std::string, t_hhuint> >	ft_vec;
		std::vector<std::pair<std::string, t_hhuint> >	std_vec;

		for (idx = 0U ; idx < g_string_size && idx < g_hhuint_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<std::string, t_hhuint>(g_string[idx], g_hhuint[idx]));
			std_vec.push_back(std::pair<std::string, t_hhuint>(g_string[idx], g_hhuint[idx]));
		}

		// Assigning empty -> empty
		{
			ft::map<std::string, t_hhuint>			ft_map0;
			ft::map<std::string, t_hhuint> const	ft_map1;
			std::map<std::string, t_hhuint>			std_map0;
			std::map<std::string, t_hhuint> const	std_map1;

			ft_map0 = ft_map1;
			std_map0 = std_map1;

			if (ft_map0.size() != std_map0.size() ||
				!std::equal(ft_map0.begin(), ft_map0.end(), std_map0.begin(), __cmp<std::string, t_hhuint>))
				return KO;
		}
		// Assigning empty -> non-empty
		{
			ft::map<std::string, t_hhuint>			ft_map0(&ft_vec[0], &ft_vec[ft_vec.size() / 2]);
			ft::map<std::string, t_hhuint> const	ft_map1;
			std::map<std::string, t_hhuint>			std_map0(&std_vec[0], &std_vec[std_vec.size() / 2]);
			std::map<std::string, t_hhuint> const	std_map1;

			ft_map0 = ft_map1;
			std_map0 = std_map1;

			if (ft_map0.size() != std_map0.size() ||
				!std::equal(ft_map0.begin(), ft_map0.end(), std_map0.begin(), __cmp<std::string, t_hhuint>))
				return KO;
		}
		// Assigning non-empty -> empty
		{
			ft::map<std::string, t_hhuint>			ft_map0;
			ft::map<std::string, t_hhuint> const	ft_map1(&ft_vec[ft_vec.size() / 2], &ft_vec[ft_vec.size()]);
			std::map<std::string, t_hhuint>			std_map0;
			std::map<std::string, t_hhuint> const	std_map1(&std_vec[std_vec.size() / 2], &std_vec[std_vec.size()]);

			ft_map0 = ft_map1;
			std_map0 = std_map1;

			if (ft_map0.size() != std_map0.size() ||
				!std::equal(ft_map0.begin(), ft_map0.end(), std_map0.begin(), __cmp<std::string, t_hhuint>))
				return KO;
		}
		// Assigning non-empty -> non-empty
		{
			ft::map<std::string, t_hhuint>			ft_map0(&ft_vec[0], &ft_vec[ft_vec.size() / 2]);
			ft::map<std::string, t_hhuint> const	ft_map1(&ft_vec[ft_vec.size() / 2], &ft_vec[ft_vec.size()]);
			std::map<std::string, t_hhuint>			std_map0(&std_vec[0], &std_vec[std_vec.size() / 2]);
			std::map<std::string, t_hhuint> const	std_map1(&std_vec[std_vec.size() / 2], &std_vec[std_vec.size()]);

			ft_map0 = ft_map1;
			std_map0 = std_map1;

			if (ft_map0.size() != std_map0.size() ||
				!std::equal(ft_map0.begin(), ft_map0.end(), std_map0.begin(), __cmp<std::string, t_hhuint>))
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

inline static int	__test_operator_access(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		std::vector<ft::pair<int, long double> >	ft_vec;
		std::vector<std::pair<int, long double> >	std_vec;

		for (idx = 0U ; idx < g_int_size && idx < g_long_double_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<int, long double>(g_int[idx], g_long_double[idx]));
			std_vec.push_back(std::pair<int, long double>(g_int[idx], g_long_double[idx]));
		}

		ft::map<int, long double>	ft_map;
		std::map<int, long double>	std_map;

		for (idx = 0U ; idx < ft_vec.size() ; ++idx)
		{
			// Inserting
			{
				long double	&ft_ret = ft_map[ft_vec[idx].first];
				long double	&std_ret = std_map[std_vec[idx].first];

				if (ft_ret != std_ret || ft_map.size() != std_map.size() ||
					!std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), __cmp<int, long double>))
					return KO;

				ft_ret = ft_vec[idx].second;
				std_ret = std_vec[idx].second;

				if (ft_map.size() != std_map.size() ||
					!std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), __cmp<int, long double>))
					return KO;
			}
			// Finding
			{
				long double	&ft_ret = ft_map[ft_vec[idx].first];
				long double	&std_ret = std_map[std_vec[idx].first];

				if (ft_ret != std_ret || ft_map.size() != std_map.size() ||
					!std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), __cmp<int, long double>))
					return KO;

				ft_ret /= 3;
				std_ret /= 3;

				if (ft_map.size() != std_map.size() ||
					!std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), __cmp<int, long double>))
					return KO;
			}
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
		std::vector<ft::pair<t_hhint, t_luint> >	ft_vec;
		std::vector<std::pair<t_hhint, t_luint> >	std_vec;
		ft::map<t_hhint, t_luint>					ft_map0;
		ft::map<t_hhint, t_luint>					ft_map1;
		std::map<t_hhint, t_luint>					std_map0;
		std::map<t_hhint, t_luint>					std_map1;

		for (idx = 0U ; idx < g_hhint_size && idx < g_luint_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<t_hhint, t_luint>(g_hhint[idx], g_luint[idx]));
			std_vec.push_back(std::pair<t_hhint, t_luint>(g_hhint[idx], g_luint[idx]));
		}

		for (idx = 0U ; idx < ft_vec.size() && idx < std_vec.size() ; ++idx)
		{
			// Key difference
			{
				ft_map0[ft_vec[idx].first + 1] = ft_vec[idx].second;
				ft_map1[ft_vec[idx].first - 1] = ft_vec[idx].second;
				std_map0[std_vec[idx].first + 1] = std_vec[idx].second;
				std_map1[std_vec[idx].first - 1] = std_vec[idx].second;

				if (ft::operator==(ft_map0, ft_map1) != std::operator==(std_map0, std_map1))
					return KO;

				ft_map0.erase(ft_vec[idx].first + 1);
				ft_map1.erase(ft_vec[idx].first - 1);
				std_map0.erase(std_vec[idx].first + 1);
				std_map1.erase(std_vec[idx].first - 1);
				
			}
			// Mapped value difference
			{
				ft_map0[ft_vec[idx].first] = ft_vec[idx].second + 1;
				ft_map1[ft_vec[idx].first] = ft_vec[idx].second - 1;
				std_map0[std_vec[idx].first] = std_vec[idx].second + 1;
				std_map1[std_vec[idx].first] = std_vec[idx].second - 1;

				if (ft::operator==(ft_map0, ft_map1) != std::operator==(std_map0, std_map1))
					return KO;

				ft_map0.erase(ft_vec[idx].first);
				ft_map1.erase(ft_vec[idx].first);
				std_map0.erase(std_vec[idx].first);
				std_map1.erase(std_vec[idx].first);
			}
			// Size difference
			{
				ft_map0.insert(ft_vec[idx]);
				std_map0.insert(std_vec[idx]);

				if (ft::operator==(ft_map0, ft_map1) != std::operator==(std_map0, std_map1))
					return KO;
			}
			// Equivalence
			{
				ft_map1.insert(ft_vec[idx]);
				std_map1.insert(std_vec[idx]);

				if (ft::operator==(ft_map0, ft_map1) != std::operator==(std_map0, std_map1))
					return KO;
			}
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
		std::vector<ft::pair<t_hhint, t_luint> >	ft_vec;
		std::vector<std::pair<t_hhint, t_luint> >	std_vec;
		ft::map<t_hhint, t_luint>					ft_map0;
		ft::map<t_hhint, t_luint>					ft_map1;
		std::map<t_hhint, t_luint>					std_map0;
		std::map<t_hhint, t_luint>					std_map1;

		for (idx = 0U ; idx < g_hhint_size && idx < g_luint_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<t_hhint, t_luint>(g_hhint[idx], g_luint[idx]));
			std_vec.push_back(std::pair<t_hhint, t_luint>(g_hhint[idx], g_luint[idx]));
		}

		for (idx = 0U ; idx < ft_vec.size() && idx < std_vec.size() ; ++idx)
		{
			// Key difference
			{
				ft_map0[ft_vec[idx].first + 1] = ft_vec[idx].second;
				ft_map1[ft_vec[idx].first - 1] = ft_vec[idx].second;
				std_map0[std_vec[idx].first + 1] = std_vec[idx].second;
				std_map1[std_vec[idx].first - 1] = std_vec[idx].second;

				if (ft::operator!=(ft_map0, ft_map1) != std::operator!=(std_map0, std_map1))
					return KO;

				ft_map0.erase(ft_vec[idx].first + 1);
				ft_map1.erase(ft_vec[idx].first - 1);
				std_map0.erase(std_vec[idx].first + 1);
				std_map1.erase(std_vec[idx].first - 1);
				
			}
			// Mapped value difference
			{
				ft_map0[ft_vec[idx].first] = ft_vec[idx].second + 1;
				ft_map1[ft_vec[idx].first] = ft_vec[idx].second - 1;
				std_map0[std_vec[idx].first] = std_vec[idx].second + 1;
				std_map1[std_vec[idx].first] = std_vec[idx].second - 1;

				if (ft::operator!=(ft_map0, ft_map1) != std::operator!=(std_map0, std_map1))
					return KO;

				ft_map0.erase(ft_vec[idx].first);
				ft_map1.erase(ft_vec[idx].first);
				std_map0.erase(std_vec[idx].first);
				std_map1.erase(std_vec[idx].first);
			}
			// Size difference
			{
				ft_map0.insert(ft_vec[idx]);
				std_map0.insert(std_vec[idx]);

				if (ft::operator!=(ft_map0, ft_map1) != std::operator!=(std_map0, std_map1))
					return KO;
			}
			// Equivalence
			{
				ft_map1.insert(ft_vec[idx]);
				std_map1.insert(std_vec[idx]);

				if (ft::operator!=(ft_map0, ft_map1) != std::operator!=(std_map0, std_map1))
					return KO;
			}
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
		std::vector<ft::pair<t_hhint, t_luint> >	ft_vec;
		std::vector<std::pair<t_hhint, t_luint> >	std_vec;
		ft::map<t_hhint, t_luint>					ft_map0;
		ft::map<t_hhint, t_luint>					ft_map1;
		std::map<t_hhint, t_luint>					std_map0;
		std::map<t_hhint, t_luint>					std_map1;

		for (idx = 0U ; idx < g_hhint_size && idx < g_luint_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<t_hhint, t_luint>(g_hhint[idx], g_luint[idx]));
			std_vec.push_back(std::pair<t_hhint, t_luint>(g_hhint[idx], g_luint[idx]));
		}

		for (idx = 0U ; idx < ft_vec.size() && idx < std_vec.size() ; ++idx)
		{
			// Key difference
			{
				ft_map0[ft_vec[idx].first + 1] = ft_vec[idx].second;
				ft_map1[ft_vec[idx].first - 1] = ft_vec[idx].second;
				std_map0[std_vec[idx].first + 1] = std_vec[idx].second;
				std_map1[std_vec[idx].first - 1] = std_vec[idx].second;

				if (ft::operator<(ft_map0, ft_map1) != std::operator<(std_map0, std_map1))
					return KO;

				ft_map0.erase(ft_vec[idx].first + 1);
				ft_map1.erase(ft_vec[idx].first - 1);
				std_map0.erase(std_vec[idx].first + 1);
				std_map1.erase(std_vec[idx].first - 1);
				
			}
			// Mapped value difference
			{
				ft_map0[ft_vec[idx].first] = ft_vec[idx].second + 1;
				ft_map1[ft_vec[idx].first] = ft_vec[idx].second - 1;
				std_map0[std_vec[idx].first] = std_vec[idx].second + 1;
				std_map1[std_vec[idx].first] = std_vec[idx].second - 1;

				if (ft::operator<(ft_map0, ft_map1) != std::operator<(std_map0, std_map1))
					return KO;

				ft_map0.erase(ft_vec[idx].first);
				ft_map1.erase(ft_vec[idx].first);
				std_map0.erase(std_vec[idx].first);
				std_map1.erase(std_vec[idx].first);
			}
			// Size difference
			{
				ft_map0.insert(ft_vec[idx]);
				std_map0.insert(std_vec[idx]);

				if (ft::operator<(ft_map0, ft_map1) != std::operator<(std_map0, std_map1))
					return KO;
			}
			// Equivalence
			{
				ft_map1.insert(ft_vec[idx]);
				std_map1.insert(std_vec[idx]);

				if (ft::operator<(ft_map0, ft_map1) != std::operator<(std_map0, std_map1))
					return KO;
			}
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
		std::vector<ft::pair<t_hhint, t_luint> >	ft_vec;
		std::vector<std::pair<t_hhint, t_luint> >	std_vec;
		ft::map<t_hhint, t_luint>					ft_map0;
		ft::map<t_hhint, t_luint>					ft_map1;
		std::map<t_hhint, t_luint>					std_map0;
		std::map<t_hhint, t_luint>					std_map1;

		for (idx = 0U ; idx < g_hhint_size && idx < g_luint_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<t_hhint, t_luint>(g_hhint[idx], g_luint[idx]));
			std_vec.push_back(std::pair<t_hhint, t_luint>(g_hhint[idx], g_luint[idx]));
		}

		for (idx = 0U ; idx < ft_vec.size() && idx < std_vec.size() ; ++idx)
		{
			// Key difference
			{
				ft_map0[ft_vec[idx].first + 1] = ft_vec[idx].second;
				ft_map1[ft_vec[idx].first - 1] = ft_vec[idx].second;
				std_map0[std_vec[idx].first + 1] = std_vec[idx].second;
				std_map1[std_vec[idx].first - 1] = std_vec[idx].second;

				if (ft::operator>(ft_map0, ft_map1) != std::operator>(std_map0, std_map1))
					return KO;

				ft_map0.erase(ft_vec[idx].first + 1);
				ft_map1.erase(ft_vec[idx].first - 1);
				std_map0.erase(std_vec[idx].first + 1);
				std_map1.erase(std_vec[idx].first - 1);
				
			}
			// Mapped value difference
			{
				ft_map0[ft_vec[idx].first] = ft_vec[idx].second + 1;
				ft_map1[ft_vec[idx].first] = ft_vec[idx].second - 1;
				std_map0[std_vec[idx].first] = std_vec[idx].second + 1;
				std_map1[std_vec[idx].first] = std_vec[idx].second - 1;

				if (ft::operator>(ft_map0, ft_map1) != std::operator>(std_map0, std_map1))
					return KO;

				ft_map0.erase(ft_vec[idx].first);
				ft_map1.erase(ft_vec[idx].first);
				std_map0.erase(std_vec[idx].first);
				std_map1.erase(std_vec[idx].first);
			}
			// Size difference
			{
				ft_map0.insert(ft_vec[idx]);
				std_map0.insert(std_vec[idx]);

				if (ft::operator>(ft_map0, ft_map1) != std::operator>(std_map0, std_map1))
					return KO;
			}
			// Equivalence
			{
				ft_map1.insert(ft_vec[idx]);
				std_map1.insert(std_vec[idx]);

				if (ft::operator>(ft_map0, ft_map1) != std::operator>(std_map0, std_map1))
					return KO;
			}
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
		std::vector<ft::pair<t_hhint, t_luint> >	ft_vec;
		std::vector<std::pair<t_hhint, t_luint> >	std_vec;
		ft::map<t_hhint, t_luint>					ft_map0;
		ft::map<t_hhint, t_luint>					ft_map1;
		std::map<t_hhint, t_luint>					std_map0;
		std::map<t_hhint, t_luint>					std_map1;

		for (idx = 0U ; idx < g_hhint_size && idx < g_luint_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<t_hhint, t_luint>(g_hhint[idx], g_luint[idx]));
			std_vec.push_back(std::pair<t_hhint, t_luint>(g_hhint[idx], g_luint[idx]));
		}

		for (idx = 0U ; idx < ft_vec.size() && idx < std_vec.size() ; ++idx)
		{
			// Key difference
			{
				ft_map0[ft_vec[idx].first + 1] = ft_vec[idx].second;
				ft_map1[ft_vec[idx].first - 1] = ft_vec[idx].second;
				std_map0[std_vec[idx].first + 1] = std_vec[idx].second;
				std_map1[std_vec[idx].first - 1] = std_vec[idx].second;

				if (ft::operator<=(ft_map0, ft_map1) != std::operator<=(std_map0, std_map1))
					return KO;

				ft_map0.erase(ft_vec[idx].first + 1);
				ft_map1.erase(ft_vec[idx].first - 1);
				std_map0.erase(std_vec[idx].first + 1);
				std_map1.erase(std_vec[idx].first - 1);
				
			}
			// Mapped value difference
			{
				ft_map0[ft_vec[idx].first] = ft_vec[idx].second + 1;
				ft_map1[ft_vec[idx].first] = ft_vec[idx].second - 1;
				std_map0[std_vec[idx].first] = std_vec[idx].second + 1;
				std_map1[std_vec[idx].first] = std_vec[idx].second - 1;

				if (ft::operator<=(ft_map0, ft_map1) != std::operator<=(std_map0, std_map1))
					return KO;

				ft_map0.erase(ft_vec[idx].first);
				ft_map1.erase(ft_vec[idx].first);
				std_map0.erase(std_vec[idx].first);
				std_map1.erase(std_vec[idx].first);
			}
			// Size difference
			{
				ft_map0.insert(ft_vec[idx]);
				std_map0.insert(std_vec[idx]);

				if (ft::operator<=(ft_map0, ft_map1) != std::operator<=(std_map0, std_map1))
					return KO;
			}
			// Equivalence
			{
				ft_map1.insert(ft_vec[idx]);
				std_map1.insert(std_vec[idx]);

				if (ft::operator<=(ft_map0, ft_map1) != std::operator<=(std_map0, std_map1))
					return KO;
			}
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
		std::vector<ft::pair<t_hhint, t_luint> >	ft_vec;
		std::vector<std::pair<t_hhint, t_luint> >	std_vec;
		ft::map<t_hhint, t_luint>					ft_map0;
		ft::map<t_hhint, t_luint>					ft_map1;
		std::map<t_hhint, t_luint>					std_map0;
		std::map<t_hhint, t_luint>					std_map1;

		for (idx = 0U ; idx < g_hhint_size && idx < g_luint_size ; ++idx)
		{
			ft_vec.push_back(ft::pair<t_hhint, t_luint>(g_hhint[idx], g_luint[idx]));
			std_vec.push_back(std::pair<t_hhint, t_luint>(g_hhint[idx], g_luint[idx]));
		}

		for (idx = 0U ; idx < ft_vec.size() && idx < std_vec.size() ; ++idx)
		{
			// Key difference
			{
				ft_map0[ft_vec[idx].first + 1] = ft_vec[idx].second;
				ft_map1[ft_vec[idx].first - 1] = ft_vec[idx].second;
				std_map0[std_vec[idx].first + 1] = std_vec[idx].second;
				std_map1[std_vec[idx].first - 1] = std_vec[idx].second;

				if (ft::operator>=(ft_map0, ft_map1) != std::operator>=(std_map0, std_map1))
					return KO;

				ft_map0.erase(ft_vec[idx].first + 1);
				ft_map1.erase(ft_vec[idx].first - 1);
				std_map0.erase(std_vec[idx].first + 1);
				std_map1.erase(std_vec[idx].first - 1);
				
			}
			// Mapped value difference
			{
				ft_map0[ft_vec[idx].first] = ft_vec[idx].second + 1;
				ft_map1[ft_vec[idx].first] = ft_vec[idx].second - 1;
				std_map0[std_vec[idx].first] = std_vec[idx].second + 1;
				std_map1[std_vec[idx].first] = std_vec[idx].second - 1;

				if (ft::operator>=(ft_map0, ft_map1) != std::operator>=(std_map0, std_map1))
					return KO;

				ft_map0.erase(ft_vec[idx].first);
				ft_map1.erase(ft_vec[idx].first);
				std_map0.erase(std_vec[idx].first);
				std_map1.erase(std_vec[idx].first);
			}
			// Size difference
			{
				ft_map0.insert(ft_vec[idx]);
				std_map0.insert(std_vec[idx]);

				if (ft::operator>=(ft_map0, ft_map1) != std::operator>=(std_map0, std_map1))
					return KO;
			}
			// Equivalence
			{
				ft_map1.insert(ft_vec[idx]);
				std_map1.insert(std_vec[idx]);

				if (ft::operator>=(ft_map0, ft_map1) != std::operator>=(std_map0, std_map1))
					return KO;
			}
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
		__test_function_key_comp,
		__test_function_value_comp,
		__test_function_size,
		__test_function_empty,
		__test_function_begin,
		__test_function_end,
		__test_function_rbegin,
		__test_function_rend,
		__test_type_iterator,
		__test_type_const_iterator,
		__test_type_reverse_iterator,
		__test_type_const_reverse_iterator,
		__test_function_insert,
		__test_function_erase,
		__test_function_clear,
		__test_function_find,
		__test_function_count,
		__test_function_lower_bound,
		__test_function_upper_bound,
		__test_function_equal_range,
		__test_function_swap,
		__test_operator_assign,
		__test_operator_access,
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
