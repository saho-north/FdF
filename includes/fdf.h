/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 02:28:25 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/20 16:40:45 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "error.h"
# include "libft.h"

# define BUFFER_SIZE 1024
# define WIN_WIDTH 1600
# define WIN_HEIGHT 900

# define MOVE_STEP 10
# define ROTATE_STEP 5

# define WHITE 0xFFFFFF
# define BLACK 0x000000

typedef enum e_projections
{
	ISOMETRIC,
	ORTHOGRAPHIC,
	OBLIQUE,
	CAVALIER
}					t_projections;

typedef struct s_point
{
	int				original_x;
	int				original_y;
	int				original_z;
	int				color;
	float			x;
	float			y;
	float			z;
	int				x_2d;
	int				y_2d;
	bool			is_exist;

}					t_point;

// TODO: Do I need max_z and min_z?
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
	float			scale;
	float			depth_scale;
	int				x_move;
	int				y_move;
	int				x_degree;
	int				y_degree;
	int				z_degree;
	t_projections	projection;

}					t_fdf;

typedef struct s_line_draw_data
{
	int				abs_dx;
	int				abs_dy;
	int				x_direction;
	int				y_direction;
	int				color0;
	int				color1;
}					t_line_draw_data;

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

/* init.c */
void				init_fdf(t_fdf *fdf, const char *filename);

/* key_hook.c */
int					key_press(int keysym, t_fdf *fdf);
int					key_release(int keysym, t_fdf *fdf);

/* liang_barsky.c */
bool				liang_barsky(t_point *point0, t_point *point1);

/* parse_map.c */
void				parse_map(const char *filename, t_fdf *fdf);

/* parse_point.c */
bool				parse_point(t_fdf *fdf, t_point *point, char *str);

/* projection.c */
float				deg_to_rad(float degrees);
void				projection(t_fdf *fdf, t_point *point);

/* render.c */
void				pixel_put(t_fdf *fdf, int x, int y, int color);
int					render(t_fdf *fdf);

/* reset.c */
void				reset_render_param(t_fdf *fdf);

/* rotation.c */
void				rotation(t_fdf *fdf, t_point *point);

/* transform.c */
void				transform(t_fdf *fdf, float scale, float z_scale,
						int x_move, int y_move);

#endif
