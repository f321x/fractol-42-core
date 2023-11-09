/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:22:02 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/11/08 12:25:11 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

/*
** Gets called if the argument is -mb (Mandelbrot mode), sets the according
** values in the gui struct
*/
static void	is_mandelbrot(t_window_frame *gui)
{
	gui->mandelbrot = 1;
	gui->julia = 0;
	gui->x_max = 1.0;
	gui->x_min = -2.0;
	gui->y_max = 1.5;
	gui->y_min = -1.5;
}

/*
** Gets called if the argument is
** -julia C_REAL C_IMAGINARY (Julia mode), sets the according
** values in the gui struct
*/
static void	is_julia(t_window_frame *gui, char *j_real_str, char *j_imag_str)
{
	gui->mandelbrot = 0;
	gui->julia = 1;
	gui->julia_c_real = ft_atod(j_real_str);
	gui->julia_c_imag = ft_atod(j_imag_str);
	gui->x_max = 1.5;
	gui->x_min = -1.5;
	gui->y_max = 1.5;
	gui->y_min = -1.5;
}

/*
** Traverse trough arguments and check for matches and mistakes
*/
void	traverse_arguments(int i, int argc, char **argv, t_window_frame *gui)
{
	while (i < argc)
	{
		if (ft_strncmp(argv[i], "-h", 2) == 0
			&& ft_strlen(argv[i]) == 2 && argc == 2)
		{
			ft_printf(HELP);
			exit(EXIT_SUCCESS);
		}
		else if (ft_strncmp(argv[i], "-mb", 3) == 0
			&& gui->julia == 0 && ft_strlen(argv[i]) == 3 && argc == 2)
			return (is_mandelbrot(gui));
		else if (ft_strncmp(argv[i], "-julia", 6) == 0
			&& gui->mandelbrot == 0 && ft_strlen(argv[i]) == 6 && argc == 4)
		{
			if (i + 2 <= argc && ft_isfloat(argv[i + 1])
				&& ft_isfloat(argv[i + 2]))
				return (is_julia(gui, argv[i + 1], argv[i + 2]));
			ft_printf(ERROR_MESSAGE);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

/*
** Parses the argc and argv (Arguments) to detect the
** entered argument and call the according mode
*/
void	handle_args(int argc, char **argv, t_window_frame *gui)
{
	int	index;

	index = 1;
	gui->mandelbrot = 0;
	gui->julia = 0;
	if (argc < 2)
	{
		ft_printf(HELP);
		exit(EXIT_SUCCESS);
	}
	traverse_arguments(index, argc, argv, gui);
	if (gui->julia == 0 && gui->mandelbrot == 0)
	{
		ft_printf(HELP);
		exit(EXIT_SUCCESS);
	}
}
