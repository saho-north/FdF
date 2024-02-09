
#include "fdf.h"
#include <math.h>
#include <stdio.h>


t_point	rotation_x(t_point points, double angle)
{
	t_point	rotated;
	double	rad;

	rad = angle * M_PI / 180.0;
	rotated.x = points.x;
	rotated.y = points.y * cos(rad) - points.z * sin(rad);
	rotated.z = points.y * sin(rad) + points.z * cos(rad);
	return (rotated);
}

t_point	rotation_y(t_point points, double angle)
{
	t_point	rotated;

	double rad = angle * M_PI / 180.0; // 角度をラジアンに変換
	rotated.x = points.x;
	rotated.y = points.y * cos(rad) - points.z * sin(rad);
	rotated.z = points.y * sin(rad) + points.z * cos(rad);
	return (rotated);
}

t_point	rotation_x(t_point points, double angle)
{
	t_point	rotated;

	double rad = angle * M_PI / 180.0; // 角度をラジアンに変換
	rotated.x = points.x;
	rotated.y = points.y * cos(rad) - points.z * sin(rad);
	rotated.z = points.y * sin(rad) + points.z * cos(rad);
	return (rotated);
}

int	main(void)
{
	t_point	point;
	t_point	rotatedPoint;

	point = {1, 2, 3};
	rotatedPoint = rotation_x(point, 10);
	printf("Rotated Point: x=%f, y=%f, z=%f\n", rotatedPoint.x, rotatedPoint.y,
			rotatedPoint.z);
	return (0);
}

Matrix4x4	createRotationMatrix(float angle){
	Rotation matrix around the Z - axis}

Matrix4x4	createTranslationMatrix(float dx, float dy, float dz){
	Translation matrix}

Matrix4x4	createScalingMatrix(float sx, float sy, float sz){
	Scaling matrix}

Matrix4x4			combinedTransformation = createScalingMatrix(sx, sy, sz)
			* createRotationMatrix(angle) * createTranslationMatrix(dx, dy, dz);


//----

t_point	rotation_x(t_point points, double angle)
{
	t_point	rotated;

	double rad = angle * M_PI / 180.0; // 角度をラジアンに変換
	rotated.x = points.x;
	rotated.y = points.y * cos(rad) - points.z * sin(rad);
	rotated.z = points.y * sin(rad) + points.z * cos(rad);
	return (rotated);
}

int	main(void)
{
	t_point	point;
	t_point	rotatedPoint;

	point = {1, 2, 3};
	rotatedPoint = rotation_x(point, 10);
	printf("Rotated Point: x=%f, y=%f, z=%f\n", rotatedPoint.x, rotatedPoint.y,
			rotatedPoint.z);
	return (0);
}

//x軸周りの回転
void	rotate_x(t_point *point, float degrees)
{
	float	x;
	float	y;
	float	z;
	float	radians;

	x = point->x;
	y = point->y;
	z = point->z;
	radians = degrees * M_PI / 180.0;
	point->x = x;
	point->y = y * cos(radians) - z * sin(radians);
	point->z = y * sin(radians) + z * cos(radians);
}

//y軸周りの回転
void	rotate_y(t_point *point, float degrees)
{
	float	x;
	float	y;
	float	z;
	float	radians;

	x = point->x;
	y = point->y;
	z = point->z;
	radians = degrees * M_PI / 180.0;
	point->x = x * cos(radians) + z * sin(radians);
	point->y = y;
	point->z = -x * sin(radians) + z * cos(radians);
}

//z軸周りの回転
void	rotate_z(t_point *point, float degrees)
{
	float	x;
	float	y;
	float	z;
	float	radians;

	x = point->x;
	y = point->y;
	z = point->z;
	radians = degrees * M_PI / 180.0;
	point->x = x * cos(radians) - y * sin(radians);
	point->y = x * sin(radians) + y * cos(radians);
	point->z = z;
}