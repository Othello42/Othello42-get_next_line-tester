#include "h_get_next_line_check.h"
#include "h_colors.h"

#include <signal.h> //signal

int	main(void)
{
	char	***check_array;
	int		i;

	signal(SIGSEGV, ft_error);
	check_array = create_check_array();
	i = 0;
	if (TEST == 1)
		check_gnl("file/fd_Basic Input", check_array, i++, 12);
	if (TEST == 2)
		check_gnl("file/fd_Line Lengths", check_array, i++, 13);
	if (TEST == 3)
		check_gnl("file/fd_Characters", check_array, i++, 3);
	if (TEST == 4)
		check_gnl("file/fd_Empty Lines", check_array, i++, 12);
	if (TEST == 5)
		check_gnl("file/fd_Alternating", check_array, i++, 9);
	if (TEST == 6)
		check_gnl("file/fd_Null end", check_array, i++, 2);
	if (TEST == 7)
		check_gnl("file/fd_Beyond File", check_array, i++, 3);
	if (TEST == 8)
		check_gnl("file/fd_Empty File", check_array, i++, 1);
	if (TEST == 9)
		check_gnl_bad_fd();
	if (BUFFER_SIZE == 0xffff)
		leak_check();
}
