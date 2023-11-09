/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 08:05:01 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/11/06 10:25:13 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

/*
** Gets the part of the number in the array after the comma
*/
double	get_post_comma(char **string)
{
	double	result;
	double	multiplier;

	multiplier = 0.1;
	result = 0;
	(*string)++;
	while (**string >= '0' && **string <= '9')
	{
		result += (**string - '0') * multiplier;
		multiplier /= 10;
		(*string)++;
	}
	return (result);
}

/*
** Gets the part of the number in the array before the comma
*/
double	get_pre_comma(char **string)
{
	double	result;

	result = 0;
	while (**string >= '0' && **string <= '9')
	{
		result += result * 10 + (**string - '0');
		(*string)++;
	}
	return (result);
}

/*
** Used to convert an array containing a floating point number to
** a double type number
*/
double	ft_atod(char *str)
{
	double	result;
	double	post_comma;
	double	seen_sign;

	result = 0.0;
	seen_sign = 1.0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
	{
		seen_sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	result = get_pre_comma(&str);
	post_comma = get_post_comma(&str);
	return ((result + post_comma) * seen_sign);
}
