/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:25:00 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/22 16:37:04 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void	setTest( void )
{
	MAINTITLE("***** TESTING SET *****");
	
	TITLE("--> Testing default constructor and insert with 6 keys");
	
// Testing default constructor
	ft::set<std::string> st;

	SUBTITLE("Set : ");
	printSet(st);
	
// Testing insert
	st.insert("one");
	st.insert("two");
	st.insert("three");
	st.insert("one");
	st.insert("two");
	st.insert("three");
	st.insert("four");
	st.insert("five");
	st.insert("six");

	SUBTITLE("Set (after insert) : ");
	printSet(st);

	TITLE("--> Testing operator=");
	
	ft::set<std::string> st1;

	SUBTITLE("Set1 : ");
	printSet(st1);
	
// Testing operator=
	st1 = st;
	
	SUBTITLE("Set1 (after operator= with value from Set) : ");
	printSet(st1);

// Testing get_allocator
	std::allocator<std::string> alloc = st.get_allocator();
	(void)alloc;

	TITLE("--> Testing iterator and reverse_iterator");
		
// Testing begin and end
	SUBTITLE("Set (printed with iterator begin() and end()) : ");
	std::cout << "size : " << st.size() << std::endl << "content : " << std::endl;
	for (ft::set<std::string>::iterator it = st.begin(); it != st.end(); ++it)
		std::cout << *it << "  ";
	std::cout << std::endl << std::endl;

// Testing rbegin and rend
	SUBTITLE("Set (printed with reverse_iterator rbegin() and rend()) : ");
	std::cout << "size : " << st.size() << std::endl << "content : " << std::endl;
	for (ft::set<std::string>::reverse_iterator it = st.rbegin(); it != st.rend(); ++it)
		std::cout << *it << "  ";
	std::cout << std::endl << std::endl;

	TITLE("--> Testing empty, size and max_size");
	
// Testing empty, size, and max_size
	std::cout << "Empty : " << st.empty() << std::endl;
	std::cout << "Size : " << st.size() << std::endl;
	std::cout << "Max size : " << st.max_size() << std::endl;
	WARNING("max_size may differ between ft_containers and std containers!");

	TITLE("--> Testing clear, insert, and erase");
	
// Testing clear
	st.clear();
	
	SUBTITLE("Set (after clear) : ");
	printSet(st);

// Testing insert with value	
	st.insert("one");
	st.insert("two");
	st.insert("three");

	SUBTITLE("Set (after insert with value) : ");
	printSet(st);


// Testing insert with range
	ft::set<std::string> st2;
	st2.insert("four");
	st2.insert("five");
	st2.insert("six");
	st.insert(st2.begin(), st2.end());

	SUBTITLE("Set (after insert with range iterator) : ");
	printSet(st);

// Testing erase with key
	st.erase("two");

	SUBTITLE("Set (after erase with key) : ");
	printSet(st);

// Testing erase with iterator
	ft::set<std::string>::iterator it = st.find("three");
	
	st.erase(it);

	SUBTITLE("Set (after insert with iterator) : ");
	printSet(st);

	TITLE("--> Testing swap");
	
// Testing swap
	SUBTITLE("Set (before swap) : ");
	printSet(st);
	
	SUBTITLE("Set2 (before swap) : ");
	printSet(st2);

	st.swap(st2);

	SUBTITLE("Set (after swap) : ");
	printSet(st);
	
	SUBTITLE("Set2 (after swap) : ");
	printSet(st2);

	TITLE("--> Testing count and find");
	
// Testing count
	SUBTITLE("Set (lookup functions) : ");
	
	std::cout << std::endl << "Count of key 'four' : " << st.count("four") << std::endl << std::endl;
	
	st.erase("four");
	
	SUBTITLE("Set (after erase of 'four') : ");
	printSet(st);
	
	std::cout << "Count of key 'four' : " << st.count("four") << std::endl;

// Testing find
	ft::set<std::string>::iterator found = st.find("four");
	if (found != st.end())
		std::cout << "Found key 'four' :" << *found << std::endl;
	else
		std::cout << "Not found key 'four'" << std::endl;

	found = st.find("six");
	if (found != st.end())
		std::cout << "Found key 'six' : ( " << *found << " )" << std::endl;
	else
		std::cout << "Not found key 'six'" << std::endl;
	std::cout << std::endl;
	
// Testing equal_range
	TITLE("--> Testing equal_range");
	
	RETURNS("std::pair containing a pair of iterators defining the wanted range: the first pointing to the first element that is not less than key and the second pointing to the first element greater than key.");
	
	ft::set<std::string>::iterator it_low;
	ft::set<std::string>::iterator it_high;
	ft::pair<ft::set<std::string>::iterator, ft::set<std::string>::iterator> ret;

	st.insert("four");
	ret = st.equal_range("four");

	it_low = ret.first;
	it_high = ret.second;

	std::cout << "first element that is not less than key 'four'	: ( " << *it_low << " )" << std::endl;
	std::cout << "first element greater than key 'four'		: ( " << *it_high << " )" << std::endl << std::endl;

	TITLE("--> Testing lower_bound and upper_bound");
	
// Testing lower_bound
	ft::set<std::string>::iterator low = st.lower_bound("four");
	std::cout << "Lower bound of 'four' : ( " << *low << " )" << std::endl;

// Testing upper_bound
	ft::set<std::string>::iterator up = st.upper_bound("four");
	std::cout << "Upper bound of 'four' : ( " << *up << " )" << std::endl << std::endl;

	TITLE("--> Testing key_comp");
	
// Testing key_comp
	RETURNS("Returns the function object that compares the keys, which is a copy of this container's constructor argument comp. Default is std::less");
	
	ft::set<std::string>::key_compare my_key_comp = st.key_comp();
	
	std::cout << "key_comp('three', 'four') : " << my_key_comp("three", "four") << std::endl;
	std::cout << "key_comp('five', 'four') : " << my_key_comp("five", "four") << std::endl << std::endl;

	TITLE("--> Testing set non-member functions");

	ft::set<int> set1;
    ft::set<int> set2;
	
// insert some values
    set1.insert(10);
    set1.insert(20);
    set1.insert(30);

    set2.insert(10);
    set2.insert(20);
    set2.insert(40);

	SUBTITLE("Set1 : ");
	printSet(set1);

	SUBTITLE("Set2 : ");
	printSet(set2);

	TITLE("--> Testing comparison, operator == != > >= < <=");

// test == operator
	if (set1 == set2)
		std::cout << "Set1 and Set2 are equal" << std::endl;
	else
		std::cout << "Set1 and Set2 are not equal" << std::endl;

// test != operator
	if (set1 != set2)
		std::cout << "Set1 and Set2 are not equal" << std::endl;
	else
		std::cout << "Set1 and Set2 are equal" << std::endl;

// test < operator
	if (set1 < set2)
		std::cout << "Set1 is less than Set2" << std::endl;
	else
		std::cout << "Set1 is not less than Set2" << std::endl;

// test <= operator
	if (set1 <= set2)
		std::cout << "Set1 is less than or equal to Set2" << std::endl;
	else
		std::cout << "Set1 is not less than or equal to Set2" << std::endl;

// test > operator
	if (set1 > set2)
		std::cout << "Set1 is greater than Set2" << std::endl;
	else
		std::cout << "Set1 is not greater than Set2" << std::endl;

// test >= operator
	if (set1 >= set2)
		std::cout << "Set1 is greater than or equal to Set2" << std::endl;
	else
		std::cout << "Set1 is not greater than or equal to Set2" << std::endl;

	std::cout << std::endl;
		
	TITLE("--> Testing non member swap function");

// test swap function

	SUBTITLE("Set1 (before swap) : ");
	printSet(set1);
	
	SUBTITLE("Set2 (before swap) : ");
	printSet(set2);

	swap(set1, set2);

	SUBTITLE("Set1 (after swap) : ");
	printSet(set1);
	
	SUBTITLE("Set2 (after swap) : ");
	printSet(set2);
}
