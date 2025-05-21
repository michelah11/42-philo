CC = cc -pthread -g
CFLAGS = -Wall -Wextra -Werror
NAME = philo

SRC_DIR = src

SRCS =	main.c \
		philo_alloc.c \
		data_init.c \
		dinner.c \
		getters_setters.c \
		monitor.c \
		mutex.c \
		parse_input.c \
		synchro_utils.c \
		utils.c \
		write.c \


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all check clean fclean re
