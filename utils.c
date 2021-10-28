/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 23:46:42 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/28 03:54:31 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	str_equal(const char *s1, const char *s2)
{
	size_t	i;

	if (ft_strlen(s1) != ft_strlen(s2))
		return (FAILURE);
	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (FAILURE);
		else
			i++;
	}
	return (SUCCESS);
}

int	ft_is_valid(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z') || (c == '_') || (c == '/'))
		return (SUCCESS);
	else
		return (FAILURE);
}

int	is_wspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

int	ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	else
		return (0);
}
