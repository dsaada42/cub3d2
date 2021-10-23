/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 19:11:24 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/23 20:27:22 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     parse_map(t_list *list, t_env *v)
{
        int     x;
        int     y;
        t_line  *current;

        v->map = (char**)malloc(sizeof(char*) * v->map_width);
        if (v->map == NULL)
                return (FAILURE);
        x = -1;
        while (++x < v->map_width)
        {
                v->map[x] = (char*)malloc(sizeof(char) * v->map_height);
                if (v->map[x] == NULL)
                       return (FAILURE);
                current = list->start;
                y = 0;
                while (current != NULL)
                {
                        if (current->size <= x)
                                v->map[x][y] = ' ';
                        else
                                v->map[x][y] = current->buffer[x];
                        current = current->next;
                        y++;
                }

        }
        return (check_map(v));
}

int     get_map_size(t_env *v, t_list *list)
{
        t_line  *current;

        v->map_width = 0;
        v->map_height = 0;
        current = list->start;
        while(current != NULL)
        {
                v->map_height++;
                if (current->size > v->map_width)
                        v->map_width = current->size;
                current = current->next;
        }
        return (SUCCESS);
}

int     print_full_map(t_env *v)
{
        int x;
        int y;

        y = -1;
        while (++y < v->map_height)
        {
                x = -1;
                while (++x < v->map_width)
                {
                        if (v->map[x][y] == -16)
                                printf("  ");
                        else
                                printf(" %c", v->map[x][y]);
                }
                printf("\n");
        }
        return (0);
}

void	free_map(t_env *v)
{
	int	x;

	x = -1;
	while (++x < v->map_width)
	{
		if (v->map[x])
			free(v->map[x]);
	}
	free(v->map);
}
