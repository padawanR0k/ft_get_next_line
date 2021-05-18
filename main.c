#include "get_next_line.h"
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	if (argc == 2)
	{
		char *line = 0;
		int fd = open(argv[1], O_RDONLY);
		int ret;
		// ret = get_next_line(fd, &line);
		// printf("line:\n%s \n", line);
		// ret = get_next_line(fd, &line);
		// printf("line:\n%s \n", line);
		// ret = get_next_line(fd, &line);
		// printf("line:\n%s \n", line);
		while (1)
		{
			ret = get_next_line(fd, &line);
			printf("\n------line------\n%s\n------line------\n\n", line);
			if (ret == 0 || ret == -1)
				break ;
		}
	}
	else if (argc == 1) {
		char *line = 0;
		// int fd = open(argv[1], O_RDONLY);
		int ret;
		while (1)
		{
			ret = get_next_line(0, &line);
			printf("\n------line------\n%s\n------line------\n\n", line);
			if (ret == 0 || ret == -1)
				break ;
		}

	}

	return 0;
}
