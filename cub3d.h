/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 23:17:25 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/21 01:33:52 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include "get_next_line.h"
# define FAILURE -1
# define MALLOC_ERROR -1
# define SUCCESS 1
# define ROTSPEED 0.1
# define WIDTH 1920
# define HEIGHT 1080
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESCAPE 65307

typedef struct  s_line
{
        char		*buffer;
        int		size;
        struct s_line	*next;
}               t_line;

typedef struct  s_list
{
        t_line  *start;
}               t_list;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int	bpp;
	int	line_length;
	int	endian;
	int	width;
	int	height;
}		t_img;

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_img	*tex[4];
	int	**map;
}		t_env;

//list.c
t_list  *init_list(void);
int     add_line_list(t_list *list, char *buffer);
int     free_list(t_list *list);
//utils.c
int     str_equal(const char *s1, const char *s2);
int     ft_is_valid(char c);
//parser.c
int	parser(char *str, t_env *v);

int     print_list(t_list *list);

#endif
