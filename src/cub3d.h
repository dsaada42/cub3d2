/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 23:17:25 by dsaada            #+#    #+#             */
/*   Updated: 2021/12/07 15:00:54 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include "../mlx_linux/mlx.h"
# include <math.h>
# include "get_next_line.h"
# define FAILURE -1
# define MALLOC_ERROR -1
# define SUCCESS 1
# define ROTSPEED 0.1
# define WIDTH 1280
# define HEIGHT 720
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESCAPE 65307
# define RED 0x00FF0000

typedef struct s_garb
{
	void			*ptr;
	struct s_garb	*next;
}	t_garb;

typedef struct s_garb_list
{
	t_garb	*start;
}	t_list_garb;

typedef struct s_line
{
	char			*buffer;
	int				size;
	struct s_line	*next;
}	t_line;

typedef struct s_list
{
	t_line	*start;
}	t_list;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_env
{
	void		*mlx;
	void		*win;
	t_img		img;
	int			mapx;
	int			mapy;
	int			incx;
	int			incy;
	int			floor;		
	int			side;
	int			first_px;
	int			last_px;
	int			ceiling;
	int			w_height;
	int			map_width;
	int			map_height;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	t_img		tex[4];
	char		**map;
	t_list_garb	*garb;
	double		wall_x;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		camerax;
	double		ray_dirx;
	double		ray_diry;
	double		sidex;
	double		sidey;
	double		deltax;
	double		deltay;
	double		dist;
}	t_env;

//init.c
void			init_player(t_env *v, int x, int y, int a);
int				init_env(t_env *v);
//list.c
t_list			*init_list(void);
int				add_line_list(t_list *list, char *buffer);
int				free_list(t_list *list);
t_line			*list_del_el(t_list *list, t_line *el);
//utils.c
int				is_wspace(char c);
int				str_equal(const char *s1, const char *s2);
int				ft_is_valid(char c);
int				ft_isprint(int c);
int				ft_isdigit(int c);
//parser.c
int				parser(char *str, t_env *v);
//parser_utils.c
int				check_args(t_env *v);
int				check_tex(char *str);
int				check_file(char *str);
int				is_path(t_line *el);
int				is_color(t_line *el);
//garb.c
t_list_garb		*init_list_garb(void);
int				add_garb(t_list_garb *list, void *ptr);
int				free_garb(t_list_garb *list);
//map.c
int				parse_map(t_list *list, t_env *v);
int				get_map_size(t_env *v, t_list *list);
void			free_map(t_env *v);
//map_check.c
int				check_block(t_env *v, int x, int y);
int				check_sides(t_env *v);
int				check_surround(t_env *v, int x, int y);
int				check_closed(t_env *v);
int				check_map(t_env *v);
//get_textures.c
int				f_exist(char *str);
int				check_tex_exist(t_env *v);
int				get_textures(t_env *v);
//raycast.c
int				raycast(t_env *v);
//drawing.c
void			draw_px_col(t_env *v, int cpt);
void			draw_tex_col(t_env *v, int cpt, char dir);
int				print_full_map(t_env *v);
int				print_list(t_list *list);
//shade.c
unsigned int	color_shade(t_env *v, unsigned int color);
unsigned int	floor_shade(unsigned int color, int px);
unsigned int	ceiling_shade(unsigned int color, int px);

#endif
