/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 23:15:44 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/21 00:25:37 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_env	v;

	if (argc != 2)
		return (FAILURE);
	if (parser(argv[1], &v) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
