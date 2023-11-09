/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:56:43 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/11/07 17:53:53 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "MLX42.h"

# define WIDTH 1024
# define HEIGHT 1024
# define ITERATIONS 20
# define HELP "\nYou can use the following flags:\n* -h -> show this help \
\n* -mb -> display the Mandelbrot fractal \n\
* -julia REAL_COORDINATE IMAGINARY_COORDINATE -> \
show the Julia Fractal at this coordinates\n\n"
# define ERROR_MESSAGE "\nWrong arguments for Julia, you need to provide 2 floating point values to Julia. \
Use -h for examples.\n\n"

typedef struct s_mandelbrot {
	size_t	current_iteration;
	double	z_real_axis;
	double	z_imag_axis;
	double	c_real_axis;
	double	c_imag_axis;
	double	z_real_temp;
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
	double	frame_width;
	double	frame_height;
}	t_mandelbrot;

typedef struct s_julia {
	size_t	current_iteration;
	double	z_real_axis;
	double	z_imag_axis;
	double	frame_width;
	double	frame_height;
	double	z_real_temp;
	double	julia_c_real;
	double	julia_c_imag;
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
	double	focus_point_x;
	double	focus_point_y;
}	t_julia;

typedef struct s_window_frame {
	mlx_t			*window;
	mlx_image_t		*frame;
	mlx_image_t		*buffer;
	double			mouse_x;
	double			mouse_y;
	double			scroll_factor;
	double			julia_c_real;
	double			julia_c_imag;
	int				julia;
	int				mandelbrot;
	double			x_min;
	double			x_max;
	double			y_min;
	double			y_max;
	unsigned int	iterations;
}	t_window_frame;

typedef struct s_scaling_params {
	double	zero_height;
	double	zero_width;
	double	range_x;
	double	range_y;
	double	new_range_x;
	double	new_range_y;
	double	x_offset;
	double	y_offset;
}	t_scaling_params;

uint32_t	convert_rgba(int r, int g, int b, int a);
uint32_t	iteration_color(unsigned int iterations);
void		traverse_mb_frame(t_window_frame *gui, mlx_image_t *frame);
void		traverse_julia_frame(t_window_frame *gui, mlx_image_t *frame);
void		resize_function(int32_t width, int32_t height, void *param);
void		cleanup(t_window_frame *gui);
void		scrolling_handler(double xdelta, double ydelta, void *param);
void		mouse_position_handler(double xpos, double ypos, void *param);
void		key_handler(mlx_key_data_t keydata, void *param);
int			ft_strncmp(const char *str1, const char *str2, size_t num);
size_t		ft_strlen(const char *string);
int			ft_isfloat(char *str);
void		handle_args(int argc, char **argv, t_window_frame *gui);
double		ft_atod(char *str);
int			ft_printf(const char *first_arg, ...);

#endif

/*
** Compile with MLX42 on homebrew:
** gcc main.c ... libmlx42.a -Iinclude -lglfw
** -L"/Users/***REMOVED***/.brew/opt/glfw/lib/"
** NOTE: Compile MLX42 with DEBUG=1 to see assertions
** and to add debug flags. This can help you find critical
** mistakes during development!
*/
