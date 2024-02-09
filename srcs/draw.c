/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:41:59 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/08 14:39:06 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, unsigned int color)
{
	char	*dst;

	dst = fdf->addr + (y * fdf->stride + x * (fdf->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	bresenham(t_point p1, t_point p2, t_fdf *fdf)
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

static bool	is_line_exist(t_point p1, t_point p2)
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;

	if (!p1.is_exist || !p2.is_exist)
	{
		return (false);
	}
	x1 = (int)p1.x_2d;
	y1 = (int)p1.y_2d;
	x2 = (int)p2.x_2d;
	y2 = (int)p2.y_2d;
	if (x1 >= 0 && x1 < WIN_WIDTH && y1 >= 0 && y1 < WIN_HEIGHT)
	{
		return (true);
	}
	if (x2 >= 0 && x2 < WIN_WIDTH && y2 >= 0 && y2 < WIN_HEIGHT)
	{
		return (true);
	}
	if ((x1 < 0 && x2 < 0) || (x1 >= WIN_WIDTH && x2 >= WIN_WIDTH))
	{
		return (false);
	}
	if ((y1 < 0 && y2 < 0) || (y1 >= WIN_HEIGHT && y2 >= WIN_HEIGHT))
	{
		return (false);
	}
	return (true);
}

static void	draw_from_start(t_fdf *fdf)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < fdf->max_y)
	{
		x = 0;
		while (x < fdf->max_x)
		{
			if (x + 1 < fdf->max_x && is_line_exist(fdf->points[y][x],
					fdf->points[y][x + 1]))
			{
				bresenham(fdf->points[y][x], fdf->points[y][x + 1], fdf);
			}
			if (y + 1 < fdf->max_y && is_line_exist(fdf->points[y][x],
					fdf->points[y + 1][x]))
			{
				bresenham(fdf->points[y][x], fdf->points[y + 1][x], fdf);
			}
			x++;
		}
		y++;
	}
}

static void	draw_from_end(t_fdf *fdf)
{
	int	x;
	int	y;

	y = fdf->max_y - 1;
	while (y >= 0)
	{
		x = fdf->max_x - 1;
		while (x >= 0)
		{
			if (x > 0 && is_line_exist(fdf->points[y][x], fdf->points[y][x
					- 1]))
			{
				bresenham(fdf->points[y][x], fdf->points[y][x - 1], fdf);
			}
			if (y > 0 && is_line_exist(fdf->points[y][x], fdf->points[y
					- 1][x]))
			{
				bresenham(fdf->points[y][x], fdf->points[y - 1][x], fdf);
			}
			x--;
		}
		y--;
	}
}

void	draw_wireframe(t_fdf *fdf)
{
	if (fdf->points[0][0].x < fdf->points[fdf->max_y - 1][fdf->max_x - 1].x)
	{
		draw_from_start(fdf);
	}
	else
	{
		draw_from_end(fdf);
	}
}
