/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:07:12 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/26 16:33:23 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
        char	*dst;

        dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
        *(unsigned int*)dst = color;
}

void    draw_px_col(t_env *v, int cpt)
{
        int     px;

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
