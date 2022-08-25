/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_integral.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:00:25 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/25 22:26:15 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include "iterator/base/input_iterator.tpp"
#include "type_traits.hpp"
#include "tester.hpp"

inline static int	__test_bool(void)
{
	title(__func__);
	try
	{
		ft::is_integral<bool>	ie;

		if (!dynamic_cast<ft::true_type *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_char(void)
{
	title(__func__);
	try
	{
		ft::is_integral<char>	ie;

		if (!dynamic_cast<ft::true_type *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_wchar_t(void)
{
	title(__func__);
	try
	{
		ft::is_integral<wchar_t>	ie;

		if (!dynamic_cast<ft::true_type *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_signed_char(void)
{
	title(__func__);
	try
	{
		ft::is_integral<signed char>	ie;

		if (!dynamic_cast<ft::true_type *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_signed_short(void)
{
	title(__func__);
	try
	{
		ft::is_integral<signed short>	ie;

		if (!dynamic_cast<ft::true_type *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_signed_int(void)
{
	title(__func__);
	try
	{
		ft::is_integral<signed int>	ie;

		if (!dynamic_cast<ft::true_type *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_signed_long(void)
{
	title(__func__);
	try
	{
		ft::is_integral<signed long>	ie;

		if (!dynamic_cast<ft::true_type *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_unsigned_char(void)
{
	title(__func__);
	try
	{
		ft::is_integral<unsigned char>	ie;

		if (!dynamic_cast<ft::true_type *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_unsigned_short(void)
{
	title(__func__);
	try
	{
		ft::is_integral<unsigned short>	ie;

		if (!dynamic_cast<ft::true_type *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_unsigned_int(void)
{
	title(__func__);
	try
	{
		ft::is_integral<unsigned int>	ie;

		if (!dynamic_cast<ft::true_type *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_unsigned_long(void)
{
	title(__func__);
	try
	{
		ft::is_integral<unsigned long>	ie;

		if (!dynamic_cast<ft::true_type *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_void(void)
{
	title(__func__);
	try
	{
		ft::is_integral<void>	ie;

		if (!dynamic_cast<ft::false_type *>(&ie) || ie.value != false)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_pointer(void)
{
	title(__func__);
	try
	{
		ft::is_integral<void *>	ie;

		if (!dynamic_cast<ft::false_type *>(&ie) || ie.value != false)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_float(void)
{
	title(__func__);
	try
	{
		ft::is_integral<float>	ie;

		if (!dynamic_cast<ft::false_type *>(&ie) || ie.value != false)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_double(void)
{
	title(__func__);
	try
	{
		ft::is_integral<double>	ie;

		if (!dynamic_cast<ft::false_type *>(&ie) || ie.value != false)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_std_string(void)
{
	title(__func__);
	try
	{
		ft::is_integral<std::string>	ie;

		if (!dynamic_cast<ft::false_type *>(&ie) || ie.value != false)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_ft_input_iterator(void)
{
	title(__func__);
	try
	{
		ft::is_integral<ft::input_iterator<t_huint> >	ie;

		if (!dynamic_cast<ft::false_type *>(&ie) || ie.value != false)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int	test_is_integral(void)
{
	t_test const	tests[] = {
		__test_bool,
		__test_wchar_t,
		__test_char,
		__test_signed_char,
		__test_signed_short,
		__test_signed_int,
		__test_signed_long,
		__test_unsigned_char,
		__test_unsigned_short,
		__test_unsigned_int,
		__test_unsigned_long,
		__test_void,
		__test_pointer,
		__test_float,
		__test_double,
		__test_std_string,
		__test_ft_input_iterator,
		NULL
	};
	t_uint			koCount;
	t_uint			idx;

	std::cerr << "\033[38;2;0;173;255m";
	std::cout << "###################################################" << '\n';
	std::cout << "##                  IS_INTEGRAL                  ##" << '\n';
	std::cout << "###################################################" << '\n';
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
