/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 02:28:25 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/08 20:46:13 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "error.h"
# include "libft.h"

# define BUFFER_SIZE 1024
# define WIN_WIDTH 1600
# define WIN_HEIGHT 900

typedef struct s_point
{
	int				height;
	float			x;
	float			y;
	float			z;
	float			x_2d;
	float			y_2d;
	unsigned char	rgb[3];
	unsigned int	color;
	bool			is_exist;
}					t_point;

typedef struct s_fdf
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img;
	char			*addr;
	int				bpp;
	int				stride;
	int				endian;
	size_t			max_x;
	size_t			max_y;
	int				max_z;
	int				min_z;
	t_point			**points;
	int				translation;
}					t_fdf;

// typedef struct s_fdf
// {

// 	int				scale;
// 	float			alpha;
// 	float			sm_y;
// 	float			bg_y;
// 	float			sm_x;
// 	float			bg_x;
// 	t_vector2		offset;
// 	t_map			map;
// 	t_vector3		*points;
// 	t_vector2		*final_points;
// 	t_vector2		*rotated;
// }					t_fdf;

/*
typedef struct s_fdf
{
	char			*map_path;
	int				**final_tab;
	int				map_w;
	int				map_h;
	int				x;
	int				y;
	int				i;
	int				c_x;
	int				c_y;

	int				scale;
	int				translation;
	float			altitude;
	float			zoom;
	float			alpha;
	t_ipoint		*initial_points;
	t_fpoint		*final_points;
	t_delta			*delta;
}					t_fdf;
 */

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

/* get_map_size.c */
void				get_map_size(const char *filename, t_fdf *fdf);

/* init.c */
void				init_fdf_struct(t_fdf *fdf);
void				init_mlx_env(t_fdf *fdf);
void				init_point_matrix(t_fdf *fdf);

/* parse_map.c */
void				parse_map(const char *filename, t_fdf *fdf);

/* parse_point.c */
bool				parse_point(t_fdf *fdf, t_point *point, char *str);

#endif
