/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:46:36 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/03 16:44:37 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

namepace ft
{
	/* PAIR ******************************************************************************* */
	
	template< class T1, class T2 >
	struct pair
	{
		public:
			
			typedef T1	first_type;
			typedef T2	second_type;

			first_type	first;
			second_type	second;

	// CONSTRUCTOR

			pair() : first(), second()	{ }

			explicit pair(const T1 &x, const T2 &y) : first( x ), second( y ) { }
			
			template< class U1, class U2 >
			explicit pair(const pair<U1, U2> &p) : first( p.first ), second( p.second ) { }
	
	// ASSIGNMENT OPERATOR

			pair	&operator=(const pair &p)
			{
				if (this != &p)
				{
					first = p.first;
					second = p.second;
				}

				return *this;
			}
		
	};
	
}

#endif
