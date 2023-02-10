/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:46:36 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/10 15:20:34 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{
	/* PAIR ******************************************************************************* */
	
	template< class T1, class T2 >
	class pair
	{
		public:
			
			typedef T1	first_type;
			typedef T2	second_type;

			first_type	first;
			second_type	second;

	// CONSTRUCTOR

			pair( void ) : first(), second()	{ }

			pair( const T1 &x, const T2 &y ) : first( x ), second( y )	{ }
			
			template< class U1, class U2 >
			pair( const pair<U1, U2> &p ) : first( p.first ), second( p.second ) { }
	
	// ASSIGNMENT OPERATOR

			pair	&operator=( const pair &p )
			{
				if (this != &p)
				{
					first = p.first;
					second = p.second;
				}

				return *this;
			}

			// template< class U1, class U2 >
			// pair	&operator=( const pair< U1, U2 > &p )
			// {
			// 	first = p.first;
			// 	second = p.second;

			// 	return *this;
			// }
	};
	
	template< class T1, class T2 >
	ft::pair< T1, T2 >	make_pair( T1 t, T2 u )
	{
		return ft::pair< T1, T2 >(t, u);
	}

	template< class T1, class T2 >
	inline bool			operator==(const ft::pair< T1, T2 > &lhs, const ft::pair< T1, T2 > &rhs )
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template< class T1, class T2 >
	inline bool			operator!=(const ft::pair< T1, T2 > &lhs, const ft::pair< T1, T2 > &rhs )
	{
		return !(lhs == rhs);
	}

	template< class T1, class T2 >
	inline bool			operator<(const ft::pair< T1, T2 > &lhs, const ft::pair< T1, T2 > &rhs )
	{
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template< class T1, class T2 >
	inline bool			operator<=(const ft::pair< T1, T2 > &lhs, const ft::pair< T1, T2 > &rhs )
	{
		return !(rhs < lhs);
	}

	template< class T1, class T2 >
	inline bool			operator>(const ft::pair< T1, T2 > &lhs, const ft::pair< T1, T2 > &rhs )
	{
		return rhs < lhs;
	}

	template< class T1, class T2 >
	inline bool			operator>=(const ft::pair< T1, T2 > &lhs, const ft::pair< T1, T2 > & rhs )
	{
		return !(lhs < rhs);
	}
	
}

#endif
