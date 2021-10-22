/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:47:00 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/22 20:23:29 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     check_tex(char *str)
{
        int     i;

        i = 0;
        while (str[i])
                i++;
        if (str_equal(&str[i - 4], ".xpm") == FAILURE)
        {
                printf("texture passed is not a .xpm file\n");
                return (FAILURE);
        }
        return (SUCCESS);

}

int     check_file(char *str)
{
        int     i;

        i = 0;
        while (str[i])
                i++;
        if (str_equal(&str[i - 4], ".cub") == FAILURE)
        {
                printf("parameter passed is not a .cub file\n");
                return (FAILURE);
        }
        return (SUCCESS);
}

int     is_path(t_line *el)
{
	if (el->size < 8)
		return (FAILURE);
        if ((el->buffer[0] == 'N' && el->buffer[1] == 'O')
                || (el->buffer[0] == 'S' && el->buffer[1] == 'O')
                || (el->buffer[0] == 'E' && el->buffer[1] == 'A')
                || (el->buffer[0] == 'W' && el->buffer[1] == 'E'))
                return (SUCCESS);
        else
                return (FAILURE);
}

int     is_color(t_line *el)
{
	if (el->size < 7)
		return (FAILURE);
        if (el->buffer[0] == 'C' || el->buffer[0] == 'F')
                return (SUCCESS);
        else
                return (FAILURE);
}

int	check_args(t_env *v)
{
	if (v->north && v->south && v->east && v->west && v->ceiling && v->floor)
		return (SUCCESS);
	else
		return (FAILURE);
}
