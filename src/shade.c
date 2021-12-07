/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:58:24 by dsaada            #+#    #+#             */
/*   Updated: 2021/12/07 16:15:19 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	color_shade(t_env *v, unsigned int color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	double			coef;

	if (v->dist > 15)
		coef = 0.25;
	else
		coef = 1.0 / ((v->dist - 0.0) * (4.0 - 1.0) / (15.0 - 0.0) + 1.0);
	r = color >> 16 & 0xff;
	g = color >> 8 & 0xff;
	b = color & 0xff;
	r = ((unsigned int)(r * coef)) << 16;
	g = ((unsigned int)(g * coef)) << 8;
	b = ((unsigned int)(b * coef));
	return (r + g + b);
}

unsigned int	floor_shade(unsigned int color, int px)
{
	unsigned int	c[3];
	double			coef_px;
	int				min_in;

	min_in = HEIGHT / 2;
	coef_px = (px - min_in) * (1.0 - 0.25) / (HEIGHT - min_in) + 0.25;
	c[0] = color >> 16 & 0xff;
	c[1] = color >> 8 & 0xff;
	c[2] = color & 0xff;
	c[0] = ((unsigned int)(c[0] * coef_px)) << 16;
	c[1] = ((unsigned int)(c[1] * coef_px)) << 8;
	c[2] = ((unsigned int)(c[2] * coef_px));
	return (c[0] + c[1] + c[2]);
}

unsigned int	ceiling_shade(unsigned int color, int px)
{
	unsigned int	c[3];
	double			coef_px;
	int				max_in;

	max_in = HEIGHT / 2;
	coef_px = (px - 0.0) * (0.25 - 1) / (max_in - 0.0) + 1.0;
	c[0] = color >> 16 & 0xff;
	c[1] = color >> 8 & 0xff;
	c[2] = color & 0xff;
	c[0] = ((unsigned int)(c[0] * coef_px)) << 16;
	c[1] = ((unsigned int)(c[1] * coef_px)) << 8;
	c[2] = ((unsigned int)(c[2] * coef_px));
	return (c[0] + c[1] + c[2]);
}
