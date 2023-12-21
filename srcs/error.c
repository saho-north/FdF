/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:49:04 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/21 19:50:09 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * error.c:
 * error handling (exit the program and display a message when called)
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
