CC = cc -pthread -g
CFLAGS = -Wall -Wextra -Werror
NAME = philo

SRCS = \
	alloc.c \
	get_set.c \
	init.c \
	input.c \
	main.c \
	ph_manage.c \
	ph_stat.c \
	sim.c \
	time_err.c \
	wait.c \
	mutex_fct.c \
	thread_fct.c

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

helgrind: CFLAGS += -DDEBUG_TIMEOUT
helgrind: re
		valgrind --tool=helgrind --log-file=helgrind.out --history-level=approx ./$(NAME) 5 180 180 60 2
