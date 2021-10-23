/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 19:14:48 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/23 20:27:25 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     check_block(t_env *v, int x, int y)
{
        int     a;

        a = v->map[x][y];
        if (a == '0' || a == '1' || a == ' ')
                return (SUCCESS);
        else if ((a == 'N' || a == 'S' || a == 'E' || a == 'W') && (!(v->posx)))
        {
                init_player(v, x, y, a);
                return (SUCCESS);
        }
        else
                return (FAILURE);
}

int     check_sides(t_env *v)
{
        int     x;
        int     y;

        x = -1;
        while (++x < v->map_width)
        {
                if (v->map[x][0] == '0')
                        return (FAILURE);
                if (v->map[x][v->map_height - 1] == '0' || v->map[x][v->map_height - 1] == '2')
                        return (FAILURE);
        }
        y = -1;
        while (++y < v->map_height)
        {
                if (v->map[0][y] == '0')
                        return (FAILURE);
                if (v->map[v->map_width - 1][y] == '0' || v->map[v->map_width - 1][y] == '2')
                        return (FAILURE);
        }
        return (SUCCESS);
}

int     check_surround(t_env *v, int x, int y)
{
        int     val[8];
        int     i;

        val[0] = v->map[x - 1][y - 1];
        val[1] = v->map[x][y - 1];
        val[2] = v->map[x + 1][y - 1];
        val[3] = v->map[x - 1][y];
        val[4] = v->map[x + 1][y];
        val[5] = v->map[x - 1][y + 1];
        val[6] = v->map[x][y + 1];
        val[7] = v->map[x + 1][y + 1];
        i = -1;
        while (++i < 8)
                if (val[i] != '1' && val[i] != '0')
                      return (FAILURE);
        return (SUCCESS);
}

int     check_closed(t_env *v)
{
        int x;
        int y;


        if (check_sides(v) == FAILURE)
                return (FAILURE);
        y = 0;
        while (++y < v->map_height - 1)
        {
                x = 0;
                while (++x < v->map_width - 1)
                {
                        if (v->map[x][y] == '0')
                                if (check_surround(v, x, y) == FAILURE)
                                        return (FAILURE);
                }
        }
        return (SUCCESS);
}

int     check_map(t_env *v)
{
        int x;
        int y;

        y = -1;
        while (++y < v->map_height)
        {
                x = -1;
                while (++x < v->map_width)
                {
                        if (check_block(v, x, y) == FAILURE)
                        {
                                printf("wrong char inside map\n");
                                return (FAILURE);
                        }
                }
        }
        if (check_closed(v) == FAILURE)
        {
                printf("map error: map not closed\n");
                return (FAILURE);
        }
        return (SUCCESS);
}
