#include "h_get_next_line_check.h"
#include "h_colors.h"

#include <string.h> //strlen
#include <fcntl.h>  //open
#include <unistd.h> //close

int	main(void)
{
	char	***check_array;
	int		i;

	check_array = create_check_array();
	i = 0;
	// printf(C_BOLD"\n\n\tBonus part"C_RESET" ");
	check_gnl_bonus_static();
	check_gnl_bonus_random();
	printf(C_BOLD"\nLeak check"C_RESET"\n");
	leak_check();
	printf("\n\n");
}

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
