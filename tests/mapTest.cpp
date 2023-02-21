/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:30:02 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/21 12:12:59 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

/*
	For make diff with std, comment the displayTree()
*/

void	mapTest( void )
{
	MAINTITLE("***** TESTING MAP *****");
	
	TITLE("--> Testing default constructor and insert with 3 values");
	
// Testing default constructor
	ft::map<int, std::string> mp;

	SUBTITLE("Map : ");
	printMap(mp);
	
// Testing insert
	mp.insert(ft::make_pair(1, "one"));
	mp.insert(ft::make_pair(2, "two"));
	mp.insert(ft::make_pair(3, "three"));
	mp.insert(ft::make_pair(4, "one"));
	mp.insert(ft::make_pair(5, "two"));
	mp.insert(ft::make_pair(6, "three"));
	mp.insert(ft::make_pair(7, "one"));
	mp.insert(ft::make_pair(8, "two"));
	mp.insert(ft::make_pair(9, "three"));
	mp.insert(ft::make_pair(10, "one"));
	mp.insert(ft::make_pair(11, "two"));
	mp.insert(ft::make_pair(12, "three"));
	mp.insert(ft::make_pair(13, "one"));
	mp.insert(ft::make_pair(14, "two"));
	mp.insert(ft::make_pair(15, "three"));

	SUBTITLE("Map (after insert) : ");
	printMap(mp);
	
	// mp.displayTree();

	TITLE("--> Testing operator=, operator[], and at");
	
	ft::map<int, std::string> mp1;

	SUBTITLE("Map1 : ");
	printMap(mp1);
	
// Testing operator=
	mp1 = mp;
	
	SUBTITLE("Map1 (after operator= with value from Map) : ");
	printMap(mp1);

// Testing get_allocator
	std::allocator<ft::pair<const int, std::string> > alloc = mp.get_allocator();
	(void)alloc;

// Testing element access at and operator[]
	SUBTITLE("Map (element access) : ");
	std::cout << "mp.at(1): " << mp.at(1) << std::endl
		<< "mp[2]	: " << mp[2] << std::endl << std::endl;

	TITLE("--> Testing iterator and reverse_iterator");
		
// Testing begin and end
	SUBTITLE("Map (printed with iterator begin() and end()) : ");
	std::cout << "size : " << mp.size() << std::endl << "content : " << std::endl;
	for (ft::map<int, std::string>::iterator it = mp.begin(); it != mp.end(); ++it)
		std::cout << it->first << " => " << it->second << std::endl;
	std::cout << std::endl;

// Testing rbegin and rend
	SUBTITLE("Map (printed with reverse_iterator rbegin() and rend()) : ");
	std::cout << "size : " << mp.size() << std::endl << "content : " << std::endl;
	for (ft::map<int, std::string>::reverse_iterator it = mp.rbegin(); it != mp.rend(); ++it)
		std::cout << it->first << " => " << it->second << std::endl;
	std::cout << std::endl;

	TITLE("--> Testing empty, size and max_size");
	
// Testing empty, size, and max_size
	std::cout << "Empty: " << (mp.empty() ? "true" : "false") << std::endl;
	std::cout << "Size: " << mp.size() << std::endl;
	std::cout << "Max size: " << mp.max_size() << std::endl;
	WARNING("max_size may differ between ft_containers and std containers!");

	TITLE("--> Testing clear, insert, and erase");
	
// Testing clear
	mp.clear();
	
	SUBTITLE("Map (after clear) : ");
	printMap(mp);

// Testing insert with value	
	mp.insert(ft::make_pair(1, "one"));
	mp.insert(ft::make_pair(2, "two"));
	mp.insert(ft::make_pair(3, "three"));

	SUBTITLE("Map (after insert with value) : ");
	printMap(mp);


// Testing insert with range
	ft::map<int, std::string> mp2;
	mp2.insert(ft::make_pair(4, "four"));
	mp2.insert(ft::make_pair(5, "five"));
	mp2.insert(ft::make_pair(6, "six"));
	mp.insert(mp2.begin(), mp2.end());

	SUBTITLE("Map (after insert with range iterator) : ");
	printMap(mp);

	// mp.displayTree();

// Testing erase with key
	mp.erase(2);

	SUBTITLE("Map (after erase with key) : ");
	printMap(mp);

	// mp.displayTree();

// Testing erase with iterator
	ft::map<int, std::string>::iterator it = mp.find(3);
	
	mp.erase(it);

	SUBTITLE("Map (after insert with iterator) : ");
	printMap(mp);

	// mp.displayTree();

	TITLE("--> Testing swap");
	
// Testing swap
	SUBTITLE("Map (before swap) : ");
	printMap(mp);
	
	SUBTITLE("Map2 (before swap) : ");
	printMap(mp2);

	mp.swap(mp2);

	SUBTITLE("Map (after swap) : ");
	printMap(mp);
	
	SUBTITLE("Map2 (after swap) : ");
	printMap(mp2);

	TITLE("--> Testing count and find");
	
// Testing count
	SUBTITLE("Map (lookup functions) : ");
	
	std::cout << std::endl << "Count of key 4 : " << mp.count(4) << std::endl << std::endl;
	
	mp.erase(4);
	
	SUBTITLE("Map (after erase of 4) : ");
	printMap(mp);
	
	std::cout << "Count of key 4 : " << mp.count(4) << std::endl;

// Testing find
	ft::map<int, std::string>::iterator found = mp.find(4);
	if (found != mp.end())
		std::cout << "Found key 4 :" << found->first << " => " << found->second << std::endl;
	else
		std::cout << "Not found key 4" << std::endl;

	found = mp.find(6);
	if (found != mp.end())
		std::cout << "Found key 6 : ( " << found->first << " => " << found->second << " )" << std::endl;
	else
		std::cout << "Not found key 6" << std::endl;
	std::cout << std::endl;

// Testing equal_range
	TITLE("--> Testing equal_range");
	
	RETURNS("std::pair containing a pair of iterators defining the wanted range: the first pointing to the first element that is not less than key and the second pointing to the first element greater than key.");
	
	ft::map<int, std::string>::iterator it_low;
	ft::map<int, std::string>::iterator it_high;
	ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator> ret;

	mp.insert(ft::make_pair(4, "four"));
	ret = mp.equal_range(4);

	it_low = ret.first;
	it_high = ret.second;

	std::cout << "first element that is not less than key 4	: ( " << it_low->first << " => " << it_low->second << " )" << std::endl;
	std::cout << "first element greater than key 4		: ( " << it_high->first << " => " << it_high->second << " )" << std::endl << std::endl;
	// mp.displayTree();

	TITLE("--> Testing lower_bound and upper_bound");
	
	// Testing lower_bound
	ft::map<int, std::string>::iterator low = mp.lower_bound(4);
	std::cout << "Lower bound of 4 : ( " << low->first << " => " << low->second << " )" << std::endl;

	// Testing upper_bound
	ft::map<int, std::string>::iterator up = mp.upper_bound(4);
	std::cout << "Upper bound of 4 : ( " << up->first << " => " << up->second << " )" << std::endl << std::endl;

	TITLE("--> Testing key_comp");
	
	// Testing key_comp
	RETURNS("Returns the function object that compares the keys, which is a copy of this container's constructor argument comp. Default is std::less");
	
	ft::map<int, std::string>::key_compare my_key_comp = mp.key_comp();
	
	std::cout << "key_comp(3, 4) : " << my_key_comp(3, 4) << std::endl;
	std::cout << "key_comp(5, 4) : " << my_key_comp(5, 4) << std::endl << std::endl;

	// Testing value_comp
	// ft::map<int, std::string>::value_compare my_value_comp = mp.value_comp();
	// std::cout << my_value_comp(std::make_pair(2, "two"), std::make_pair(1, "one")) << std::endl;

	TITLE("--> Testing map non-member functions");

	ft::map<int, int> map1;
    ft::map<int, int> map2;
	
    // insert some values
    map1.insert(ft::make_pair(1, 10));
    map1.insert(ft::make_pair(2, 20));
    map1.insert(ft::make_pair(3, 30));

    map2.insert(ft::make_pair(1, 10));
    map2.insert(ft::make_pair(2, 20));
    map2.insert(ft::make_pair(4, 40));

	SUBTITLE("Map1 : ");
	printMap(map1);

	SUBTITLE("Map2 : ");
	printMap(map2);

	TITLE("--> Testing comparison, operator == != > >= < <=");

// test == operator
	if (map1 == map2)
		std::cout << "Map1 and Map2 are equal" << std::endl;
	else
		std::cout << "Map1 and Map2 are not equal" << std::endl;

// test != operator
	if (map1 != map2)
		std::cout << "Map1 and Map2 are not equal" << std::endl;
	else
		std::cout << "Map1 and Map2 are equal" << std::endl;

// test < operator
	if (map1 < map2)
		std::cout << "Map1 is less than Map2" << std::endl;
	else
		std::cout << "Map1 is not less than Map2" << std::endl;

// test <= operator
	if (map1 <= map2)
		std::cout << "Map1 is less than or equal to Map2" << std::endl;
	else
		std::cout << "Map1 is not less than or equal to Map2" << std::endl;

// test > operator
	if (map1 > map2)
		std::cout << "Map1 is greater than Map2" << std::endl;
	else
		std::cout << "Map1 is not greater than Map2" << std::endl;

// test >= operator
	if (map1 >= map2)
		std::cout << "Map1 is greater than or equal to Map2" << std::endl;
	else
		std::cout << "Map1 is not greater than or equal to Map2" << std::endl;

	std::cout << std::endl;
		
	TITLE("--> Testing non member swap function");

// test swap function

	SUBTITLE("Map1 (before swap) : ");
	printMap(map1);
	
	SUBTITLE("Map2 (before swap) : ");
	printMap(map2);

	swap(map1, map2);

	SUBTITLE("Map1 (after swap) : ");
	printMap(map1);
	
	SUBTITLE("Map2 (after swap) : ");
	printMap(map2);
}
