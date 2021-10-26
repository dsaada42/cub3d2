/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 23:15:44 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/26 15:53:52 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_vars(t_env *v)
{
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, "Cub3d");
	return (0);
}

int	keypress_handler(int keycode, t_env *v)
{
	if (keycode == ESCAPE)
	{
		mlx_destroy_window(v->mlx, v->win);
		free_map(v);
		exit(0);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_env	v;

	init_vars(&v);	
	if (argc != 2)
		return (FAILURE);
	if (parser(argv[1], &v) == FAILURE)
		return (FAILURE);
	if (get_textures(&v) == FAILURE)
		return (FAILURE);
	mlx_hook(v.win, 2, 1L << 0, keypress_handler, &v);
	mlx_loop(v.mlx);
	return (SUCCESS);
}
