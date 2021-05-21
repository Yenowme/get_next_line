CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= get_next_line.c get_next_line_utils.c main.c
OBJS	= $(SRCS:.c=.o)
NAME	= a.out

all : $(NAME)

# %.o: %.c
# 	$(CC) -c -o $@ $(CFLAGS) $< main.c -I./

$(NAME) : $(SRCS)
	gcc $(CFLAGS) $(SRCS) -I ./

clean :
	rm -f $(OBJS) $(OBJS_B)

fclean : clean
	rm -rf $(NAME) a.out.dSYM

re :
	make fclean
	make all

test :
	gcc -g $(SRCS) -I ./

.PHONY: clean fclean re all bonus
