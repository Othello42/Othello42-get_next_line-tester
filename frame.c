#include "h_get_next_line_check.h"
#include "h_colors.h"

#include <fcntl.h>	//open
#include <unistd.h>	//close
#include <stdlib.h>	//system

int	main(void)
{
	int	grep;

	if (BANNER == 0)
	{
		printf("\n\t"C_HEADER" Othello's get_next_line Tester "C_RESET"\n\n");
		printf(C_BOLD"\tLegend"C_RESET"\n");
		printf(C_GREEN"[OK]"C_RESET"\tTest checks out.\n");
		printf(C_RED"[KO]"C_RESET"\tTest has failed on basic functionality.\n");
		printf(C_RED"[NULL]"C_RESET"\tTest incorrectly gave/didn't give NULL.\n");
		printf(C_DGREY"[KO]"C_RESET"\tTest failed to execute.\n");
		printf("\n");
		printf(C_BLUE"[PR"C_ORANGE"OT]"C_RESET"\tFunctions "C_BLUE"is"C_RESET"/"C_ORANGE"isn't"C_RESET" protected.\n");
		printf(C_ORANGE"[L"C_BLUE"K]"C_RESET"\tFunction "C_ORANGE"does"C_RESET"/"C_BLUE"doesn't"C_RESET" contain leaks at some point.\n");
		printf("\n");
		printf("Read "C_BLUE"errorlog.txt"C_RESET" for more information.\n\n");
		close(open("errorlog.txt", O_CREAT | O_TRUNC, 0666));
	}
	if (BANNER == 1)
	{
		printf(C_BOLD"\tN");
		fflush(NULL);
		system("norminette -v | cut -c 2-99");
		printf(C_RESET C_RED);
		fflush(NULL);
		grep = system("norminette "PROJECT" | grep Error");
		if (grep != 0)
			printf(C_GREEN"[OK]"C_RESET"\n");
		printf(C_RESET);
	}
	if (BANNER == 2)
		printf(C_BOLD"\n\tMandatory part"C_RESET"\n");
	if (BANNER == 3)
		printf(C_BOLD"\n\n\tBonus part"C_RESET" ");
	if (BANNER == 4)
		printf(C_BLUE"BUFFER_SIZE"C_BOLD"\t 42\t  1\t 10\t0xffff\t0xfffffff\tLeaks"C_RESET" ");
}
