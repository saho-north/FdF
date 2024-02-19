/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:47:30 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/20 01:16:44 by sakitaha         ###   ########.fr       */
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
	mlx_hook(fdf.win, KeyPress, KeyPressMask, &key_press, &fdf);
	mlx_key_hook(fdf.win, &key_release, &fdf);
	mlx_mouse_hook(fdf.win, &button_press, &fdf);
	mlx_hook(fdf.win, ButtonRelease, ButtonReleaseMask, &button_release, &fdf);
	mlx_hook(fdf.win, DestroyNotify, StructureNotifyMask, &clean_exit, &fdf);
	mlx_loop_hook(fdf.mlx, &render, &fdf);
	mlx_loop(fdf.mlx);
	// これいつ使うの？
	//int		(t_xvar *mlx,t_win_list *win)
	return (0);
}

/**
 * The destructor function of the program.
 * It is used to check for memory leaks using the leaks command.
 * TODO: It will be deleted before the final submission.
 */

__attribute__((destructor)) static void destructor()
{
	system("leaks -q fdf");
}

/*
<<< 課題の内容のメモ >>>

TODO: Mandetory

Each number represents a point in space:
• The horizontal position corresponds to its axis.
• The vertical position corresponds to its ordinate.
• The value corresponds to its altitude.

V.2 Graphic management
• Your program has to display the image in a window.
• The management of your window must remain smooth (changing to another win-
dow, minimizing, and so forth).
• Pressing ESC must close the window and quit the program in a clean way.
• Clicking on the cross on the window’s frame must close the window and quit the program in a clean way.
• The use of the images of the MiniLibX is mandatory

TODO: bonus
You will get some extra points if you can:

• Include one extra projection (such as parallel or conic)!
• Zoom in and out.
• Translate your model.
• Rotate your model.
• Add one more bonus of your choice
 */
