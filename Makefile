# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsaada <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 00:15:00 by dsaada            #+#    #+#              #
#    Updated: 2021/10/22 17:51:26 by dsaada           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc

CFLAGS = -Wall -Wextra -Werror

DEBUG = -g3 -fsanitize=address

SRC = main.c\
      utils.c\
      parser.c\
      parser_utils.c\
      list.c\
      garb.c\
      get_next_line.c\
      get_next_line_utils.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(DEBUG) -lm -lX11 -lXext -Lmlx -o $(NAME)

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all $(NAME) clean fclean re

