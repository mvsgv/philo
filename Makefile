NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread
SRCS = \
			./srcs/philo.c \
			./srcs/getters_setters.c \
			./srcs/init.c \
			./srcs/parsing.c \
			./srcs/safety.c \
			./srcs/start.c \
			./srcs/status.c \
			./srcs/synchro.c 

OBJ = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@ $(CC) -c $(CFLAGS) -I includes -o $@ $<

$(NAME): $(OBJ)
	@ $(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	@echo "Cleaning"
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re