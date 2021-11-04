/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 23:15:44 by dsaada            #+#    #+#             */
/*   Updated: 2021/11/04 15:40:34 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_vars(t_env *v)
{
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, "Cub3d");
	v->tex[0].img = NULL;
	v->tex[1].img = NULL;
	v->tex[2].img = NULL;
	v->tex[3].img = NULL;
	return (SUCCESS);
}

int	generate_next_frame(t_env *v)
{
	v->img.img = mlx_new_image(v->mlx, WIDTH, HEIGHT);
	v->img.addr = mlx_get_data_addr(v->img.img, &v->img.bpp,
			&v->img.line_length, &v->img.endian);
	raycast(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
        mlx_destroy_image(v->mlx, v->img.img);
	return (SUCCESS);
}

int	keypress_handler(int keycode, t_env *v)
{
	double	old_dirx;
	double	old_planex;

	if (keycode == ESCAPE)
	{
		free_garb(v->garb);
		mlx_destroy_image(v->mlx, v->tex[0].img);
		mlx_destroy_image(v->mlx, v->tex[1].img);
		mlx_destroy_image(v->mlx, v->tex[2].img);
		mlx_destroy_image(v->mlx, v->tex[3].img);
		free_map(v);
		mlx_destroy_window(v->mlx, v->win);
                mlx_destroy_display(v->mlx);
		free(v->mlx);
		exit(0);
	}
	else
	{
		if (keycode == W)
		{
			if (v->map[(int)(v->posx + v->dirx / 5)][(int)(v->posy)] == '0')
				v->posx += v->dirx / 10;
			if (v->map[(int)(v->posx)][(int)(v->posy + v->diry / 5)] == '0')
				v->posy += v->diry / 10;
		}
		else if (keycode == S)
		{
			if (v->map[(int)(v->posx - v->dirx / 5)][(int)(v->posy)] == '0')
				v->posx -= v->dirx / 10;
			if (v->map[(int)(v->posx)][(int)(v->posy - v->diry / 5)] == '0')
				v->posy -= v->diry / 10;
		}
		else if (keycode == D)
		{
			if (v->map[(int)(v->posx - v->diry / 5)][(int)(v->posy)] == '0')
				v->posx += -v->diry / 10;
			if (v->map[(int)(v->posx)][(int)(v->posy + v->dirx / 5)] == '0')
				v->posy += v->dirx / 10;
		}
		else if (keycode == A)
		{
			if (v->map[(int)(v->posx + v->diry / 5)][(int)(v->posy)] == '0')
				v->posx += v->diry / 10;
			if (v->map[(int)(v->posx)][(int)(v->posy - v->dirx / 5)] == '0')
				v->posy += -v->dirx / 10;
		}
		else if (keycode == RIGHT)
		{
			old_dirx = v->dirx;
			v->dirx = v->dirx * cos(ROTSPEED) - v->diry * sin(ROTSPEED);
			v->diry = old_dirx * sin(ROTSPEED) + v->diry * cos(ROTSPEED);
			old_planex = v->planex;
			v->planex = v->planex * cos(ROTSPEED) - v->planey * sin(ROTSPEED);
			v->planey = old_planex * sin(ROTSPEED) + v->planey * cos(ROTSPEED);
		}
		else if (keycode == LEFT)
		{
			old_dirx = v->dirx;
			v->dirx = v->dirx * cos(-ROTSPEED) - v->diry * sin(-ROTSPEED);
			v->diry = old_dirx * sin(-ROTSPEED) + v->diry * cos(-ROTSPEED);
			old_planex = v->planex;
			v->planex = v->planex * cos(-ROTSPEED) - v->planey * sin(-ROTSPEED);
			v->planey = old_planex * sin(-ROTSPEED) + v->planey * cos(-ROTSPEED);
		}
		generate_next_frame(v);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_env	v;

	if (argc != 2)
		return (FAILURE);
	if (parser(argv[1], &v) == FAILURE)
		return (FAILURE);
	init_vars(&v);
	if (get_textures(&v) == FAILURE)
	{
		free_map(&v);
		free_garb(v.garb);
		if (v.tex[0].img)
			mlx_destroy_image(v.mlx, v.tex[0].img);
                if (v.tex[1].img)
			mlx_destroy_image(v.mlx, v.tex[1].img);
                if (v.tex[2].img)
			mlx_destroy_image(v.mlx, v.tex[2].img);
		if (v.tex[3].img)
                	mlx_destroy_image(v.mlx, v.tex[3].img);
		mlx_destroy_window(v.mlx, v.win);
                mlx_destroy_display(v.mlx);
		free(v.mlx);
		return (FAILURE);
	}
	generate_next_frame(&v);
	mlx_hook(v.win, 2, 1L << 0, keypress_handler, &v);
	mlx_loop(v.mlx);
	return (SUCCESS);
}
