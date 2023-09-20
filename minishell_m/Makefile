LIBFT = ./libft/libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -lreadline
SRC =  minishell.c nodes.c lists.c env.c utils.c errors.c syntax.c tokenize.c

NAME = minishell
OBJ_FILES=$(SRC:%.c=%.o)

all: $(NAME) $(LIBFT)

$(LIBFT):
	make -C libft/

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME)


%.o : %.c minishell.h
	$(CC) $(FLAGS) -c  $< -o $@

clean:
	rm -f $(OBJ_FILES)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all