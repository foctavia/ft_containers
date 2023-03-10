/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:20:16 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/27 19:14:09 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{
	/* LEXICOGRAPHICAL_COMPARE ************************************************************ */

	template< class InputIt1, class InputIt2 >
	bool	lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 )
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
 
    	return (first1 == last1) && (first2 != last2);
	}

	template< class InputIt1, class InputIt2, class Compare >
	bool	lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp )
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
	
		return (first1 == last1) && (first2 != last2);
	}

	/* EQUAL ****************************************************************************** */
	
	template< class InputIt1, class InputIt2 >
	bool	equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2)) 
			{
				return false;
			}
		}
		
		return true;
	}
	
	template< class InputIt1, class InputIt2, class BinaryPredicate >
	bool	equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p )
	{
		    for (; first1 != last1; ++first1, ++first2)
			{
				if (!p(*first1, *first2))
				{
					return false;
				}
			}
			
			return true;
	}

	template< class InputIt1, class InputIt2 >
	InputIt2 copy_backward(InputIt1 first, InputIt1 last, InputIt2 d_last)
	{
		while (first != last)
			*(--d_last) = *(--last);
	
		return d_last;
	}
	
}

#endif
