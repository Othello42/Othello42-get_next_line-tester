#include "h_get_next_line_check.h"
#include "h_colors.h"

int	main(void)
{
	char	***check_array;
	int		i;

	check_array = create_check_array();
	i = 0;
	check_gnl_bonus_static();
	check_gnl_bonus_random();
	printf(C_BOLD"\nLeak check"C_RESET"\n");
	leak_check();
	printf("\n\n");
}
