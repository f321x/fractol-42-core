/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 08:55:55 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/10/18 15:11:50 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*array;
	size_t	amount;
	size_t	index;

	amount = num * size;
	index = 0;
	array = malloc(amount);
	if (array == NULL)
		return (NULL);
	while (amount-- > 0)
		((unsigned char *)array)[index++] = 0;
	return (array);
}
