/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorTest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:13:23 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/15 11:06:35 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if REAL
    #include <vector>
    namespace ft = std;
#else
	#include <vector.hpp>
#endif

#define RED(s) "\033[1;31m" s "\033[m"
#define GREEN(s) "\033[1;32m" s "\033[m"

template < typename T >
void	print( T &vector )
{
	if (vector.empty())
		std::cout << "Vector is empty" << std::endl;
	
	std::cout << "Vector size : " << vector.size() << "  capacity : " << vector.capacity() << std::endl;
	
	std::cout << "Vector : ";
	for (size_t i = 0; i < vector.size(); ++i)
		std::cout << vector[i] << " ";
		
	std::cout << std::endl << std::endl;
}

