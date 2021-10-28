/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:34:40 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/28 02:38:01 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*stack;
	char		*tmp;
	int			rdcpt;

	rdcpt = 0;
	if (fd < 0 || BUFFER_SIZE == 0 || !line)
		return (-1);
	if (!ft_strchr(stack, '\n'))
	{
		while ((rdcpt = read(fd, buffer, BUFFER_SIZE)) > 0)
		{
			if (!(handle_stack(&stack, &tmp, buffer, rdcpt)))
				return (-1);
			if (ft_strchr(stack, '\n'))
				break ;
		}
	}
	return (manage_output(&stack, line, rdcpt));
}

int	handle_stack(char **stack, char **tmp, char *buffer, int rdcpt)
{
	buffer[rdcpt] = '\0';
	if (!(*stack))
	{
		if (!(*stack = ft_strdup(buffer)))
			return (-1);
	}
	else
	{
		if (!(*tmp = ft_strjoin(*stack, buffer)))
		{
			free(*stack);
			return (-1);
		}
		free(*stack);
		if (!(*stack = ft_strdup(*tmp)))
		{
			free(*tmp);
			return (-1);
		}
		free(*tmp);
	}
	return (1);
}

int	manage_output(char **stack, char **line, int rdcpt)
{
	if (rdcpt < 0)
		return (-1);
	if (rdcpt == 0 && *stack == NULL)
	{
		if (!(*line = ft_strdup("")))
			return (-1);
		return (0);
	}
	else
		return (extract_line(stack, line));
}

int	handle_line(char **stack, char **line, char **tmp, int end)
{
	if (!(*line = ft_substr(*stack, 0, end)))
	{
		free(*stack);
		return (-1);
	}
	if (!(*tmp = ft_strdup((*stack) + end + 1)))
	{
		free(*stack);
		return (-1);
	}
	free(*stack);
	*stack = *tmp;
	return (1);
}

int	extract_line(char **stack, char **line)
{
	size_t	end;
	char	*tmp;

	end = 0;
	while ((*stack)[end] != '\n' && (*stack)[end] != '\0')
		end++;
	if ((*stack)[end] == '\n')
	{
		return (handle_line(stack, line, &tmp, end));
	}
	else
	{
		if (!(*line = ft_strdup(*stack)))
		{
			free(*stack);
			return (-1);
		}
		free(*stack);
		*stack = NULL;
		return (0);
	}
}
