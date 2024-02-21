/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:47:30 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/21 14:50:25 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <X11/X.h>

/**
 * Checks if the given filename has the given extension.
 * It ignores the case of the filename and extension.
 */
static bool	is_valid_extension(const char *filename, const char *extension)
{
	size_t	filename_len;
	size_t	extension_len;
	int		result;

	if (!filename || !extension)
	{
		return (false);
	}
	filename_len = ft_strlen(filename);
	extension_len = ft_strlen(extension);
	if (filename_len <= extension_len)
	{
		return (false);
	}
	result = ft_strcasecmp(&filename[filename_len - extension_len], extension);
	return (result == 0);
}

int	main(int argc, const char *argv[])
{
	t_fdf	fdf;

	if (argc != 2 || !is_valid_extension(argv[1], ".fdf"))
	{
		print_error_exit(ERR_ARG);
	}
	init_fdf(&fdf, argv[1]);
	parse_map(argv[1], &fdf);
	fdf.redraw = true;
	mlx_hook(fdf.win, KeyPress, KeyPressMask, &key_press, &fdf);
	mlx_key_hook(fdf.win, &key_release, &fdf);
	mlx_mouse_hook(fdf.win, &button_press, &fdf);
	mlx_hook(fdf.win, ButtonRelease, ButtonReleaseMask, &button_release, &fdf);
	mlx_hook(fdf.win, MotionNotify, PointerMotionMask, &motion_notify, &fdf);
	mlx_hook(fdf.win, DestroyNotify, StructureNotifyMask, &clean_exit, &fdf);
	mlx_hook(fdf.win, ConfigureNotify, StructureNotifyMask, &render, &fdf);
	mlx_loop_hook(fdf.mlx, &handle_loop_hook, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}

/**
 * The destructor function of the program.
 * It is used to check for memory leaks using the leaks command.
 * TODO: It will be commented out in the final version.
 */
__attribute__((destructor)) static void destructor()
{
	system("leaks -q fdf");
}
