# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 08:32:59 by akhaliss          #+#    #+#              #
#    Updated: 2023/10/08 21:04:22 by abelkace         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = ./libft/libft.a
CC = cc  #-fsanitize=address
CFLAGS = -Wall -Werror -Wextra #-g
SRC =  minishell.c nodes.c lists.c env.c utils.c errors.c syntax.c tokenize.c \
		parse.c finals.c files.c free_.c \
		a_cd.c a_cd_path.c a_echo.c a_env.c a_execv.c a_exit.c a_export_ext.c a_export.c\
	a_file_or_folder.c a_ft_execute.c  a_ftbuiltins.c a_pwd.c a_unset.c a_signals.c \
	a_ft_execute_ext.c
	
NAME = minishell
OBJ_FILES=$(SRC:%.c=%.o)

all: $(NAME) $(LIBFT)

$(LIBFT):
	make -C libft/

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC)  -lreadline -L ~/.brew/opt/readline/lib  $(OBJ_FILES) $(LIBFT) -o $(NAME)


%.o : %.c minishell.h 
	$(CC) $(CFLAGS) -c  $< -o $@

clean:
	rm -f $(OBJ_FILES)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all