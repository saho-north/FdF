/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:47:30 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/08 20:46:12 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Checks if the given filename has the given extension.
 * It ignores the case of the filename and extension.
 */
static bool	check_file_extension(const char *filename, const char *extension)
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

/**
 * Print out the points struct for debugging.
 * TODO: Delete this function later.
 */
static void	print_points(t_fdf *fdf)
{
	size_t	x;
	size_t	y;

	y = 0;
	printf("fdf.max_x: %zu, fdf.max_y: %zu\n", fdf->max_x, fdf->max_y);
	while (y < fdf->max_y)
	{
		x = 0;
		printf("point[%zu]: ", y);
		while (x < fdf->max_x)
		{
			printf("%d ", fdf->points[y][x].height);
			x++;
		}
		printf("\n");
		y++;
	}
}

/**
 * The main function of the program.
 * It checks the arguments and initializes the struct, mlx environment and map.
 * TODO: The function is not finished yet.
 * It will have more function calls to parse the map and render it.
 */
int	main(int argc, const char *argv[])
{
	t_fdf	fdf;

	printf("-------------------------------------------------\n");
	if (argc != 2 || !check_file_extension(argv[1], ".fdf"))
	{
		print_error_exit(ERR_ARG);
	}
	init_fdf_struct(&fdf);
	init_mlx_env(&fdf);
	get_map_size(argv[1], &fdf);
	init_point_matrix(&fdf);
	parse_map(argv[1], &fdf);
	print_points(&fdf); // TODO: Delete this function later.
	transform_points(&fdf);
	draw_wireframe(&fdf);
	// TODO: parse the map and render it
	// mlx_key_hook(fdf.window, key_hook, &fdf);
	// mlx_hook(fdf.window, 17, 1L << 17, close_window, &fdf);
	// mlx_loop_hook(fdf.xvar, loop_hook, &fdf);
	mlx_loop(fdf.mlx_ptr);
	free_mlx_ptr(&fdf);
	free_point_matrix(fdf.points, fdf.max_y);
	return (0);
}

int	main(void)
{
	t_fdf	fdf;

	fdf.xvar = mlx_init();
	if (!fdf.xvar)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	fdf.width = 640;
	fdf.height = 480;
	fdf.name = "Hello, world!";
	fdf.window = mlx_new_window(fdf.xvar, fdf.width, fdf.height, fdf.name);
	if (!fdf.window)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	fdf.img = mlx_new_image(fdf.xvar, fdf.width, fdf.height);
	if (!fdf.img)
	{
		mlx_destroy_window(fdf.xvar, fdf.window);
		mlx_destroy_display(fdf.xvar);
		free(fdf.xvar);
		write(1, "Error\n", 6);
		return (1);
	}
	fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.stride, &fdf.endian);
	if (!fdf.addr)
	{
		mlx_destroy_image(fdf.xvar, fdf.img);
		mlx_destroy_window(fdf.xvar, fdf.window);
		mlx_destroy_display(fdf.xvar);
		free(fdf.xvar);
		write(1, "Error\n", 6);
		return (1);
	}
	printf("stride %d <-> width %d\n"
			"bpp %d\n"
			"endian %d\n",
			fdf.stride,
			fdf.width,
			fdf.bpp,
			fdf.endian);
	mlx_key_hook(fdf.window, key_hook, &fdf);
	mlx_mouse_hook(fdf.window, button_press, &fdf);
	h_management(env);
	mlx_loop_hook(env->mlx, render, env);
	mlx_loop(env->mlx);
	mlx_loop_hook(fdf.xvar, change_color, &fdf);
	mlx_loop(fdf.xvar);
	/* Setup hooks */
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	/*
	mlx_destroy_window(xvar, mlx_window);
	mlx_destroy_display(xvar);
	free(xvar);
	*/
// これいつ使うのか？
//int		mlx_clear_window(t_xvar *xvar,t_win_list *win)
	return (0);
}

void	h_management(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, key_handler, fdf);
	mlx_hook(fdf->win, 17, 0, close_win, fdf);
	mlx_hook(fdf->win, 4, 0, mouse_handler, fdf);
	mlx_hook(fdf->win, 2, 1L << 0, key_handler, fdf);
	//-------------------------------------------------------------------
	mlx_hook(fdf.win, 4, 0, mouse_handler, &fdf);
	mlx_hook(fdf.win, 2, 1L << 0, key_handler, &fdf);
	mlx_hook(fdf.win, 17, 1L << 0, close_window, &fdf);
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
