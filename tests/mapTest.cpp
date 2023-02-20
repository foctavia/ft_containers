/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:30:02 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/20 18:29:27 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

template <class Key, class T>
void	print(ft::map<Key, T>& lst)
{
	std::cout << std::endl << "size : " << lst.size() << std::endl;
	
	if (lst.empty())
		std::cout << "Map is empty" << std::endl;
	else
	{	
		std::cout << "content :" << std::endl;
		for (typename ft::map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
			std::cout << it->first << " => " << it->second << '\n';
	}
}

/*
	For make diff with std, comment the displayTree()
*/

void	mapTest( void )
{

	MAINTITLE("***** TESTING MAP *****");
	
// test constructor
	TITLE("--> Testing default constructor and insert with 3 values");
	ft::map<int, std::string> mp;

	std::cout << GREEN("Map : ");
	print(mp);
	
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

	std::cout << GREEN("Map (after insert) : ");
	print(mp);
	
	// mp.displayTree();

// Testing operator=, operator[], and at
	TITLE("--> Testing operator=, operator[], and at");
	
	ft::map<int, std::string> mp1;

	std::cout << GREEN("Map1 : ");
	print(mp1);
	
	mp1 = mp;
	
	std::cout << GREEN("Map1 (after operator= with value from Map) : ");
	print(mp1);

// Testing get_allocator
	std::allocator<ft::pair<const int, std::string> > my_allocator = mp.get_allocator();
	// ft::map<int, std::string> my_third_map(my_allocator);

	std::cout << GREEN("Map (element access) : ") << std::endl;
	std::cout << "mp.at(1)	: " << mp.at(1) << std::endl
		<< "mp[2]	: " << mp[2] << std::endl << std::endl;

	TITLE("--> Testing iterator and reverse_iterator");
		
// Testing begin and end
	std::cout << GREEN("Map (printed with iterator begin() and end()) : ") << std::endl;
	std::cout << "size : " << mp.size() << std::endl << "content : ";
	for (ft::map<int, std::string>::iterator it = mp.begin(); it != mp.end(); ++it)
		std::cout << it->first << " => " << it->second << std::endl;

// Testing rbegin and rend
	std::cout << GREEN("Map (printed with reverse_iterator rbegin() and rend()) : ") << std::endl;
	std::cout << "size : " << mp.size() << std::endl << "content : ";
	for (ft::map<int, std::string>::reverse_iterator it = mp.rbegin(); it != mp.rend(); ++it)
		std::cout << it->first << " => " << it->second << std::endl;

	TITLE("--> Testing empty, size and max_size");
	
// Testing empty, size, and max_size
	std::cout << "Empty: " << mp.empty() << std::endl;
	std::cout << "Size: " << mp.size() << std::endl;
	std::cout << "Max size: " << mp.max_size() << std::endl;
	WARNING("max_size may differ between ft_containers and std containers!");

	TITLE("--> Testing clear, insert, and erase");
	
// Testing clear
	mp.clear();
	
	std::cout << GREEN("Map (after clear) : ");
	print(mp);

// Testing insert with value	
	mp.insert(ft::make_pair(1, "one"));
	mp.insert(ft::make_pair(2, "two"));
	mp.insert(ft::make_pair(3, "three"));

	std::cout << GREEN("Map (after insert with value) : ");
	print(mp);


// Testing insert with range
	ft::map<int, std::string> mp2;
	mp2.insert(ft::make_pair(4, "four"));
	mp2.insert(ft::make_pair(5, "five"));
	mp2.insert(ft::make_pair(6, "six"));
	mp.insert(mp2.begin(), mp2.end());

	std::cout << GREEN("Map (after insert with range iterator) : ");
	print(mp);

	// mp.displayTree();

// Testing erase with key
	mp.erase(2);

	std::cout << GREEN("Map (after erase with key) : ");
	print(mp);

	// mp.displayTree();

// Testing erase with iterator
	ft::map<int, std::string>::iterator it = mp.find(3);
	
	mp.erase(it);

	std::cout << GREEN("Map (after insert with iterator) : ");
	print(mp);

	// mp.displayTree();

	TITLE("--> Testing swap");
	
// Testing swap
	std::cout << GREEN("Map (before swap) : ");
	print(mp);
	
	std::cout << GREEN("Map2 (before swap) : ");
	print(mp2);

	mp.swap(mp2);

	std::cout << GREEN("Map (after swap) : ");
	print(mp);
	
	std::cout << GREEN("Map2 (after swap) : ");
	print(mp2);

	TITLE("Testing count and find");
	
// Testing count
	std::cout << GREEN("Map (lookup functions) : ") << std::endl;
	
	std::cout << "Count of key 4 : " << mp.count(4) << std::endl;
	
	mp.erase(4);
	
	std::cout << GREEN("Map (after erase of 4) : ");
	print(mp);
	
	std::cout << "Count of key 4 : " << mp.count(4) << std::endl;

// Testing find
	ft::map<int, std::string>::iterator found = mp.find(4);
	if (found != mp.end())
		std::cout << "Found key 4 :" << found->first << " => " << found->second << std::endl;
	else
		std::cout << "Not found key 4" << std::endl;

	found = mp.find(6);
	if (found != mp.end())
		std::cout << "Found key 6 : " << found->first << " => " << found->second << std::endl;
	else
		std::cout << "Not found key 6" << std::endl;

// Testing equal_range
	TITLE("--> Testing equal_range\n-> searching for key 4");
	RETURNS("std::pair containing a pair of iterators defining the wanted range: \
			 the first pointing to the first element that is not less than key and the second pointing to the first element greater than key.");
	ft::map<int, std::string>::iterator it_low;
	ft::map<int, std::string>::iterator it_high;
	ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator> ret;

	mp.insert(ft::make_pair(4, "four"));
	ret = mp.equal_range(4);

	it_low = ret.first;
	it_high = ret.second;

	std::cout << "\tfirst element that is not less than key = " << it_low->first << std::endl;
	std::cout << "\tfirst element greater than key = " << it_high->first << std::endl;

	// mp.displayTree();

	TITLE("Testing lower_bound and upper_bound");
	
	// Testing lower_bound
	ft::map<int, std::string>::iterator low = mp.lower_bound(4);
	std::cout << "Lower bound of 4: " << low->first << ": " << low->second << std::endl;

	// Testing upper_bound
	ft::map<int, std::string>::iterator up = mp.upper_bound(4);
	std::cout << "Upper bound of 4: " << up->first << ": " << up->second << std::endl;

	// Testing key_comp
	TITLE("--> Testing key_comp\n->key_comp(3, 4)");
	RETURNS("Returns the function object that compares the keys, which is a copy of this container's constructor argument comp. Default is std::less");
	ft::map<int, std::string>::key_compare my_key_comp = mp.key_comp();
	std::cout << my_key_comp(3, 4) << std::endl;
	TITLE("--> Testing key_comp\n->key_comp(5, 4)");
	std::cout << my_key_comp(5, 4) << std::endl;

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

	std::cout << GREEN("Map1 : ") << std::endl;
	print(map1);

	std::cout << GREEN("Map2 : ") << std::endl;
	print(map2);

	TITLE("--> Testing comparison, operator == != > >= < <=");

// test == operator
	if (map1 == map2)
		std::cout << "map1 and map2 are equal" << std::endl;
	else
		std::cout << "map1 and map2 are not equal" << std::endl;

// test != operator
	if (map1 != map2)
		std::cout << "map1 and map2 are not equal" << std::endl;
	else
		std::cout << "map1 and map2 are equal" << std::endl;

// test < operator
	if (map1 < map2)
		std::cout << "map1 is less than map2" << std::endl;
	else
		std::cout << "map1 is not less than map2" << std::endl;

// test <= operator
	if (map1 <= map2)
		std::cout << "map1 is less than or equal to map2" << std::endl;
	else
		std::cout << "map1 is not less than or equal to map2" << std::endl;

// test > operator
	if (map1 > map2)
		std::cout << "map1 is greater than map2" << std::endl;
	else
		std::cout << "map1 is not greater than map2" << std::endl;

// test >= operator
	if (map1 >= map2)
		std::cout << "map1 is greater than or equal to map2" << std::endl;
	else
		std::cout << "map1 is not greater than or equal to map2" << std::endl;
		
	TITLE("--> Testing non member swap function");

// test swap function

	std::cout << GREEN("Map1 (before swap) : ");
	print(map1);
	
	std::cout << GREEN("Map2 (before swap) : ");
	print(map2);

	std::swap(map1, map2);

	std::cout << GREEN("Map1 (after swap) : ");
	print(map1);
	
	std::cout << GREEN("Map2 (after swap) : ");
	print(map2);
}
