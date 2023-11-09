/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:18:41 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/11/06 10:20:26 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

/*
** Function gets called by the resize hook when the window is resized.
** Will genereate a new frame with the new size which is passed as
** arg by the hook.
** Cleans the old frame and stores the new in the gui struct.
*/
void	resize_function(int32_t width, int32_t height, void *param)
{
	t_window_frame	*gui;

	gui = (t_window_frame *)param;
	gui->buffer = mlx_new_image(gui->window, width, height);
	if (!gui->buffer)
		cleanup(gui);
	if (gui->mandelbrot)
		traverse_mb_frame(gui, gui->buffer);
	else if (gui->julia)
		traverse_julia_frame(gui, gui->buffer);
	if ((mlx_image_to_window(gui->window, gui->buffer, 0, 0)) < 0)
		cleanup(gui);
	mlx_delete_image(gui->window, gui->frame);
	gui->frame = gui->buffer;
	gui->buffer = NULL;
}

/*
** 1. Calculate the relative position of the mouse in the viewport (0-1)
** 2. Calculate the current ranges of the x and y axis (max - min)
** 3. Calculate the new ranges after scaling
** 4. Calculate the offset to apply based on the mouse position
** 5. Apply the offsets to the min and max values of x and y
*/
static void	scaling_calculator(t_window_frame *gui)
{
	t_scaling_params	sp;

	sp.zero_width = gui->mouse_x / (double)gui->frame->width;
	sp.zero_height = gui->mouse_y / (double)gui->frame->height;
	sp.range_x = gui->x_max - gui->x_min;
	sp.range_y = gui->y_max - gui->y_min;
	sp.new_range_x = sp.range_x * (1 - gui->scroll_factor);
	sp.new_range_y = sp.range_y * (1 - gui->scroll_factor);
	sp.x_offset = (sp.range_x - sp.new_range_x) * sp.zero_width;
	sp.y_offset = (sp.range_y - sp.new_range_y) * sp.zero_height;
	gui->x_min += sp.x_offset;
	gui->x_max -= (sp.range_x - sp.new_range_x) - sp.x_offset;
	gui->y_min += sp.y_offset;
	gui->y_max -= (sp.range_y - sp.new_range_y) - sp.y_offset;
}

/*
** Gets called when the user is scrolling with the mouse wheel
** Will zoom in or out at the position of the mouse pointer
** by scaling the coordinate size to the respective values and
** generates a new frame which is then printed and stored while
** the previous one is being freed.
*/
void	scrolling_handler(double xdelta, double ydelta, void *param)
{
	t_window_frame	*gui;

	xdelta = 0;
	gui = (t_window_frame *)param;
	if (ydelta > 0 || xdelta > 0)
		gui->scroll_factor = 0.2;
	else if (ydelta < 0 || xdelta < 0)
		gui->scroll_factor = -0.2;
	scaling_calculator(gui);
	gui->buffer = mlx_new_image(gui->window,
			gui->frame->width, gui->frame->height);
	if (!gui->buffer)
		cleanup(gui);
	if (gui->mandelbrot)
		traverse_mb_frame(gui, gui->buffer);
	else if (gui->julia)
		traverse_julia_frame(gui, gui->buffer);
	if ((mlx_image_to_window(gui->window, gui->buffer, 0, 0)) < 0)
		cleanup(gui);
	mlx_delete_image(gui->window, gui->frame);
	gui->frame = gui->buffer;
	gui->buffer = NULL;
}

/*
** Gets called on every mouse movement and stores the current mouse
** position in the gui struct. If the mouse is outside of the window
** the middle of the screen will be stored in the gui struct on mouse
** movement.
*/
void	mouse_position_handler(double xpos, double ypos, void *param)
{
	t_window_frame	*gui;

	gui = (t_window_frame *)param;
	if (xpos > 0.0 && xpos < gui->frame->width)
		gui->mouse_x = xpos;
	else
	{
		gui->mouse_x = (gui->frame->width / 2);
		gui->mouse_y = (gui->frame->height / 2);
		return ;
	}
	if (ypos > 0.0 && ypos < gui->frame->height)
		gui->mouse_y = ypos;
	else
	{
		gui->mouse_x = (gui->frame->width / 2);
		gui->mouse_y = (gui->frame->height / 2);
		return ;
	}
}

/*
** Short hook handler for the keypresses which terminates the
** programm on press of the ESC key (256).
*/
void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_window_frame	*gui;

	gui = (t_window_frame *)param;
	if (keydata.key == 256)
	{
		mlx_delete_image(gui->window, gui->frame);
		mlx_terminate(gui->window);
		exit(EXIT_SUCCESS);
	}
}
