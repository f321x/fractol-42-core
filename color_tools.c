/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:57:40 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/11/06 10:27:34 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

/*
** Takes values for red, green, blue and transparency (a) and
** encodes all values in a single 32 bit integer at the according
** bit positions which is the correct format for the MLX42 library
*/
uint32_t	convert_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/*
** Used to assign a color to a number of iterations.
** Depending on the amount of iterations done as opposed to
** the maximum iteration limit a color is being assigned
*/
uint32_t	iteration_color(unsigned int iterations)
{
	unsigned int	iteration_percent;

	iteration_percent = (iterations * 100) / ITERATIONS;
	if (iteration_percent > 66)
	{
		return (convert_rgba(0, ((iteration_percent * 255) / 100), 0, 255));
	}
	else if (iteration_percent > 33)
	{
		return (convert_rgba(((iteration_percent * 255) / 100), 0, 0, 255));
	}
	else
	{
		return (convert_rgba(0, 0, ((iteration_percent * 255) / 100), 255));
	}
}
