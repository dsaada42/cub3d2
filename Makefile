# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsaada <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 00:15:00 by dsaada            #+#    #+#              #
#    Updated: 2021/12/07 15:01:15 by dsaada           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc

MLX_FLAG    = -Lmlx_linux -Imlx_linux -lmlx -lXext -lX11 -lm -lz

MLX_PATH    = ./mlx_linux

CFLAGS = -Wall -Wextra -Werror

DEBUG = -g3 -fsanitize=address

SRC = ./src/main.c\
      ./src/init.c\
      ./src/utils.c\
      ./src/parser.c\
      ./src/parser_utils.c\
      ./src/list.c\
      ./src/garb.c\
      ./src/map.c\
      ./src/map_check.c\
      ./src/get_textures.c\
      ./src/get_next_line.c\
      ./src/get_next_line_utils.c\
      ./src/raycast.c\
      ./src/drawing.c\
	  ./src/shade.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -lmlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ) ./src/cub3d.h ./src/get_next_line.h
	make -C $(MLX_PATH)
	$(CC) $(OBJ) $(MLX_FLAG) -o $(NAME)

all: $(NAME)

clean:
	make -C $(MLX_PATH) clean
	rm -f ./src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all $(NAME) clean fclean re

