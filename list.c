/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 00:00:37 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/22 20:23:26 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list  *init_list(void)
{
        t_list *list;

        list = malloc(sizeof(t_list *));
        if (list == NULL)
                return (NULL);
        list->start = NULL;
        return (list);
}

int     add_line_list(t_list *list, char *buffer)
{
        t_line  *new;
        t_line  *current;

        new = malloc(sizeof(t_line));
        if (new == NULL)
                return (MALLOC_ERROR);
        new->buffer = buffer;
        new->size = ft_strlen(buffer);
        new->next = NULL;
        if (list->start == NULL)
                list->start = new;
        else
        {
                current = list->start;
                while (current->next != NULL)
                        current = current->next;
                current->next = new;
        }
        return (SUCCESS);
}

int     free_list(t_list *list)
{
        t_line  *current;
        t_line  *next;

        current = list->start;
        while (current != NULL)
        {
                next = current->next;
		free(current->buffer);
                free(current);
                current = next;
        }
        free(list);
        return (SUCCESS);
}

int     print_list(t_list *list)
{
        t_line  *current;

        if (list == NULL)
                return (-1);
        current = list->start;
        while (current != NULL)
        {
                printf("-> %s :: %d \n", current->buffer, current->size);
                current = current->next;
        }
        return (1);
}

t_line  *list_del_el(t_list *list, t_line *el)
{
        t_line  *current;
        t_line  *prev;

        prev = NULL;
        current = list->start;
        if (current == el)
        {
                list->start = current->next;
                free(current->buffer);
                free(current);
		return (list->start);
        }
        else
        {
                while (current != el)
                {
                        prev = current;
                        current = current->next;
                }
                prev->next = current->next;
                free(current->buffer);
                free(current);
        }
        return (prev->next);
}
