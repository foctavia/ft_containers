/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainTest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:08:23 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/21 12:48:01 by foctavia         ###   ########.fr       */
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
	checkPerformance("Vector : ", start);
	
	stackTest();
	checkPerformance("Stack : ", start);

	mapTest();
	checkPerformance("Map : ", start);

	setTest();
	checkPerformance("Set : ", start);
	
    return 0;
}

