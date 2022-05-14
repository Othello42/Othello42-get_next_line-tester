
#include "gnl_test_prototypes.h"

#include "h_os_version.h"

#define FILE_SIZE	64000

/* ====================================||==================================== *\
||																			  ||
||									 Array									  ||
||						To compare against get_next_line					  ||
||																			  ||
\* ============get_next_line===========||==============©Othello============== */

int	create_check_array(char ***check_array, int fd)
{
	char	*buffer;
	int		line;
	int		i;
	int		j;

	buffer = calloc(sizeof(char), FILE_SIZE + 1);
	pread(fd, buffer, FILE_SIZE, 0);
	check_array[fd] = (char **)calloc(sizeof(char *), 256);
	i = 0;
	line = 0;
	while (buffer[i] != '\0')
	{
		check_array[fd][line] = (char *)calloc(sizeof(char), FILE_SIZE);
		j = 0;
		while (i <= FILE_SIZE)
		{
			check_array[fd][line][j] = buffer[i];
			if (buffer[i] == '\n' || buffer[i] == '\0')
				break ;
			j++;
			i++;
		}
		i++;
		if (buffer[i] == '\0')
			break ;
		line++;
	}
	free(buffer);
	return (line + 1);
}

void	free_check_array(char ***check_array)
{
	int	fd;
	int	line;

	fd = 0;
	line = 0;
	while (fd < OPEN_MAX)
	{
		if (check_array[fd])
		{
			while (check_array[fd][line] != 0)
			{

				free(check_array[fd][line]);
				line++;
			}
		}
		if (check_array[fd] != 0)
			free(check_array[fd]);
		fd++;
		line = 0;
	}
	free(check_array);
}

/* ====================================||==================================== *\
||																			  ||
||								Compare strings								  ||
||																			  ||
\* ============get_next_line===========||==============©Othello============== */

int	compare_lines(char *name, char *gnl, char *comp, int fd, int line)
{
	if (gnl == NULL || comp == NULL)
	{
		if (gnl == comp)
			return (2);
		print_errors(name, gnl, comp, fd, line);
		return (0);
	}
	if (strcmp(gnl, comp) != 0)
	{
		print_errors(name, gnl, comp, fd, line);
		return (1);
	}
	return (2);
}

/* ====================================||==================================== *\
||																			  ||
||																			  ||
||							   Print name of test							  ||
||																			  ||
||																			  ||
\* ============get_next_line===========||==============©Othello============== */

void	print_name(char *name)
{
	char	*print_name;

	print_name = (char *)calloc(sizeof(char), 20);
	memcpy(print_name, name, strlen(name));
	print_name[strlen(print_name)] = ':';
	printf(C_BOLD"\n%-14.14s"C_RESET"\t", print_name);
}

/* ====================================||==================================== *\
||																			  ||
||																			  ||
||									Errorlog								  ||
||																			  ||
||																			  ||
\* ============get_next_line===========||==============©Othello============== */

void	print_errors(char *name, char *gnl, char *comp, int fd, int line)
{
	int	fd_err;
	int	len;

	fd_err = errorlog_fd(1);
	dprintf(fd_err, "======= TEST FAILED =======\n");
	dprintf(fd_err, "File(%i):\t\t%s\n", fd, name);
	dprintf(fd_err, "BUFFER_SIZE:\t%i\n", BUFFER_SIZE);
	dprintf(fd_err, "Line:\t\t\t%i\n\n", line + 1);
	len = 0;
	if (comp != NULL)
		len = strlen(comp);
	dprintf(fd_err, "expected(%i):\t\t%s\n", len, comp);
	len = 0;
	if (gnl != NULL)
		len = strlen(gnl);
	dprintf(fd_err, "get_next_line(%i):\t%s\n", len, gnl);
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

/* ====================================||==================================== *\
||																			  ||
||																			  ||
||								Error protection							  ||
||																			  ||
||																			  ||
\* ============get_next_line===========||==============©Othello============== */

void	ft_error(int num)
{
	if (num == 11)
		printf(C_RED"[SIGSEGV]"C_RESET" ");
	exit (0);
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
	if (BUFFER_SIZE == 0xfffffff)
		printf("\t\t");
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

