/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:04:58 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/20 00:07:29 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1024

typedef enum e_line_status
{
	READ_ERROR,
	READ_SUCCESS,
	READ_EOF
}					t_line_status;

typedef enum e_read_status
{
	READ_INIT,
	READ_CONTINUE,
	READ_EOF_REACHED,
	READ_ERROR_OCCURED
}					t_read_status;

typedef struct s_gnl_result
{
	char			*line;
	t_line_status	line_status;
}					t_gnl_result;

t_gnl_result		*get_next_line(int fd);

char				*get_next_line(int fd, t_read_status *read_status);

#endif
