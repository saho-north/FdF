/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:35:23 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/21 16:26:36 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/**
 * Reset all scale parameters to the initial state.
 */
static void	reset_scale(t_fdf *fdf)
{
	float	x_len;
	float	y_len;

	x_len = (float)WIN_WIDTH / fdf->max_x / 2;
	y_len = (float)WIN_HEIGHT / fdf->max_y / 2;
	fdf->scale = fmin(x_len, y_len);
	if (fdf->scale > 3)
	{
		fdf->scale /= 1.2;
	}
	fdf->depth_scale = 3;
}

/**
 * Reset all move parameters to the initial state.
 */
static void	reset_move(t_fdf *fdf)
{
	fdf->x_move = ((float)WIN_WIDTH - (fdf->max_x - 1) * fdf->scale) / 1.6;
	fdf->y_move = ((float)WIN_HEIGHT - (fdf->max_y - 1) * fdf->scale) / 2;
}

/**
 * Reset all rotation parameters to the initial state.
 */
static void	reset_degree(t_fdf *fdf)
{
	fdf->x_degree = 0;
	fdf->y_degree = 0;
	fdf->z_degree = 0;
}

/**
 * Reset all render parameters to the initial state.
 */
void	reset_render_param(t_fdf *fdf)
{
	reset_scale(fdf);
	reset_move(fdf);
	reset_degree(fdf);
}
