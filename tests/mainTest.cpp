/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainTest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:08:23 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/20 14:01:27 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if REAL
    #include <vector>
	#include <stack>
	#include <map>
    namespace ft = std;
#else
	#include <vector.hpp>
	#include <stack.hpp>
	#include <map.hpp>
#endif

void vectorTest( void );
void mapTest( void );

int main( void )
{
	vectorTest();
	// mapTest();
	
    return 0;
}

