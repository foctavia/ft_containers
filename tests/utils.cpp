/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:37:50 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/21 10:42:19 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void	MAINTITLE(std::string s)
{
	std::cout << std::endl << BLUE_ << s << RESET_ << std::endl << std::endl;
}

void	TITLE(std::string s)
{
	std::cout << std::endl;
	std::cout << ITALIC_GREEN_ << s << RESET_ << std::endl << std::endl;
}

void	SUBTITLE(std::string s)
{
	std::cout << GREEN_ << s << RESET_ << std::endl;
}

void	RETURNS(std::string s)
{
	std::cout << BOLD_ << "Return value" << RESET_ << std::endl;
	std::cout << ITALIC_ << s << RESET_ << std::endl << std::endl;
}

void	WARNING(std::string s)
{
	std::cout << YELLOW_ << " \u26A0 " << s << RESET_ << std::endl << std::endl;
}
