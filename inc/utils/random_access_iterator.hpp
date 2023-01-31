/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:44:31 by foctavia          #+#    #+#             */
/*   Updated: 2023/01/31 18:28:17 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <iterator_traits.hpp>

namespace ft
{
	/* RANDOM_ACCESS_ITERATOR ************************************************************* */
	
	template< typename Iter >
	class random_access_iterator : public std::iterator< std::random_access_iterator_tag, Iter , std::ptrdiff_t, Iter *, Iter & >
	{
		protected:
			
			Iter											current;
			typedef ft::iterator_traits< Iter >				traits_type;

		public:
			
			typedef Iter									iterator_type;
			typedef typename traits_type::iterator_category	iterator_category;
			typedef typename traits_type::value_type		value_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::reference			reference;
			typedef typename traits_type::pointer			pointer;

	// CONTRUCTOR

		random_access_iterator( void ) : current( Iter() ) { }
		explicit random_access_iterator( const Iter &i ) : current( i ) { }

	// DESTRUCTOR

		~random_access_iterator( void ) { }

	// MEMBER FUNCTION
		
		// Member functions for element access
			
		const Iter	&base() const									{ return current; }
		
		reference	operator*( void ) const							{ return *current; }

		pointer		operator->( void ) const 						{ return current; }

		reference	operator[]( const difference_type &n ) const	{ return current[ n ]; }

		// Member functions for overload operator

		random_access_iterator	operator++( int )					{ return random_access_iterator(current++); }

		random_access_iterator	operator--( int )					{ return random_access_iterator(current--); }

		random_access_iterator	&operator++( void )
		{
			++current;
			return *this;
		}

		random_access_iterator	&operator--( void )
		{
			--current;
			return *this;
		}

		random_access_iterator	&operator+=( const difference_type &n )
		{
			current += n;
			return *this;
		}

		random_access_iterator	&operator-=( const difference_type &n )
		{
			current -= n;
			return *this;
		}

		random_access_iterator	operator+( const difference_type &n ) const
		{
			return random_access_iterator( current + n );
		}
		
		random_access_iterator	operator-( const difference_type &n ) const
		{
			return random_access_iterator( current - n );
		}

	};

	// NON-MEMBER FUNCTION

	template< typename Iter1, typename Iter2 >
	inline bool	operator==( const random_access_iterator< Iter1 > &lhs, const random_access_iterator< Iter2 > &rhs )
	{ return lhs.base() == rhs.base(); }

	template< typename Iter1, typename Iter2 >
	inline bool	operator!=( const random_access_iterator< Iter1 > &lhs, const random_access_iterator< Iter2 > &rhs )
	{ return lhs.base() != rhs.base(); }

	template< typename Iter >
	inline bool	operator==( const random_access_iterator< Iter > &lhs, const random_access_iterator< Iter > &rhs )
	{ return lhs.base() == rhs.base(); }

	template< typename Iter >
	inline bool	operator!=( const random_access_iterator< Iter > &lhs, const random_access_iterator< Iter > &rhs )
	{ return lhs.base() != rhs.base(); }

	template< typename Iter1, typename Iter2 >
	inline bool	operator<( const random_access_iterator< Iter1 > &lhs, const random_access_iterator< Iter2 > &rhs )
	{ return lhs.base() < rhs.base(); }

	template< typename Iter >
	inline bool	operator<( const random_access_iterator< Iter > &lhs, const random_access_iterator< Iter > &rhs )
	{ return lhs.base() < rhs.base(); }

	template< typename Iter1, typename Iter2 >
	inline bool	operator>( const random_access_iterator< Iter1 > &lhs, const random_access_iterator< Iter2 > &rhs )
	{ return lhs.base() > rhs.base(); }

	template< typename Iter >
	inline bool	operator>( const random_access_iterator< Iter > &lhs, const random_access_iterator< Iter > &rhs )
	{ return lhs.base() > rhs.base(); }

	template< typename Iter1, typename Iter2 >
	inline bool	operator<=( const random_access_iterator< Iter1 > &lhs, const random_access_iterator< Iter2 > &rhs )
	{ return lhs.base() <= rhs.base(); }

	template< typename Iter >
	inline bool	operator<=( const random_access_iterator< Iter > &lhs, const random_access_iterator< Iter > &rhs )
	{ return lhs.base() <= rhs.base(); }

	template< typename Iter1, typename Iter2 >
	inline bool	operator>=( const random_access_iterator< Iter1 > &lhs, const random_access_iterator< Iter2 > &rhs )
	{ return lhs.base() >= rhs.base(); }

	template< typename Iter >
	inline bool	operator>=( const random_access_iterator< Iter > &lhs, const random_access_iterator< Iter > &rhs )
	{ return lhs.base() >= rhs.base(); }

	template< typename Iter >
	inline typename random_access_iterator< Iter >::difference_type
	operator-( const random_access_iterator< Iter > &lhs, const random_access_iterator< Iter > &rhs)
	{ return lhs.base() - rhs.base(); }
	
	template< typename Iter >
	inline random_access_iterator< Iter >
	operator+( typename random_access_iterator< Iter >::difference_type n, const random_access_iterator< Iter > &i )
	{ return random_access_iterator<Iter>(i.base() + n); }
	
}

#endif
