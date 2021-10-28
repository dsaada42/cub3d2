/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 23:30:39 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/28 03:52:31 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_cub_file(char *str, t_list *list)
{
	int		fd;
	char	*buffer;

	if (check_file(str) != SUCCESS)
		return (FAILURE);
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		printf("cannot open given file\n");
		return (FAILURE);
	}
	while (get_next_line(fd, &buffer) != 0)
	{
		if (add_line_list(list, buffer) == MALLOC_ERROR)
		{
			free_list(list);
			return (MALLOC_ERROR);
		}
	}
	free(buffer);
	close(fd);
	return (SUCCESS);
}

int	parse_path(t_line *el, t_env *v)
{
	int		i;
	int		j;
	int		cpt;
	char	*res;

	cpt = 0;
	j = 0;
	i = 2;
	while (el->buffer[i] && is_wspace(el->buffer[i]))
		i++;
	while (el->buffer[i + cpt] && ft_isprint(el->buffer[i + cpt]) == SUCCESS && !(is_wspace(el->buffer[i + cpt])))
		cpt++;
	res = malloc(sizeof(char) * (cpt + 1));
	if (res == NULL)
		return (FAILURE);
	if (add_garb(v->garb, res) == FAILURE)
		return (FAILURE);
	while (j < cpt)
	{
		res[j] = el->buffer[i + j];
		j++;
	}
	res[j] = '\0';
	if (check_tex(res) == FAILURE)
		return (FAILURE);
	if (el->buffer[0] == 'N')
		v->north = res;
	else if (el->buffer[0] == 'S')
		v->south = res;
	else if (el->buffer[0] == 'E')
		v->east = res;
	else
		v->west = res;
	return (SUCCESS);
}

//___________________FONCTION A RECODER POUR LA SECURISER_________________
int	parse_color(t_line *el, t_env *v)
{
	int	i;
	int	res[3];
	int	cpt;

	i = 1;
	cpt = 0;
	while (cpt < 3)
	{
		res[cpt] = 0;
		while (is_wspace(el->buffer[i]))
			i++;
		while (ft_isdigit(el->buffer[i]))
		{
			res[cpt] = res[cpt] * 10 + el->buffer[i] - '0';
			i++;
		}
		if (el->buffer[i] == ',')
			i++;
		else if (cpt < 2)
			return (FAILURE);
		cpt++;
	}
	if (el->buffer[0] == 'C')
		v->ceiling = res[2] + 256 * res[1] + 256 * 256 * res[0];
	else
		v->floor = res[2] + 256 * res[1] + 256 * 256 * res[0];
	return (SUCCESS);
}

int	parse_data(t_list *list, t_env *v)
{
	t_line	*el;
	int		flag;

	flag = 0;
	el = list->start;
	while (el != NULL && flag == 0)
	{
		if (el->size == 0)
			el = list_del_el(list, el);
		else if (is_path(el) != FAILURE)
		{
			if (parse_path(el, v) == FAILURE)
				return (FAILURE);
			el = list_del_el(list, el);
		}
		else if (is_color(el) != FAILURE)
		{
			if (parse_color(el, v) == FAILURE)
				return (FAILURE);
			el = list_del_el(list, el);
		}
		else
			flag = 1;
	}
	if (flag == 1 && check_args(v) == SUCCESS)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	parser(char *param, t_env *v)
{
	t_list	*list;

	list = init_list();
	if (!list)
		return (MALLOC_ERROR);
	init_env(v);
	if (get_cub_file(param, list) == FAILURE)
		return (FAILURE);
	if (parse_data(list, v) == FAILURE)
	{
		printf("Error inside .cub file\n");
		free_list(list);
		free_garb(v->garb);
		return (FAILURE);
	}
	get_map_size(v, list);
	if (parse_map(list, v) == FAILURE)
	{
		printf("Error inside map\n");
		free_list(list);
		free_garb(v->garb);
		free_map(v);
		return (FAILURE);
	}
	free_list(list);
	return (SUCCESS);
}
