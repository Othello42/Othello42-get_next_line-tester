#ifndef H_GET_NEXT_LINE_CHECK_H
# define H_GET_NEXT_LINE_CHECK_H

# include <stdio.h> //printf, NULL

char	*get_next_line(int fd);

/* test_gnl_man.c */
void	check_gnl(char *name, char ***check_array, int num, int lines);
void	check_gnl_bad_fd(void);

/* test_gnl_bon.c */
void	check_gnl_bonus_static(void);
void	check_gnl_bonus_random(void);

/* utils.c */
char	***create_check_array(void);
void	add_to_check_array(char ***array, int fd, int num, int lines);

void	leak_check(void);
void	leak_check_apple(int should);
void	print_test_name(char *name);

int		errorlog_fd(int command);
void	print_error(char *fd, char *next_line, char **check_array, int i);

void	ft_error(int num);

#endif
