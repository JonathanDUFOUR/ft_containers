/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_reverse_iterator.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 09:40:33 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/31 10:51:35 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include "iterator/base/random_access_iterator.tpp"
#include "iterator/base/reverse_iterator.tpp"
#include "tester.hpp"

inline static int	__test_constructor(void)
{
	int		arr[] = {
		0,
		1,
		2,
		3,
		4,
		5,
		6,
		7,
		8,
		9,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		// Default constructor
		{
			ft::reverse_iterator<ft::random_access_iterator<std::iostream> >	ft_rit;
			std::reverse_iterator<ft::random_access_iterator<std::iostream> >	std_rit;

			if (sizeof(ft_rit) != sizeof(std_rit) || memcmp(&ft_rit, &std_rit, sizeof(ft_rit)))
				return EXIT_FAILURE;
		}
		// Iterator constructor
		{
			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft::random_access_iterator<int>							it(arr + idx);
				ft::reverse_iterator<ft::random_access_iterator<int> >	ft_rit(it);
				std::reverse_iterator<ft::random_access_iterator<int> >	std_rit(it);

				if (sizeof(ft_rit) != sizeof(std_rit) || memcmp(&ft_rit, &std_rit, sizeof(ft_rit)))
					return EXIT_FAILURE;
			}
		}
		// Copy constructor
		{
			for (idx = 0U ; idx < 10U ; ++idx)
			{
				ft::random_access_iterator<int>									it(arr + idx);
				ft::reverse_iterator<ft::random_access_iterator<int> >			ft_rit0(it);
				ft::reverse_iterator<ft::random_access_iterator<int> >			ft_rit1(ft_rit0);
				ft::reverse_iterator<ft::random_access_iterator<int> const>		ft_rit2(ft_rit1);
				std::reverse_iterator<ft::random_access_iterator<int> >			std_rit0(it);
				std::reverse_iterator<ft::random_access_iterator<int> >			std_rit1(std_rit0);
				std::reverse_iterator<ft::random_access_iterator<int> const>	std_rit2(std_rit1);

				if ((sizeof (ft_rit1) != sizeof (std_rit1)) || sizeof(ft_rit2) != sizeof(std_rit2) ||
					(memcmp(&ft_rit0, &ft_rit1, sizeof(ft_rit0)) != memcmp(&std_rit0, &std_rit1, sizeof(std_rit0))) ||
					(memcmp(&ft_rit1, &ft_rit2, sizeof(ft_rit1)) != memcmp(&std_rit1, &std_rit2, sizeof(std_rit1))))
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

inline static int	__test_function_base(void)
{
	double	arr[] = {
		3.14,
		12.25,
		-971.02,
		-0.0,
		0.00001,
		5544.332211,
		159753.6,
		std::numeric_limits<double>::max(),
		std::numeric_limits<double>::min(),
		std::numeric_limits<double>::infinity(),
	};
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft::random_access_iterator<double>							it(arr + idx);
			ft::reverse_iterator<ft::random_access_iterator<double> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator<double> >	std_rit(it);

			if (ft_rit.base() != std_rit.base())
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
	std::string	arr[] = {
		std::string("I"),
		std::string("wanna"),
		std::string("be"),
		std::string("the"),
		std::string("very"),
		std::string("best"),
		std::string("like"),
		std::string("no"),
		std::string("one"),
		std::string("ever"),
		std::string("was"),
	};
	t_uint		idx;

	title(__func__);
	try
	{
		ft::reverse_iterator<ft::random_access_iterator<std::string> >	rit0;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft::random_access_iterator<std::string>								it0(arr + idx);
			ft::random_access_iterator<std::string> const						it1(arr + idx);
			ft::reverse_iterator<ft::random_access_iterator<std::string> >		rit1(it0);
			ft::reverse_iterator<ft::random_access_iterator<std::string> const>	rit2(it1);

			rit0 = rit1;
			if (memcmp(&rit0, &rit1, sizeof(ft::reverse_iterator<ft::random_access_iterator<std::string> >)))
				return EXIT_FAILURE;
			rit0 = rit2;
			if (memcmp(&rit0, &rit2, sizeof(ft::reverse_iterator<ft::random_access_iterator<std::string> >)))
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

inline static int	__test_operator_dereference(void)
{
	t_hint	arr[] = {
		-0,
		-1,
		-2,
		-3,
		-4,
		-5,
		-6,
		-7,
		-8,
		-9,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 1U ; idx < 11U ; ++idx)
		{
			ft::random_access_iterator<t_hint>							it(arr + idx);
			ft::reverse_iterator<ft::random_access_iterator<t_hint> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator<t_hint> >	std_rit(it);

			*ft_rit += 42;
			*std_rit += 42;
			if (*ft_rit != *std_rit)
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
	int		arr[] = {
		0,
		1,
		2,
		3,
		4,
		5,
		6,
		7,
		8,
		9,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft::random_access_iterator<int>							it(arr + idx);
			ft::reverse_iterator<ft::random_access_iterator<int> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator<int> >	std_rit(it);

			if (&*ft_rit != &*std_rit)
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
	t_luint	arr[] = {
		424242424242420LU,
		424242424242421LU,
		424242424242422LU,
		424242424242423LU,
		424242424242424LU,
		424242424242425LU,
		424242424242426LU,
		424242424242427LU,
		424242424242428LU,
		424242424242429LU,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		// Prefix incrementation
		{
			ft::random_access_iterator<t_luint>							it(arr + 9);
			ft::reverse_iterator<ft::random_access_iterator<t_luint> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator<t_luint> >	std_rit(it);

			for (idx = 9U ; idx > 0U ; --idx)
				if ((++ft_rit).base() != (++std_rit).base())
					return EXIT_FAILURE;
		}
		// Postfix incrementation
		{
			ft::random_access_iterator<t_luint>							it(arr + 9);
			ft::reverse_iterator<ft::random_access_iterator<t_luint> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator<t_luint> >	std_rit(it);

			for (idx = 9U ; idx > 0U ; --idx)
				if (ft_rit++.base() != std_rit++.base() || ft_rit.base() != std_rit.base())
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
	t_luint	arr[] = {
		424242424242420LU,
		424242424242421LU,
		424242424242422LU,
		424242424242423LU,
		424242424242424LU,
		424242424242425LU,
		424242424242426LU,
		424242424242427LU,
		424242424242428LU,
		424242424242429LU,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		// Prefix decrementation
		{
			ft::random_access_iterator<t_luint>							it(arr);
			ft::reverse_iterator<ft::random_access_iterator<t_luint> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator<t_luint> >	std_rit(it);

			for (idx = 0U ; idx < 9U ; ++idx)
				if ((--ft_rit).base() != (--std_rit).base())
					return EXIT_FAILURE;
		}
		// Postfix decrementation
		{
			ft::random_access_iterator<t_luint>							it(arr);
			ft::reverse_iterator<ft::random_access_iterator<t_luint> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator<t_luint> >	std_rit(it);

			for (idx = 0U ; idx < 9U ; ++idx)
				if (ft_rit--.base() != std_rit--.base() || ft_rit.base() != std_rit.base())
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
	t_luint	arr[] = {
		0LU,
		1LU,
		10LU,
		11LU,
		100LU,
		101LU,
		110LU,
		111LU,
		1000LU,
		1001LU,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft::random_access_iterator<t_luint>							it(arr + 9);
			ft::reverse_iterator<ft::random_access_iterator<t_luint> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator<t_luint> >	std_rit(it);

			ft_rit = (ft_rit += idx);
			std_rit = (std_rit += idx);
			if (ft_rit.base() != std_rit.base())
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
	t_luint	arr[] = {
		0LU,
		1LU,
		10LU,
		11LU,
		100LU,
		101LU,
		110LU,
		111LU,
		1000LU,
		1001LU,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < 10U ; ++idx)
		{
			ft::random_access_iterator<t_luint>							it(arr);
			ft::reverse_iterator<ft::random_access_iterator<t_luint> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator<t_luint> >	std_rit(it);

			ft_rit = (ft_rit -= idx);
			std_rit = (std_rit -= idx);
			if (ft_rit.base() != std_rit.base())
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
	float	arr[] = {
		0.0f,
		1.0f,
		10.0f,
		11.0f,
		100.0f,
		101.0f,
		110.0f,
		111.0f,
		1000.0f,
		1001.0f,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		// Member operator
		{
			ft::random_access_iterator<float>							it(arr + 9);
			ft::reverse_iterator<ft::random_access_iterator<float> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator<float> >	std_rit(it);

			for (idx = 0U ; idx < 10U ; ++idx)
			{
				if ((ft_rit + idx).base() != (std_rit + idx).base())
					return EXIT_FAILURE;
			}
		}
		// Non-member operator
		{
			ft::random_access_iterator<float>							it(arr + 9);
			ft::reverse_iterator<ft::random_access_iterator<float> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator<float> >	std_rit(it);

			for (idx = 0U ; idx < 10U ; ++idx)
				if ((idx + ft_rit).base() != (idx + std_rit).base())
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

inline static int	__test_operator_sub(void)
{
	float	arr[] = {
		0.0f,
		1.0f,
		10.0f,
		11.0f,
		100.0f,
		101.0f,
		110.0f,
		111.0f,
		1000.0f,
		1001.0f,
	};
	t_uint	idx;

	title(__func__);
	try
	{
		ft::random_access_iterator<float>							it(arr);
		ft::reverse_iterator<ft::random_access_iterator<float> >	ft_rit(it);
		std::reverse_iterator<ft::random_access_iterator<float> >	std_rit(it);

		for (idx = 0U ; idx < 10U ; ++idx)
			if ((ft_rit - idx).base() != (std_rit - idx).base())
				return EXIT_FAILURE;
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
	t_hhuint	arr[] = {
		0xff,
		0xfe,
		0xfd,
		0xfc,
		0xfb,
		0xfa,
		0xf9,
		0xf8,
		0xf7,
		0xf6,
	};
	t_uint		idx;

	title(__func__);
	try
	{
		ft::random_access_iterator<t_hhuint>							it(arr + 10);
		ft::reverse_iterator<ft::random_access_iterator<t_hhuint> >		ft_rit(it);
		std::reverse_iterator<ft::random_access_iterator<t_hhuint> >	std_rit(it);

		for (idx = 0U ; idx < 10U ; ++idx)
			if (ft_rit[idx] != std_rit[idx])
				return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_SUCCESS;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_distance(void)
{
	std::string const	arr[] = {
		std::string("Un"),
		std::string("elephant"),
		std::string("qui"),
		std::string("se"),
		std::string("balancait"),
		std::string("sur"),
		std::string("une"),
		std::string("toile"),
		std::string("d'"),
		std::string("araignee"),
	};
	t_uint				idx0;
	t_uint				idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < 10U ; ++idx0)
		{
			ft::random_access_iterator<std::string const>							it0(arr + idx0);
			ft::reverse_iterator<ft::random_access_iterator<std::string const> >	ft_rit0(it0);
			std::reverse_iterator<ft::random_access_iterator<std::string const> >	std_rit0(it0);

			for (idx1 = 0U ; idx1 < 10U ; ++idx1)
			{
				ft::random_access_iterator<std::string const>								it1(arr + idx1);
				ft::reverse_iterator<ft::random_access_iterator<std::string const> const>	ft_rit1(it1);
				std::reverse_iterator<ft::random_access_iterator<std::string const> const>	std_rit1(it1);

				if (ft::operator-(ft_rit0, ft_rit1) != std::operator-(std_rit0, std_rit1))
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

inline static int	__test_operator_equal(void)
{
	int const	arr[] = {
		1,
		2,
		4,
		8,
		16,
		32,
		64,
		128,
		256,
		512,
	};
	t_uint		idx0;
	t_uint		idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < 10U ; ++idx0)
		{
			ft::random_access_iterator<int const>							it0(arr + idx0);
			ft::reverse_iterator<ft::random_access_iterator<int const> >	ft_rit0(it0);
			std::reverse_iterator<ft::random_access_iterator<int const> >	std_rit0(it0);

			for (idx1 = 0U ; idx1 < 10U ; ++idx1)
			{
				ft::random_access_iterator<int const> const							it1(arr + idx1);
				ft::reverse_iterator<ft::random_access_iterator<int const> const>	ft_rit1(it1);
				std::reverse_iterator<ft::random_access_iterator<int const> const>	std_rit1(it1);

				if (ft::operator==(ft_rit0, ft_rit1) != std::operator==(std_rit0, std_rit1))
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
	int const	arr[] = {
		1,
		2,
		4,
		8,
		16,
		32,
		64,
		128,
		256,
		512,
	};
	t_uint		idx0;
	t_uint		idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < 10U ; ++idx0)
		{
			ft::random_access_iterator<int const> const						it0(arr + idx0);
			ft::reverse_iterator<ft::random_access_iterator<int const> >	ft_rit0(it0);
			std::reverse_iterator<ft::random_access_iterator<int const> >	std_rit0(it0);

			for (idx1 = 0U ; idx1 < 10U ; ++idx1)
			{
				ft::random_access_iterator<int const> const							it1(arr + idx1);
				ft::reverse_iterator<ft::random_access_iterator<int const> const>	ft_rit1(it1);
				std::reverse_iterator<ft::random_access_iterator<int const> const>	std_rit1(it1);

				if (ft::operator!=(ft_rit0, ft_rit1) != std::operator!=(std_rit0, std_rit1))
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

inline static int	__test_operator_lower(void)
{
	int const	arr[] = {
		1,
		2,
		4,
		8,
		16,
		32,
		64,
		128,
		256,
		512,
	};
	t_uint		idx0;
	t_uint		idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < 10U ; ++idx0)
		{
			ft::random_access_iterator<int const>							it0(arr + idx0);
			ft::reverse_iterator<ft::random_access_iterator<int const> >	ft_rit0(it0);
			std::reverse_iterator<ft::random_access_iterator<int const> >	std_rit0(it0);

			for (idx1 = 0U ; idx1 < 10U ; ++idx1)
			{
				ft::random_access_iterator<int const>								it1(arr + idx1);
				ft::reverse_iterator<ft::random_access_iterator<int const> const>	ft_rit1(it1);
				std::reverse_iterator<ft::random_access_iterator<int const> const>	std_rit1(it1);

				if (ft::operator<(ft_rit0, ft_rit1) != std::operator<(std_rit0, std_rit1))
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
	int const	arr[] = {
		1,
		2,
		4,
		8,
		16,
		32,
		64,
		128,
		256,
		512,
	};
	t_uint		idx0;
	t_uint		idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < 10U ; ++idx0)
		{
			ft::random_access_iterator<int const>							it0(arr + idx0);
			ft::reverse_iterator<ft::random_access_iterator<int const> >	ft_rit0(it0);
			std::reverse_iterator<ft::random_access_iterator<int const> >	std_rit0(it0);

			for (idx1 = 0U ; idx1 < 10U ; ++idx1)
			{
				ft::random_access_iterator<int const> const							it1(arr + idx1);
				ft::reverse_iterator<ft::random_access_iterator<int const> const>	ft_rit1(it1);
				std::reverse_iterator<ft::random_access_iterator<int const> const>	std_rit1(it1);

				if (ft::operator>(ft_rit0, ft_rit1) != std::operator>(std_rit0, std_rit1))
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

inline static int	__test_operator_lower_equal(void)
{
	int const	arr[] = {
		1,
		2,
		4,
		8,
		16,
		32,
		64,
		128,
		256,
		512,
	};
	t_uint		idx0;
	t_uint		idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < 10U ; ++idx0)
		{
			ft::random_access_iterator<int const>							it0(arr + idx0);
			ft::reverse_iterator<ft::random_access_iterator<int const> >	ft_rit0(it0);
			std::reverse_iterator<ft::random_access_iterator<int const> >	std_rit0(it0);

			for (idx1 = 0U ; idx1 < 10U ; ++idx1)
			{
				ft::random_access_iterator<int const> const							it1(arr + idx1);
				ft::reverse_iterator<ft::random_access_iterator<int const> const>	ft_rit1(it1);
				std::reverse_iterator<ft::random_access_iterator<int const> const>	std_rit1(it1);

				if (ft::operator<=(ft_rit0, ft_rit1) != std::operator<=(std_rit0, std_rit1))
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

inline static int	__test_operator_greater_equal(void)
{
	int const	arr[] = {
		1,
		2,
		4,
		8,
		16,
		32,
		64,
		128,
		256,
		512,
	};
	t_uint		idx0;
	t_uint		idx1;

	title(__func__);
	try
	{
		for (idx0 = 0 ; idx0 < 10 ; ++idx0)
		{
			ft::random_access_iterator<int const>							it0(arr + idx0);
			ft::reverse_iterator<ft::random_access_iterator<int const> >	ft_rit0(it0);
			std::reverse_iterator<ft::random_access_iterator<int const> >	std_rit0(it0);

			for (idx1 = 0 ; idx1 < 10 ; ++idx1)
			{
				ft::random_access_iterator<int const> const							it1(arr + idx1);
				ft::reverse_iterator<ft::random_access_iterator<int const> > const	ft_rit1(it1);
				std::reverse_iterator<ft::random_access_iterator<int const> > const	std_rit1(it1);

				if (ft::operator>=(ft_rit0, ft_rit1) != std::operator>=(std_rit0, std_rit1))
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

int	test_reverse_iterator(void)
{
	t_test const	tests[] = {
		__test_constructor,
		__test_function_base,
		__test_operator_assign,
		__test_operator_dereference,
		__test_operator_maddress,
		__test_operator_increment,
		__test_operator_decrement,
		__test_operator_add_assign,
		__test_operator_sub_assign,
		__test_operator_add,
		__test_operator_sub,
		__test_operator_access,
		__test_operator_distance,
		__test_operator_equal,
		__test_operator_difference,
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
	std::cout << "##                REVERSE ITERATOR                ##" << '\n';
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
