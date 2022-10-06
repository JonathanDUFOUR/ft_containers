/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:06:05 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/06 08:45:50 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <set>
#include "arrays.hpp"
#include "tester.hpp"
#include "set.hpp"
#include "iterator/requirements_check.tpp"
#include "iterator/restrictor/random_access_iterator_restrictor.tpp"
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
			ft::set<int> const	ft_set;
			std::set<int> const	std_set;

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

inline static int	__test_type_key_type(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint>	set_type;

		if (!ft::is_same<set_type::key_type, t_lint>::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_value_type(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint>	set_type;

		if (!ft::is_same<set_type::value_type, t_lint>::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_key_compare(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint, std::less<int> >	set_type;

		if (!ft::is_same<set_type::key_compare, std::less<int> >::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_value_compare(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint, std::less<int> >	set_type;

		if (!ft::is_same<set_type::value_compare, std::less<int> >::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_allocator_type(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint, std::less<int>, std::allocator<char> >	set_type;

		if (!ft::is_same<set_type::allocator_type, std::allocator<char> >::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_reference(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint, std::less<int>, std::allocator<char> >	set_type;

		if (!ft::is_same<set_type::reference, std::allocator<char>::reference >::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_const_reference(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint, std::less<int>, std::allocator<char> >	set_type;

		if (!ft::is_same<set_type::const_reference, std::allocator<char>::const_reference >::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_pointer(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint, std::less<int>, std::allocator<char> >	set_type;

		if (!ft::is_same<set_type::pointer, std::allocator<char>::pointer >::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_const_pointer(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint, std::less<int>, std::allocator<char> >	set_type;

		if (!ft::is_same<set_type::const_pointer, std::allocator<char>::const_pointer >::value)
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

inline static int	__test_function_size(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_huint_size ; ++idx)
		{
			ft::set<t_huint> const	ft_set(&g_huint[idx], &g_huint[g_huint_size]);
			std::set<t_huint> const	std_set(&g_huint[idx], &g_huint[g_huint_size]);

			if (ft_set.size() != std_set.size())
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

inline static int	__test_function_empty(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_uint_size ; ++idx)
		{
			ft::set<t_uint> const	ft_set(&g_uint[idx * (idx % 2)], &g_uint[idx]);
			std::set<t_uint> const	std_set(&g_uint[idx * (idx % 2)], &g_uint[idx]);

			if (ft_set.empty() != std_set.empty())
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
		// Mutable access
		{
			ft::set<char>::iterator		ft_it;
			std::set<char>::iterator	std_it;

			for (idx = 1U ; idx < g_char_size ; ++idx)
			{
				ft::set<char>	ft_set(&g_char[idx - 1], &g_char[g_char_size]);
				std::set<char>	std_set(&g_char[idx - 1], &g_char[g_char_size]);

				ft_it = ft_set.begin();
				std_it = std_set.begin();

				if (!!ft_it.base() != !!std_it._M_node)
					ret = ISO_OK;
				if (*ft_it != *std_it)
					return KO;
			}

			ft::set<char>	ft_set;
			std::set<char>	std_set;

			ft_it = ft_set.begin();
			std_it = std_set.begin();

			if (!!ft_it.base() != !!std_it._M_node)
				ret = ISO_OK;
		}
		// Constant access
		{
			ft::set<char>::const_iterator	ft_cit;
			std::set<char>::const_iterator	std_cit;

			for (idx = 1U ; idx < g_char_size ; ++idx)
			{
				ft::set<char> const		ft_set(&g_char[idx - 1], &g_char[g_char_size]);
				std::set<char> const	std_set(&g_char[idx - 1], &g_char[g_char_size]);

				ft_cit = ft_set.begin();
				std_cit = std_set.begin();

				if (!!ft_cit.base() != !!std_cit._M_node)
					ret = ISO_OK;
				if (*ft_cit != *std_cit)
					return KO;
			}

			ft::set<char> const		ft_set;
			std::set<char> const	std_set;

			ft_cit = ft_set.begin();
			std_cit = std_set.begin();

			if (!!ft_cit.base() != !!std_cit._M_node)
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
		// Mutable access
		{
			ft::set<char>::iterator		ft_it;
			std::set<char>::iterator	std_it;

			for (idx = 1U ; idx < g_char_size ; ++idx)
			{
				ft::set<char>	ft_set(&g_char[0], &g_char[idx]);
				std::set<char>	std_set(&g_char[0], &g_char[idx]);

				ft_it = ft_set.end();
				std_it = std_set.end();

				if (!!ft_it.base() != !!std_it._M_node)
					ret = ISO_OK;

				--ft_it;
				--std_it;

				if (*ft_it != *std_it)
					return KO;
			}

			ft::set<char>	ft_set;
			std::set<char>	std_set;

			ft_it = ft_set.end();
			std_it = std_set.end();

			if (!!ft_it.base() != !!std_it._M_node)
				ret = ISO_OK;
		}
		// Constant access
		{
			ft::set<char>::const_iterator	ft_cit;
			std::set<char>::const_iterator	std_cit;

			for (idx = 1U ; idx < g_char_size ; ++idx)
			{
				ft::set<char> const		ft_set(&g_char[0], &g_char[idx]);
				std::set<char> const	std_set(&g_char[0], &g_char[idx]);

				ft_cit = ft_set.end();
				std_cit = std_set.end();

				if (!!ft_cit.base() != !!std_cit._M_node)
					ret = ISO_OK;

				--ft_cit;
				--std_cit;

				if (*ft_cit != *std_cit)
					return KO;
			}

			ft::set<char> const		ft_set;
			std::set<char> const	std_set;

			ft_cit = ft_set.end();
			std_cit = std_set.end();

			if (!!ft_cit.base() != !!std_cit._M_node)
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
		// Mutable access
		{
			ft::set<char>::reverse_iterator		ft_rit;
			std::set<char>::reverse_iterator	std_rit;

			for (idx = 1U ; idx < g_char_size ; ++idx)
			{
				ft::set<char>	ft_set(&g_char[idx - 1], &g_char[g_char_size]);
				std::set<char>	std_set(&g_char[idx - 1], &g_char[g_char_size]);

				ft_rit = ft_set.rbegin();
				std_rit = std_set.rbegin();

				if (!!ft_rit.base().base() != !!std_rit.base()._M_node)
					ret = ISO_OK;
				if (*ft_rit != *std_rit)
					return KO;
			}

			ft::set<char>	ft_set;
			std::set<char>	std_set;

			ft_rit = ft_set.rbegin();
			std_rit = std_set.rbegin();

			if (!!ft_rit.base().base() != !!std_rit.base()._M_node)
				ret = ISO_OK;
		}
		// Constant access
		{
			ft::set<char>::const_reverse_iterator	ft_crit;
			std::set<char>::const_reverse_iterator	std_crit;

			for (idx = 1U ; idx < g_char_size ; ++idx)
			{
				ft::set<char> const		ft_set(&g_char[idx - 1], &g_char[g_char_size]);
				std::set<char> const	std_set(&g_char[idx - 1], &g_char[g_char_size]);

				ft_crit = ft_set.rbegin();
				std_crit = std_set.rbegin();

				if (!!ft_crit.base().base() != !!std_crit.base()._M_node)
					ret = ISO_OK;
				if (*ft_crit != *std_crit)
					return KO;
			}

			ft::set<char> const		ft_set;
			std::set<char> const	std_set;

			ft_crit = ft_set.rbegin();
			std_crit = std_set.rbegin();

			if (!!ft_crit.base().base() != !!std_crit.base()._M_node)
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
		// Mutable access
		{
			ft::set<char>::reverse_iterator		ft_rit;
			std::set<char>::reverse_iterator	std_rit;

			for (idx = 1U ; idx < g_char_size ; ++idx)
			{
				ft::set<char>	ft_set(&g_char[0], &g_char[idx]);
				std::set<char>	std_set(&g_char[0], &g_char[idx]);

				ft_rit = ft_set.rend();
				std_rit = std_set.rend();

				if (!!ft_rit.base().base() != !!std_rit.base()._M_node)
					ret = ISO_OK;

				--ft_rit;
				--std_rit;

				if (*ft_rit != *std_rit)
					return KO;
			}

			ft::set<char>	ft_set;
			std::set<char>	std_set;

			ft_rit = ft_set.rend();
			std_rit = std_set.rend();

			if (!!ft_rit.base().base() != !!std_rit.base()._M_node)
				ret = ISO_OK;
		}
		// Constant access
		{
			ft::set<char>::const_reverse_iterator	ft_crit;
			std::set<char>::const_reverse_iterator	std_crit;

			for (idx = 1U ; idx < g_char_size ; ++idx)
			{
				ft::set<char> const		ft_set(&g_char[0], &g_char[idx]);
				std::set<char> const	std_set(&g_char[0], &g_char[idx]);

				ft_crit = ft_set.rend();
				std_crit = std_set.rend();

				if (!!ft_crit.base().base() != !!std_crit.base()._M_node)
					ret = ISO_OK;

				--ft_crit;
				--std_crit;

				if (*ft_crit != *std_crit)
					return KO;
			}

			ft::set<char> const		ft_set;
			std::set<char> const	std_set;

			ft_crit = ft_set.rend();
			std_crit = std_set.rend();

			if (!!ft_crit.base().base() != !!std_crit.base()._M_node)
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
		ft::set<float>				ft_set(&g_float[0], &g_float[g_float_size]);
		std::set<float>				std_set(&g_float[0], &g_float[g_float_size]);
		ft::set<float>::iterator	ft_it;
		std::set<float>::iterator	std_it;

		if (sizeof(ft_it) != sizeof(std_it))
			ret = ISO_OK;

		for (ft_it = ft_set.begin(), std_it = std_set.begin(), idx = 0U ;
			ft_it != ft_set.end() && std_it != std_set.end() ;
			++ft_it, ++std_it, ++idx)
		{
			if (idx)
			{
				BidirectionalIteratorCheck(ft_it);
				BidirectionalIteratorCheck(std_it);
			}

			if (*ft_it != *std_it)
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
		ft::set<float> const			ft_set(&g_float[0], &g_float[g_float_size]);
		std::set<float> const			std_set(&g_float[0], &g_float[g_float_size]);
		ft::set<float>::const_iterator	ft_cit;
		std::set<float>::const_iterator	std_cit;

		if (sizeof(ft_cit) != sizeof(std_cit))
			ret = ISO_OK;

		for (ft_cit = ft_set.begin(), std_cit = std_set.begin(), idx = 0U ;
			ft_cit != ft_set.end() && std_cit != std_set.end() ;
			++ft_cit, ++std_cit)
		{
			if (idx)
			{
				BidirectionalIteratorCheck(ft_cit);
				BidirectionalIteratorCheck(std_cit);
			}

			if (*ft_cit != *std_cit)
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
		ft::set<float>						ft_set(&g_float[0], &g_float[g_float_size]);
		std::set<float>						std_set(&g_float[0], &g_float[g_float_size]);
		ft::set<float>::reverse_iterator	ft_rit;
		std::set<float>::reverse_iterator	std_it;

		if (sizeof(ft_rit) != sizeof(std_it))
			ret = ISO_OK;

		for (ft_rit = ft_set.rbegin(), std_it = std_set.rbegin(), idx = 0U ;
			ft_rit != ft_set.rend() && std_it != std_set.rend() ;
			++ft_rit, ++std_it, ++idx)
		{
			if (idx)
			{
				BidirectionalIteratorCheck(ft_rit);
				BidirectionalIteratorCheck(std_it);
			}

			if (*ft_rit != *std_it)
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
		ft::set<float> const					ft_set(&g_float[0], &g_float[g_float_size]);
		std::set<float> const					std_set(&g_float[0], &g_float[g_float_size]);
		ft::set<float>::const_reverse_iterator	ft_crit;
		std::set<float>::const_reverse_iterator	std_crit;

		if (sizeof(ft_crit) != sizeof(std_crit))
			ret = ISO_OK;

		for (ft_crit = ft_set.rbegin(), std_crit = std_set.rbegin(), idx = 0U ;
			ft_crit != ft_set.rend() && std_crit != std_set.rend() ;
			++ft_crit, ++std_crit)
		{
			if (idx)
			{
				BidirectionalIteratorCheck(ft_crit);
				BidirectionalIteratorCheck(std_crit);
			}

			if (*ft_crit != *std_crit)
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

int	test_set(void)
{
	t_test const	tests[] = {
		__test_constructor,
		__test_type_key_type,
		__test_type_value_type,
		__test_type_key_compare,
		__test_type_value_compare,
		__test_type_allocator_type,
		__test_type_reference,
		__test_type_const_reference,
		__test_type_pointer,
		__test_type_const_pointer,
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
