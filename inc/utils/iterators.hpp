/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:26:34 by foctavia          #+#    #+#             */
/*   Updated: 2023/01/26 15:51:43 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
# define ITERATORS_HPP

# include <iterator>

namespace ft
{
	// iterator_traits
	
	template< typename Iter >
	struct iterator_traits
	{
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};
	
	template< typename T >
	struct iterator_traits< T * >
	{
		typedef std::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef T									*pointer;
		typedef T									&reference;
	};

	template< typename T >
	struct iterator_traits< const T * >
	{
		typedef std::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef const T								*pointer;
		typedef const T								&reference;	
	};

	// reverse_iterator

	template< typename Iter >
	class reverse_iterator : public std::iterator<typename ft::iterator_traits< Iter >::iterator_category,
		     					typename ft::iterator_traits< Iter >::value_type,
		    					typename ft::iterator_traits< Iter >::difference_type,
		    					typename ft::iterator_traits< Iter >::pointer,
                    			typename ft::iterator_traits< Iter >::reference>
	{
		public:
			
			typedef Iter													iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef typename ft::iterator_traits<Iter>::reference			reference;
		
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

			iterator_type	base( void ) const { return current; }
			
			reference		operator*( void ) const
			{
				Iter	tmp = current;
				return	*--tmp;
			}

			pointer			operator->( void ) const { return &(operator*()); }

			reference		operator[]( difference_type n ) const { return *(*this + n); }

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

			reverse_iterator	&operator++( int )
			{
				reverse_iterator	tmp = *this;
				--current;
				return tmp;
			}

			reverse_iterator	&operator--( int )
			{
				reverse_iterator	tmp = *this;
				++current;
				return tmp;
			}

			reverse_iterator	&operator+( difference_type n ) const
			{ return reverse_iterator(current - n); }

			reverse_iterator	&operator-( difference_type n ) const
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
			
		protected:
		
			Iter	current;
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
