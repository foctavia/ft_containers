/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainTest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:08:23 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/21 14:04:45 by foctavia         ###   ########.fr       */
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
	checkPerformance("vector : ", start);
	
	gettimeofday(&start, NULL);
	stackTest();
	checkPerformance("stack : ", start);

	gettimeofday(&start, NULL);
	mapTest();
	checkPerformance("map : ", start);

	gettimeofday(&start, NULL);
	setTest();
	checkPerformance("set : ", start);
	
    return 0;
}

