# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marmand <marmand@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 12:43:25 by marmand           #+#    #+#              #
#    Updated: 2022/01/27 14:15:11 by marmand          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_FILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
		ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
		ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

BONUS_FILES = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
		ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

.PHONY = all clean fclean re bonus
FLAGS = -Wextra -Werror -Wall
O_FILES = $(C_FILES:.c=.o)
BONUS_O_FILES = $(BONUS_FILES:.c=.o)

NAME = libft.a
CC = gcc

all: $(NAME)

$(NAME): $(O_FILES)
	ar rcs $(NAME) $(O_FILES)

bonus: $(BONUS_O_FILES) $(O_FILES)
	ar rcs $(NAME) $(O_FILES) $(BONUS_O_FILES)

%.o: %.c libft.h
	$(CC) $(FLAGS) -c $<

clean:
	rm -f $(O_FILES) $(BONUS_O_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
	
