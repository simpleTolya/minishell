# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaunch <hlaunch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 14:43:06 by marmand           #+#    #+#              #
#    Updated: 2022/02/04 00:03:07 by hlaunch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = srcs
OBJ_PATH = obj

PARSE_LIB_CFILES = ft_parse_lexemes.c ft_pobject_append_lexeme.c ft_clear_util.c\
					ft_clear_total_block.c ft_get_path_to_process.c ft_replace_magic_chars.c \
					ft_wildcard_star.c fixing_heredoc.c ft_error_parse.c \
					ft_parse.c ft_transform_procblock2.c ft_transform_procblock.c \
					ft_transform_tocommands.c ft_transform_toprocblocks.c ft_replace_magic.c \

EXEC_CFILES = minishell.c process_commands.c builtins.c \
				signals.c check_iostreams.c if_builtins.c \
				builtin_export.c builtin_cd.c \

readline = srcs/readline/libhistory.a srcs/readline/libreadline.a

NAME = minishell

SRCS = $(addprefix $(SRC_PATH)/parselib/, $(PARSE_LIB_CFILES)) $(addprefix $(SRC_PATH)/execution/, $(EXEC_CFILES))

.PHONY = all clean fclean re bonus
FLAGS = -Wextra -Werror -Wall -MMD
OBJS = $(SRCS:.c=.o)
SRCS_D = $(SRCS:.c=.d)

%.o : %.c
	gcc $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_PATH)/libft.a $(OBJ_PATH)/libstr.a $(OBJS)
	gcc $(FLAGS) $(OBJS) $(OBJ_PATH)/libstr.a $(OBJ_PATH)/libft.a $(readline) -ltermcap -o $(NAME)

$(OBJ_PATH)/libft.a:
	$(MAKE) bonus -C $(SRC_PATH)/libft && cp $(SRC_PATH)/libft/libft.a $(OBJ_PATH)

$(OBJ_PATH)/libstr.a:
	$(MAKE) -C $(SRC_PATH)/libstr && cp $(SRC_PATH)/libstr/libstr.a $(OBJ_PATH)

re: fclean all

clean:
	$(MAKE) fclean -C srcs/libft/
	$(MAKE) fclean -C srcs/libstr/
	rm -rf srcs/get_next_line/*.o
	rm -rf $(OBJS)
	rm -rf $(OBJ_PATH)/*
	rm -rf $(SRCS_D)

fclean: clean
	rm -rf $(NAME)

bonus: all

-include $(SRCS_D)