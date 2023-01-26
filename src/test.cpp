/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:08:23 by foctavia          #+#    #+#             */
/*   Updated: 2023/01/26 15:51:13 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if REAL
    #include <map>
    #include <stack>
    #include <vector>
	#include <type_traits>
    namespace ft = std;
#else
    #include <type_traits.hpp>
	#include <iterators.hpp>
	#include <vector.hpp>
#endif

#include <ios>
#include <iostream>
#include <new>
#include <string>

void	is_integralTest( void )
{
    std::cout << "***TESTING IS_INTEGRAL TEMPLATE***" << "\n" << "\n";
    std::cout << std::boolalpha;
    std::cout << "char : " << ft::is_integral<char>::value << std::endl;
    std::cout << "const char : " << ft::is_integral<const char >::value << std::endl;
    std::cout << "const volatile int : " << ft::is_integral<const volatile int>::value << std::endl;
    std::cout << "float : " << ft::is_integral<float>::value << "\n";
    std::cout << "int : " << ft::is_integral<int>::value << "\n";
    std::cout << "ft::vector<int> : " << ft::is_integral<ft::vector<int> >::value << "\n";
    std::cout << "short : " << ft::is_integral<short>::value << "\n";
    std::cout << "***" << "\n";
}

template<typename T>
typename ft::enable_if<ft::is_integral<T>::value, T>::type add(T a, T b)
{
	return a + b;
}

template<typename T>
typename ft::enable_if<!ft::is_integral<T>::value, T>::type add(T a, T b)
{
	(void)a;
	(void)b;
	return T();
}

void	enable_ifTest( void )
{
	std::cout << add(1, 5);
	std::cout << add("hihi", "hoho");
}
 
void reverse_iteratorTest()
{
}

int main()
{
	is_integralTest();
	std::cout << std::endl;
	enable_ifTest();
	std::cout << std::endl;
	reverse_iteratorTest();
    return 0;
}

