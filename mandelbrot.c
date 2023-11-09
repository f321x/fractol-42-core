/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:56:28 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/11/06 11:15:22 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
/*
** Used to initialize the t_mandelbrot struct with the correct
** values from the main gui struct.
*/
static void	init_mb(t_mandelbrot *mb, t_window_frame *gui)
{
	mb->current_iteration = 0;
	mb->z_real_axis = 0.0;
	mb->z_imag_axis = 0.0;
	mb->frame_width = gui->frame->width;
	mb->frame_height = gui->frame->height;
	gui->scroll_factor = 1.0;
}

/*
** Gets called for each pixel and calculates the mandelbrot formula for
** the coordinates of this pixel. After the coordinates exceed the
** maximum iterations or limit coordinates the number of iterations
** is used to determine the color of the pixel which is returned as
** 32 bit integer (the way to encode the colors of a pixel in MLX42)
*/
static uint32_t	gen_mb_pixel(unsigned int current_width,
	unsigned int current_height, t_window_frame *gui)
{
	t_mandelbrot	mb;

	init_mb(&mb, gui);
	mb.c_real_axis = gui->x_min + (gui->x_max - (gui->x_min))
		* ((double)current_width / mb.frame_width);
	mb.c_imag_axis = gui->y_min + (gui->y_max - (gui->y_min))
		* ((double)current_height / mb.frame_height);
	while (mb.current_iteration < ITERATIONS)
	{
		mb.z_real_temp = mb.z_real_axis * mb.z_real_axis
			- mb.z_imag_axis * mb.z_imag_axis + mb.c_real_axis;
		mb.z_imag_axis = 2 * mb.z_real_axis * mb.z_imag_axis + mb.c_imag_axis;
		mb.z_real_axis = mb.z_real_temp;
		if (mb.z_real_axis * mb.z_real_axis + mb.z_imag_axis * mb.z_imag_axis
			> 4.0)
			break ;
		mb.current_iteration++;
	}
	if (mb.current_iteration == gui->iterations)
		return (convert_rgba(0, 0, 0, 255));
	else
		return (iteration_color(mb.current_iteration));
}

/*
** Traverses the frame pixels one by one and calls the gen_mb_pixel function
** each pixel to generate the color for the pixel which is afterwards
** written to the image/frame. Gets called at startup and every resize
** and scroll
*/
void	traverse_mb_frame(t_window_frame *gui, mlx_image_t *frame)
{
	unsigned int	current_pixel_height;
	unsigned int	current_pixel_width;
	uint32_t		pixel;
	uint32_t		frame_width;
	uint32_t		frame_height;

	current_pixel_height = 0;
	current_pixel_width = 0;
	frame_width = frame->width;
	frame_height = frame->height;
	while (current_pixel_height < frame_height)
	{
		while (current_pixel_width < frame_width)
		{
			pixel = gen_mb_pixel(current_pixel_width,
					current_pixel_height, gui);
			mlx_put_pixel(frame, current_pixel_width,
				current_pixel_height, pixel);
			current_pixel_width++;
		}
		current_pixel_width = 0;
		current_pixel_height++;
	}
}
