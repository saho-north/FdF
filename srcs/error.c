/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:49:04 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/23 20:30:22 by sakitaha         ###   ########.fr       */
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

void	free_point_matrix(t_point **points, size_t max_y)
{
	size_t	i;

	if (points == NULL)
		return ;
	i = 0;
	while (i < max_y)
	{
		free(points[i]);
		i++;
	}
	free(points);
}

/**
 * Safely frees a dynamically allocated splited lines of str.
 */

void	free_split_line(char **split_line)
{
	size_t	i;

	if (split_line == NULL)
		return ;
	i = 0;
	while (split_line[i])
	{
		free(split_line[i]);
		i++;
	}
	free(split_line);
}
