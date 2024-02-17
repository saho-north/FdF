/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:41:59 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/18 02:33:43 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	pixel_put(t_fdf *fdf, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
	{
		return ;
	}
	dst = fdf->addr + (y * fdf->stride + x * (fdf->bpp / 8));
	*(unsigned int *)dst = color;
}

/*
if (dx <= dy)
{
	draw_steep(fdf, p, end);
}
1以上（垂直に近い）の場合の描画方法
線は垂直に近いため、`y`座標を基準にして線を描画します。各ステップで`y`を増加（または減少）
条件に応じて`x`の値を調整します。このケースでは`draw_steep`関数が使用されます。
 */
static void	draw_steep(t_fdf *fdf, t_point *p, t_line_draw_data *line_data)
{
	int	err;
	int	x;
	int	y;
	int	i;

	err = 2 * line_data->dx - line_data->dy;
	x = p->x_2d;
	y = p->y_2d;
	i = 0;
	while (i++ <= line_data->dy)
	{
		pixel_put(fdf, x, y, WHITE);
		err += 2 * line_data->dx;
		if (err > 0)
		{
			x += line_data->x_direction;
			err -= 2 * line_data->dy;
		}
		y += line_data->y_direction;
	}
}

/*
if (dx > dy)
{
	draw_shallow(fdf, p, end);
}
線の傾斜が1未満（水平に近い）の場合の描画方法
線は水平に近いため、`x`座標を基準にして線を描画します。各ステップで`x`を増加（または減少）
条件に応じて`y`の値を調整します。このケースでは`draw_shallow`関数が使用されます。
 */
static void	draw_shallow(t_fdf *fdf, t_point *p, t_line_draw_data *line_data)
{
	int	err;
	int	x;
	int	y;
	int	i;

	err = 2 * line_data->dy - line_data->dx;
	x = p->x_2d;
	y = p->y_2d;
	i = 0;
	while (i++ <= line_data->dx)
	{
		pixel_put(fdf, x, y, WHITE);
		err += 2 * line_data->dy;
		if (err > 0)
		{
			y += line_data->y_direction;
			err -= 2 * line_data->dx;
		}
		x += line_data->x_direction;
	}
}

static void	draw_line(t_fdf *fdf, t_point *start, t_point *end)
{
	t_line_draw_data	line_data;

	line_data.dx = abs(end->x_2d - start->x_2d);
	line_data.dy = abs(end->y_2d - start->y_2d);
	line_data.x_direction = 1;
	if (end->x_2d < start->x_2d)
	{
		line_data.x_direction = -1;
	}
	line_data.y_direction = 1;
	if (end->y_2d < start->y_2d)
	{
		line_data.y_direction = -1;
	}
	if (line_data.dx > line_data.dy)
	{
		draw_shallow(fdf, start, &line_data);
	}
	else
	{
		draw_steep(fdf, start, &line_data);
	}
}

void	clear_image(t_fdf *fdf)
{
	ft_bzero(fdf->addr, WIN_WIDTH * WIN_HEIGHT * fdf->bpp);
}

void	draw_wireframe(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	clear_image(fdf);
	while (y < fdf->max_y)
	{
		x = 0;
		while (x < fdf->max_x)
		{
			if (x + 1 < fdf->max_x)
			{
				draw_line(fdf, &fdf->points[y][x], &fdf->points[y][x + 1]);
			}
			if (y + 1 < fdf->max_y)
			{
				draw_line(fdf, &fdf->points[y][x], &fdf->points[y + 1][x]);
			}
			x++;
		}
		y++;
	}
}
