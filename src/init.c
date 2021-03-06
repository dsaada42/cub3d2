/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 19:57:31 by dsaada            #+#    #+#             */
/*   Updated: 2021/11/04 14:44:55 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_env *v, int x, int y, int a)
{
	v->posx = x;
	v->posy = y;
	if (a == 'N' || a == 'S')
		v->dirx = 0;
	if (a == 'N')
		v->diry = -1;
	if (a == 'S')
		v->diry = 1;
	if (a == 'E' || a == 'W')
		v->diry = 0;
	if (a == 'E')
		v->dirx = 1;
	if (a == 'W')
		v->dirx = -1;
	v->map[x][y] = '0';
	if (v->dirx == 0)
	{
		v->planex = -0.66 * v->diry;
		v->planey = 0;
	}
	else
	{
		v->planex = 0;
		v->planey = 0.66 * v->dirx;
	}
}

int	init_env(t_env *v)
{
	v->north = NULL;
	v->south = NULL;
	v->east = NULL;
	v->west = NULL;
	v->floor = -1;
	v->ceiling = -1;
	v->posx = 0;
	v->posy = 0;
	v->garb = init_list_garb();
	if (v->garb == NULL)
		return (MALLOC_ERROR);
	return (SUCCESS);
}
