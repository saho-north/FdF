/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:31:32 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/18 02:36:27 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

/**
 * Safely frees a dynamically allocated mlx pointer.
 * Essential for preventing memory leaks by ensuring that all allocated memory
 * is properly freed when an error occurs or when the program ends.
 */
void	free_mlx_ptr(t_fdf *fdf)
{
	if (fdf->img)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		fdf->img = NULL;
	}
	if (fdf->win)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		fdf->win = NULL;
	}
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
		fdf->mlx = NULL;
	}
}

/**
 * Frees all dynamically allocated memory
 */
void	free_all(t_fdf *fdf)
{
	free_mlx_ptr(fdf);
	ft_free2d((void **)fdf->points, fdf->max_y);
	ft_free2d((void **)fdf->depth_buffer, WIN_HEIGHT);
	free(fdf);
}

/**
 * Frees all dynamically allocated memory and exits the program.
 * Called for successfully terminating the program.
  */
int	clean_exit(t_fdf *fdf)
{
	free_all(fdf);
	exit(0);
	return (0);
}
