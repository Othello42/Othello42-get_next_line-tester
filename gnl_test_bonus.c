
#include "gnl_test_prototypes.h"

#include <time.h>	//time

static void	check_gnl_bonus_static(void);
static void	check_gnl_bonus_multiple_fd(void);

int	main(void)
{
	signal(SIGSEGV, ft_error);
	check_gnl_bonus_static();
	check_gnl_bonus_multiple_fd();
	printf(C_BOLD"\nLeak check"C_RESET"\n");
	leak_check();
	printf("\n\n");
}

/* ====================================||==================================== *\
||																			  ||
||									 Bonus:									  ||
||								Check for Static							  ||
||																			  ||
\* ============get_next_line===========||==============©Othello============== */

#define FILE_SIZE 64000

static int	count_static_file(int fd);
static int	counter(char *buff);

static void	check_gnl_bonus_static(void)
{
	int	count_gnl;
	int	count_utils;
	int	total;
	int	fd;

	printf(C_BOLD"\nMaximum of 1 static variable"C_RESET"\n");
	fd = open(PROJECT"get_next_line_bonus.c", O_RDONLY);
	if (fd <= 0)
		fd = open(PROJECT"get_next_line.c", O_RDONLY);
	count_gnl = count_static_file(fd);
	fd = open(PROJECT"get_next_line_utils_bonus.c", O_RDONLY);
	if (fd <= 0)
		fd = open(PROJECT"get_next_line_utils.c", O_RDONLY);
	count_utils = count_static_file(fd);
	total = count_gnl + count_utils;
	if (total == 0 || total == 1)
		printf(C_GREEN"[OK]"C_RESET" ");
	else
	{
		printf(C_RED"A total of "C_WHITE"%i"C_RED" static variables have been detected."C_RESET"\n", total);
		printf(C_RED"%-28s"C_WHITE"%i"C_RED" static variables have been detected."C_RESET"\n", "get_next_line_bonus.c", count_gnl); //PATH
		printf(C_RED"%-28s"C_WHITE"%i"C_RED" static variables have been detected."C_RESET"\n", "get_next_line_utils_bonus.c", count_utils); //PATH
	}
}

static int	count_static_file(int fd)
{
	char	*buff;
	int		count;

	buff = calloc(sizeof(char), FILE_SIZE + 1);
	read(fd, buff, FILE_SIZE);
	close(fd);
	count = counter(buff);
	free(buff);
	return (count);
}

/* ====================================||==================================== *\
||									strnstr									  ||
||							 (added from string.h)							  ||
||																			  ||
||					  Implemented for compatability from:					  ||
|/																			  \|
https://opensource.apple.com/source/Libc/Libc-391.2.10/string/FreeBSD/strnstr.c.auto.html
|\																			  /|
\* ============get_next_line===========||==============©Othello============== */

char	*strnstr(const char *s, const char *find, size_t slen)
{
	char c, sc;
	size_t len;

	if ((c = *find++) != '\0')
	{
		len = strlen(find);
		do
		{
			do
			{
				if ((sc = *s++) == '\0' || slen-- < 1)
					return (NULL);
			}
			while (sc != c);
				if (len > slen)
					return (NULL);
		}
		while (strncmp(s, find, len) != 0);
			s--;
	}
	return ((char *)s);
}

static int	counter(char *buff)
{
	int	i;
	int	brackets;
	int	count;

	i = 0;
	brackets = 0;
	count = 0;
	while (i <= FILE_SIZE)
	{
		if (buff[i] == '/' && buff[i + 1] == '/')
		{
			i = i + 2;
			while (buff[i - 1] != '\n' && i <= FILE_SIZE)
				i++;
		}
		if (buff[i] == '/' && buff[i + 1] == '*')
		{
			i = i + 2;
			while (buff[i - 2] != '*' && buff[i - 1] != '/' && i <= FILE_SIZE)
				i++;
		}
		if (buff[i] == '"')
		{
			i++;
			while (buff[i] != '"' && i <= FILE_SIZE)
				i++;
		}
		if (buff[i] == '{')
			brackets++;
		if (buff[i] == '}')
			brackets--;
		if (brackets > 0)
		{
			if (buff[i] == 's')
				if (strnstr(&buff[i], "static ", 7) != NULL)
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

static void	open1_and_close2(int *fd, int i);
static void	error_check(char *gnl, char *comp, int fd, int line);
static void	add_fds_to_array(int *lines, char ***check_array, int *fd);
static void	random_tests(char ***check_array, int *fd, int *lines);

static void	check_gnl_bonus_multiple_fd(void)
{
	int		fd[5];
	int		lines[5] = {0, 0, 0, 0, 0};
	char	***check_array;

	check_array = (char ***)calloc(sizeof(char **), OPEN_MAX);
	printf(C_BOLD"\nMultiple file descriptors, in randomized order."C_RESET"\n");
	open1_and_close2((int *)fd, 1);
	add_fds_to_array((int *)lines, check_array, (int *) fd);
	random_tests(check_array, (int *) fd, (int *) lines);
	open1_and_close2((int *)fd, 2);
	free_check_array(check_array);
}

static void	random_tests(char ***check_array, int *fd, int *lines)
{
	int		i;
	int		lines_checked[5] = {0, 0, 0, 0, 0};
	int		random_check;
	char	*gnl;
	char	*comp;

	i = 0;
	srandom(time(0));
	while (lines_checked[0] + lines_checked[1] + lines_checked[2] + lines_checked[3] + lines_checked[4] < lines[0] + lines[1] + lines[2] + lines[3] + lines[4] + 5)
	{
		random_check = (random() % 5);
		gnl = get_next_line(fd[random_check]);
		comp = check_array[fd[random_check]][lines_checked[random_check]];
		if (lines_checked[random_check] <= lines[random_check])
		{
			error_check(gnl, comp, random_check, lines_checked[random_check]);
			lines_checked[random_check]++;
			i++;
			if ((i) % 12 == 0)
				printf("\n");
		}
		free(gnl);
	}
}

static void	open1_and_close2(int *fd, int i)
{
	if (i == 1)
	{
		fd[0] = open("file/fd_bonus0", O_RDONLY);
		fd[1] = open("file/fd_bonus1", O_RDONLY);
		fd[2] = open("file/fd_bonus2", O_RDONLY);
		fd[3] = open("file/fd_bonus3", O_RDONLY);
		fd[4] = open("file/fd_bonus4", O_RDONLY);
	}
	else if (i == 2)
	{
		close(fd[0]);
		close(fd[1]);
		close(fd[2]);
		close(fd[3]);
		close(fd[4]);
	}
}

static void	add_fds_to_array(int *lines, char ***check_array, int *fd)
{
	lines[0] = create_check_array(check_array, fd[0]);
	lines[1] = create_check_array(check_array, fd[1]);
	lines[2] = create_check_array(check_array, fd[2]);
	lines[3] = create_check_array(check_array, fd[3]);
	lines[4] = create_check_array(check_array, fd[4]);
}

static void	error_check(char *gnl, char *comp, int fd, int line)
{
	int	check;

	check = compare_lines("Bonus", gnl, comp, fd, line);
	if (check == 0)
		printf(C_RED"[NULL]"C_RESET" ");
	if (check == 1)
		printf(C_RED"[KO]"C_RESET" ");
	if (check == 2)
		printf(C_GREEN"[OK]"C_RESET" ");
}
