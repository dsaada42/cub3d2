/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 19:57:31 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/23 20:27:29 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     init_player(t_env *v, int x, int y, int a)
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
        printf("player initialised in X = %d, Y = %d\n", x, y);
        return (0);
}

int     init_env(t_env *v)
{
        v->north = NULL;
        v->south = NULL;
        v->east = NULL;
        v->west = NULL;
        v->floor = 0;
        v->ceiling = 0;
	v->posx = 0;
	v->posy = 0;
        v->garb = init_list_garb();
        if (v->garb == NULL)
                return (MALLOC_ERROR);
        return (SUCCESS);
}

