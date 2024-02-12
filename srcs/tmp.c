/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   later_to_delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:06:40 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/08 14:38:08 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * This is a temporary file for keeping snippets of code.
 */

// 正面投影 これいらないよね？
void	orthographic_projection(t_point *point)
{
	point->x = point->x;
	point->y = point->y;
	point->z = 0;
}

// 斜投影
void	oblique_projection(t_point *point, float degrees)
{
	float	x;
	float	y;
	float	z;
	float	radians;

	x = point->x;
	y = point->y;
	z = point->z;
	radians = degrees * M_PI / 180.0;
	point->x = x + z * cos(radians);
	point->y = y + z * sin(radians);
	point->z = 0;
}

// 透視投影
void	perspective_projection(t_point *point)
{
	float	x;
	float	y;
	float	z;

	x = point->x;
	y = point->y;
	z = point->z;
	// 徐算エラー防止
	if (z == 0)
		z = 1.0;
	point->x = x / z;
	point->y = y / z;
	point->z = z;
}



#define ZOOM_IN_FACTOR 1.5
#define ZOOM_OUT_FACTOR 0.5

void	zoom_in(t_point *point)
{
	point->x *= ZOOM_IN_FACTOR;
	point->y *= ZOOM_IN_FACTOR;
	point->z *= ZOOM_IN_FACTOR;
}

void	zoom_out(t_point *point)
{
	point->x *= ZOOM_OUT_FACTOR;
	point->y *= ZOOM_OUT_FACTOR;
	point->z *= ZOOM_OUT_FACTOR;
}

// TODO: x_min, x_max, y_min, y_maxも構造体に入れるか後で考える
 void centering_preparation(t_fdf *fdf)
 {
	size_t	x;
	size_t	y;
	int		x_min = INT_MAX;
	int		x_max = INT_MIN;
	int		y_min = INT_MAX;
	int		y_max = INT_MIN;

	x = 0;
	y = 0;
	while (y < fdf->max_y)
	{
		x = 0;
		while (x < fdf->max_x)
		{
			if(fdf->points[y][x].is_exist == false)
			{
				break;
			}
			x_min = min((int)fdf->points[y][x].x_2d, x_min);
			x_max = max((int)fdf->points[y][x].x_2d, x_max);
			y_min = min((int)fdf->points[y][x].y_2d, y_min);
			y_max = max((int)fdf->points[y][x].y_2d, y_max);
		}
		y++;
	}
	fdf->x_move = WIN_WIDTH / 2 - (x_max + x_min) / 2;
	fdf->y_move = WIN_HEIGHT / 2 - (y_max + y_min) / 2;
 }
