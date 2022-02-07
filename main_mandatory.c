#include "h_get_next_line_check.h"
#include "h_colors.h"

#include <string.h> //strlen
#include <fcntl.h>  //open
#include <unistd.h> //close
#include <signal.h> //signal
#include <stdlib.h> //exit

void	ft_error(int num)
{
	if(num == 11)
	printf(C_RED"[SIGSEGV]"C_RESET" ");
	exit (0);
}

int	main(void)
{
	char	***check_array;
	int		i;

	signal(SIGSEGV, ft_error);
	check_array = create_check_array();
	i = 0;
	// printf(C_BLUE"BUFFER_SIZE = "C_RESET"%i", BUFFER_SIZE);
	if (TEST == 1)
		check_gnl("fd_Basic Input", check_array, i++, 1); //12
	if (TEST == 2)
		check_gnl("fd_Null end", check_array, i++, 2); //1
	if (TEST == 3)
		check_gnl("fd_Empty Lines", check_array, i++, 12); //12
	if (TEST == 4)
		check_gnl("fd_Line Lengths", check_array, i++, 6);
	if (TEST == 5)
		check_gnl("fd_Beyond File", check_array, i++, 3); //3
	if (TEST == 6)
		check_gnl("fd_Empty File", check_array, i++, 1); //make empty file
	if (BUFFER_SIZE == 0xfff)
	{
	// printf(C_BOLD"\nLeak check:"C_RESET"\t");
	leak_check();
	}
	// printf("\n\n");
}
// int	main(void)
// {
// 	char	*next_line;
// 	int		fd;
// 	int		i;

// 	i = 0;
// 	fd = open ("fd_Basic Input", O_RDONLY);
// 	printf("\n");
// 	while (i < 15)
// 	{
// 		next_line = get_next_line(fd);
// 		printf("%s", next_line);
// 		i++;
// 	}
// 	printf("\n\n");
// }

void	print_test_name(char *name)
{
	int		len;
	char	longest[] = "ft_Line Lengths";
	int		mod;
	int		max;

	mod = 3;
	max = strlen(longest) - mod + 1;
	max = max - (max % 8) + 8;
	len = strlen(name) - mod + 1;
	len = len - (len % 8) + 8;
	len = (max - len) / 8;
	printf(C_BOLD"\n%s:"C_RESET"\t", &name[3]);
	while (len > 0)
	{
		printf("\t");
		len--;
	}
}
