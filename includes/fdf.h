/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 02:28:25 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/21 16:16:16 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "error.h"
# include "get_next_line.h"
# include "libft.h"
// # include <errno.h>
// # include <fcntl.h>
// # include <stdbool.h>
// # include <stdio.h>
# include <stdlib.h>
// # include <unistd.h>

# define BUFFER_SIZE 1024

/**
 * color: 0xRRGGBBAA
 */
typedef struct s_point
{
	int				source_z;
	float			x;
	float			y;
	float			z;
	unsigned int	color;
}					t_point;
typedef struct s_env
{
	// map関連の情報
	t_point			**points;
	size_t			max_x;
	size_t			max_y;
	int				max_z;
	int				min_z;
}					t_env;

// typedef struct s_cam
// {
// 	int				projection;
// 	float			scale_factor;
// 	float			move_x;
// 	float			move_y;
// 	double alpha; // X軸回転
// 	double beta;  // Y軸回転
// 	double gamma; // Z軸回転
// }					t_cam;

// typedef struct s_image
// {
// 	void			*image;
// 	char			*buffer;
// 	int				pixel_bits;
// 	int				line_bytes;
// 	int				endian;
// }					t_image;

// typedef struct s_fdf
// {
// 	t_map			*map;
// 	t_cam			*cam;
// 	t_image			*image;
// 	void			*mlx;
// 	void			*win;
// }					t_fdf;

// // ??

// typedef struct s_ivector
// {
// 	int				x;
// 	int				y;
// 	int				z;
// }					t_ipoint;

// typedef struct s_fpoint
// {
// 	float			x;
// 	float			y;
// }					t_fpoint;

// typedef struct s_delta
// {
// 	float			dx;
// 	float			dy;
// }					t_delta;

// typedef struct s_env
// {
// 	void			*mlx;
// 	void			*win;
// 	void			*image;
// 	char			*address;
// 	char			*map_path;
// 	int				**final_tab;
// 	int				map_w;
// 	int				map_h;
// 	int				x;
// 	int				y;
// 	int				i;
// 	int				c_x;
// 	int				c_y;
// 	int				bits_per_pixel;
// 	int				line_length;
// 	int				endian;
// 	int				scale;
// 	int				translation;
// 	float			altitude;
// 	float			zoom;
// 	float			alpha;
// 	t_ipoint		*initial_points;
// 	t_fpoint		*final_points;
// 	t_delta			*delta;
// }					t_env;

// typedef struct s_vector3
// {
// 	float			x;
// 	float			y;
// 	float			z;
// }					t_vector3;

// typedef struct s_stvector2
// {
// 	size_t			x;
// 	size_t			y;
// }					t_stvector2;

// typedef struct s_vector2
// {
// 	float			x;
// 	float			y;
// }					t_vector2;

// typedef struct s_map
// {
// 	char			*path;
// 	size_t			h;
// 	size_t			w;
// 	int				**i_grid;
// }					t_map;

// typedef struct s_env
// {
// 	void			*mlx;
// 	void			*win;
// 	void			*img;
// 	char			*addr;
// 	int				bits_per_pixel;
// 	int				line_length;
// 	int				endian;
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
// }					t_env;

void				get_map_size(const char *filename, t_env *env);

#endif
