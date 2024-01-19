/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:47:30 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/19 21:09:09 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

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

static void	init_fdf_struct(t_fdf *fdf)
{
	fdf->xvar = NULL;
	fdf->window = NULL;
	fdf->img = NULL;
	fdf->addr = NULL;
	fdf->bpp = 0;
	fdf->stride = 0;
	fdf->endian = 0;
	fdf->points = NULL;
	fdf->max_x = 0;
	fdf->max_y = 0;
	fdf->max_z = INT_MIN;
	fdf->min_z = INT_MAX;
}

static void	init_mlx_env(t_fdf *fdf)
{
	fdf->xvar = mlx_init();
	if (!fdf->xvar)
	{
		print_error_exit(ERR_FDF_INIT);
	}
	fdf->window = mlx_new_window(fdf->xvar, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!fdf->window)
	{
		free_mlx_ptr(fdf);
		print_error_exit(ERR_FDF_INIT);
	}
	fdf->img = mlx_new_image(fdf->xvar, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img)
	{
		free_mlx_ptr(fdf);
		print_error_exit(ERR_FDF_INIT);
	}
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->stride,
			&fdf->endian);
	if (!fdf->addr)
	{
		free_mlx_ptr(fdf);
		print_error_exit(ERR_FDF_INIT);
	}
}

void	init_point_matrix(t_fdf *fdf)
{
	size_t	y;

	fdf->points = (t_point **)ft_calloc(fdf->max_y, sizeof(t_point *));
	if (!fdf->points)
	{
		print_error_exit(ERR_MALLOC);
	}
	y = 0;
	while (y < fdf->max_y)
	{
		fdf->points[y] = (t_point *)ft_calloc(fdf->max_x, sizeof(t_point));
		if (!fdf->points[y])
		{
			free_point_matrix(fdf->points, y);
			print_error_exit(ERR_MALLOC);
		}
		y++;
	}
}

int	main(int argc, const char *argv[])
{
	t_fdf	fdf;

	if (argc != 2 || !check_file_extension(argv[1], ".fdf"))
	{
		print_error_exit(ERR_ARG);
	}
	init_fdf_struct(&fdf);
	init_mlx_env(&fdf);
	get_map_size(argv[1], &fdf);
	init_point_matrix(&fdf);
	return (0);
}
