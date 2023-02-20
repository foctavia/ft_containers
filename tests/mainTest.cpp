/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainTest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:08:23 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/20 17:45:01 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

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

int main( void )
{
	// vectorTest();
	mapTest();
	// stackTest();
	// setTest();
	
    return 0;
}

