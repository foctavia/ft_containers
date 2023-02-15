/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainTest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:08:23 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/15 17:54:15 by foctavia         ###   ########.fr       */
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

#include "vectorTest.cpp"
#include "mapTest.cpp"

void vectorTest( void )
{
// vec -> test constructor and insert with count and value
	ft::vector<int>	vec(3, 2);
	
	if (vec.empty())
		std::cout << "is empty" << std::endl;
		
	ft::vector<int>::iterator	it;

	std::cout << "vec : ";
	for(it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";	
	std::cout << std::endl;

	vec.insert(vec.begin(), 3, 6);

	std::cout << "vec : ";
	for(it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";	
	std::cout << std::endl << std::endl;
	
// vec1 -> test constructor with range iterator

	ft::vector<int>	vec1(vec.begin(), vec.end());
	
	if (vec == vec1)
		std::cout << "vec and vec1 is equal" << std:: endl;
	else
		std::cout << "vec and vec1 is not equal" << std::endl;

	std::cout << "vec1 : ";
	for(ft::vector<int>::iterator it1 = vec1.begin(); it1 != vec1.end(); ++it1)
			std::cout << *it1 << " ";
	std::cout << std::endl;
	std::cout << "vec1 capacity " << vec1.capacity() 
		<< "  vec1 size " << vec1.size() 
		<< std::endl << std::endl;

// vec2 -> test assignment operator and operator[] and at

	ft::vector<int>	vec2;

	vec2.insert(vec2.begin(), 6);

	std::cout << "vec2 : ";
	for(ft::vector<int>::iterator it2 = vec2.begin(); it2 != vec2.end(); ++it2)
			std::cout << *it2 << " ";
	std::cout << std::endl;
	std::cout << "vec2 capacity " << vec2.capacity() 
		<< "  vec2 size " << vec2.size() << std::endl;

	vec2 = vec;

	if (vec != vec2)
		std::cout << "vec and vec2 is not equal" << std:: endl;
	else
		std::cout << "vec and vec2 is equal" << std::endl;

	std::cout << "vec2 : ";
	for(ft::vector<int>::iterator it2 = vec2.begin(); it2 != vec2.end(); ++it2)
			std::cout << *it2 << " ";
	std::cout << std::endl;
	std::cout << "vec2 capacity " << vec2.capacity() << "  vec2 size " << vec2.size() << std::endl;
	
	std::cout << "elem access : ";
	std::cout << vec2.front() << " " 
		<< vec2[2] << " " 
		<< vec2.at(3) << " " 
		<< vec2.back() << std::endl << std::endl;

// vec3 -> test pushback, popback, swap, erase

	ft::vector<int>	vec3;

	vec3.insert(vec3.begin(), 3, 4);
	vec3.push_back(5);
	vec3.push_back(5);
	vec3.push_back(6);
	vec3.push_back(6);
	vec3.push_back(7);
	vec3.push_back(7);
	vec3.push_back(8);
	vec3.push_back(8);


	std::cout << "vec3 : ";
	for(ft::vector<int>::iterator it3 = vec3.begin(); it3 != vec3.end(); ++it3)
			std::cout << *it3 << " ";
	std::cout << std::endl;

	vec3.pop_back();
	
	std::cout << "after pop_back" << std::endl << "vec3 : ";
	for(ft::vector<int>::iterator it3 = vec3.begin(); it3 != vec3.end(); ++it3)
			std::cout << *it3 << " ";
	std::cout << std::endl;

	vec3.erase(vec3.begin() + 3);
	
	std::cout << "after erase" << std::endl << "vec3 : ";
	for(ft::vector<int>::iterator it3 = vec3.begin(); it3 != vec3.end(); ++it3)
			std::cout << *it3 << " ";
	std::cout << std::endl;

	vec3.erase(vec3.begin() + 5, vec3.begin() + 7);
	
	std::cout << "after erase range" << std::endl << "vec3 : ";
	for(ft::vector<int>::iterator it3 = vec3.begin(); it3 != vec3.end(); ++it3)
			std::cout << *it3 << " ";
	std::cout << std::endl;

	if (vec2 < vec3)
		std::cout << "vec2 is less than vec3" << std:: endl << std::endl;
	else
		std::cout << "vec2 is not less than vec3" << std::endl << std::endl;
	
	vec3.swap(vec2);
	
	std::cout << "after swap" << std::endl;
	
	std::cout << "vec2 : ";
	for(ft::vector<int>::iterator it2 = vec2.begin(); it2 != vec2.end(); ++it2)
			std::cout << *it2 << " ";
	std::cout << std::endl;
	std::cout << "vec2 capacity " << vec2.capacity() << "  vec2 size " << vec2.size() << std::endl;

	std::cout << "vec3 : ";
	for(ft::vector<int>::iterator it3 = vec3.begin(); it3 != vec3.end(); ++it3)
			std::cout << *it3 << " ";
	std::cout << std::endl;
	std::cout << "vec3 capacity " << vec3.capacity() << "  vec3 size " << vec3.size() << std::endl;

	if (vec2 < vec3)
		std::cout << "vec2 is less than vec3" << std:: endl << std::endl;
	else
		std::cout << "vec2 is not less than vec3" << std::endl << std::endl;

// vec4 -> test resize and assign

	ft::vector<int>	vec4;
	
	vec4.insert(vec4.begin(), 3, 4);

	std::cout << "vec4 : ";
	for(ft::vector<int>::iterator it4 = vec4.begin(); it4 != vec4.end(); ++it4)
			std::cout << *it4 << " ";
	std::cout << std::endl;

	vec4.resize(6, 7);
	
	std::cout << "after resize more" << std::endl << "vec4 : ";
	for(ft::vector<int>::iterator it4 = vec4.begin(); it4 != vec4.end(); ++it4)
			std::cout << *it4 << " ";
	std::cout << std::endl;
	std::cout << "vec4 capacity " << vec4.capacity() << "  vec4 size " << vec4.size() << std::endl;

	ft::vector<int>	vec5 = vec4;

	vec4.resize(4, 8);
	
	std::cout << "after resize less" << std::endl << "vec4 : ";
	for(ft::vector<int>::iterator it4 = vec4.begin(); it4 != vec4.end(); ++it4)
			std::cout << *it4 << " ";
	std::cout << std::endl;

	std::cout << "with data" << std::endl << "vec4 : ";
	for(size_t i = 0; i < vec4.size(); ++i)
			std::cout << *(vec4.data() + i) << " ";
	std::cout << std::endl;
	std::cout << "vec4 capacity " << vec4.capacity() << "  vec4 size " << vec4.size() << std::endl;

	vec4.assign(15, 3);

	std::cout << "after assign " << std::endl << "vec4 : ";
	for(ft::vector<int>::iterator it4 = vec4.begin(); it4 != vec4.end(); ++it4)
			std::cout << *it4 << " ";
	std::cout << std::endl;
	std::cout << "vec4 capacity " << vec4.capacity() << "  vec4 size " << vec4.size() << std::endl << std::endl;

	if (vec4 > vec5)
		std::cout << "vec4 is more than vec5" << std:: endl;
	else
		std::cout << "vec4 is not more than vec5" << std::endl;

	std::cout << "vec5 : ";
	for(ft::vector<int>::iterator it5 = vec5.begin(); it5 != vec5.end(); ++it5)
			std::cout << *it5 << " ";
	std::cout << std::endl;
	std::cout << "vec5 capacity " << vec5.capacity() << "  vec5 size " << vec5.size() << std::endl;

	vec5.assign(vec4.begin(), vec4.begin() + 5);

	std::cout << "after assign " << std::endl << "vec5 : ";
	for(ft::vector<int>::iterator it5 = vec5.begin(); it5 != vec5.end(); ++it5)
			std::cout << *it5 << " ";
	std::cout << std::endl;
	std::cout << "vec5 capacity " << vec5.capacity() << "  vec5 size " << vec5.size() << std::endl << std::endl;

	std::cout << "with reverse_iterator " << std::endl << "vec5 : ";
	for(ft::vector<int>::reverse_iterator it5 = vec5.rbegin(); it5 != vec5.rend(); ++it5)
			std::cout << *it5 << " ";
	std::cout << std::endl;
	std::cout << "vec5 capacity " << vec5.capacity() << "  vec5 size " << vec5.size() << std::endl << std::endl;

	ft::vector<int>	vec6;
	
	ft::vector<int>::iterator it5 = vec5.begin();
	ft::vector<int>	vec7;
	
	vec7.insert(vec7.begin(), it5, vec6.begin());

	std::cout << "vec7 : ";
	for(ft::vector<int>::iterator it7 = vec7.begin(); it7 != vec7.end(); ++it7)
			std::cout << *it7 << " ";
	std::cout << std::endl;
	std::cout << "vec7 capacity " << vec7.capacity() << "  vec7 size " << vec7.size() << std::endl << std::endl;

	ft::vector<int>	vec8(it5, vec6.begin());

	std::cout << "vec8 : ";
	for(ft::vector<int>::iterator it8 = vec8.begin(); it8 != vec8.end(); ++it8)
			std::cout << *it8 << " ";
	std::cout << std::endl;
	std::cout << "vec8 capacity " << vec8.capacity() << "  vec8 size " << vec8.size() << std::endl << std::endl;
	
}

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

	std::cout << std::endl << "End" << std::endl << std::endl;
}

int main( void )
{
	// vectorTest();
	mapTest();
	
    return 0;
}

