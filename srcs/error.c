/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:49:04 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/21 20:05:48 by sakitaha         ###   ########.fr       */
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
 * Safely frees a dynamically allocated 2D array (matrix) of t_point structures.
 * Essential for preventing memory leaks by ensuring that all allocated memory
 * is properly freed when an error occurs or when the program ends.
 */

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

/**
 * Integrates the functionality of freeing the 2D array and then displaying
 * an error message before exiting. A higher-level function that simplifies
 * error handling by combining resource cleanup and error messaging in one call.
 */

void	free_and_print_error_exit(char *message, t_env *env)
{
	free_point_matrix(env);
	print_error_exit(message);
}
