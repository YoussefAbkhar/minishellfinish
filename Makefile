# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/16 19:55:13 by yabakhar          #+#    #+#              #
#    Updated: 2019/11/06 19:00:14 by yabakhar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Werror -Wextra 

SRCS = 	cd.c\
		ft_echo.c\
		main.c\
		ft_addenv.c\
		ft_unsetenv.c\
		ft_del_quote.c\
		free.c\
		ft_stock.c\
		suit_cd.c\
		ft_fork.c\
		ft_strspliti.c\
		ft_env.c

LIBFT = libft/libft.a

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):$(OBJ) minishell.h
	@make -C libft
	@gcc $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME)
	@echo "\033[32m$(NAME) created\n\033[0m"

clean:
	@make clean -C libft
	@rm -f $(OBJ)
	@echo "\033[31mFiles .o deleted\n\033[0m"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "\033[31mBinary $(NAME) deleted\n\033[0m"

re: fclean all
