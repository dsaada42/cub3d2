/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:07:12 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/28 19:17:34 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_px_col(t_env *v, int cpt)
{
	int	px;

	if (v->first_px > 0)
	{
		px = -1;
		while (++px < v->first_px)
			my_mlx_pixel_put(&v->img, cpt, px, v->ceiling);
	}
	px = v->first_px - 1;
	while (++px < v->last_px)
		my_mlx_pixel_put(&v->img, cpt, px, RED);
	while (px < HEIGHT)
	{
		my_mlx_pixel_put(&v->img, cpt, px, v->floor);
		px++;
	}
}

static int     get_px_color(t_img *img, int y, double preci, int w_height)
{
        char    *px;
        double  step;
        double  x_tex;
        double  y_tex;
        unsigned int     color;

        step = img->height / (double)w_height;
        x_tex = preci * (double)img->width;
        y_tex = (double)y * step;

        px = img->addr + ((int)y_tex * img->line_length + (int)x_tex * (img->bpp / 8));
        color = *(unsigned int *)px;
        return (color);
}

unsigned int	color_shade(t_env *v, unsigned int color)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
	double coef;

	if (v->dist <= 1)
		return (color);
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

void	draw_tex_col(t_env *v, int cpt, char dir)
{
	int	px;
	int	y;
	unsigned int	color;
	t_img	*img;

	if (dir == 'N')
                img = &v->tex[0];
        else if (dir == 'S')
                img = &v->tex[1];
        else if (dir == 'E')
                img = &v->tex[2];
        else
                img = &v->tex[3];
        if (v->first_px > 0)
        {
                px = -1;
                while (++px < v->first_px)
                        my_mlx_pixel_put(&v->img, cpt, px, v->ceiling);
        }
        px = v->first_px - 1;
        y = 0;
        while (++px < v->last_px)
        {
                color = get_px_color(img, y, v->wall_x - (int)v->wall_x, v->w_height);
		color = color_shade(v, color);
                my_mlx_pixel_put(&v->img, cpt, px, color);
                y++;
        }
        while (px < HEIGHT)
        {
                my_mlx_pixel_put(&v->img, cpt, px, v->floor);
                px++;
        }
}
