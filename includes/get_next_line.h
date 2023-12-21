/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:04:58 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/20 23:36:38 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define BUFFER_SIZE 1024

typedef enum e_line_status
{
	LINE_SUCCESS,
	LINE_EOF_REACHED,
	LINE_ERROR
}					t_line_status;

typedef struct s_gnl_res
{
	char			*line;
	t_line_status	line_status;
}					t_gnl_res;

t_gnl_res			get_next_line(int fd);

#endif
