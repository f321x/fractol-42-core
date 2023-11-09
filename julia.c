/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:45:06 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/11/06 10:39:32 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

/*
** Used to initialize the t_julia struct with the correct
** values from the main gui struct.
*/
static void	init_julia(unsigned int current_width,
	unsigned int current_height, t_julia *j, t_window_frame *gui)
{
	j->current_iteration = 0;
	j->z_real_axis = 0.0;
	j->z_imag_axis = 0.0;
	j->frame_width = gui->frame->width;
	j->frame_height = gui->frame->height;
	j->julia_c_real = gui->julia_c_real;
	j->julia_c_imag = gui->julia_c_imag;
	j->focus_point_x = (double)current_width / j->frame_width;
	j->focus_point_y = (double)current_height / j->frame_height;
}

/*
** Gets called for each pixel and calculates the julia formula for
** the coordinates of this pixel. After the coordinates exceed the
** maximum iterations or limit coordinates the number of iterations
** is used to determine the color of the pixel which is returned as
** 32 bit integer (the way to encode the colors of a pixel in MLX42)
*/
static uint32_t	gen_julia_pixel(unsigned int current_width,
	unsigned int current_height, t_window_frame *gui)
{
	t_julia	j;

	init_julia(current_width, current_height, &j, gui);
	j.z_real_axis = gui->x_min + (gui->x_max - (gui->x_min))
		* (j.focus_point_x);
	j.z_imag_axis = gui->y_min + (gui->y_max - (gui->y_min))
		* (j.focus_point_y);
	while (j.current_iteration < ITERATIONS)
	{
		j.z_real_temp = j.z_real_axis * j.z_real_axis - j.z_imag_axis
			* j.z_imag_axis + gui->julia_c_real;
		j.z_imag_axis = 2 * j.z_real_axis * j.z_imag_axis + gui->julia_c_imag;
		j.z_real_axis = j.z_real_temp;
		if (j.z_real_axis * j.z_real_axis + j.z_imag_axis * j.z_imag_axis > 4.0)
			break ;
		j.current_iteration++;
	}
	if (j.current_iteration == ITERATIONS)
		return (convert_rgba(0, 0, 0, 255));
	else
		return (iteration_color(j.current_iteration));
}

/*
** Traverses the frame pixels one by one and calls the gen_julia_pixel function
** on each pixel to generate the color for the pixel which is afterwards
** written to the image/frame. Gets called at startup and every resize
** and scroll
*/
void	traverse_julia_frame(t_window_frame *gui, mlx_image_t *frame)
{
	unsigned int	current_pixel_height;
	unsigned int	current_pixel_width;
	uint32_t		pixel;

	current_pixel_height = 0;
	current_pixel_width = 0;
	while (current_pixel_height < frame->height)
	{
		while (current_pixel_width < frame->width)
		{
			pixel = gen_julia_pixel(current_pixel_width,
					current_pixel_height, gui);
			mlx_put_pixel(frame, current_pixel_width,
				current_pixel_height, pixel);
			current_pixel_width++;
		}
		current_pixel_width = 0;
		current_pixel_height++;
	}
}
