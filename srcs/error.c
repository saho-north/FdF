/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:49:04 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/08 20:46:14 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Displays a system error message based on the current errno
 * and exits the program with EXIT_FAILURE status.
 */
void	perror_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

/**
 * Writes a custom error message to the standard error output (stderr).
 * Used for displaying non-system errors that require attention.
 */
void	print_error(char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

/**
 * Combines the functionality of print_error and then exits the program.
 * Useful for handling errors where the program cannot continue its execution
 * and needs to terminate immediately after displaying an error message.
 */
void	print_error_exit(char *message)
{
	print_error(message);
	exit(EXIT_FAILURE);
}

/**
 * Frees the mlx pointer and matrix of t_point structures,
 * then displays a system error message based on the current errno
 */
void	free_and_perror_exit(t_fdf *fdf, char *message)
{
	free_mlx_ptr(fdf);
	free_point_matrix(fdf->points, fdf->max_y);
	perror_exit(message);
}

/**
 * Frees the mlx pointer and matrix of t_point structures,
 * then displays a custom error message.
 */
void	free_and_error_exit(t_fdf *fdf, char *message)
{
	free_mlx_ptr(fdf);
	free_point_matrix(fdf->points, fdf->max_y);
	print_error_exit(message);
}
