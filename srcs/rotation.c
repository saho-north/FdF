

// #include <math.h>
// #include <stdio.h>

// typedef struct s_point
// {
// 	int				source_z;
// 	float			x;
// 	float			y;
// 	float			z;
// 	unsigned char	rgb[3];
// 	unsigned int	color;
// 	bool			is_exist;
// }					t_point;

// t_point	rotation_x(t_point points, double angle)
// {
// 	t_point	rotated;
// 	double	rad;

// 	rad = angle * M_PI / 180.0;
// 	rotated.x = points.x;
// 	rotated.y = points.y * cos(rad) - points.z * sin(rad);
// 	rotated.z = points.y * sin(rad) + points.z * cos(rad);
// 	return (rotated);
// }

// t_point	rotation_y(t_point points, double angle)
// {
// 	t_point	rotated;

// 	double rad = angle * M_PI / 180.0; // 角度をラジアンに変換
// 	rotated.x = points.x;
// 	rotated.y = points.y * cos(rad) - points.z * sin(rad);
// 	rotated.z = points.y * sin(rad) + points.z * cos(rad);
// 	return (rotated);
// }

// t_point	rotation_x(t_point points, double angle)
// {
// 	t_point	rotated;

// 	double rad = angle * M_PI / 180.0; // 角度をラジアンに変換
// 	rotated.x = points.x;
// 	rotated.y = points.y * cos(rad) - points.z * sin(rad);
// 	rotated.z = points.y * sin(rad) + points.z * cos(rad);
// 	return (rotated);
// }

// int	main(void)
// {
// 	t_point	point;
// 	t_point	rotatedPoint;

// 	point = {1, 2, 3};
// 	rotatedPoint = rotation_x(point, 10);
// 	printf("Rotated Point: x=%f, y=%f, z=%f\n", rotatedPoint.x, rotatedPoint.y,
// 			rotatedPoint.z);
// 	return (0);
// }

// Matrix4x4	createRotationMatrix(float angle){
// 	Rotation matrix around the Z - axis}

// Matrix4x4	createTranslationMatrix(float dx, float dy, float dz){
// 	Translation matrix}

// Matrix4x4	createScalingMatrix(float sx, float sy, float sz){
// 	Scaling matrix}

// Matrix4x4			combinedTransformation = createScalingMatrix(sx, sy, sz)
// 			* createRotationMatrix(angle) * createTranslationMatrix(dx, dy, dz);

// typedef struct
// {
// 	double x, y, z;
// }					t_point;

// t_point	rotation_x(t_point points, double angle)
// {
// 	t_point	rotated;

// 	double rad = angle * M_PI / 180.0; // 角度をラジアンに変換
// 	rotated.x = points.x;
// 	rotated.y = points.y * cos(rad) - points.z * sin(rad);
// 	rotated.z = points.y * sin(rad) + points.z * cos(rad);
// 	return (rotated);
// }

// int	main(void)
// {
// 	t_point	point;
// 	t_point	rotatedPoint;

// 	point = {1, 2, 3};
// 	rotatedPoint = rotation_x(point, 10);
// 	printf("Rotated Point: x=%f, y=%f, z=%f\n", rotatedPoint.x, rotatedPoint.y,
// 			rotatedPoint.z);
// 	return (0);
// }
