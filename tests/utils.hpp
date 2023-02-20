/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:10:12 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/20 18:09:57 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if REAL
	#include <map>
	#include <vector>
	#include <set>
	#include <stack>
	namespace ft = std;
#else
	#include "map.hpp"
	#include "vector.hpp"
	#include "set.hpp"
	#include "stack.hpp"
#endif

#include <iostream>

#define _pair namespace::pair

#define RED(s) "\033[1;31m" s "\033[m"
#define GREEN(s) "\033[1;32m" s "\033[m"
#define YELLOW(s) "\033[1;33m" s "\033[m"
#define BLUE(s) "\033[1;34m" s "\033[m"
#define PURPLE(s) "\033[1;35m" s "\033[m"
#define ITALIC_GREEN_ "\033[3;32m"
#define YELLOW_ "\033[1;33m"
#define BLUE_ "\033[1;34m"
#define PURPLE_ "\033[1;35m"
#define BOLD_ "\e[1m"
#define ITALIC_ "\e[3m"
#define RESET_ "\033[m"

#define nl() std::cout << std::endl;


// void	MAINTITLE(std::string s);
// void	TITLE(std::string s);
// void	SUBTITLE(std::string s);
// void	RETURNS(std::string s);
// void	WARNING(std::string s);

// void	vectorTest( void );
// void	mapTest( void );
// void	stackTest( void );
// void	setTest( void );

void	MAINTITLE(std::string s)
{
	std::cout << PURPLE_ << s << RESET_ << std::endl;
}

void	TITLE(std::string s)
{
	std::cout << std::endl;
	std::cout << ITALIC_GREEN_ << s << RESET_ << std::endl;
}

void	SUBTITLE(std::string s)
{
	std::cout << std::endl;
	std::cout << BLUE_ << s << RESET_ << std::endl << std::endl;
}

void	RETURNS(std::string s)
{
	std::cout << BOLD_ << "Return value" << RESET_ << std::endl;
	std::cout << ITALIC_ << s << RESET_ << std::endl;
}

void	WARNING(std::string s)
{
	std::cout << YELLOW_ << " \u26A0 " << s << RESET_ << std::endl;
}


template< typename T >
void	print( T &container )
{
	std::cout << std::endl << "size : " << container.size() << "  capacity : " << container.capacity() << std::endl;
	
	if (container.empty())
		std::cout << "Container is empty" << std::endl << std::endl;
	else
	{
		std::cout << "content : ";
		for (size_t i = 0; i < container.size(); ++i)
			std::cout << container[i] << " ";
			
		std::cout << std::endl << std::endl;
	}
}

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}