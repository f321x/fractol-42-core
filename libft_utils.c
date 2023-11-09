/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:24:28 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/11/06 09:42:10 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

/*
** Used in argument parsing to compare the user entered argument
** with the hardcoded arguments.
*/
int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	while (num > 0 && *str1 == *str2 && *str1 != '\0' && *str2 != '\0')
	{
		str1++;
		str2++;
		num--;
	}
	if (num == 0)
		return (0);
	return ((unsigned char)*str1 - (unsigned char)*str2);
}

/*
** Counts the characters of a string which is returned as size_t
*/
size_t	ft_strlen(const char *string)
{
	size_t	counter;

	counter = 0;
	while (string[counter] != '\0')
		counter++;
	return (counter);
}

/*
** Used to check if a string contains a valid floating point number
*/
int	ft_isfloat(char *str)
{
	int		index;
	int		dot_count;

	dot_count = 0;
	index = 0;
	if (str[index] == '-')
		index++;
	while (str[index])
	{
		if (str[index] == '.')
		{
			dot_count++;
			if (!str[index + 1] || index == 0 || dot_count > 1)
				return (0);
		}
		if ((str[index] >= '0' && str[index] <= '9') || str[index] == '.')
			index++;
		else
			return (0);
	}
	return (1);
}
