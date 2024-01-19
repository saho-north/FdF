/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:31:32 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/19 23:38:00 by sakitaha         ###   ########.fr       */
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
		mlx_destroy_image(fdf->xvar, fdf->img);
		fdf->img = NULL;
	}
	if (fdf->window)
	{
		mlx_destroy_window(fdf->xvar, fdf->window);
		fdf->window = NULL;
	}
	if (fdf->xvar)
	{
		mlx_destroy_display(fdf->xvar);
		free(fdf->xvar);
		fdf->xvar = NULL;
	}
}

/**
 * Safely frees a dynamically allocated 2D array (matrix) of t_point structures.
 * Essential for preventing memory leaks by ensuring that all allocated memory
 * is properly freed when an error occurs or when the program ends.
 */
void	free_point_matrix(t_point **points, size_t max_y)
{
	size_t	i;

	if (points == NULL)
	{
		return ;
	}
	i = 0;
	while (i < max_y)
	{
		free(points[i]);
		points[i] = NULL;
		i++;
	}
	free(points);
	points = NULL;
}

/**
 * Safely frees a dynamically allocated splited lines of str.
 */
void	free_split_line(char **split_line)
{
	size_t	i;

	if (split_line == NULL)
	{
		return ;
	}
	i = 0;
	while (split_line[i])
	{
		free(split_line[i]);
		split_line[i] = NULL;
		i++;
	}
	free(split_line);
	split_line = NULL;
}
