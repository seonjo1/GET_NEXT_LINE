NAME = get_next_line.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
ARFLGS = ar rusc

SRCS = get_next_line_utils.c get_next_line.c
OBJS = $(SRCS:.c=.o)
SRCS2 = get_next_line_utils_bonus.c get_next_line_bonus.c
OBJS2 = $(SRCS2:.c=.o)

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	$(ARFLGS) $(NAME) $(OBJS)

bonus : $(OBJS2) $(NAME)
	$(ARFLGS) $(NAME) $(OBJS2)
	@touch bonus

%.o : %.c
	$(CC) $(CFLAGS) -I . -c $<

clean :
	rm -f $(OBJS) $(OBJS2) bonus

fclean : 
	make clean
	rm -f $(NAME)

re : 
	make fclean
	make all