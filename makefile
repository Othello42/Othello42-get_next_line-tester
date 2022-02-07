CC = gcc
CFLAGS = -Wall -Wextra -Werror

PROJECT = ../get_next_line/

SRC = $(SRC_FT) $(SRC_TEST)
SRC_FT = $(PROJECT)get_next_line.c\
			$(PROJECT)get_next_line_utils.c
MN_MAN = main_mandatory.c
MN_BON = main_bonus.c
SRC_TEST = 	utils.c\
			test_gnl_man.c\
			test_gnl_bon.c

SIZE = 10

all: frame norm man bonus

m: frame man

b: frame bonus

man: headman headbuff
	@TEST=1 ; while [[ $$TEST -le 6 ]] ; do \
		$(CC) $(CFLAGS) $(MN_MAN) $(SRC) -D BUFFER_SIZE=42  -D TEST=$$TEST -D PROJECT='"$(PROJECT)"' && ./a.out;\
		$(CC) $(CFLAGS) $(MN_MAN) $(SRC) -D BUFFER_SIZE=1 -D TEST=$$TEST -D PROJECT='"$(PROJECT)"' && ./a.out;\
		$(CC) $(CFLAGS) $(MN_MAN) $(SRC) -D BUFFER_SIZE=10 -D TEST=$$TEST -D PROJECT='"$(PROJECT)"' && ./a.out;\
		$(CC) $(CFLAGS) $(MN_MAN) $(SRC) -D BUFFER_SIZE=0xfff -D TEST=$$TEST -D PROJECT='"$(PROJECT)"' && ./a.out;\
		((TEST = TEST + 1)) ; \
	done

norm: frame
	@$(CC) $(CFLAGS) frame.c -D BANNER=4 -D PROJECT='"$(PROJECT)"' && ./a.out

bonus: headbon
	@$(CC) $(CFLAGS) $(MN_BON) $(SRC) -D BUFFER_SIZE=42 -D PROJECT='"$(PROJECT)"' && ./a.out;\

temp: frame
	gcc temp.c ../get_next_line/get_next_line.c ../get_next_line/get_next_line_utils.c -D BUFFER_SIZE=42 && ./a.out

frame:
	@$(CC) $(CFLAGS) frame.c -D BANNER=0 -D PROJECT='"$(PROJECT)"' && ./a.out

headman: 
	@$(CC) $(CFLAGS) frame.c -D BANNER=1 -D PROJECT='"$(PROJECT)"' && ./a.out

headbon: 
	@$(CC) $(CFLAGS) frame.c -D BANNER=2 -D PROJECT='"$(PROJECT)"' && ./a.out

headbuff:
	@$(CC) $(CFLAGS) frame.c -D BANNER=3 -D PROJECT='"$(PROJECT)"' && ./a.out

quick: frame
	$(CC) $(MN_MAN) $(SRC) -D BUFFER_SIZE=42 -D PROJECT='"$(PROJECT)"' && ./a.out;



test:
	@$(CC) $(SRC) -D BUFFER_SIZE=42 && ./a.out