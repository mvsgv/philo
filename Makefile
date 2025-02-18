NAME = philo

CC = gcc

FLAGS = -Wall -Werror -Wextra 
SRCS = \
			./srcs/getters_setters \
			./srcs/init \
			./srcs/parsing \
			./srcs/philo \
			./srcs/safety \
			./srcs/start \
			./srcs/status \
			./srcs/synchro 

OBJ = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c $(HEADER)
	@ $(CC) -c $(CFLAGS) -I includes -o $@ $<

$(NAME): $(OBJ)
	@ $(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	@echo "Cleaning"
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re