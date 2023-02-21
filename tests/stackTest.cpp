/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackTest.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:25:11 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/21 08:21:55 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

template <typename T>
void print_stack(ft::stack<T>& src)
{
	ft::stack<int>	s(src);
    while (!s.empty())
	{
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
}

int main()
{

	std::cout << PURPLE("***** TESTING STACK *****") << std::endl << std::endl;

	TITLE("Testing default constructor\n-> create s1 and push 3 elements");
    // default constructor
    ft::stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    std::cout << "printing s1" << std::endl;
    print_stack(s1);

    // copy constructor
	TITLE("Testing copy constructor\n-> create s2 as a copy of s1");
    ft::stack<int> s2(s1);
    // std::cout << "printing s2";
    // print_stack(s2);

    // // operator=
	// TITLE("Testing operator=\n-> create s2 as a copy of s1");
    // ft::stack<int> s3;
    // s3 = s2;
    // std::cout << "printing s3";
    // print_stack(s3);

    // // empty
	// TITLE("Testing empty");
    // std::cout << "is s1 empty? " << (s1.empty() ? "true" : "false") << std::endl;

    // // size
	// TITLE("Testing size");
    // std::cout << "s1 size: " << s1.size() << std::endl;

    // // push
	// TITLE("Testing push");
    // s1.push(4);
    // s1.push(5);
    // std::cout << "s1 after push: ";
    // print_stack(s1);

    // // top
	// TITLE("Testing top");
    // std::cout << "s1 top: " << s1.top() << std::endl;

    // // pop
	// TITLE("Testing pop");
    // s1.pop();
    // std::cout << "s1 after pop: ";
    // print_stack(s1);

    // // operator==
	// TITLE("Testing operator==");
    // ft::stack<int> s4(s3);
    // std::cout << "s3 == s4? " << (s3 == s4 ? "true" : "false") << std::endl;

    // // operator!=
	// TITLE("Testing operator!=");
    // std::cout << "s3 != s4? " << (s3 != s4 ? "true" : "false") << std::endl;

    // // operator<
	// TITLE("Testing operator<\n->s5.push(6) and creating stack s5 as a copy of s3");
    // ft::stack<int> s5(s3);
    // s5.push(6);
    // std::cout << "s3 < s5? " << (s3 < s5 ? "true" : "false") << std::endl;

    // // operator<=
	// TITLE("Testing operator<=");
    // std::cout << "s3 <= s5? " << (s3 <= s5 ? "true" : "false") << std::endl;

    // // operator>
	// TITLE("Testing operator>");
    // std::cout << "s5 > s3? " << (s5 > s3 ? "true" : "false") << std::endl;

    // // operator>=
	// TITLE("Testing operator>=");
    // std::cout << "s5 >= s3? " << (s5 >= s3 ? "true" : "false") << std::endl;

    // // swap
	// TITLE("Testing swap");
    // std::cout << "Before swap:" << std::endl;
    // std::cout << "s3: ";
    // print_stack(s3);
    // std::cout << "s5: ";
    // print_stack(s5);
    // swap(s3, s5);
    // std::cout << "s3: ";
    // print_stack(s3);
    // std::cout << "s5: ";
    // std::cout << "After swap:" << std::endl;
    // print_stack(s5);

	return 0;
}
