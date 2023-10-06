# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 08:32:59 by akhaliss          #+#    #+#              #
#    Updated: 2023/10/05 23:44:41 by akhaliss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = ./libft/libft.a
CC = cc  #-fsanitize=address
CFLAGS = -Wall -Werror -Wextra #-g
SRC =  minishell.c nodes.c lists.c env.c utils.c errors.c syntax.c tokenize.c parse.c finals.c files.c free_.c

NAME = minishell
OBJ_FILES=$(SRC:%.c=%.o)

all: $(NAME) $(LIBFT)

$(LIBFT):
	make -C libft/

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) -lreadline $(OBJ_FILES) $(LIBFT) -o $(NAME)


%.o : %.c minishell.h 
	$(CC) $(CFLAGS) -c  $< -o $@

clean:
	rm -f $(OBJ_FILES)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all