SRCS	= ./src/philo.c ./src/utils.c ./src/routine.c
OBJS	= $(SRCS:.c=.o)
NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -lpthread

all: $(NAME)
	clear

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean re