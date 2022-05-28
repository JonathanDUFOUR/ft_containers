/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 06:00:18 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/28 17:25:43 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "tester.hpp"

int	main(void)
{
	int	koCount;
	int	idx;

	for (koCount = 0, idx = 0 ; g_test[idx] ; ++idx)
		koCount += g_test[idx]();
	return !!koCount;
}
