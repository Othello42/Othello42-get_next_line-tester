char	*get_next_line(int fd);

#include <string.h> //strlen
#include <fcntl.h>  //open
#include <unistd.h> //close
#include <signal.h> //signal
#include <stdlib.h> //exit
#include <stdio.h> //printf

int	main(void)
{
	int	fd;

	fd = open("fd_Basic Input", O_RDONLY);
	printf("%s", get_next_line(fd));
	close(fd);
}
