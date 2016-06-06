# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/16 11:16:50 by rmenegau          #+#    #+#              #
#    Updated: 2016/06/02 19:21:06 by rmenegau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
SRC = main.c \
	  error.c \
	  get_info.c \
	  get_nb_ants.c \
	  get_rooms.c \
	  get_tubes.c \
	  nb_tube_init.c \
	  algo.c
OBJ = $(SRC:.c=.o)
LIBFT = ../libft
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	gcc -o $@ -c $< -I $(LIBFT)/includes #$(FLAGS)

$(NAME): $(OBJ)
	make -C $(LIBFT) re
	gcc -o $(NAME) $^ -L$(LIBFT) -lft

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
