/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:44:31 by foctavia          #+#    #+#             */
/*   Updated: 2023/01/26 18:48:34 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <iterators.hpp>

namespace ft
{
	// normal_iterator
	
	template< typename Iter >
	class normal_iterator : public std::iterator< std::random_access_iterator_tag, class T, std::ptrdiff_t, T *, T& >
	{
		protected:
			
			Iter											current;
			typedef iterator_traits< Iter >					traits_type;

		public:
			
			typedef Iter									iterator_type;
			typedef typename traits_type::iterator_category	iterator_category;
			typedef typename traits_type::value_type		value_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::reference			reference;
			typedef typename traits_type::pointer			pointer;

	// CONTRUCTOR

		normal_iterator( void ) : current( Iter() ) { }
		explicit normal_iterator( const Iter &i ) : current( i ) { }

	// DESTRUCTOR

		~normal_iterator( void ) { }

	// MEMBER FUNCTION

		reference	operator[]( const difference_type &n ) const
		{ return current[ n ]; }

		normal_iterator		&operator+=( const difference_type &n )
		{
			current += n;
			return *this;
		}

		normal_iterator		operator+( const difference_type &n ) const
		{ return normal_iterator( current + n ); }

		normal_iterator		&operator-=( const difference_type &n )
		{
			current -= n;
			return *this;
		}

		normal_iterator		operator-( const difference_type &n ) const
		{ return normal_iterator( current - n ); }

		const Iter			&base() const
		{ return current; }
		
	};

	// NON-MEMBER FUNCTION

	template< typename Iter1, typename Iter2 >
	inline bool	operator<( const normal_iterator< Iter1 > &lhs, const normal_iterator< Iter2 > &rhs )
	{ return lhs.base() < rhs.base(); }

	template< typename Iter >
	inline bool	operator<( const normal_iterator< Iter > &lhs, const normal_iterator< Iter > &rhs )
	{ return lhs.base() < rhs.base(); }

	template< typename Iter1, typename Iter2 >
	inline bool	operator>( const normal_iterator< Iter1 > &lhs, const normal_iterator< Iter2 > &rhs )
	{ return lhs.base() > rhs.base(); }

	template< typename Iter >
	inline bool	operator>( const normal_iterator< Iter > &lhs, const normal_iterator< Iter > &rhs )
	{ return lhs.base() > rhs.base(); }

	template< typename Iter1, typename Iter2 >
	inline bool	operator<=( const normal_iterator< Iter1 > &lhs, const normal_iterator< Iter2 > &rhs )
	{ return lhs.base() <= rhs.base(); }

	template< typename Iter >
	inline bool	operator<=( const normal_iterator< Iter > &lhs, const normal_iterator< Iter > &rhs )
	{ return lhs.base() <= rhs.base(); }

	template< typename Iter1, typename Iter2 >
	inline bool	operator>=( const normal_iterator< Iter1 > &lhs, const normal_iterator< Iter2 > &rhs )
	{ return lhs.base() >= rhs.base(); }

	template< typename Iter >
	inline bool	operator>=( const normal_iterator< Iter > &lhs, const normal_iterator< Iter > &rhs )
	{ return lhs.base() >= rhs.base(); }

	template< typename Iter >
	inline typename normal_iterator< Iter >::difference_type
	operator-( const normal_iterator< Iter > &lhs, const normal_iterator< Iter > &rhs)
	{ return lhs.base() - rhs.base(); }
	
	template< typename Iter >
	inline normal_iterator< Iter >
	operator+( typename normal_iterator< Iter >::difference_type n, const normal_iterator< Iter > &i )
	{ return normal_iterator<Iter>(i.base() + n); }
}

#endif
