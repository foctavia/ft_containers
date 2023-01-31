/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:47:58 by foctavia          #+#    #+#             */
/*   Updated: 2023/01/31 18:28:29 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <iterator_traits.hpp>

namespace ft
{
	/* REVERSE_ITERATOR ******************************************************************* */

	template< typename Iter >
	class reverse_iterator
	{
		protected:
			
			Iter											current;
			typedef ft::iterator_traits< Iter >				traits_type;
		
		public:
			
			typedef Iter									iterator_type;
			typedef typename traits_type::iterator_category	iterator_category;
			typedef typename traits_type::value_type		value_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::pointer			pointer;
			typedef typename traits_type::reference			reference;
		
	// CONSTRUCTOR
		
			reverse_iterator( void ) : current() { }
			explicit reverse_iterator( iterator_type x ) : current( x ) { }

		// Copy constructor
		
			reverse_iterator( const reverse_iterator &x ) : current( x.current ) { }
			template< typename _Iter >
			reverse_iterator( const reverse_iterator< _Iter > &x ) : current( x.base() ) { }

	// DESTRUCTOR

			~reverse_iterator( void ) { }

	// ASSIGNMENT OPERATOR

			template< typename _Iter >
			reverse_iterator	&operator=( const reverse_iterator< _Iter > &x )
			{
				if (this != &x)
					this->current = x.current;
				return *this;
			}
			
	// MEMBER FUNCTION

			iterator_type		base( void ) const { return current; }
			
			reference			operator*( void ) const
			{
				Iter	tmp = current;
				return	*--tmp;
			}

			pointer				operator->( void ) const { return &(operator*()); }

			reference			operator[]( difference_type n ) const { return *(*this + n); }

			reverse_iterator	&operator++( void )
			{
				--current;
				return *this;
			}

			reverse_iterator	&operator--( void )
			{
				++current;
				return *this;
			}

			reverse_iterator	operator++( int )
			{
				reverse_iterator	tmp = *this;
				--current;
				return tmp;
			}

			reverse_iterator	operator--( int )
			{
				reverse_iterator	tmp = *this;
				++current;
				return tmp;
			}

			reverse_iterator	operator+( difference_type n ) const
			{ return reverse_iterator(current - n); }

			reverse_iterator	operator-( difference_type n ) const
			{ return reverse_iterator(current + n); }

			reverse_iterator	&operator+=( difference_type n )
			{
				current -= n;
				return *this;
			}

			reverse_iterator	&operator-=( difference_type n )
			{
				current += n;
				return *this;
			}

	};

	// NON-MEMBER FUNCTIONS

	template< typename Iter1, typename Iter2 >
	inline bool		operator==( const ft::reverse_iterator< Iter1 > &x, const ft::reverse_iterator< Iter2 > &y )
	{ return x.base() == y.base(); }

	template< typename Iter1, typename Iter2 >
	inline bool		operator!=( const ft::reverse_iterator< Iter1 > &x, const ft::reverse_iterator< Iter2 > &y )
	{ return !(x == y); }

	template< typename Iter1, typename Iter2 >
	inline bool		operator<( const ft::reverse_iterator< Iter1 > &x, const ft::reverse_iterator< Iter2 > &y )
	{ return y.base() < x.base(); }
	
	template< typename Iter1, typename Iter2 >
	inline bool		operator<=( const ft::reverse_iterator< Iter1 > &x, const ft::reverse_iterator< Iter2 > &y )
	{ return !(y < x); }

	template< typename Iter1, typename Iter2 >
	inline bool		operator>( const ft::reverse_iterator< Iter1 > &x, const ft::reverse_iterator< Iter2 > &y )
	{ return y < x; }
	
	template< typename Iter1, typename Iter2 >
	inline bool		operator>=( const ft::reverse_iterator< Iter1 > &x, const ft::reverse_iterator< Iter2 > &y )
	{ return !(x < y); }

	template< typename Iter >
	inline typename reverse_iterator< Iter >::difference_type
	operator-( const reverse_iterator< Iter > &x, const reverse_iterator< Iter > &y )
	{ return y.base() - x.base(); }

	template< typename Iter >
	inline reverse_iterator< Iter >
	operator+(typename reverse_iterator< Iter >::difference_type n, const reverse_iterator< Iter > &x)
	{ return reverse_iterator< Iter >(x.base() - n); }
	
}

#endif
