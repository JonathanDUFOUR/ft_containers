/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 06:00:18 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/25 09:45:58 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include "vector.hpp"
#include "tester.hpp"

int	main(void)
{
	int	koCount;
	int	idx;

	for (koCount = 0, idx = 0 ; g_test[idx] ; ++idx)
		koCount += g_test[idx]();
	return !!koCount;
}
