/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 02:28:25 by sakitaha          #+#    #+#             */
/*   Updated: 2024/03/14 23:42:24 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "color.h"
# include "error.h"
# include "libft.h"

# define BUFFER_SIZE 1024
# define WIN_WIDTH 1600
# define WIN_HEIGHT 900

# define MOVE_STEP 10
# define ROTATE_STEP 5
# define SCALE_STEP 1
# define DEPTH_SCALE_STEP 0.5

# define ISO_DEGREE 30
# define CABINET_DEGREE 45
# define TRIMETRIC_DEGREE_X 20
# define TRIMETRIC_DEGREE_Y 30
# define TRIMETRIC_DEGREE_Z 45

typedef enum e_projections
{
	ISOMETRIC,
	ORTHOGRAPHIC,
	CABINET,
	TRIMETRIC
}					t_projections;

typedef struct s_point
{
	int				original_x;
	int				original_y;
	int				original_z;
	int				color;
	double			x;
	double			y;
	double			z;
	int				x_2d;
	int				y_2d;
	bool			is_exist;

}					t_point;

typedef struct s_fdf
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				stride;
	int				endian;
	int				max_x;
	int				max_y;
	int				max_z;
	int				min_z;
	t_point			**points;
	double			depth_buffer[WIN_HEIGHT][WIN_WIDTH];
	double			scale;
	double			depth_scale;
	int				x_move;
	int				y_move;
	int				x_degree;
	int				y_degree;
	int				z_degree;
	t_projections	projection;
	int				mouse_press_x;
	int				mouse_press_y;
	bool			is_shift_pressed;
	bool			is_mouse_dragging;
	bool			redraw;
	bool			colorful;

}					t_fdf;

typedef struct s_line_draw_data
{
	int				abs_dx;
	int				abs_dy;
	int				x_direction;
	int				y_direction;
	int				color0;
	int				color1;
	double			start_z;
	double			end_z;
}					t_line_draw_data;

/* color.c */
int					get_color(t_fdf *fdf, t_point *p);

/* draw_utils.c */
void				pixel_put(t_fdf *fdf, int x, int y, int color);
bool				is_valid_pixel(t_fdf *fdf, int x, int y, double z);
double				get_depth(t_line_draw_data *line_data, double t);
int					get_lerpcolor(t_line_draw_data *line_data, double t);

/* draw.c */
void				draw_wireframe(t_fdf *fdf);

/* error.c */
void				perror_exit(char *message);
void				print_error(char *message);
void				print_error_exit(char *message);
void				free_and_perror_exit(t_fdf *fdf, char *message);
void				free_and_error_exit(t_fdf *fdf, char *message);

/* free.c */
void				free_mlx_ptr(t_fdf *fdf);
void				free_point_matrix(t_point **points, size_t max_y);
void				free_split_line(char **split_line);
int					clean_exit(t_fdf *fdf);

/* get_map_size.c */
void				get_map_size(t_fdf *fdf, const char *filename);

/* hook.c */
int					button_press(int button, int x, int y, t_fdf *fdf);
int					button_release(int button, int x, int y, t_fdf *fdf);
int					motion_notify(int x, int y, t_fdf *fdf);
int					handle_loop_hook(t_fdf *fdf);

/* init.c */
void				init_fdf(t_fdf *fdf, const char *filename);

/* key_handler.c */
void				handle_simple_actions(int key, t_fdf *fdf);
void				handle_projection(int key, t_fdf *fdf);
void				handle_scale(int key, t_fdf *fdf);
void				handle_movement(int key, t_fdf *fdf);
void				handle_rotation(int key, t_fdf *fdf);

/* key_hook.c */
int					key_press(int keysym, t_fdf *fdf);
int					key_release(int keysym, t_fdf *fdf);

/* liang_barsky.c */
bool				liang_barsky(t_point *point0, t_point *point1);

/* parse_map.c */
void				parse_map(t_fdf *fdf, const char *filename);

/* parse_point.c */
bool				parse_point(t_fdf *fdf, t_point *point, char *str);

/* projection.c */
void				projection(t_fdf *fdf, t_point *point);

/* render.c */
// void				put_pixel_if_valid(t_fdf *fdf, int x, int y, int color);
int					render(t_fdf *fdf);

/* reset.c */
void				reset_render_param(t_fdf *fdf);

/* rotation.c */
double				deg_to_rad(double degrees);
void				rotation(t_fdf *fdf, t_point *point);

/* transform.c */
void				transform(t_fdf *fdf, double scale, double z_scale);

/* usage.c */
void				draw_usage(t_fdf *fdf);

#endif
