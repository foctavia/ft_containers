/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackTest.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:25:11 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/21 12:21:02 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void	stackTest( void )
{
	MAINTITLE("***** TESTING STACK *****");

	TITLE("--> Testing default constructor");
	
// default constructor
	ft::stack<int> s1;
	
	SUBTITLE("Stack1 : ");
	printStack(s1);
	
	TITLE("Testing push, pop, and top");
	
	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);
	s1.push(5);
	
	SUBTITLE("Stack1 (after push) : ");
	printStack(s1);

// pop
	s1.pop();
	
	SUBTITLE("Stack1 (after pop) : ");
	printStack(s1);

// top
	std::cout << "Stack1 top: " << s1.top() << std::endl << std::endl;

// empty
	TITLE("--> Testing empty and size");
	
	std::cout << "Stack1 empty() : " << (s1.empty() ? "true" : "false") << std::endl;

// size
	std::cout << "Stack1 size() : " << s1.size() << std::endl << std::endl;
	
	TITLE("--> Testing copy constructor and operator=");
	
// copy constructor
	ft::stack<int> s2(s1);
	
	SUBTITLE("Stack2 (created by copying Stack1) : ");
	printStack(s2);

// operator=
	ft::stack<int> s3;
	s3 = s2;
	
	SUBTITLE("Stack3 (created with operator= to the value of Stack2) : ");
	printStack(s3);

	TITLE("--> Testing comparison, operator== != < <= > >=");
	
// operator==
	std::cout << "Stack2 == Stack3 : " << (s2 == s3 ? "true" : "false") << std::endl;

// operator!=
	std::cout << "Stack2 != Stack3 : " << (s2 != s3 ? "true" : "false") << std::endl;
	
	std::cout << std::endl;

	ft::stack<int> s4;
	s4.push(6);
	s4.push(7);
	
	SUBTITLE("Stack4 : ");
	printStack(s4);
	
// operator<
	std::cout << "Stack3 < Stack4 : " << (s3 < s4 ? "true" : "false") << std::endl;

// operator<=
	std::cout << "Stack3 <= Stack4 : " << (s3 <= s4 ? "true" : "false") << std::endl;

// operator>
	std::cout << "Stack3 > Stack4 : " << (s3 > s4 ? "true" : "false") << std::endl;

// operator>=
	std::cout << "Stack3 >= Stack4 : " << (s3 >= s4 ? "true" : "false") << std::endl;
	
	std::cout << std::endl;

	TITLE("--> Testing non member swap function");

// test swap function

	SUBTITLE("Stack3 (before swap) : ");
	printStack(s3);
	
	SUBTITLE("Stack4 (before swap) : ");
	printStack(s4);
	
	swap(s3, s4);
	
	SUBTITLE("Stack3 (after swap) : ");
	printStack(s3);
	
	SUBTITLE("Stack4 (after swap) : ");
	printStack(s4);
}
