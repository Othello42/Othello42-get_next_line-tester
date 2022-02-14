#include "h_get_next_line_check.h"
#include "h_colors.h"
#include "h_os_version.h"

#include <strings.h> //bzero, strcmp, strlen
#include <fcntl.h> //open
#include <unistd.h> //read, close
#include <stdlib.h> //calloc, system, exit

/* ====================================||==================================== *\
||																			  ||
||								  Create Array								  ||
||						To compare against get_next_line					  ||
||																			  ||
||																			  ||
\* ============get_next_line===========||==============©Othello============== */

char	***create_check_array(void)
{
	static char	***array;

	if (!array)
		array = (char ***)calloc(sizeof(char **), 256);
	return (array);
}

void	add_to_check_array(char ***array, int fd, int num, int lines)
{
	char	buff[0xfffff];
	int		max;
	int		i;
	int		line;
	int		c;

	i = 0;
	line = 0;
	c = 0;
	if (!array[num])
		array[num] = (char **)calloc(sizeof(char *), 256);
	bzero(buff, 0xfffff);
	max = read(fd, buff, 0xfffff);
	while (i < max)
	{
		if (!array[num][line])
			array[num][line] = (char *)calloc(sizeof(char), 0xfffff);
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
	while (line < lines)
	{
		if (!array[num][line])
			array[num][line] = NULL;
		line++;
	}
}

/* ====================================||==================================== *\
||																			  ||
||																			  ||
||								  Leak Checks								  ||
||																			  ||
||																			  ||
\* ============get_next_line===========||==============©Othello============== */

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

	system("leaks test.out | grep leaked | cut -f2 -d: > temp_leaks_gnl");
	fd = open("temp_leaks_gnl", O_RDONLY);
	read (fd, buff, 99);
	close (fd);
	if (strncmp(buff, " 0 leaks for 0 total leaked bytes.", 34) != 0)
	{
		if (should == 1)
			printf(C_ORANGE"\t[LK]"C_RESET" ");
		else
			printf(C_RED"\t[CHEAT]"C_RESET" ");
		fd = errorlog_fd(1);
		dprintf(fd, "get_next_line leaks:\n");
		dprintf(fd, "%s\n\n", buff);
	}
	else
		if (should == 1)
			printf(C_BLUE"\t[LK]"C_RESET" ");
	system("rm temp_leaks_gnl");
}

/* ====================================||==================================== *\
||																			  ||
||																			  ||
||							   Print name of test							  ||
||																			  ||
||																			  ||
\* ============get_next_line===========||==============©Othello============== */

void	print_test_name(char *name)
{
	int		len;
	char	longest[] = "file/fd_Line Lengths";
	int		mod;
	int		max;

	mod = 8;
	max = strlen(longest) - mod + 1;
	max = max - (max % 8) + 8;
	len = strlen(name) - mod + 1;
	len = len - (len % 8) + 8;
	len = (max - len) / 8;
	printf(C_BOLD"\n%s:"C_RESET"\t", &name[8]);
	while (len > 0)
	{
		printf("\t");
		len--;
	}
}

/* ====================================||==================================== *\
||																			  ||
||																			  ||
||									Errorlog								  ||
||																			  ||
||																			  ||
\* ============get_next_line===========||==============©Othello============== */

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

void	print_error(char *fd, char *next_line, char **check_array, int i)
{
	int	fd_err;
	int	len_ca;
	int	len_gnl;

	len_ca = 0;
	len_gnl = 0;
	if (check_array[i] != NULL)
		len_ca = strlen(check_array[i]);
	if (next_line != NULL)
		len_gnl = strlen(next_line);
	fd_err = errorlog_fd(1);

	dprintf(fd_err, "======= TEST FAILED =======\n");
	dprintf(fd_err, "File:\t\t\t%s\n", fd);
	dprintf(fd_err, "BUFFER_SIZE:\t%i\n", BUFFER_SIZE);
	dprintf(fd_err, "Line:\t\t\t%i\n\n", i + 1);
	dprintf(fd_err, "expected(%i):\t\t%s\n", len_ca, check_array[i]);
	dprintf(fd_err, "get_next_line(%i):\t%s\n", len_gnl, next_line);
}

/* ====================================||==================================== *\
||																			  ||
||																			  ||
||								Error protection							  ||
||																			  ||
||																			  ||
\* ============get_next_line===========||==============©Othello============== */

void	ft_error(int num)
{
	if(num == 11)
	printf(C_RED"[SIGSEGV]"C_RESET" ");
	exit (0);
}
