#include "get_next_line.h"
#include <stdio.h>

// int	main(void)
// {
// 	char			*line;
// 	t_read_status	status;

// 	while (1)
// 	{
// 		line = get_next_line(STDIN_FILENO, &status);
// 		if (status == READ_ERROR)
// 		{
// 			fprintf(stderr, "Error reading line.\n");
// 			break ;
// 		}
// 		if (line == NULL)
// 		{
// 			if (status == READ_EOF)
// 			{
// 				printf("End of file reached.\n");
// 			}
// 			break ;
// 		}
// 		printf("Read line: %s", line);
// 		free(line);
// 	}
// 	return (0);
// }

int	main(void)
{
	int				fd;
	char			*line;
	t_read_status	status;
	char			command[1024];

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd, &status);
		if (status == READ_ERROR)
		{
			fprintf(stderr, "Error reading line.\n");
			break ;
		}
		if (line == NULL)
		{
			if (status == READ_EOF)
			{
				printf("End of file reached.\n");
			}
			break ;
		}
		printf("Read line: %s", line);
		free(line);
	}
	close(fd);
	sprintf(command, "leaks %d", getpid());
	system(command);
	return (0);
}
