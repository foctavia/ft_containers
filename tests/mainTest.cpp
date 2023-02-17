/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainTest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:08:23 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/17 08:07:40 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if REAL
    #include <vector>
	#include <map>
    namespace ft = std;
#else
	#include <vector.hpp>
	#include <map.hpp>
#endif

void vectorTest( void );
void mapTest( void );

int eraseTest()
{
  ft::map<char,int> mymap;
  ft::map<char,int>::iterator it;

  // insert some values:
  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;
  mymap['d']=40;
  mymap['e']=50;
  mymap['f']=60;

  it=mymap.find('b');
  std::cout << "found b\n";
  mymap.erase (it);                   // erasing by iterator
  std::cout << "erase iterator to b\n";
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
  mymap.erase ('c');                  // erasing by key
  std::cout << "erase by key 'c'\n";
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
  it=mymap.find ('e');
  
  std::cout << "erase by range 'e' to end\n";
  mymap.erase ( it, mymap.end() );    // erasing by range

  std::cout << " display :\n";
  // show content:
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}

int main( void )
{
	// vectorTest();
	// mapTest();
	eraseTest();
	
    return 0;
}

