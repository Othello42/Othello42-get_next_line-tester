
#ifndef GNL_TEST_PROTOTYPES_H
# define GNL_TEST_PROTOTYPES_H

# include "h_colors.h"

# include <stdlib.h>	//calloc, random, free, system, exit
# include <signal.h>	//signal
# include <stdio.h>		//printf, FOPEN_MAX
# include <fcntl.h>		//open
# include <unistd.h>	//read, close
# include <string.h>	//strcmp, memcpy, strlen

/* ====================================||==================================== *\
||								 	Function								  ||
\* ============get_next_line===========||==============©Othello============== */

char	*get_next_line(int fd);

/* ====================================||==================================== *\
||								 	 Utils									  ||
\* ============get_next_line===========||==============©Othello============== */

int		create_check_array(char ***check_array, int fd);
void	free_check_array(char ***check_array);
int		compare_lines(char *name, char *gnl, char *comp, int fd, int line);
void	print_name(char *name);
void	print_errors(char *name, char *gnl, char *comp, int fd, int line);
int		errorlog_fd(int command);
void	ft_error(int num);
void	leak_check(void);
void	leak_check_apple(int should);

#endif