#include <math.h>

typedef struct {
	int		source_x;
	int		source_y;
	int		source_z;
    double	x;
    double	y;
    double	z;
	unsigned int	color;
} t_point;

// 等角投影 
void isometric_projection(t_point *point) {
    
	double x = (double)point->source_x;
	double y = (double)point->source_y;
	double z = (double)point->source_z;

    point->x = (x - y) * sqrt(2.0) / 2;
    point->y = ((x + y) * sqrt(2.0) - z * sqrt(6.0)) / 3;
	point->z = z;
}

// 正面投影
void orthographic_projection(t_point *point) {

    point->x = (double)point->source_x;
    point->y = (double)point->source_y;
    point->z = 0;
}


// 斜投影
void oblique_projection(t_point *point, double degrees) {

	double x = (double)point->source_x;
	double y = (double)point->source_y;
	double z = (double)point->source_z;
	double radians = degrees * M_PI / 180.0;

	point->x = x + z * cos(radians);
	point->y = y + z * sin(radians);
	point->z = 0;
}

// 透視投影
void perspective_projection(t_point *point) {

	double x = (double)point->source_x;
	double y = (double)point->source_y;
	double z = (double)point->source_z;

	// 徐算エラー防止
	if (z == 0)
		z = 1.0;
	point->x = x / z;
	point->y = y / z;
	point->z = z;
}

// x軸周りの回転
void rotate_x(t_point *point, double degrees) {

	double x = (double)point->source_x;
	double y = (double)point->source_y;
	double z = (double)point->source_z;

	double radians = degrees * M_PI / 180.0;

	point->x = x;
	point->y = y * cos(radians) - z * sin(radians);
	point->z = y * sin(radians) + z * cos(radians);
}

// y軸周りの回転
void rotate_y(t_point *point, double degrees) {

	double x = (double)point->source_x;
	double y = (double)point->source_y;
	double z = (double)point->source_z;

	double radians = degrees * M_PI / 180.0;

	point->x = x * cos(radians) + z * sin(radians);
	point->y = y;
	point->z = - x * sin(radians) + z * cos(radians);
}

// z軸周りの回転
void rotate_z(t_point *point, double degrees) {

	double x = (double)point->source_x;
	double y = (double)point->source_y;
	double z = (double)point->source_z;

	double radians = degrees * M_PI / 180.0;

	point->x = x * cos(radians) - y * sin(radians);
	point->y = x * sin(radians) + y * cos(radians);
	point->z = z;
}

# define ZOOM_IN_FACTOR 1.5
# define ZOOM_OUT_FACTOR 0.5

void zoom_in(t_point *point)
{
	point->x *= ZOOM_IN_FACTOR;
	point->y *= ZOOM_IN_FACTOR;
	point->z *= ZOOM_IN_FACTOR;
}

void zoom_out(t_point *point)
{
	point->x *= ZOOM_OUT_FACTOR;
	point->y *= ZOOM_OUT_FACTOR;
	point->z *= ZOOM_OUT_FACTOR;
}