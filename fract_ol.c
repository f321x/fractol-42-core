/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:19:06 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/11/06 11:16:10 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

/*
** called on errors to clean everything (free the memory) and exit the program
*/
void	cleanup(t_window_frame *gui)
{
	if (gui->frame)
		mlx_delete_image(gui->window, gui->frame);
	if (gui->buffer)
		mlx_delete_image(gui->window, gui->buffer);
	if (gui->window)
		mlx_terminate(gui->window);
	exit(EXIT_FAILURE);
}

/*
** Initializes the gui struckt with the image
*/
static void	init_gui(t_window_frame *gui)
{
	gui->window = mlx_init(WIDTH, HEIGHT, "fract-ol | ***REMOVED***", true);
	if (!(gui->window))
		cleanup(gui);
	gui->frame = mlx_new_image(gui->window, WIDTH, HEIGHT);
	if (!(gui->frame))
	{
		mlx_terminate(gui->window);
		cleanup(gui);
	}
	gui->scroll_factor = 1.0;
	gui->iterations = ITERATIONS;
}

/*
** Initializes the hooks to handle key and mouse input
*/
static void	init_hooks(t_window_frame *gui)
{
	mlx_resize_hook(gui->window, resize_function, gui);
	mlx_scroll_hook(gui->window, scrolling_handler, gui);
	mlx_cursor_hook(gui->window, mouse_position_handler, gui);
	mlx_key_hook(gui->window, key_handler, gui);
}

int	main(int argc, char **argv)
{
	t_window_frame	gui;

	handle_args(argc, argv, &gui);
	init_gui(&gui);
	if (gui.mandelbrot)
		traverse_mb_frame(&gui, gui.frame);
	else if (gui.julia)
		traverse_julia_frame(&gui, gui.frame);
	mlx_image_to_window(gui.window, gui.frame, 0, 0);
	init_hooks(&gui);
	mlx_loop(gui.window);
	mlx_terminate(gui.window);
	return (EXIT_SUCCESS);
}

/*
** 	system("leaks fractol");
** +----------------------------+-------------------------------------------+
** |       Julia Set c Value     |           Short Description              |
** +----------------------------+-------------------------------------------+
** |  -0.7 + 0.27015i           | Dragon-like design                        |
** |  -0.123 + 0.745i           | Reminiscent of seashells                  |
** |  0.355 + 0.355i            | Looks like a squiggly line                |
** |  -0.70176 - 0.3842i        | Electrified cloud appearance              |
** |  0.285 + 0.01i             | Spiraled design with a central "eye"      |
** +----------------------------+-------------------------------------------+
*/
