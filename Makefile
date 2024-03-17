CC = cc
CFLAGS =
SRC = minishell.c ft_malloc.c f.c pwd.c cd.c env.c
OBJ = $(SRC:.c=.o)
NAME = minishell
all : $(NAME)
%.o : %.c
	$(CC) -c $< -g -o $@ $(CFLAGS)
$(NAME) : $(OBJ)
	(cd ft_libft && make)
	$(CC) $(SRC) ft_libft/libft.a -lreadline -g -o minishell

clean : 
	(cd ft_libft && make clean)
	rm -f $(OBJ)

fclean : clean
	(cd ft_libft && make fclean)
	rm -f $(NAME)

re : fclean all