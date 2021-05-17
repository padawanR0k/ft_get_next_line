#include "get_next_line.h"
#include <fcntl.h>

int main()
{
	char *line = 0;
	int fd = open("./get_next_line.h", O_RDONLY);
	int ret;
	ret = get_next_line(fd, &line);
	printf("line: [%s] \n", line);
	// while ((ret = get_next_line(fd, &line)))
	// {
	// 	printf("line: [%s] \n", line);
	// }
	return 0;
}
