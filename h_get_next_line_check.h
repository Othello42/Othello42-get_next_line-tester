#ifndef H_GET_NEXT_LINE_CHECK_H
# define H_GET_NEXT_LINE_CHECK_H

# include <stdio.h> //printf

char	*get_next_line(int fd);

char	***create_check_array(void);
void	add_to_check_array(char ***array, int fd, int num);

void	print_test_name(char *name);
void	check_gnl(char *name, char ***check_array, int num, int lines);
void	check_the_line(char **check_array, char *fd, int lines);

void	check_gnl_bonus_static(void);
int		count_static_file(char *file);
void	check_gnl_bonus_random(void);
void	create_bonus_check_array(char ***check_array);

void	leak_check(void);
void	leak_check_apple(int should);
int		errorlog_fd(int command);

#endif
