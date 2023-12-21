/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:49:04 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/21 19:56:27 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * error.c:
 * This file contains functions for error handling in the FDF project.
 *
 * Functions in this file include:
 * - perror_exit: Displays a system error message based on the current errno
 *   and exits the program with EXIT_FAILURE status. This function is used
 *   when a system call fails and we need to provide feedback about the error.
 *
 * - print_error: Writes a custom error message to the standard error output
 *   (stderr). This function is used for displaying non-system errors that
 *   require attention.
 *
 * - print_error_exit: Combines the functionality of print_error and then
 *   exits the program. This is useful for handling errors where the program
 *   cannot continue its execution and needs to terminate immediately after
 *   displaying an error message.
 *
 * - free_point_matrix: Safely frees a dynamically allocated 2D array (matrix)
 *   of t_point structures. This function is essential for preventing memory
 *   leaks by ensuring that all allocated memory is properly freed when
 *   an error occurs or when the program ends.
 *
 * - free_and_print_error_exit: Integrates the functionality of freeing the
 *   2D array and then displaying an error message before exiting. This is a
 *   higher-level function that simplifies error handling by combining
 *   resource cleanup and error messaging in one call.
 *
 * Note: These functions are designed to provide a robust error handling
 * mechanism throughout the FDF project, ensuring that resources are properly
 * managed and errors are reported clearly, aiding in debugging and maintaining
 * the program's integrity.
 */

void	perror_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	print_error(char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

void	print_error_exit(char *message)
{
	print_error(message);
	exit(EXIT_FAILURE);
}

void	free_point_matrix(t_env *env)
{
	size_t	i;

	if (env->points == NULL)
		return ;
	i = 0;
	while (i < env->max_y)
	{
		free(env->points[i]);
		i++;
	}
	free(env->points);
}

void	free_and_print_error_exit(char *message, t_env *env)
{
	free_point_matrix(env);
	print_error_exit(message);
}
