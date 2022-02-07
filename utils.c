#include "h_get_next_line_check.h"
#include "h_colors.h"
#include "h_os_version.h"

#include <fcntl.h> //open
#include <unistd.h> //read, close
#include <stdio.h> //printf
#include <strings.h> //bzero
#include <stdlib.h> //system

char	***create_check_array(void)
{
	static char	***array;

	// if (!array)
		array = (char ***)calloc(sizeof(char **), 256);
	return (array);
}

void	add_to_check_array(char ***array, int fd, int num)
{
	char	buff[0xfff];
	int		max;
	int		i;
	int		line;
	int		c;

	i = 0;
	line = 0;
	c = 0;
	if (!array[num])
		array[num] = (char **)calloc(sizeof(char *), 256);
	max = read(fd, buff, 0xfff);
	while (i < max)
	{
		if (!array[num][line])
			array[num][line] = (char *)calloc(sizeof(char), 0xfff);
		array[num][line][c] = buff[i];
		if (array[num][line][c] == '\n')
		{
			line++;
			c = 0;
		}
		else
			c++;
		i++;
	}
}

void	leak_check(void)
{
	int	should;

	should = 1;
	if (strcmp(OS, "apple") == 0)
		leak_check_apple(should);
	else
		printf(C_DGREY"\t[LK]"C_RESET" ");
}

void	leak_check_apple(int should)
{
	int		fd;
	char	buff[99];

	system("leaks a.out | grep leaked | cut -f2 -d: > temp_leaks_gnl");
	fd = open("temp_leaks_gnl", O_RDONLY);
	read (fd, buff, 99);
	close (fd);
	if (strncmp(buff, " 0 leaks for 0 total leaked bytes.", 34) != 0)
	{
		if (should == 1)
			printf(C_ORANGE"[LK]"C_RESET" ");
		else
			printf(C_RED"[CHEAT]"C_RESET" ");
		fd = errorlog_fd(1);
		dprintf(fd, "get_next_line leaks:\n");
		dprintf(fd, "%s\n\n", buff);
	}
	else
		if (should == 1)
			printf(C_BLUE"[LK]"C_RESET" ");
	system("rm temp_leaks_gnl");
}

int	errorlog_fd(int command)
{
	static int	errorfd = 0;

	if (command == 1)
	{
		if (errorfd == 0)
			errorfd = open("errorlog.txt", O_APPEND | O_RDWR);
	}
	else
		close(errorfd);
	return (errorfd);
}
