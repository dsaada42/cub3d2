# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsaada <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 00:15:00 by dsaada            #+#    #+#              #
#    Updated: 2021/10/26 16:32:55 by dsaada           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc

MLX_FLAG    = -Lmlx_linux -Imlx_linux -lmlx -lXext -lX11 -lm -lz

MLX_PATH    = ./mlx_linux

CFLAGS = -Wall -Wextra -Werror

DEBUG = -g3 -fsanitize=address

SRC = main.c\
      init.c\
      utils.c\
      parser.c\
      parser_utils.c\
      list.c\
      garb.c\
      map.c\
      map_check.c\
      get_textures.c\
      get_next_line.c\
      get_next_line_utils.c\
      raycast.c\
      drawing.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -lmlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	make -C $(MLX_PATH)
	$(CC) $(OBJ) $(MLX_FLAG) -o $(NAME)

all: $(NAME)

clean:
	make -C $(MLX_PATH) clean
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all $(NAME) clean fclean re

