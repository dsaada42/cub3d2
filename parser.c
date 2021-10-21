/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 23:30:39 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/21 04:56:52 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_valid(str[i]) == SUCCESS)
		i++;
	if (i == 0 || str[i] != '.')
	{
		printf("wrong filename, must contain only alphanumeric and underscore before extension\n");
		return (FAILURE);
	}
	else if (str_equal(&str[i], ".cub") == FAILURE)
	{
		printf("parameter passed is not a .cub file\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	get_cub_file(char *str, t_list *list)
{
	int	fd;
	char	*buffer;

	if (check_file(str) != SUCCESS)
		return (FAILURE);
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		printf("cannot open given file\n");
		return (FAILURE);
	}
	list = init_list();
	if (!list)
		return (MALLOC_ERROR);
	while (get_next_line(fd, &buffer) != 0)
	{
		if (add_line_list(list, buffer) == MALLOC_ERROR)
		{
			free_list(list);
			return (MALLOC_ERROR);
		}
	}
	free(buffer);
	print_list(list);
	close(fd);
	return (SUCCESS);
}

int	is_path(t_line *el)
{
	int	i;

}

int	parse_data(t_list *list, t_env *v)
{
	t_line *el;
	int	flag;

	flag = 0;
	el = list->start;
	while (el != NULL && flag == 0)
	{
		if (el->size == 0)
			el = el->next;
		else if (is_path(el))
		{
			parse_path(el, v);
			el = el->next;
		}	
		else if (is_color(el))
		{
			parse_color(el, v);
			el = el->next;
		}
		else
			flag = 1; //signals start of map/ or error before map	
	}
	return (SUCCESS);
}

int	parser(char *param, t_env *v)
{
	t_list	*list;

	list = NULL;
	if (get_cub_file(param, list) == FAILURE)
		return (FAILURE);
	parse_data(list, v);
	return (SUCCESS);	
}
