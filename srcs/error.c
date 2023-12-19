/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 05:50:30 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/20 00:17:49 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * error.c:
 * - error handling (exit the program and display a message when called)
 */

void	print_error_exit(char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	perror_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
