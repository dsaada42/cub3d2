/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:05:56 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/28 19:17:44 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	f_exist(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd)
	{
		close(fd);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	check_tex_exist(t_env *v)
{
	if (f_exist(v->north) + f_exist(v->south)
		+ f_exist(v->east) + f_exist(v->west) == 4)
		return (SUCCESS);
	else
	{	
		printf("Error importing texture\n");
		return (FAILURE);
	}
}

int	get_textures(t_env *v)
{
	if (check_tex_exist(v) == FAILURE)
		return (FAILURE);
	v->tex[0].img = mlx_xpm_file_to_image(v->mlx, v->north,
			&v->tex[0].width, &v->tex[0].height);
	if (v->tex[0].img == NULL)
		return (FAILURE);
	v->tex[0].addr = mlx_get_data_addr(v->tex[0].img, &v->tex[0].bpp,
			&v->tex[0].line_length, &v->tex[0].endian);
	v->tex[1].img = mlx_xpm_file_to_image(v->mlx, v->south,
			&v->tex[1].width, &v->tex[1].height);
	if (v->tex[1].img == NULL)
		return (FAILURE);
	v->tex[1].addr = mlx_get_data_addr(v->tex[1].img, &v->tex[1].bpp,
			&v->tex[1].line_length, &v->tex[1].endian);
	v->tex[2].img = mlx_xpm_file_to_image(v->mlx, v->east,
			&v->tex[2].width, &v->tex[2].height);
	if (v->tex[2].img == NULL)
		return (FAILURE);
	v->tex[2].addr = mlx_get_data_addr(v->tex[2].img, &v->tex[2].bpp,
			&v->tex[2].line_length, &v->tex[2].endian);
	v->tex[3].img = mlx_xpm_file_to_image(v->mlx, v->west,
			&v->tex[3].width, &v->tex[3].height);
	if (v->tex[3].img == NULL)
		return (FAILURE);
	v->tex[3].addr = mlx_get_data_addr(v->tex[3].img, &v->tex[3].bpp,
			&v->tex[3].line_length, &v->tex[3].endian);
	return (SUCCESS);
}
