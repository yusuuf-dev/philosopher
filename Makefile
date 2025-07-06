CC = cc
FLAG = -Wall -Wextra -Werror -pthread
SRC = custom_atoi.c ft_clean.c ft_malloc.c ft_putstr_fd.c ft_setup.c monitor.c philo.c routine.c utils.c
OBJ = $(SRC:.c=.o)
NAME = philo

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(FLAG) $(OBJ) -o $(NAME)

all : $(NAME)

clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re