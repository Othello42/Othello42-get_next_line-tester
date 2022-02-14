#include "h_get_next_line_check.h"
#include "h_colors.h"

#include <strings.h> //strcmp, strnstr
#include <fcntl.h> //open
#include <unistd.h> //read, close
#include <stdlib.h> //random
#include <time.h> //time

/* ====================================||==================================== *\
||																			  ||
||																			  ||
||							Bonus: Check for Static							  ||
||																			  ||
||																			  ||
\* ============get_next_line===========||==============©Othello============== */

static int	count_static_file(char *file);
static int	move_to_first_function(char *buff);
static int	counter(char *buff);

void	check_gnl_bonus_static(void)
{
	int	count_gnl;
	int	count_utils;
	int	total;

	printf(C_BOLD"\nMaximum of 1 static variable"C_RESET"\n");
	count_gnl = count_static_file(PROJECT"get_next_line.c"); //PATH
	count_utils = count_static_file(PROJECT"get_next_line_utils.c"); //PATH
	total = count_gnl + count_utils;
	if (total == 0 || total == 1)
		printf(C_GREEN"[OK]"C_RESET" ");
	else
	{
		printf(C_RED"A total of "C_WHITE"%i"C_RED" static variables have been detected."C_RESET"\n", total);
		printf(C_RED"%s\t\t"C_WHITE"%i"C_RED" static variables have been detected."C_RESET"\n", "get_next_line.c", count_gnl); //PATH
		printf(C_RED"%s\t"C_WHITE"%i"C_RED" static variables have been detected."C_RESET"\n", "get_next_line_utils.c", count_utils); //PATH
	}
}

static int	count_static_file(char *file)
{
	char	buff[25000];
	int		fd;
	int		count;
	int		loc;

	fd = open(file, O_RDONLY);
	read(fd, buff, 25000);
	loc = move_to_first_function(buff);
	count = counter(&buff[loc]);
	close(fd);
	return (count);
}

static int	move_to_first_function(char *buff)
{
	int	i;

	i = 0;
	while (buff[i] == '/' && buff[i + 1] == '*')
	{
		while (i <= 25000)
		{
			i++;
			if (buff[i - 1] == '/' && buff[i - 2] == '*')
			{
				if (buff[i] == '\n')
					i++;
				break ;
			}
		}
	}
	while (i < 25000)
	{
		if (strncmp(&buff[i], ")\n{", 3) == 0 || strncmp(&buff[i], "){", 2) == 0)
			break ;
		i++;
	}
	return (i);
}

static int	counter(char *buff)
{
	int	i;
	int	brackets;
	int	count;

	i = 0;
	brackets = 0;
	count = 0;
	while (i < 25000)
	{
		if (buff[i] == '{')
			brackets++;
		if (buff[i] == '}')
			brackets--;
		if (brackets > 0)
		{
			if (buff[i] == 's')
				if (strnstr(&buff[i], "static", 6) != NULL)
					count++;
		}
		i++;
	}
	return (count);
}

/* ====================================||==================================== *\
||																			  ||
||									 Bonus:									  ||
||					  Check for multiple File Descriptors					  ||
||								In random order								  ||
||																			  ||
\* ============get_next_line===========||==============©Othello============== */

static void	create_bonus_check_array(char ***check_array);

void	check_gnl_bonus_random(void)
{
	int		gnl_fd[5];
	int		check_fd[5] = {0, 0, 0, 0, 0};
	char	***check_array;
	int		random_check;
	int		i;
	char	*next_line;
	int		fd_err;
	int	len_ca;
	int	len_gnl;

	check_array = create_check_array();
	create_bonus_check_array(check_array);
	printf(C_BOLD"\nMultiple file descriptors, in randomized order."C_RESET"\n");
	gnl_fd[0] = open("file/fd_bonus0", O_RDONLY);
	gnl_fd[1] = open("file/fd_bonus1", O_RDONLY);
	gnl_fd[2] = open("file/fd_bonus2", O_RDONLY);
	gnl_fd[3] = open("file/fd_bonus3", O_RDONLY);
	gnl_fd[4] = open("file/fd_bonus4", O_RDONLY);
	i = 0;
	srandom(time(0));
	while (i <= 42)
	{
		len_ca = 0;
		len_gnl = 0;
		random_check = (random() % 5);
		next_line = get_next_line(gnl_fd[random_check]);
		if (next_line != check_array[random_check][check_fd[random_check]])
		{
			if (next_line == NULL || check_array[random_check][check_fd[random_check]] == NULL)
			{	
				printf(C_RED"[NULL]"C_RESET" ");
				if (check_array[random_check][check_fd[random_check]] != NULL)
					len_ca = strlen(check_array[random_check][check_fd[random_check]]);
				if (next_line != NULL)
					len_gnl = strlen(next_line);				fd_err = errorlog_fd(1);
				dprintf(fd_err, "======= TEST FAILED =======\n");
				dprintf(fd_err, "File:\t\t\tfd_bonus%i\n", random_check);
				dprintf(fd_err, "Line:\t\t\t%i\n\n", check_fd[random_check] + 1);
				dprintf(fd_err, "expected(%i):\t\t%s\n", len_ca, check_array[random_check][check_fd[random_check]]);
				dprintf(fd_err, "get_next_line(%i):\t%s\n", len_gnl, next_line);
			}
			else if (strcmp(next_line, check_array[random_check][check_fd[random_check]]) != 0)
			{
				printf(C_RED"[KO]"C_RESET" ");
				fd_err = errorlog_fd(1);
				dprintf(fd_err, "======= TEST FAILED =======\n");
				dprintf(fd_err, "File:\t\t\tfd_bonus%i\n", random_check);
				dprintf(fd_err, "Line:\t\t\t%i\n\n", check_fd[random_check] + 1);
				dprintf(fd_err, "expected(%i):\t\t%s\n", len_ca, check_array[random_check][check_fd[random_check]]);
				dprintf(fd_err, "get_next_line(%i):\t%s\n", len_gnl, next_line);
			}
			else
				printf(C_GREEN"[OK]"C_RESET" ");
		}
		else
			printf(C_GREEN"[OK]"C_RESET" ");
		free(next_line);
		check_fd[random_check]++;
		if (check_fd[random_check] > 12)
			break ;
		if ((i + 1) % 12 == 0)
			printf("\n");
		i++;
	}
	close(gnl_fd[0]);
	close(gnl_fd[1]);
	close(gnl_fd[2]);
	close(gnl_fd[3]);
	close(gnl_fd[4]);
}

static void	create_bonus_check_array(char ***check_array)
{
	int	fd[5];
	int	i;

	i = 0;
	fd[0] = open("file/fd_bonus0", O_RDONLY);
	fd[1] = open("file/fd_bonus1", O_RDONLY);
	fd[2] = open("file/fd_bonus2", O_RDONLY);
	fd[3] = open("file/fd_bonus3", O_RDONLY);
	fd[4] = open("file/fd_bonus4", O_RDONLY);
	while (i <= 4)
	{
		add_to_check_array(check_array, fd[i], i, 42); //42 is random hardcoded
		close(fd[i]);
		i++;
	}
}
