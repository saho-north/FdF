#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int			fd;
	t_gnl_res	res;
	char		command[1024];

	fd = open("test_maps/plat.fdf", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	while (1)
	{
		res = get_next_line(fd);
		if (res.line_status == LINE_ERROR)
		{
			fprintf(stderr, "Error reading line.\n");
			break ;
		}
		if (res.line == NULL)
		{
			if (res.line_status == LINE_EOF_REACHED)
			{
				printf("End of file reached.\n");
			}
			break ;
		}
		printf("Read line: %s", res.line);
		free(res.line);
	}
	close(fd);
	sprintf(command, "leaks %d", getpid());
	system(command);
	return (0);
}
