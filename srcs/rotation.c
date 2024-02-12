
#include "fdf.h"
#include <math.h>

/**
 * Rotates the given point around the X-axis.
 */
void	rotate_x(t_point *point, float degrees)
{
	float	original_y;
	float	radians;

	original_y = point->y;
	radians = degrees * M_PI / 180.0;
	point->y = original_y * cos(radians) - point->z * sin(radians);
	point->z = original_y * sin(radians) + point->z * cos(radians);
}

/**
 * Rotates the given point around the Y-axis.
 */
void	rotate_y(t_point *point, float degrees)
{
	float	original_x;
	float	radians;

	original_x = point->x;
	radians = degrees * M_PI / 180.0;
	point->x = original_x * cos(radians) + point->z * sin(radians);
	point->z = -original_x * sin(radians) + point->z * cos(radians);
}

/**
 * Rotates the given point around the Z-axis.
 */
void	rotate_z(t_point *point, float degrees)
{
	float	original_x;
	float	original_y;
	float	radians;

	original_x = point->x;
	original_y = point->y;
	radians = degrees * M_PI / 180.0;
	point->x = original_x * cos(radians) - original_y * sin(radians);
	point->y = original_x * sin(radians) + original_y * cos(radians);
}

/**
 * Rotates the map around the X, Y and Z axes.
*/
void	rotation(t_fdf *fdf)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < fdf->max_y)
	{
		x = 0;
		while (x < fdf->max_x)
		{
			if (fdf->points[y][x].is_exist == false)
			{
				break ;
			}
			//TODO: ZOOMは別の関数でやるのか？まだよくわからないです。何回もiterateすることになるから無駄になりそうだけど、、
			rotate_x(&fdf->points[y][x], fdf->ctrl.x_degree);
			rotate_y(&fdf->points[y][x], fdf->ctrl.y_degree);
			rotate_z(&fdf->points[y][x], fdf->ctrl.z_degree);
			x++;
		}
		y++;
	}
}
