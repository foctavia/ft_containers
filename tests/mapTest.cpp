/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:30:02 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/20 16:26:20 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void mapTest( void )
{
// mp -> test constructor and insert with value

	ft::pair<char, int>				pr('a', 1);
	ft::map<char, int> 				mp;

	if (mp.empty())
		std::cout << "mp is empty (before insert)" << std::endl;
	
	mp.insert(pr);
	mp.insert(pr);
	mp.insert(ft::pair<char, int>('e', 5));

	mp.insert(ft::pair<char, int>('f', 6));
	mp.insert(ft::pair<char, int>('c', 3));
	mp.insert(ft::pair<char, int>('h', 8));
	mp.insert(ft::pair<char, int>('n', 14));
	mp.insert(ft::pair<char, int>('j', 10));
	mp.insert(ft::pair<char, int>('b', 2));

	ft::map<char, int>::iterator	it = mp.begin();
	
	if (mp.empty())
		std::cout << "mp is empty (after insert)" << std::endl;
	
	std::cout << "Mp after insert:" << std::endl;

	while (it != mp.end())
	{
		std::cout << it->first << ", " << it->second << std::endl;
		it++;
	}
}
