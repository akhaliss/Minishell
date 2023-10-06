# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 17:43:47 by akhaliss          #+#    #+#              #
#    Updated: 2023/10/05 22:22:45 by akhaliss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME=libft.a

CC=cc

FLAGS= -Wall -Werror -Wextra #-g

FILES= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_strlen.c \
	   ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
	   ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_atoi.c ft_strdup.c \
	   ft_substr.c ft_strjoin.c ft_split.c ft_itoa.c ft_strmapi.c \
	   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_isprint.c \
	   ft_putnbr_fd.c ft_strtrim.c ft_memcpy.c ft_memmove.c \
	   ft_memcmp.c ft_memchr.c ft_bzero.c ft_calloc.c ft_striteri.c\
	   ft_memset.c ft_strcmp.c ft_strncpy.c ft_strcpy.c\

BONUS_FILES  = ft_lstnew.c ft_lstadd_front.c \
	   			 ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \

OBJ=$(FILES:%.c=%.o)
BBJ=$(BONUS_FILES:%.c=%.o)

all: $(NAME)

%.o : %.c libft.h
	$(CC) $(FLAGS) -c  $< -o $@

$(NAME):	$(OBJ)
		ar rc $(NAME) $(OBJ)
		
bonus:	$(BBJ)
	ar rc $(NAME) $(BBJ)
clean:
	rm -rf $(OBJ) $(BBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY	: all bonus clean fclean re