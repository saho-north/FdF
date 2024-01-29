/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:41:59 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/27 00:41:49 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_default_line_len(t_fdf *fdf)
{
	float	x_len;
	float	y_len;
	float	min_len;
	size_t	x;
	size_t	y;

	x_len = (float)(WIN_WIDTH * 0.8) / (fdf->max_x - 1);
	y_len = (float)(WIN_HEIGHT * 0.8) / (fdf->max_y - 1);
	min_len = fmin(x_len, y_len);
	y = 0;
	while (y < fdf->max_y)
	{
		x = 0;
		while (x < fdf->max_x)
		{
			fdf->points[y][x].x += min_len * x;
			fdf->points[y][x].y += min_len * y;
			x++;
		}
		y++;
	}
}

void	move_to_center(t_fdf *fdf)
{
	size_t	x;
	size_t	y;
	float	current_center_x;
	float	current_center_y;
	float	x_offset;
	float	y_offset;

	current_center_x = (fdf->points[0][0].x + fdf->points[fdf->max_y
			- 1][fdf->max_x - 1].x) / 2;
	current_center_y = (fdf->points[0][0].y + fdf->points[fdf->max_y
			- 1][fdf->max_x - 1].y) / 2;
	x_offset = (float)WIN_WIDTH / 2 - current_center_x;
	y_offset = (float)WIN_HEIGHT / 2 - current_center_y;
	y = 0;
	while (y < fdf->max_y)
	{
		x = 0;
		while (x < fdf->max_x)
		{
			fdf->points[y][x].x += x_offset;
			fdf->points[y][x].y += y_offset;
			x++;
		}
		y++;
	}
}

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, unsigned int color)
{
	char	*dst;

	dst = fdf->addr + (y * fdf->stride + x * (fdf->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_point p1, t_point p2, t_fdf *fdf)
{
	int		x;
	int		y;
	int		max;
	t_point	delta;

	delta.x = abs(p2.x - p1.x);
	delta.y = abs(p2.y - p1.y);
	max = fmax(delta.x, delta.y);
	x = -1;
	while (++x <= max)
	{
		y = x * delta.y / delta.x;
		if (p1.x < p2.x)
			mlx_pixel_put(fdf->xvar, fdf->window, p1.x + x, p1.y + y, 0xFFFFFF);
		else
			mlx_pixel_put(fdf->xvar, fdf->window, p1.x - x, p1.y - y, 0xFFFFFF);
	}
}

void	bresenham(t_point p1, t_point p2, t_fdf *fdf)
{
	int	slope_error_new;
	int	m_new;
	int	dx;
	int	x;
	int	y;

	m_new = 2 * ((int)p2.y - (int)p1.y);
	dx = (int)p2.x - (int)p1.x;
	slope_error_new = m_new - dx;
	x = (int)p1.x;
	y = (int)p1.y;
	while (x <= (int)p2.x)
	{
		my_mlx_pixel_put(fdf, x, y, 0xFFFFFF);
		slope_error_new += m_new;
		if (slope_error_new >= 0)
		{
			y++;
			slope_error_new -= 2 * dx;
		}
		x++;
	}
}

void	draw_map(t_fdf *fdf)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < fdf->max_y)
	{
		x = 0;
		while (x < fdf->max_x)
		{
			if (x < fdf->max_x - 1)
			{
				draw_line(fdf->points[y][x], fdf->points[y][x + 1], fdf);
			}
			if (y < fdf->max_y - 1)
			{
				draw_line(fdf->points[y][x], fdf->points[y + 1][x], fdf);
			}
			x++;
		}
		y++;
	}
}

void	visualize_wireframe(t_fdf *fdf)
{
	calculate_default_line_len(fdf);
	move_to_center(fdf);
	draw_map(fdf);
}
