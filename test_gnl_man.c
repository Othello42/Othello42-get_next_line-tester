#include "h_get_next_line_check.h"
#include "h_colors.h"

#include <unistd.h> //close
#include <string.h> //strcmp
#include <stdlib.h> //free
#include <fcntl.h> //open

void	print_error(char *fd, char *next_line, char **check_array, int i)
{
	int	fd_err;

	fd_err = errorlog_fd(1);
	dprintf(fd_err, "======= TEST FAILED =======\n");
	dprintf(fd_err, "File:\t\t\t%s\n", fd);
	dprintf(fd_err, "BUFFER_SIZE:\t%i\n", BUFFER_SIZE);
	dprintf(fd_err, "Line:\t\t\t%i\n\n", i + 1);
	dprintf(fd_err, "expected(%lu):\t\t%s\n", strlen(check_array[i]), check_array[i]);
	dprintf(fd_err, "get_next_line(%lu):\t%s\n", strlen(next_line), next_line);
}

void	check_gnl(char *name, char ***check_array, int num, int lines)
{
	int		check;

	if (BUFFER_SIZE == 42)
		print_test_name(name);
	else
		printf("\t");
	check = open(name, O_RDONLY);
	add_to_check_array(check_array, check, num);
	close(check);
	check_the_line(check_array[num], name, lines);
}

void	check_the_line(char **check_array, char *fd, int lines)
{
	char	*next_line;
	int		gnl_fd;
	int		i;
	int		check;

	check = 2;
	gnl_fd = open(fd, O_RDONLY);
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
