/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:26:34 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/27 17:40:07 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <iterator>

namespace ft
{
	/* ITERATOR_TRAITS ******************************************************************** */
	
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

	template< typename Iter >
	typename iterator_traits< Iter >::difference_type
	iterator_difference( Iter first, Iter last )
	{
		return (last - first);
	}

	template< typename Iter >
	typename iterator_traits< Iter >::difference_type
	compute_difference( Iter first, Iter last, std::random_access_iterator_tag )
	{
		return (last - first);
	}

	template< typename Iter >
	typename iterator_traits< Iter >::difference_type
	compute_difference( Iter first, Iter last, std::bidirectional_iterator_tag )
	{
		size_t	i = 0;
		while (first != last)
		{
			first++;
			i++;
		}

		return i;
	}

	template< typename Iter >
	typename iterator_traits< Iter >::difference_type
	compute_difference( Iter first, Iter last, std::input_iterator_tag )
	{
		typename std::iterator_traits< Iter >::difference_type	count = 0;
		while(first != last)
		{
			++count;
			++first;
		}

		return count;
	}

	template< typename Iter >
	typename iterator_traits< Iter >::difference_type
	distance( Iter first, Iter last )
	{
		return compute_difference(first, last, typename ft::iterator_traits< Iter >::iterator_category());
	}

}

#endif
