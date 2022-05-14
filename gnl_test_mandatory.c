
#include "gnl_test_prototypes.h"

static void	check_gnl(char *name, int tests);
static void	run_gnl_tests(char *name, char ***check_array, int fd, int tests);
static void	check_gnl_bad_fd(void);

/* ====================================||==================================== *\
||																			  ||
||																			  ||
||							  Check get_next_line							  ||
||																			  ||
||																			  ||
\* ============get_next_line===========||==============©Othello============== */

int	main(void)
{
	signal(SIGSEGV, ft_error);
	printf("\t");
	if (TEST == 1)
		check_gnl("file/fd_Basic Input", 12);
	if (TEST == 2)
		check_gnl("file/fd_Line Lengths", 12);
	if (TEST == 3)
		check_gnl("file/fd_Characters", 3);
	if (TEST == 4)
		check_gnl("file/fd_Empty Lines", 12);
	if (TEST == 5)
		check_gnl("file/fd_Null end", 2);
	if (TEST == 6)
		check_gnl("file/fd_Beyond File", 3);
	if (TEST == 7)
		check_gnl("file/fd_Empty File", 1);
	if (TEST == 8)
		check_gnl_bad_fd();
	if (BUFFER_SIZE == 0xfffffff)
		leak_check();
}

static void	check_gnl(char *name, int tests)
{
	int		fd;
	char	***check_array;

	if (BUFFER_SIZE == 42)
		print_name(&name[8]);
	fd = open(name, O_RDONLY);
	if (fd <= 0)
	{
		printf(C_DGREY"[KO]"C_RESET" ");
		return ;
	}
	check_array = (char ***)calloc(sizeof(char **), OPEN_MAX);
	create_check_array(check_array, fd);
	run_gnl_tests(name, check_array, fd, tests);
	close(fd);
	free_check_array(check_array);
}

static void	run_gnl_tests(char *name, char ***check_array, int fd, int tests)
{
	char	*gnl;
	int		line;
	int		check;
	int		ret;

	check = 2;
	line = 0;
	while (line < tests)
	{
		gnl = get_next_line(fd);
		ret = compare_lines(name, gnl, check_array[fd][line], fd, line);
		if (ret == 1)
			check = 1;
		else if (ret == 0 && check != 1)
			check = 0;
		if (gnl != NULL)
			free(gnl);
		line++;
	}
	if (check == 0)
		printf(C_RED"[NULL]"C_RESET" ");
	else if (check == 1)
		printf(C_RED"[KO]"C_RESET" ");
	else if (check == 2)
		printf(C_GREEN"[OK]"C_RESET" ");
}

static void	check_gnl_bad_fd(void)
{
	char	*gnl;
	int		fd_err;

	if (BUFFER_SIZE == 42)
		print_name("Bad fd");
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
