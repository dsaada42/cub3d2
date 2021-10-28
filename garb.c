/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:56:33 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/28 03:55:06 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list_garb	*init_list_garb(void)
{
	t_list_garb	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->start = NULL;
	return (list);
}

int	add_garb(t_list_garb *list, void *ptr)
{
	t_garb	*garb;
	t_garb	*current;

	garb = malloc(sizeof(t_garb));
	if (garb == NULL)
		return (FAILURE);
	garb->ptr = ptr;
	garb->next = NULL;
	if (list->start == NULL)
		list->start = garb;
	else
	{
		current = list->start;
		while (current->next != NULL)
			current = current->next;
		current->next = garb;
	}
	return (SUCCESS);
}

int	free_garb(t_list_garb *list)
{
	t_garb	*current;
	t_garb	*next;

	current = list->start;
	while (current != NULL)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	free(list);
	return (SUCCESS);
}
