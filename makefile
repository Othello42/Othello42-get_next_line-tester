# SHELL := /bin/bash

CC = gcc
CFLAGS = -Wall -Wextra -Werror

#adjust to get_next_line.c's ciredtory location
PROJECT = ../get_next_line/

#adjust if nececary to find your files.
SRC_ALL = $(SRC_FT) $(SRC_BON_FT) $(SRC_HEAD)
SRC =	$(SRC_FT) $(SRC_TEST)
SRC_FT =	$(PROJECT)get_next_line.c\
			$(PROJECT)get_next_line_utils.c
SRC_HEAD =	$(PROJECT)get_next_line.h
SRC_BON =	$(SRC_BON_FT) $(SRC_TEST)
SRC_BON_FT =	$(PROJECT)get_next_line_bonus.c\
				$(PROJECT)get_next_line_utils_bonus.c
SRC_BON_HEAD = $(PROJECT)get_next_line_bonus.h

MN_MAN = main_mandatory.c
MN_BON = main_bonus.c
SRC_TEST = 	utils.c\
			test_gnl_man.c\
			test_gnl_bon.c

all: frame norm man bonus
	@rm test.out;

m: frame man
	@rm test.out;

b: frame bonus
	@rm test.out;

man: headman headbuff
	@TEST=1 ; while [[ $$TEST -le 7 ]] ; do \
		$(CC) $(CFLAGS) $(MN_MAN) $(SRC) -D BUFFER_SIZE=42  -D TEST=$$TEST -D PROJECT='"$(PROJECT)"' -o test.out && ./test.out;\
		$(CC) $(CFLAGS) $(MN_MAN) $(SRC) -D BUFFER_SIZE=1 -D TEST=$$TEST -D PROJECT='"$(PROJECT)"' -o test.out && ./test.out;\
		$(CC) $(CFLAGS) $(MN_MAN) $(SRC) -D BUFFER_SIZE=10 -D TEST=$$TEST -D PROJECT='"$(PROJECT)"' -o test.out && ./test.out;\
		$(CC) $(CFLAGS) $(MN_MAN) $(SRC) -D BUFFER_SIZE=0xffff -D TEST=$$TEST -D PROJECT='"$(PROJECT)"' -o test.out && ./test.out;\
		((TEST = TEST + 1)) ; \
	done

bonus: headbon
ifneq ("$(wildcard $(SRC_BON_FT)) $(SRC_BON_HEAD))","")
	@$(CC) $(CFLAGS) $(MN_BON) $(SRC_BON) -D BUFFER_SIZE=42 -D PROJECT='"$(PROJECT)"' -o test.out && ./test.out;
else
 ifeq ("$(wildcard $(PROJECT)get_next_line_bonus.c)","")
	@echo "\033[38;5;196m\nCould not find \033[38;5;226mget_next_line_bonus.c\033[0m"
 endif
 ifeq ("$(wildcard $(PROJECT)get_next_line_utils_bonus.c)","")
	@echo "\033[38;5;196mCould not find \033[38;5;226mget_next_line_utils_bonus.c\033[0m"
 endif
 ifeq ("$(wildcard $(SRC_BON_HEAD))","")
	@echo "\033[38;5;196mCould not find \033[38;5;226mget_next_line__bonus.h\033[0m"
 endif
	@echo "\033[38;5;196mRunning with functions \033[38;5;226mget_next_line.c\033[38;5;196m and \033[38;5;226mget_next_line_utils.c\033[38;5;196m instead.\033[0m"
	@$(CC) $(CFLAGS) $(MN_BON) $(SRC) -D BUFFER_SIZE=42 -D PROJECT='"$(PROJECT)"' -o test.out && ./test.out;
endif

frame:
	@$(CC) $(CFLAGS) frame.c -D BANNER=0 -D PROJECT='"$(PROJECT)"' -o temp.out && ./temp.out;
	@rm temp.out;

norm: frame
	@$(CC) $(CFLAGS) frame.c -D BANNER=1 -D PROJECT='"$(SRC_ALL)"' -o test.out && ./test.out;
	@rm test.out;

headman: 
	@$(CC) $(CFLAGS) frame.c -D BANNER=2 -D PROJECT='"$(PROJECT)"' -o temp.out && ./temp.out;
	@rm temp.out;

headbon: 
	@$(CC) $(CFLAGS) frame.c -D BANNER=3 -D PROJECT='"$(PROJECT)"' -o temp.out && ./temp.out;
	@rm temp.out;

headbuff:
	@$(CC) $(CFLAGS) frame.c -D BANNER=4 -D PROJECT='"$(PROJECT)"' -o temp.out && ./temp.out;
	@rm temp.out;

# debugg:
# 	$(CC) -g $(CFLAGS) $(MN_MAN) $(SRC) -D BUFFER_SIZE=42 -D TEST=1 -D PROJECT='"$(PROJECT)"' -o test.out && ./test.out;\
