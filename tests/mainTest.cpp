/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainTest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:08:23 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/21 13:19:35 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

/*
	For make diff with std, comment checkPerformance
	For make performance, uncomment checkPerformance
*/

int main( void )
{
	struct timeval	start;
	
	gettimeofday(&start, NULL);
	vectorTest();
	// checkPerformance("Vector : ", start);
	
	gettimeofday(&start, NULL);
	stackTest();
	// checkPerformance("Stack : ", start);

	gettimeofday(&start, NULL);
	mapTest();
	// checkPerformance("Map : ", start);

	gettimeofday(&start, NULL);
	setTest();
	// checkPerformance("Set : ", start);
	
    return 0;
}

