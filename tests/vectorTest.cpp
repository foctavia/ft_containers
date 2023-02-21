/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorTest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:13:23 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/21 11:46:55 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void vectorTest( void )
{
	MAINTITLE("***** TESTING VECTOR *****");
	
// vec -> test constructor and insert with count and value

	TITLE("--> Testing constructor and insert with count and value");
	
	ft::vector<int>	vec(5, 1);
	
	SUBTITLE("Vector (constructed with value) : ");
	printVector(vec);

	vec.insert(vec.begin(), 3, 2);

	SUBTITLE("Vector (after insert) : ");
	printVector(vec);
	
// vec1 -> test constructor with range iterator

	TITLE("--> Testing constructor with range iterator");

	ft::vector<int>	vec1(vec.begin(), vec.end());

	SUBTITLE("Vector1 (constructed with range iterator) : ");
	printVector(vec1);
	
	SUBTITLE("Comparison test :");
	if (vec == vec1)
		std::cout << "Vector and Vector1 is equal" << std:: endl << std::endl;
	else
		std::cout << "Vector and Vector1 is not equal" << std::endl << std::endl;

// vec2 -> test assignment operator and operator[] and at

	TITLE("--> Testing operator=, operator[], and at");

	ft::vector<int>	vec2;

	SUBTITLE("Vector2 : ");
	printVector(vec2);

	vec2.insert(vec2.begin(), 6);

	SUBTITLE("Vector2 (after insert) : ");
	printVector(vec2);

	vec2 = vec;

	SUBTITLE("Vector2 (after operator= with Vector) : ");
	printVector(vec2);

	SUBTITLE("Comparison test :");
	if (vec != vec2)
		std::cout << "Vector and Vector2 is not equal" << std::endl << std::endl;
	else
		std::cout << "Vector and Vector2 is equal" << std::endl << std::endl;
	
	SUBTITLE("Vector2 (element access) : ");
	std::cout << "Vector2.front()	: " << vec2.front() << std::endl
		<< "Vector2[2]	: " << vec2[2] << std::endl 
		<< "Vector2.at(3)	: " << vec2.at(3) << std::endl 
		<< "Vector2.back()	: " << vec2.back() << std::endl << std::endl;

// vec3 -> test pushback, popback, swap, erase, reverse_iterator

	TITLE("--> Testing push_back, pop_back, swap, erase, reverse_iterator");

	ft::vector<int>	vec3;

	SUBTITLE("Vector3 : ");
	printVector(vec3);

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

	SUBTITLE("Vector3 (after push_back) : ");
	printVector(vec3);

	vec3.pop_back();

	SUBTITLE("Vector3 (after pop_back) : ");
	printVector(vec3);

	vec3.erase(vec3.begin() + 4);

	SUBTITLE("Vector3 (after erase with single iterator) : ");
	printVector(vec3);

	vec3.erase(vec3.begin() + 6, vec3.begin() + 8);

	SUBTITLE("Vector3 (after erase with range iterator) : ");
	printVector(vec3);

	SUBTITLE("Comparison test :");
	if (vec2 < vec3)
		std::cout << "Vector2 is less than vec3" << std:: endl << std::endl;
	else
		std::cout << "Vector2 is not less than vec3" << std::endl << std::endl;
	
	vec3.swap(vec2);

	SUBTITLE("Vector3 (after swap with Vector2) : ");
	printVector(vec3);

	SUBTITLE("Vector2 (after swap with Vector3) : ");
	printVector(vec2);

	SUBTITLE("Comparison test :");
	if (vec2 < vec3)
		std::cout << "Vector2 is less than vec3" << std:: endl << std::endl;
	else
		std::cout << "Vector2 is not less than vec3" << std::endl << std::endl;

	SUBTITLE("Vector2 (printed with reverse_iterator) : ");
	std::cout << "size : " << vec2.size() << "  capacity : " << vec2.capacity() << std::endl << "content : ";
	for(ft::vector<int>::reverse_iterator rit = vec2.rbegin(); rit != vec2.rend(); ++rit)
			std::cout << *rit << " ";
	std::cout << std::endl << std::endl;

// vec4 & vec5 -> test resize, data and assign

	TITLE("--> Testing resize, data, and assign");

	ft::vector<int>	vec4(3, 6);

	SUBTITLE("Vector4 : ");
	printVector(vec4);

	vec4.resize(6, 7);

	SUBTITLE("Vector4 (after resize with more value) : ");
	printVector(vec4);

	ft::vector<int>	vec5 = vec4;

	SUBTITLE("Vector5 (assigned with operator= the value of Vector4) : ");
	printVector(vec5);

	vec4.resize(4, 8);

	SUBTITLE("Vector4 (after resize with less value) : ");
	printVector(vec4);

	SUBTITLE("Vector4 (printed with data()) : ");
	std::cout << "size : " << vec4.size() << "  capacity : " << vec4.capacity() << std::endl << "content : ";
	for(size_t i = 0; i < vec4.size(); ++i)
			std::cout << *(vec4.data() + i) << " ";
	std::cout << std::endl << std::endl;

	vec4.assign(15, 3);

	SUBTITLE("Vector4 (after assign with value) : ");
	printVector(vec4);

	SUBTITLE("Comparison test :");
	if (vec4 > vec5)
		std::cout << "Vector4 is more than Vector5" << std:: endl << std::endl;
	else
		std::cout << "Vector4 is not more than Vector5" << std::endl << std::endl;

	SUBTITLE("Vector5 : ");
	printVector(vec5);

	vec5.assign(vec4.begin(), vec4.begin() + 5);

	SUBTITLE("Vector5 (after assign with range iterator): ");
	printVector(vec5);

// vec6 & vec7 -> test exception

	TITLE("--> Testing error and exception");

	ft::vector<int>	vec6;
	ft::vector<int>	vec7;
	
	ft::vector<int>::iterator it5 = vec5.begin();
	try
	{
		vec7.insert(vec7.begin(), it5, vec6.begin());
		
		SUBTITLE("Vector7 (after insert with a range of different iterator): ");
		printVector(vec7);
	}
	catch(const std::exception &e)
	{
		std::cerr << RED("ERROR : ") << e.what() << std::endl << std::endl;
	}
	
	try
	{	
		ft::vector<int>	vec8(it5, vec6.begin());

		SUBTITLE("Vector8 (constructed with a range of different iterator): ");
		printVector(vec8);
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