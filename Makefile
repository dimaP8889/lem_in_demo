# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmitriy1 <dmitriy1@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/15 17:02:34 by dpogrebn          #+#    #+#              #
#    Updated: 2018/06/14 01:19:31 by dmitriy1         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
 NAME = ./lem-in
LIBA = libft/libft.a
SRC = src/ft_valid.c src/lem_in.c src/ft_make_links.c src/ft_make_graph.c src/ft_put_len.c \
src/ft_move_ants.c src/ft_make_way.c
HEADER = src/lem_in.h
FLAGS = -Wall -Wextra -Werror
CC = gcc

all: $(NAME)

$(NAME):
	make -C libft/
	$(CC) $(FLAGS) -o $(NAME) $(SRC) $(LIBA)

clean:
	make clean -C libft/

fclean:
	make fclean -C libft/
	rm -rf $(NAME)

re: fclean all
	make re -C libft/