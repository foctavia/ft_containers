/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorTest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:13:23 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/20 16:26:16 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void vectorTest( void )
{
	std::cout << PURPLE("***** TESTING VECTOR *****") << std::endl << std::endl;
	
// vec -> test constructor and insert with count and value

	std::cout << std::endl << BLUE("--> Testing constructor and insert with count and value") << std::endl << std::endl;
	
	ft::vector<int>	vec(5, 1);
	
	std::cout << GREEN("Vec (constructed with value) : ");
	print(vec);

	vec.insert(vec.begin(), 3, 2);

	std::cout << GREEN("Vec (after insert) : ");
	print(vec);
	
// vec1 -> test constructor with range iterator

	std::cout << std::endl << BLUE("--> Testing constructor with range iterator") << std::endl << std::endl;

	ft::vector<int>	vec1(vec.begin(), vec.end());

	std::cout << GREEN("Vec1 (constructed with range iterator) : ");
	print(vec1);
	
	std::cout << YELLOW("Comparison test :") << std::endl;
	if (vec == vec1)
		std::cout << "Vec and Vec1 is equal" << std:: endl << std::endl;
	else
		std::cout << "Vec and Vec1 is not equal" << std::endl << std::endl;

// vec2 -> test assignment operator and operator[] and at

	std::cout << std::endl << BLUE("--> Testing operator=, operator[], and at") << std::endl << std::endl;

	ft::vector<int>	vec2;

	std::cout << GREEN("Vec2 : ");
	print(vec2);

	vec2.insert(vec2.begin(), 6);

	std::cout << GREEN("Vec2 (after insert) : ");
	print(vec2);

	vec2 = vec;

	std::cout << GREEN("Vec2 (after operator= with Vec) : ");
	print(vec2);

	std::cout << YELLOW("Comparison test :") << std::endl;
	if (vec != vec2)
		std::cout << "Vec and Vec2 is not equal" << std::endl << std::endl;
	else
		std::cout << "Vec and Vec2 is equal" << std::endl << std::endl;
	
	std::cout << GREEN("Vec2 (element access) : ") << std::endl;
	std::cout << "Vec2.front()	: " << vec2.front() << std::endl
		<< "Vec2[2]		: " << vec2[2] << std::endl 
		<< "Vec2.at(3)	: " << vec2.at(3) << std::endl 
		<< "Vec2.back()	: " << vec2.back() << std::endl << std::endl;

// vec3 -> test pushback, popback, swap, erase, reverse_iterator

	std::cout << std::endl << BLUE("--> Testing push_back, pop_back, swap, erase, reverse_iterator") << std::endl << std::endl;

	ft::vector<int>	vec3;

	std::cout << GREEN("Vec3 : ");
	print(vec3);

	vec3.push_back(1);
	vec3.push_back(2);
	vec3.push_back(3);
	vec3.push_back(4);
	vec3.push_back(5);
	vec3.push_back(5);
	vec3.push_back(6);
	vec3.push_back(6);
	vec3.push_back(7);
	vec3.push_back(7);
	vec3.push_back(8);
	vec3.push_back(8);

	std::cout << GREEN("Vec3 (after push_back) : ");
	print(vec3);

	vec3.pop_back();

	std::cout << GREEN("Vec3 (after pop_back) : ");
	print(vec3);

	vec3.erase(vec3.begin() + 4);

	std::cout << GREEN("Vec3 (after erase with single iterator) : ");
	print(vec3);

	vec3.erase(vec3.begin() + 6, vec3.begin() + 8);

	std::cout << GREEN("Vec3 (after erase with range iterator) : ");
	print(vec3);

	std::cout << YELLOW("Comparison test :") << std::endl;
	if (vec2 < vec3)
		std::cout << "Vec2 is less than vec3" << std:: endl << std::endl;
	else
		std::cout << "Vec2 is not less than vec3" << std::endl << std::endl;
	
	vec3.swap(vec2);

	std::cout << GREEN("Vec3 (after swap with Vec2) : ");
	print(vec3);

	std::cout << GREEN("Vec2 (after swap with Vec3) : ");
	print(vec2);

	std::cout << YELLOW("Comparison test :") << std::endl;
	if (vec2 < vec3)
		std::cout << "Vec2 is less than vec3" << std:: endl << std::endl;
	else
		std::cout << "Vec2 is not less than vec3" << std::endl << std::endl;

	std::cout << GREEN("Vec2 (printed with reverse_iterator) : ") << std::endl;
	std::cout << "size : " << vec2.size() << "  capacity : " << vec2.capacity() << std::endl << "content : ";
	for(ft::vector<int>::reverse_iterator rit = vec2.rbegin(); rit != vec2.rend(); ++rit)
			std::cout << *rit << " ";
	std::cout << std::endl << std::endl;

// vec4 & vec5 -> test resize, data and assign

	std::cout << std::endl << BLUE("--> Testing resize, data, and assign") << std::endl << std::endl;

	ft::vector<int>	vec4(3, 6);

	std::cout << GREEN("Vec4 : ");
	print(vec4);

	vec4.resize(6, 7);

	std::cout << GREEN("Vec4 (after resize with more value) : ");
	print(vec4);

	ft::vector<int>	vec5 = vec4;

	std::cout << GREEN("Vec5 (assigned with operator= the value of Vec4) : ");
	print(vec5);

	vec4.resize(4, 8);

	std::cout << GREEN("Vec4 (after resize with less value) : ");
	print(vec4);

	std::cout << GREEN("Vec4 (printed with data()) : ") << std::endl;
	std::cout << "size : " << vec4.size() << "  capacity : " << vec4.capacity() << std::endl << "content : ";
	for(size_t i = 0; i < vec4.size(); ++i)
			std::cout << *(vec4.data() + i) << " ";
	std::cout << std::endl << std::endl;

	vec4.assign(15, 3);

	std::cout << GREEN("Vec4 (after assign with value) : ");
	print(vec4);

	std::cout << YELLOW("Comparison test :") << std::endl;
	if (vec4 > vec5)
		std::cout << "Vec4 is more than Vec5" << std:: endl << std::endl;
	else
		std::cout << "Vec4 is not more than Vec5" << std::endl << std::endl;

	std::cout << GREEN("Vec5 : ");
	print(vec5);

	vec5.assign(vec4.begin(), vec4.begin() + 5);

	std::cout << GREEN("Vec5 (after assign with range iterator): ");
	print(vec5);

// vec6 & vec7 -> test exception

	std::cout << std::endl << BLUE("--> Testing error and exception") << std::endl << std::endl;

	ft::vector<int>	vec6;
	ft::vector<int>	vec7;
	
	ft::vector<int>::iterator it5 = vec5.begin();
	try
	{
		vec7.insert(vec7.begin(), it5, vec6.begin());
		
		std::cout << GREEN("Vec7 (after insert with a range of different iterator): ");
		print(vec7);
	}
	catch(const std::exception &e)
	{
		std::cerr << RED("ERROR : ") << e.what() << std::endl << std::endl;
	}
	
	try
	{	
		ft::vector<int>	vec8(it5, vec6.begin());

		std::cout << GREEN("Vec8 (constructed with a range of different iterator): ");
		print(vec8);
	}
	catch(const std::exception &e)
	{
		std::cerr << RED("ERROR : ") << "construction : " << e.what() << std::endl << std::endl;
	}

	try
	{	
		vec.at(vec.size());
	}
	catch(const std::exception &e)
	{
		std::cerr << RED("ERROR : ") << e.what() << std::endl << std::endl;
	}

	try
	{	
		vec.reserve(vec.max_size());
	}
	catch(const std::exception &e)
	{
		std::cerr << RED("ERROR : ") << e.what() << std::endl << std::endl;
	}

	try
	{	
		vec.reserve(vec.max_size() + 1);
	}
	catch(const std::exception &e)
	{
		std::cerr << RED("ERROR : ") << e.what() << std::endl << std::endl;
	}

	try
	{	
		vec.resize(vec.max_size(), 0);
	}
	catch(const std::exception &e)
	{
		std::cerr << RED("ERROR : ") << e.what() << std::endl << std::endl;
	}

	try
	{	
		vec.resize(vec.max_size() + 1, 0);
	}
	catch(const std::exception &e)
	{
		std::cerr << RED("ERROR : ") << e.what() << std::endl << std::endl;
	}
	
}