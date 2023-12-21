/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:45:00 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/21 15:30:23 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_ARGC "Usage: ./fdf <file_name>.fdf"
# define ERR_FILE_EXT "Error: Invalid file extension"
# define ERR_FILE_OPEN "Error: Failed to open file"
# define ERR_READ_LINE "Error: Failed to read line"
# define ERR_MAP "Error: Invalid map"

// Below are not edited yet
# define ERR_MAP_READING "Reading error"
# define ERR_MAP_INIT "Map initialization error"
# define ERR_FDF_INIT "FdF initialization error"
# define ERR_CONV_TO_ARR "Conversion to array"
# define ERR_CAMERA_INIT "Camera initialization error"

void	print_error_exit(char *message);
void	perror_exit(char *message);

#endif
