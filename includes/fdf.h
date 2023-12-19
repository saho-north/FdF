/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 02:28:25 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/20 00:09:45 by sakitaha         ###   ########.fr       */
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
	int				source_x;
	int				source_y;
	int				source_z;
	float			x;
	float			y;
	float			z;
	unsigned int	color;
}					t_point;

typedef struct s_map
{
	t_point			**grids;
	int				max_x;
	int				max_y;
	int				max_z;
	int				min_z;
}					t_map;

typedef struct s_cam
{
	int				projection;
	float			scale_factor;
	float			move_x;
	float			move_y;
	double alpha; // X軸回転
	double beta;  // Y軸回転
	double gamma; // Z軸回転
}					t_cam;

typedef struct s_image
{
	void			*image;
	char			*buffer;
	int				pixel_bits;
	int				line_bytes;
	int				endian;
}					t_image;

typedef struct s_fdf
{
	t_map			*map;
	t_cam			*cam;
	t_image			*image;
	void			*mlx;
	void			*win;
}					t_fdf;

#endif
