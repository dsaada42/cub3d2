/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:07:12 by dsaada            #+#    #+#             */
/*   Updated: 2021/11/02 18:03:02 by dsaada           ###   ########.fr       */
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
	int	offset;

	offset = (w_height - HEIGHT);
        step = img->height / (double)w_height;
        x_tex = preci * (double)img->width;
        y_tex = (double)y * step;

	if (w_height > HEIGHT)
		y_tex = (double)(y + offset / 2) * step;
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
	double		coef_px;
	int	min_in;

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
	double		coef_px;
	int		max_in;

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
		{
			color = ceiling_shade(v->ceiling, px);
                        my_mlx_pixel_put(&v->img, cpt, px, color);
		}
        }
        px = v->first_px - 1;
        y = 0;
        while (++px < v->last_px)
        {
		if (v->w_height > HEIGHT)
		{
			color = get_px_color(img, y, v->wall_x - (int)v->wall_x, v->w_height);
			
		}
		else
                	color = get_px_color(img, y, v->wall_x - (int)v->wall_x, v->w_height);
		color = color_shade(v, color);
                my_mlx_pixel_put(&v->img, cpt, px, color);
                y++;
        }
        while (px < HEIGHT)
        {	
		color = floor_shade(v->floor, px);
                my_mlx_pixel_put(&v->img, cpt, px, color);
                px++;
        }
}
