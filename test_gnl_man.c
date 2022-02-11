#include "h_get_next_line_check.h"
#include "h_colors.h"

#include <string.h> //strcmp
#include <stdlib.h> //free
#include <fcntl.h> //open
#include <unistd.h> //close

/* ====================================||==================================== *\
||																			  ||
||																			  ||
||							  Check get_next_line							  ||
||																			  ||
||																			  ||
\* ============get_next_line===========||==============©Othello============== */

static void	check_the_line(char **check_array, char *fd, int lines);

void	check_gnl(char *name, char ***check_array, int num, int lines)
{
	int		check;

	if (BUFFER_SIZE == 42)
		print_test_name(name);
	else
		printf("\t");
	check = open(name, O_RDONLY);
	add_to_check_array(check_array, check, num, lines);
	close(check);
	check_the_line(check_array[num], name, lines);
}

static void	check_the_line(char **check_array, char *fd, int lines)
{
	char	*next_line;
	int		gnl_fd;
	int		i;
	int		check;

	check = 2;
	gnl_fd = open(fd, O_RDONLY);
	if (gnl_fd <= 0)
	{
		printf(C_DGREY"[KO]"C_RESET" ");
		return ;
	}
	i = 0;
	while (i < lines)
	{
		next_line = get_next_line(gnl_fd);
		if (next_line == NULL || check_array[i] == NULL)
		{
			if (next_line != check_array[i])
			{
				print_error(fd, next_line, check_array, i);
				check = 0;
			}
			break ;
		}
		else if (strcmp(next_line, check_array[i]) != 0)
		{
			print_error(fd, next_line, check_array, i);
			if (check == 2)
				check = 1;
		}
		free(check_array[i]);
		free(next_line);
		i++;
	}
	if (check == 0)
		printf(C_RED"[NULL]"C_RESET" ");
	if (check == 1)
		printf(C_RED"[KO]"C_RESET" ");
	if (check == 2)
		printf(C_GREEN"[OK]"C_RESET" ");
	if (BUFFER_SIZE == 0xfff)
		printf("\t");
	close(gnl_fd);
}

/* ====================================||==================================== *\
||																			  ||
||																			  ||
||								Check Edge Cases							  ||
||																			  ||
||																			  ||
\* ============get_next_line===========||==============©Othello============== */

void	check_gnl_bad_fd(void)
{
	char	*gnl;
	int		fd_err;

	if (BUFFER_SIZE == 42)
		print_test_name("........Bad fd");
	else
		printf("\t");
	gnl = get_next_line(-1);
	if (gnl != NULL)
	{
		printf(C_RED"[NULL]"C_RESET" ");
		fd_err = errorlog_fd(1);
		dprintf(fd_err, "======= TEST FAILED =======\n");
		dprintf(fd_err, "Received bad fd: -1\n");
		dprintf(fd_err, "get_next_line returned %s\n", gnl);
		dprintf(fd_err, "\n\n");
	}
	else
		printf(C_GREEN"[OK]"C_RESET" ");
}
