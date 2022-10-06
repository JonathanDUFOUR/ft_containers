/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:36:04 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/06 10:18:33 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "arrays.hpp"
#include "iterator/requirements_check.tpp"
#include "iterator/restrictor/random_access_iterator_restrictor.tpp"
#include "tester.hpp"
#include "utility.hpp"
#include "vector.hpp"
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
			ft::vector<int> const	ft_vec;
			std::vector<int> const	std_vec;

			if (sizeof(ft_vec) != sizeof(std_vec) || memcmp(&ft_vec, &std_vec, sizeof(ft_vec)))
				ret = ISO_OK;
		}
		// Fill constructor
		// Trivially copyable
		{
			// Non-null size | default value
			{
				ft::vector<char> const	ft_vec(21LU);
				std::vector<char> const	std_vec(21LU);

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Null size | defined value
			{
				ft::vector<char> const	ft_vec(0LU, 'A');
				std::vector<char> const	std_vec(0LU, 'A');

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Non-null size | defined value
			{
				ft::vector<char> const	ft_vec(42LU, 42);
				std::vector<char> const	std_vec(42LU, 42);

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
		}
		// Fill constructor
		// Trivially copyable
		// Ambiguous
		{
			// Non-null size | default value
			{
				ft::vector<char> const	ft_vec(static_cast<char>(21LU));
				std::vector<char> const	std_vec(static_cast<char>(21LU));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Null size | defined value
			{
				ft::vector<char> const	ft_vec(static_cast<char>(0LU), 'A');
				std::vector<char> const	std_vec(static_cast<char>(0LU), 'A');

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Non-null size | defined value
			{
				ft::vector<char> const	ft_vec(static_cast<char>(42LU), 42);
				std::vector<char> const	std_vec(static_cast<char>(42LU), 42);

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
		}
		// Fill constructor
		// Non-trivial copy required
		{
			// Non-null size | default value
			{
				ft::vector<std::string> const	ft_vec(21LU);
				std::vector<std::string> const	std_vec(21LU);

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Null size | defined value
			{
				ft::vector<std::string> const	ft_vec(0LU, std::string("pouic"));
				std::vector<std::string> const	std_vec(0LU, std::string("pouic"));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Non-null size | defined value
			{
				ft::vector<std::string> const	ft_vec(42LU, std::string("Hello World !"));
				std::vector<std::string> const	std_vec(42LU, std::string("Hello World !"));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
		}
		// Range constructor
		// Trivially copyable
		{
			// Range of input_iterator_restrictor
			{
				ft::input_iterator_restrictor<t_huint const *> const	it0(&g_huint[0]);
				ft::input_iterator_restrictor<t_huint const *> const	it1(&g_huint[0]);
				ft::vector<t_huint> const								ft_vec(it0, it1);
				std::vector<t_huint> const								std_vec(it0, it1);

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Range of forward_iterator_restrictor
			{
				ft::forward_iterator_restrictor<void const *const *> const	it;
				ft::vector<void const *> const								ft_vec(it, it);
				std::vector<void const *> const								std_vec(it, it);

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Range of random_access_iterator_restrictor
			{
				ft::random_access_iterator_restrictor<t_huint const *> const	it0(&g_huint[0]);
				ft::random_access_iterator_restrictor<t_huint const *> const	it1(&g_huint[g_huint_size]);
				ft::vector<t_huint> const										ft_vec(it0, it1);
				std::vector<t_huint> const										std_vec(it0, it1);

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Range of char const *
			{
				ft::vector<char> const	ft_vec(g_char, &g_char[g_char_size]);
				std::vector<char> const	std_vec(g_char, &g_char[g_char_size]);

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
		}
		// Range constructor
		// Non-trivial copy required
		{
			// Range of input_iterator_restrictor
			{
				ft::input_iterator_restrictor<std::string const *> const	it0(&g_string[0]);
				ft::input_iterator_restrictor<std::string const *> const	it1(&g_string[0]);
				ft::vector<std::string> const								ft_vec(it0, it1);
				std::vector<std::string> const								std_vec(it0, it1);

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Range of forward_iterator_restrictor
			{
				ft::forward_iterator_restrictor<std::string const *> const	it0;
				ft::forward_iterator_restrictor<std::string const *> const	it1;
				ft::vector<std::string> const								ft_vec(it0, it1);
				std::vector<std::string> const								std_vec(it0, it1);

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Range of random_access_iterator_restrictor
			{
				ft::random_access_iterator_restrictor<std::string const *> const	it0(&g_string[0]);
				ft::random_access_iterator_restrictor<std::string const *> const	it1(&g_string[g_string_size]);
				ft::vector<std::string> const										ft_vec(it0, it1);
				std::vector<std::string> const										std_vec(it0, it1);

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Range of std::string const *
			{
				ft::vector<std::string> const	ft_vec(&g_string[0], &g_string[g_string_size]);
				std::vector<std::string> const	std_vec(&g_string[0], &g_string[g_string_size]);

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
		}
		// Range constructor
		// Trivially copyable
		// Force naive iteration along the range
		{
			std::ifstream						ifs0(g_file[g_file_size - 1]);
			std::ifstream						ifs1(g_file[g_file_size - 1]);
			std::istream_iterator<char> const	it0(ifs0);
			std::istream_iterator<char> const	it1(ifs1);
			std::istream_iterator<char> const	end_of_stream;
			ft::vector<char> const				ft_vec(it0, end_of_stream);
			std::vector<char> const				std_vec(it1, end_of_stream);

			if (sizeof(ft_vec) != sizeof(std_vec))
				ret = ISO_OK;
		}
		// Copy constructor
		// Trivially copyable
		{
			// Default vector
			{
				ft::vector<t_huint> const	ft_vec0;
				ft::vector<t_huint> const	ft_vec1(ft_vec0);
				std::vector<t_huint> const	std_vec0;
				std::vector<t_huint> const	std_vec1(std_vec0);

				if (sizeof(ft_vec1) != sizeof(std_vec1))
					ret = ISO_OK;
			}
			// Filled vector
			{
				ft::forward_iterator_restrictor<t_huint const *> const	it0(&g_huint[0]);
				ft::forward_iterator_restrictor<t_huint const *> const	it1(&g_huint[g_huint_size]);
				ft::vector<t_huint> const								ft_vec0(it0, it1);
				ft::vector<t_huint> const								ft_vec1(ft_vec0);
				std::vector<t_huint> const								std_vec0(it0, it1);
				std::vector<t_huint> const								std_vec1(std_vec0);

				if (sizeof(ft_vec1) != sizeof(std_vec1))
					ret = ISO_OK;
			}
		}
		// Copy constructor
		// Non-trivial copy required
		{
			// Default vector
			{
				ft::vector<std::string> const	ft_vec0;
				ft::vector<std::string> const	ft_vec1(ft_vec0);
				std::vector<std::string> const	std_vec0;
				std::vector<std::string> const	std_vec1(std_vec0);

				if (sizeof(ft_vec1) != sizeof(std_vec1))
					ret = ISO_OK;
			}
			// Filled vector
			{
				ft::forward_iterator_restrictor<std::string const *> const	it0(&g_string[0]);
				ft::forward_iterator_restrictor<std::string const *> const	it1(&g_string[g_string_size]);
				ft::vector<std::string> const								ft_vec0(it0, it1);
				ft::vector<std::string> const								ft_vec1(ft_vec0);
				std::vector<std::string> const								std_vec0(it0, it1);
				std::vector<std::string> const								std_vec1(std_vec0);

				if (sizeof(ft_vec1) != sizeof(std_vec1))
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

inline static int	__test_default_template_type_Alloc(void)
{
	title(__func__);

	typedef ft::vector<float>							vec_type_0;
	typedef ft::vector<float, std::allocator<float> >	vec_type_1;

	if (!is_same<vec_type_0, vec_type_1>::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_type_value_type(void)
{
	title(__func__);

	typedef ft::vector<t_lint, std::allocator<t_lint> >	vec_type;

	if (!is_same<vec_type::value_type, t_lint>::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_type_allocator_type(void)
{
	title(__func__);

	typedef ft::vector<t_lint, std::allocator<t_lint> >	vec_type;

	if (!is_same<vec_type::allocator_type, std::allocator<t_lint> >::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_type_reference(void)
{
	title(__func__);

	typedef ft::vector<t_lint, std::allocator<t_lint> >	vec_type;

	if (!is_same<vec_type::reference, std::allocator<t_lint>::reference>::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_type_const_reference(void)
{
	title(__func__);

	typedef ft::vector<t_lint, std::allocator<t_lint> >	vec_type;

	if (!is_same<vec_type::const_reference, std::allocator<t_lint>::const_reference>::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_type_pointer(void)
{
	title(__func__);

	typedef ft::vector<t_lint, std::allocator<t_lint> >	vec_type;

	if (!is_same<vec_type::pointer, std::allocator<t_lint>::pointer>::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_type_const_pointer(void)
{
	title(__func__);

	typedef ft::vector<t_lint, std::allocator<t_lint> >	vec_type;

	if (!is_same<vec_type::const_pointer, std::allocator<t_lint>::const_pointer>::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_function_get_allocator(void)
{
	title(__func__);
	try
	{
		ft::vector<char> const	ft_vec;
		std::vector<char> const	std_vec;

		if (ft_vec.get_allocator() != std_vec.get_allocator())
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
		ft::vector<t_hhint> const							ft_vec0;
		ft::vector<t_uint> const							ft_vec1;
		ft::vector<std::pair<long double, t_lint> > const	ft_vec2;
		std::vector<t_hhint> const							std_vec0;
		std::vector<t_uint> const							std_vec1;
		std::vector<std::pair<long double, t_lint> > const	std_vec2;

		if (ft_vec0.max_size() != std_vec0.max_size() || ft_vec1.max_size() != std_vec1.max_size() ||
			ft_vec2.max_size() != std_vec2.max_size())
			ret = ISO_OK;
		if ((ft_vec0.max_size() < ft_vec1.max_size()) != (std_vec0.max_size() < std_vec1.max_size()) ||
			(ft_vec0.max_size() < ft_vec2.max_size()) != (std_vec0.max_size() < std_vec2.max_size()) ||
			(ft_vec1.max_size() < ft_vec2.max_size()) != (std_vec1.max_size() < std_vec2.max_size()))
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_function_capacity(void)
{
	int		ret;
	size_t	n;

	title(__func__);
	ret = IMP_OK;
	try
	{
		for (n = 0LU ; n < 10LU ; ++n)
		{
			ft::vector<float> const		ft_vec(n, 3.14f);
			std::vector<float> const	std_vec(n, 3.14f);

			if (ft_vec.capacity() != std_vec.capacity())
			{
				if (ft_vec.capacity() < n)
					return KO;
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

inline static int	__test_function_size(void)
{
	size_t	n;

	title(__func__);
	try
	{
		for (n = 0LU ; n < 10LU ; ++n)
		{
			ft::vector<t_hhuint> const	ft_vec(n, 42U);
			std::vector<t_hhuint> const	std_vec(n, 42U);

			if (ft_vec.size() != std_vec.size())
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
	size_t	n;

	title(__func__);
	try
	{
		for (n = 0LU ; n < 10LU ; ++n)
		{
			ft::vector<std::string> const	ft_vec(n * (n % 2), std::string("Hello World"));
			std::vector<std::string> const	std_vec(n * (n % 2), std::string("Hello World"));

			if (ft_vec.empty() != std_vec.empty())
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

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::vector<char>::iterator	ft_it;
			std::vector<char>::iterator	std_it;

			for (idx = 0U ; idx < g_file_size ; ++idx)
			{
				std::ifstream						ifs0(g_file[idx]);
				std::ifstream						ifs1(g_file[idx]);
				std::istream_iterator<char> const	it0(ifs0);
				std::istream_iterator<char> const	it1(ifs1);
				std::istream_iterator<char> const	end_of_stream;
				ft::vector<char>					ft_vec(it0, end_of_stream);
				std::vector<char>					std_vec(it1, end_of_stream);

				ft_it = ft_vec.begin();
				std_it = std_vec.begin();

				if (!!ft_it.base() != !!std_it.base() || (ft_it.base() && std_it.base() && *ft_it != *std_it))
					return KO;
			}
		}
		// Constant access
		{
			ft::vector<char>::const_iterator	ft_cit;
			std::vector<char>::const_iterator	std_cit;

			for (idx = 0U ; idx < g_file_size ; ++idx)
			{
				std::ifstream						ifs0(g_file[idx]);
				std::ifstream						ifs1(g_file[idx]);
				std::istream_iterator<char> const	it0(ifs0);
				std::istream_iterator<char> const	it1(ifs1);
				std::istream_iterator<char> const	end_of_stream;
				ft::vector<char> const				ft_vec(it0, end_of_stream);
				std::vector<char> const				std_vec(it1, end_of_stream);

				ft_cit = ft_vec.begin();
				std_cit = std_vec.begin();

				if (!!ft_cit.base() != !!std_cit.base() || (ft_cit.base() && std_cit.base() && *ft_cit != *std_cit))
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

inline static int	__test_function_end(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::vector<char>::iterator	ft_it;
			std::vector<char>::iterator	std_it;

			for (idx = 0U ; idx < g_file_size ; ++idx)
			{
				std::ifstream						ifs0(g_file[idx]);
				std::ifstream						ifs1(g_file[idx]);
				std::istream_iterator<char> const	it0(ifs0);
				std::istream_iterator<char> const	it1(ifs1);
				std::istream_iterator<char> const	end_of_stream;
				ft::vector<char>					ft_vec(it0, end_of_stream);
				std::vector<char>					std_vec(it1, end_of_stream);

				ft_it = ft_vec.end();
				std_it = std_vec.end();

				if (!!ft_it.base() != !!std_it.base() || (ft_it.base() && std_it.base() && *--ft_it != *--std_it))
					return KO;
			}
		}
		// Constant access
		{
			ft::vector<char>::const_iterator	ft_cit;
			std::vector<char>::const_iterator	std_cit;

			for (idx = 0U ; idx < g_file_size ; ++idx)
			{
				std::ifstream						ifs0(g_file[idx]);
				std::ifstream						ifs1(g_file[idx]);
				std::istream_iterator<char> const	it0(ifs0);
				std::istream_iterator<char> const	it1(ifs1);
				std::istream_iterator<char> const	end_of_stream;
				ft::vector<char> const				ft_vec(it0, end_of_stream);
				std::vector<char> const				std_vec(it1, end_of_stream);

				ft_cit = ft_vec.end();
				std_cit = std_vec.end();

				if (!!ft_cit.base() != !!std_cit.base() || (ft_cit.base() && std_cit.base() && *--ft_cit != *--std_cit))
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

inline static int	__test_function_rbegin(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::vector<char>::reverse_iterator	ft_rit;
			std::vector<char>::reverse_iterator	std_rit;

			for (idx = 0U ; idx < g_file_size ; ++idx)
			{
				std::ifstream						ifs0(g_file[idx]);
				std::ifstream						ifs1(g_file[idx]);
				std::istream_iterator<char> const	it0(ifs0);
				std::istream_iterator<char> const	it1(ifs1);
				std::istream_iterator<char> const	end_of_stream;
				ft::vector<char>					ft_vec(it0, end_of_stream);
				std::vector<char>					std_vec(it1, end_of_stream);

				ft_rit = ft_vec.rbegin();
				std_rit = std_vec.rbegin();

				if (!!ft_rit.base().base() != !!std_rit.base().base() ||
					(ft_rit.base().base() && std_rit.base().base() && *ft_rit != *std_rit))
					return KO;
			}
		}
		// Constant access
		{
			ft::vector<char>::const_reverse_iterator	ft_crit;
			std::vector<char>::const_reverse_iterator	std_crit;

			for (idx = 0U ; idx < g_file_size ; ++idx)
			{
				std::ifstream						ifs0(g_file[idx]);
				std::ifstream						ifs1(g_file[idx]);
				std::istream_iterator<char> const	it0(ifs0);
				std::istream_iterator<char> const	it1(ifs1);
				std::istream_iterator<char> const	end_of_stream;
				ft::vector<char> const				ft_vec(it0, end_of_stream);
				std::vector<char> const				std_vec(it1, end_of_stream);

				ft_crit = ft_vec.rbegin();
				std_crit = std_vec.rbegin();

				if (!!ft_crit.base().base() != !!std_crit.base().base() ||
					(ft_crit.base().base() && std_crit.base().base() && *ft_crit != *std_crit))
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

inline static int	__test_function_rend(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::vector<char>::reverse_iterator	ft_rit;
			std::vector<char>::reverse_iterator	std_rit;

			for (idx = 0U ; idx < g_file_size ; ++idx)
			{
				std::ifstream						ifs0(g_file[idx]);
				std::ifstream						ifs1(g_file[idx]);
				std::istream_iterator<char> const	it0(ifs0);
				std::istream_iterator<char> const	it1(ifs1);
				std::istream_iterator<char> const	end_of_stream;
				ft::vector<char>					ft_vec(it0, end_of_stream);
				std::vector<char>					std_vec(it1, end_of_stream);

				ft_rit = ft_vec.rend();
				std_rit = std_vec.rend();

				if (!!ft_rit.base().base() != !!std_rit.base().base() ||
					(ft_rit.base().base() && std_rit.base().base() && *--ft_rit != *--std_rit))
					return KO;
			}
		}
		// Constant access
		{
			ft::vector<char>::const_reverse_iterator	ft_crit;
			std::vector<char>::const_reverse_iterator	std_crit;

			for (idx = 0U ; idx < g_file_size ; ++idx)
			{
				std::ifstream						ifs0(g_file[idx]);
				std::ifstream						ifs1(g_file[idx]);
				std::istream_iterator<char> const	it0(ifs0);
				std::istream_iterator<char> const	it1(ifs1);
				std::istream_iterator<char> const	end_of_stream;
				ft::vector<char> const				ft_vec(it0, end_of_stream);
				std::vector<char> const				std_vec(it1, end_of_stream);

				ft_crit = ft_vec.rend();
				std_crit = std_vec.rend();

				if (!!ft_crit.base().base() != !!std_crit.base().base() ||
					(ft_crit.base().base() && std_crit.base().base() && *--ft_crit != *--std_crit))
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

inline static int	__test_type_iterator(void)
{
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::vector<int>							ft_vec(&g_int[0], &g_int[g_int_size]);
		std::vector<int>						std_vec(&g_int[0], &g_int[g_int_size]);
		ft::vector<int>::iterator const			ft_mid(&ft_vec[ft_vec.size() / 2]);
		std::vector<int>::iterator const		std_mid(&std_vec[std_vec.size() / 2]);
		ft::vector<int>::const_iterator const	ft_cmid(ft_mid);
		std::vector<int>::const_iterator const	std_cmid(std_mid);
		ft::vector<int>::iterator				ft_it;
		std::vector<int>::iterator				std_it;

		if (sizeof(ft_it) != sizeof(std_it))
			ret = ISO_OK;

		for (ft_it = ft_vec.begin(), std_it = std_vec.begin() ;
			ft_it != ft_vec.end() && std_it != std_vec.end() ;
			++ft_it, ++std_it)
		{
			RandomAccessIteratorCheck(ft_it);
			RandomAccessIteratorCheck(std_it);

			if (!!ft_it.base() != !!std_it.base() ||
				(ft_it - ft_mid) != (std_it - std_mid) || (ft_it - ft_cmid) != (std_it - std_cmid) ||
				(ft_it < ft_mid) != (std_it < std_mid) || (ft_it < ft_cmid) != (std_it < std_cmid) ||
				(ft_it > ft_mid) != (std_it > std_mid) || (ft_it > ft_cmid) != (std_it > std_cmid) ||
				(ft_it <= ft_mid) != (std_it <= std_mid) || (ft_it <= ft_cmid) != (std_it <= std_cmid) ||
				(ft_it >= ft_mid) != (std_it >= std_mid) || (ft_it >= ft_cmid) != (std_it >= std_cmid) ||
				(*ft_it)++ != (*std_it)++ || ++(ft_it[0]) != ++(std_it[0]) ||
				(*ft_it)-- != (*std_it)-- || --(ft_it[0]) != --(std_it[0]))
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
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::vector<int>							ft_vec(&g_int[0], &g_int[g_int_size]);
		std::vector<int>						std_vec(&g_int[0], &g_int[g_int_size]);
		ft::vector<int>::iterator const			ft_mid(&ft_vec[ft_vec.size() / 2]);
		std::vector<int>::iterator const		std_mid(&std_vec[std_vec.size() / 2]);
		ft::vector<int>::const_iterator const	ft_cmid(ft_mid);
		std::vector<int>::const_iterator const	std_cmid(std_mid);
		ft::vector<int>::const_iterator			ft_cit;
		std::vector<int>::const_iterator		std_cit;

		if (sizeof(ft_cit) != sizeof(std_cit))
			ret = ISO_OK;

		for (ft_cit = ft_vec.begin(), std_cit = std_vec.begin() ;
			ft_cit != ft_vec.end() && std_cit != std_vec.end() ;
			++ft_cit, ++std_cit)
		{
			RandomAccessIteratorCheck(ft_cit);
			RandomAccessIteratorCheck(std_cit);

			if (!!ft_cit.base() != !!std_cit.base() ||
				(ft_cit - ft_mid) != (std_cit - std_mid) || (ft_cit - ft_cmid) != (std_cit - std_cmid) ||
				(ft_cit < ft_mid) != (std_cit < std_mid) || (ft_cit < ft_cmid) != (std_cit < std_cmid) ||
				(ft_cit > ft_mid) != (std_cit > std_mid) || (ft_cit > ft_cmid) != (std_cit > std_cmid) ||
				(ft_cit <= ft_mid) != (std_cit <= std_mid) || (ft_cit <= ft_cmid) != (std_cit <= std_cmid) ||
				(ft_cit >= ft_mid) != (std_cit >= std_mid) || (ft_cit >= ft_cmid) != (std_cit >= std_cmid) ||
				*ft_cit != *std_cit || ft_cit[0] != std_cit[0])
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
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::vector<int>									ft_vec(&g_int[0], &g_int[g_int_size]);
		std::vector<int>								std_vec(&g_int[0], &g_int[g_int_size]);
		ft::vector<int>::reverse_iterator const			ft_rend(ft_vec.rend());
		std::vector<int>::reverse_iterator const		std_rend(std_vec.rend());
		ft::vector<int>::const_reverse_iterator const	ft_crend(ft_vec.rend());
		std::vector<int>::const_reverse_iterator const	std_crend(std_vec.rend());
		ft::vector<int>::reverse_iterator				ft_rit;
		std::vector<int>::reverse_iterator				std_rit;

		if (sizeof(ft_rit) != sizeof(std_rit))
			ret = ISO_OK;

		for (ft_rit = ft_vec.rbegin(), std_rit = std_vec.rbegin() ;
			ft_rit != ft_vec.rend() && std_rit != std_vec.rend() ;
			++ft_rit, ++std_rit)
		{
			RandomAccessIteratorCheck(ft_rit);
			RandomAccessIteratorCheck(std_rit);

			if (!!ft_rit.base().base() != !!std_rit.base().base() ||
				(ft_rit - ft_rend) != (std_rit - std_rend) || (ft_rit - ft_crend) != (std_rit - std_crend) ||
				(ft_rit < ft_rend) != (std_rit < std_rend) || (ft_rit < ft_crend) != (std_rit < std_crend) ||
				(ft_rit > ft_rend) != (std_rit > std_rend) || (ft_rit > ft_crend) != (std_rit > std_crend) ||
				(ft_rit <= ft_rend) != (std_rit <= std_rend) || (ft_rit <= ft_crend) != (std_rit <= std_crend) ||
				(ft_rit >= ft_rend) != (std_rit >= std_rend) || (ft_rit >= ft_crend) != (std_rit >= std_crend) ||
				(*ft_rit)++ != (*std_rit)++ || ++(ft_rit[0]) != ++(std_rit[0]) ||
				(*ft_rit)-- != (*std_rit)-- || --(ft_rit[0]) != --(std_rit[0]))
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
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::vector<int> const						ft_vec(&g_int[0], &g_int[g_int_size]);
		std::vector<int> const						std_vec(&g_int[0], &g_int[g_int_size]);
		ft::vector<int>::const_reverse_iterator		ft_crit;
		std::vector<int>::const_reverse_iterator	std_crit;

		if (sizeof(ft_crit) != sizeof(std_crit))
			ret = ISO_OK;

		for (ft_crit = ft_vec.rbegin(), std_crit = std_vec.rbegin() ;
			ft_crit != ft_vec.rend() && std_crit != std_vec.rend() ;
			++ft_crit, ++std_crit)
		{
			RandomAccessIteratorCheck(ft_crit);
			RandomAccessIteratorCheck(std_crit);

			if (!!ft_crit.base().base() != !!std_crit.base().base() ||
				(ft_crit - ft_vec.rend()) != (std_crit - std_vec.rend()) ||
				(ft_crit < ft_vec.rend()) != (std_crit < std_vec.rend()) ||
				(ft_crit > ft_vec.rend()) != (std_crit > std_vec.rend()) ||
				(ft_crit <= ft_vec.rend()) != (std_crit <= std_vec.rend()) ||
				(ft_crit >= ft_vec.rend()) != (std_crit >= std_vec.rend()) ||
				*ft_crit != *std_crit || ft_crit[0] != std_crit[0])
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

inline static int	__test_function_front(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			for (idx = 0U ; idx < g_int_size ; ++idx)
			{
				ft::vector<int>		ft_vec(&g_int[idx], &g_int[g_int_size]);
				std::vector<int>	std_vec(&g_int[idx], &g_int[g_int_size]);

				if (++ft_vec.front() != ++std_vec.front())
					return KO;
			}
		}
		// Constant access
		{
			for (idx = 0U ; idx < g_int_size ; ++idx)
			{
				ft::vector<int> const	ft_vec(&g_int[idx], &g_int[g_int_size]);
				std::vector<int> const	std_vec(&g_int[idx], &g_int[g_int_size]);

				if (ft_vec.front() != std_vec.front())
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

inline static int	__test_function_back(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			for (idx = 1U ; idx <= g_int_size ; ++idx)
			{
				ft::vector<int>		ft_vec(&g_int[0], &g_int[idx]);
				std::vector<int>	std_vec(&g_int[0], &g_int[idx]);

				if (--ft_vec.back() != --std_vec.back())
					return KO;
			}
		}
		// Constant access
		{
			for (idx = 1U ; idx <= g_int_size ; ++idx)
			{
				ft::vector<int> const	ft_vec(&g_int[0], &g_int[idx]);
				std::vector<int> const	std_vec(&g_int[0], &g_int[idx]);

				if (ft_vec.back() != std_vec.back())
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

inline static int	__test_function_at(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::vector<int>		ft_vec(&g_int[0], &g_int[g_int_size]);
			std::vector<int>	std_vec(&g_int[0], &g_int[g_int_size]);

			// Normal usage
			{
				for (idx = 0U ; idx < g_int_size ; ++idx)
					if (++ft_vec.at(idx) != ++std_vec.at(idx))
						return KO;
			}
			// Overlimits usage
			{
				try
				{
					++ft_vec.at(42LU);
				}
				catch (std::out_of_range const &e)
				{
					goto mutable_at_overlimits_usage_ok;
				}
				return KO;
				mutable_at_overlimits_usage_ok:;
			}
		}
		// Constant access
		{
			ft::vector<int> const	ft_vec(&g_int[0], &g_int[g_int_size]);
			std::vector<int> const	std_vec(&g_int[0], &g_int[g_int_size]);

			// Normal usage
			{
				for (idx = 0U ; idx < g_int_size ; ++idx)
					if (ft_vec.at(idx) != std_vec.at(idx))
						return KO;
			}
			// Overlimits usage
			{
				try
				{
					ft_vec.at(42LU);
				}
				catch (std::out_of_range const &e)
				{
					goto constant_at_overlimits_usage_ok;
				}
				return KO;
				constant_at_overlimits_usage_ok:;
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

inline static int	__test_function_insert(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Fill insertion
		// Trivially copyable
		{
			ft::vector<float>	ft_vec;
			std::vector<float>	std_vec;

			for (idx = 0U ; idx < g_float_size ; ++idx)
			{
				ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, g_float_size - idx, g_float[idx]);
				std_vec.insert(std_vec.begin() + std_vec.size() / 2, g_float_size - idx, g_float[idx]);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Fill insertion
		// Trivially copyable
		// Ambiguous
		{
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;

			for (idx = 0U ; idx < g_int_size ; ++idx)
			{
				ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, static_cast<int>(g_int_size - idx), g_int[idx]);
				std_vec.insert(std_vec.begin() + std_vec.size() / 2, static_cast<int>(g_int_size - idx), g_int[idx]);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Fill insertion
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec;
			std::vector<std::string>	std_vec;

			for (idx = 0U ; idx < g_string_size ; ++idx)
			{
				ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, g_string_size - idx, g_string[idx]);
				std_vec.insert(std_vec.begin() + std_vec.size() / 2, g_string_size - idx, g_string[idx]);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Range insertion
		// Trivially copyable
		{
			ft::vector<float>	ft_vec;
			std::vector<float>	std_vec;

			for (idx = 0U ; idx < g_float_size ; ++idx)
			{
				ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, g_float, &g_float[idx]);
				std_vec.insert(std_vec.begin() + std_vec.size() / 2, g_float, &g_float[idx]);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Range insertion
		// Trivially copyable
		// Force naive iteration along th range
		{
			ft::vector<char>	ft_vec;
			std::vector<char>	std_vec;

			for (idx = 0U ; idx < g_file_size ; ++idx)
			{
				std::ifstream				ifs0(g_file[idx]);
				std::ifstream				ifs1(g_file[idx]);
				std::istream_iterator<char>	it0(ifs0);
				std::istream_iterator<char>	it1(ifs1);
				std::istream_iterator<char>	end_of_stream;

				ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, it0, end_of_stream);
				std_vec.insert(std_vec.begin() + std_vec.size() / 2, it1, end_of_stream);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Range insertion
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec;
			std::vector<std::string>	std_vec;

			for (idx = 0U ; idx < g_string_size ; ++idx)
			{
				ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, g_string, &g_string[idx]);
				std_vec.insert(std_vec.begin() + std_vec.size() / 2, g_string, &g_string[idx]);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Single insertion
		// Trivially copyable
		{
			ft::vector<float>					ft_vec;
			std::vector<float>					std_vec;
			ft::vector<float>::const_iterator	ft_cit;
			std::vector<float>::const_iterator	std_cit;

			for (idx = 0U ; idx < g_float_size ; ++idx)
			{
				ft_cit = ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, g_float[idx]);
				std_cit = std_vec.insert(std_vec.begin() + std_vec.size() / 2, g_float[idx]);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()) ||
					ft_cit - ft_vec.begin() != std_cit - std_vec.begin())
					return KO;
			}
		}
		// Single insertion
		// Non-trivial copy required
		{
			ft::vector<std::string>						ft_vec;
			std::vector<std::string>					std_vec;
			ft::vector<std::string>::const_iterator		ft_cit;
			std::vector<std::string>::const_iterator	std_cit;

			for (idx = 0U ; idx < g_string_size ; ++idx)
			{
				ft_cit = ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, g_string[idx]);
				std_cit = std_vec.insert(std_vec.begin() + std_vec.size() / 2, g_string[idx]);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()) ||
					ft_cit - ft_vec.begin() != std_cit - std_vec.begin())
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

inline static int	__test_function_erase(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Range erase
		{
			ft::vector<t_hhuint>					ft_vec;
			std::vector<t_hhuint>					std_vec;
			ft::vector<t_hhuint>::const_iterator	ft_cit;
			std::vector<t_hhuint>::const_iterator	std_cit;

			for (idx = 0U ; idx < g_hhuint_size ; ++idx)
			{
				ft_vec.insert(ft_vec.end(), &g_hhuint[idx], &g_hhuint[g_hhuint_size]);
				std_vec.insert(std_vec.end(), &g_hhuint[idx], &g_hhuint[g_hhuint_size]);

				ft_cit = ft_vec.erase(ft_vec.begin() + idx, ft_vec.begin() + idx * 2);
				std_cit = std_vec.erase(std_vec.begin() + idx, std_vec.begin() + idx * 2);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()) ||
					ft_cit - ft_vec.begin() != std_cit - std_vec.begin())
					return KO;
			}
		}
		// Single erase
		{
			ft::vector<t_hhuint>					ft_vec;
			std::vector<t_hhuint>					std_vec;
			ft::vector<t_hhuint>::const_iterator	ft_cit;
			std::vector<t_hhuint>::const_iterator	std_cit;

			for (idx = 0U ; idx < g_hhuint_size ; ++idx)
			{
				ft_vec.insert(ft_vec.end(), &g_hhuint[idx], &g_hhuint[g_hhuint_size]);
				std_vec.insert(std_vec.end(), &g_hhuint[idx], &g_hhuint[g_hhuint_size]);

				ft_cit = ft_vec.erase(ft_vec.begin() + idx);
				std_cit = std_vec.erase(std_vec.begin() + idx);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()) ||
					ft_cit - ft_vec.begin() != std_cit - std_vec.begin())
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

inline static int	__test_function_push_back(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Trivially copyable
		{
			ft::vector<long double>		ft_vec;
			std::vector<long double>	std_vec;

			for (idx = 0U ; idx < g_long_double_size ; ++idx)
			{
				ft_vec.push_back(g_long_double[idx]);
				std_vec.push_back(g_long_double[idx]);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec;
			std::vector<std::string>	std_vec;

			for (idx = 0U ; idx < g_string_size ; ++idx)
			{
				ft_vec.push_back(g_string[idx]);
				std_vec.push_back(g_string[idx]);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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

inline static int	__test_function_pop_back(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::vector<int>		ft_vec(&g_int[0], &g_int[g_int_size]);
		std::vector<int>	std_vec(&g_int[0], &g_int[g_int_size]);

		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			ft_vec.pop_back();
			std_vec.pop_back();

			if (ft_vec.capacity() != std_vec.capacity())
				return ISO_OK;
			if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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

inline static int	__test_function_clear(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			ft::vector<std::string>		ft_vec(&g_string[0], &g_string[idx]);
			std::vector<std::string>	std_vec(&g_string[0], &g_string[idx]);

			ft_vec.clear();
			std_vec.clear();

			if (ft_vec.capacity() != std_vec.capacity())
				return ISO_OK;
			if (ft_vec.size() != std_vec.size())
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

inline static int	__test_function_assign(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Fill assignation
		// Trivially copyable
		{
			ft::vector<double>	ft_vec(7LU, NAN);
			std::vector<double>	std_vec(7LU, NAN);

			for (idx = 0U ; idx < g_double_size ; ++idx)
			{
				ft_vec.assign(idx * idx, g_double[idx]);
				std_vec.assign(idx * idx, g_double[idx]);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Fill assignation
		// Trivially copyable
		// Ambiguous
		{
			ft::vector<t_lint>	ft_vec(7LU, 42L);
			std::vector<t_lint>	std_vec(7LU, 42L);

			for (idx = 0U ; idx < g_lint_size ; ++idx)
			{
				ft_vec.assign(static_cast<t_lint>(idx * idx), g_lint[idx]);
				std_vec.assign(static_cast<t_lint>(idx * idx), g_lint[idx]);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Fill assignation
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec(7LU, std::string("Koala"));
			std::vector<std::string>	std_vec(7LU, std::string("Koala"));

			for (idx = 0U ; idx < g_string_size ; ++idx)
			{
				ft_vec.assign(idx * idx, g_string[idx]);
				std_vec.assign(idx * idx, g_string[idx]);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
			
		}
		// Range assignation
		// Trivially copyable
		{
			ft::vector<double>	ft_vec(7LU, NAN);
			std::vector<double>	std_vec(7LU, NAN);

			for (idx = 0U ; idx < g_double_size ; ++idx)
			{
				ft_vec.assign(&g_double[idx / 2 + (idx % 2)], &g_double[g_double_size - idx / 2 - !(idx % 2)]);
				std_vec.assign(&g_double[idx / 2 + (idx % 2)], &g_double[g_double_size - idx / 2 - !(idx % 2)]);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Range assignation
		// Trivially copyable
		// Force naive iteration along the range
		{
			ft::vector<char>	ft_vec(7LU, '+');
			std::vector<char>	std_vec(7LU, '+');

			for (idx = 0U ; idx < g_file_size ; ++idx)
			{
				std::ifstream				ifs0(g_file[idx]);
				std::ifstream				ifs1(g_file[idx]);
				std::istream_iterator<char>	it0(ifs0);
				std::istream_iterator<char>	it1(ifs1);
				std::istream_iterator<char>	end_of_stream;

				ft_vec.assign(it0, end_of_stream);
				std_vec.assign(it1, end_of_stream);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Range assignation
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec(7LU, std::string("Koala"));
			std::vector<std::string>	std_vec(7LU, std::string("Koala"));

			for (idx = 0U ; idx < g_string_size ; ++idx)
			{
				ft_vec.assign(&g_string[idx / 2 + (idx % 2)], &g_string[10 - idx / 2 - !(idx % 2)]);
				std_vec.assign(&g_string[idx / 2 + (idx % 2)], &g_string[10 - idx / 2 - !(idx % 2)]);

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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

inline static int	__test_function_swap(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Member function
		// Trivially copyable
		{
			ft::vector<t_uint>	ft_vec0(&g_uint[0], &g_uint[g_uint_size]);
			std::vector<t_uint>	std_vec0(&g_uint[0], &g_uint[g_uint_size]);
			ft::vector<t_uint>	ft_vec1;
			std::vector<t_uint>	std_vec1;

			for (idx = 0U ; idx < g_uint_size * 2 ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin(), g_uint[idx / 2]);
				std_vec1.insert(std_vec1.begin(), g_uint[idx / 2]);
			}

			ft_vec0.swap(ft_vec1);
			std_vec0.swap(std_vec1);

			if (ft_vec0.capacity() != std_vec0.capacity())
			{
				if (ft_vec0.capacity() < ft_vec0.size())
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec0.size() != std_vec0.size() || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()) ||
				ft_vec1.size() != std_vec1.size() || !std::equal(ft_vec1.begin(), ft_vec1.end(), std_vec1.begin()))
				return KO;
		}
		// Member function
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec0(&g_string[0], &g_string[g_string_size]);
			std::vector<std::string>	std_vec0(&g_string[0], &g_string[g_string_size]);
			ft::vector<std::string>		ft_vec1;
			std::vector<std::string>	std_vec1;

			for (idx = 0U ; idx < g_string_size * 2 ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin(), g_string[idx / 2]);
				std_vec1.insert(std_vec1.begin(), g_string[idx / 2]);
			}
			
			ft_vec0.swap(ft_vec1);
			std_vec0.swap(std_vec1);

			if (ft_vec0.capacity() != std_vec0.capacity())
			{
				if (ft_vec0.capacity() < ft_vec0.size())
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec0.size() != std_vec0.size() || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()) ||
				ft_vec1.size() != std_vec1.size() || !std::equal(ft_vec1.begin(), ft_vec1.end(), std_vec1.begin()))
				return KO;
		}
		// Non-member function
		// Trivially copyable
		{
			ft::vector<t_uint>	ft_vec0(&g_uint[0], &g_uint[g_uint_size]);
			std::vector<t_uint>	std_vec0(&g_uint[0], &g_uint[g_uint_size]);
			ft::vector<t_uint>	ft_vec1;
			std::vector<t_uint>	std_vec1;

			for (idx = 0U ; idx < g_uint_size * 2 ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin(), g_uint[idx / 2]);
				std_vec1.insert(std_vec1.begin(), g_uint[idx / 2]);
			}

			ft::swap(ft_vec0, ft_vec1);
			std::swap(std_vec0, std_vec1);

			if (ft_vec0.capacity() != std_vec0.capacity())
			{
				if (ft_vec0.capacity() < ft_vec0.size())
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec0.size() != std_vec0.size() || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()) ||
				ft_vec1.size() != std_vec1.size() || !std::equal(ft_vec1.begin(), ft_vec1.end(), std_vec1.begin()))
				return KO;
		}
		// Non-member function
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec0(&g_string[0], &g_string[g_string_size]);
			std::vector<std::string>	std_vec0(&g_string[0], &g_string[g_string_size]);
			ft::vector<std::string>		ft_vec1;
			std::vector<std::string>	std_vec1;

			for (idx = 0U ; idx < g_string_size * 2 ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin(), g_string[idx / 2]);
				std_vec1.insert(std_vec1.begin(), g_string[idx / 2]);
			}

			ft::swap(ft_vec0, ft_vec1);
			std::swap(std_vec0, std_vec1);

			if (ft_vec0.capacity() != std_vec0.capacity())
			{
				if (ft_vec0.capacity() < ft_vec0.size())
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec0.size() != std_vec0.size() || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()) ||
				ft_vec1.size() != std_vec1.size() || !std::equal(ft_vec1.begin(), ft_vec1.end(), std_vec1.begin()))
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

inline static int	__test_function_reserve(void)
{
	int		ret;
	size_t	n;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::vector<t_huint>		ft_vec(&g_huint[0], &g_huint[g_huint_size]);
		std::vector<t_huint>	std_vec(&g_huint[0], &g_huint[g_huint_size]);

		// Normal usage
		{
			for (n = 0LU ; n < 100LU ; n += 10LU)
			{
				ft_vec.reserve(n);
				std_vec.reserve(n);

				if (ft_vec.capacity() != std_vec.capacity())
				{
					if (ft_vec.capacity() < n)
						return KO;
					ret = ISO_OK;
				}
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
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
				goto reserve_overlimits_ok;
			}
			return KO;
			reserve_overlimits_ok:

			if (ft_vec.capacity() != std_vec.capacity())
			{
				if (ft_vec.capacity() < ft_vec.size())
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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

inline static int	__test_function_resize(void)
{
	int		ret;
	size_t	n;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::vector<int>		ft_vec;
		std::vector<int>	std_vec;

		for (n = 0LU ; n < g_int_size ; ++n)
		{
			ft_vec.resize(n * n, g_int[n]);
			std_vec.resize(n * n, g_int[n]);

			if (ft_vec.capacity() != std_vec.capacity())
			{
				if (ft_vec.capacity() < n * n)
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
				return KO;
		}
		for (--n ; n ; --n)
		{
			ft_vec.resize(n * n);
			std_vec.resize(n * n);

			if (ft_vec.capacity() != std_vec.capacity())
			{
				if (ft_vec.capacity() < n * n)
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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

inline static int	__test_operator_assign(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Trivially copyable
		{
			ft::vector<double>	ft_vec0(&g_double[0], &g_double[g_double_size]);
			std::vector<double>	std_vec0(&g_double[0], &g_double[g_double_size]);
			ft::vector<double>	ft_vec1;
			std::vector<double>	std_vec1;

			for (idx = 0U ; idx < g_double_size * 2 ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin() + idx / 2, g_double[idx / 2]);
				std_vec1.insert(std_vec1.begin() + idx / 2, g_double[idx / 2]);
			}

			ft_vec0 = ft_vec1;
			std_vec0 = std_vec1;

			if (ft_vec0.capacity() != std_vec0.capacity())
			{
				if (ft_vec0.capacity() < ft_vec0.size())
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec0.size() != std_vec0.size() || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()))
				return KO;
		}
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec0(&g_string[0], &g_string[g_string_size]);
			std::vector<std::string>	std_vec0(&g_string[0], &g_string[g_string_size]);
			ft::vector<std::string>		ft_vec1;
			std::vector<std::string>	std_vec1;

			for (idx = 0U ; idx < g_string_size * 2 ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin() + idx / 2, g_string[idx / 2]);
				std_vec1.insert(std_vec1.begin() + idx / 2, g_string[idx / 2]);
			}

			ft_vec0 = ft_vec1;
			std_vec0 = std_vec1;

			if (ft_vec0.capacity() != std_vec0.capacity())
			{
				if (ft_vec0.capacity() < ft_vec0.size())
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec0.size() != std_vec0.size() || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()))
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

inline static int	__test_operator_access(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::vector<t_lint>	ft_vector(&g_lint[0], &g_lint[g_lint_size]);
			std::vector<t_lint>	std_vector(&g_lint[0], &g_lint[g_lint_size]);

			for (idx = 0U ; idx < 10U ; ++idx)
				if (++(ft_vector[idx]) != ++(std_vector[idx]))
					return KO;
		}
		// Constant access
		{
			ft::vector<t_lint> const	ft_vector(&g_lint[0], &g_lint[g_lint_size]);
			std::vector<t_lint> const	std_vector(&g_lint[0], &g_lint[g_lint_size]);

			for (idx = 0U ; idx < 10U ; ++idx)
				if (ft_vector[idx] != std_vector[idx])
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
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			if (ft::operator==(ft_vec0, ft_vec1) != std::operator==(std_vec0, std_vec1))
				return KO;
			ft_vec0.push_back(g_string[idx]);
			std_vec0.push_back(g_string[idx]);
			if (ft::operator==(ft_vec0, ft_vec1) != std::operator==(std_vec0, std_vec1))
				return KO;
			ft_vec1.push_back(g_string[idx]);
			std_vec1.push_back(g_string[idx]);
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
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			if (ft::operator!=(ft_vec0, ft_vec1) != std::operator!=(std_vec0, std_vec1))
				return KO;
			ft_vec0.push_back(g_string[idx]);
			std_vec0.push_back(g_string[idx]);
			if (ft::operator!=(ft_vec0, ft_vec1) != std::operator!=(std_vec0, std_vec1))
				return KO;
			ft_vec1.push_back(g_string[idx]);
			std_vec1.push_back(g_string[idx]);
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
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			if (ft::operator<(ft_vec0, ft_vec1) != std::operator<(std_vec0, std_vec1))
				return KO;
			ft_vec0.push_back(g_string[idx]);
			std_vec0.push_back(g_string[idx]);
			if (ft::operator<(ft_vec0, ft_vec1) != std::operator<(std_vec0, std_vec1))
				return KO;
			ft_vec1.push_back(g_string[idx]);
			std_vec1.push_back(g_string[idx]);
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
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			if (ft::operator>(ft_vec0, ft_vec1) != std::operator>(std_vec0, std_vec1))
				return KO;
			ft_vec0.push_back(g_string[idx]);
			std_vec0.push_back(g_string[idx]);
			if (ft::operator>(ft_vec0, ft_vec1) != std::operator>(std_vec0, std_vec1))
				return KO;
			ft_vec1.push_back(g_string[idx]);
			std_vec1.push_back(g_string[idx]);
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
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			if (ft::operator<=(ft_vec0, ft_vec1) != std::operator<=(std_vec0, std_vec1))
				return KO;
			ft_vec0.push_back(g_string[idx]);
			std_vec0.push_back(g_string[idx]);
			if (ft::operator<=(ft_vec0, ft_vec1) != std::operator<=(std_vec0, std_vec1))
				return KO;
			ft_vec1.push_back(g_string[idx]);
			std_vec1.push_back(g_string[idx]);
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
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			if (ft::operator>=(ft_vec0, ft_vec1) != std::operator>=(std_vec0, std_vec1))
				return KO;
			ft_vec0.push_back(g_string[idx]);
			std_vec0.push_back(g_string[idx]);
			if (ft::operator>=(ft_vec0, ft_vec1) != std::operator>=(std_vec0, std_vec1))
				return KO;
			ft_vec1.push_back(g_string[idx]);
			std_vec1.push_back(g_string[idx]);
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

int	test_vector(void)
{
	t_test const	tests[] = {
		__test_constructor,
		__test_default_template_type_Alloc,
		__test_type_value_type,
		__test_type_allocator_type,
		__test_type_reference,
		__test_type_const_reference,
		__test_type_pointer,
		__test_type_const_pointer,
		__test_function_get_allocator,
		__test_function_max_size,
		__test_function_capacity,
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
	std::cout << "##                     VECTOR                     ##" << '\n';
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
