/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:05:13 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/26 16:33:20 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     get_dist(t_env *v)
{
        int     cpt;
        int     wall;

        cpt = -1;
        while (++cpt < WIDTH)
        {
                //Initialisation du rayon
                v->mapx = (int)v->posx;
                v->mapy = (int)v->posy;
                v->camerax = 2 * cpt / (double)WIDTH - 1; //camera X entre -1 et 1
                v->ray_dirx = v->dirx + v->planex * (double)v->camerax;
                v->ray_diry = v->diry + v->planey * (double)v->camerax;
                v->deltax = sqrt(1 + (v->ray_diry * v->ray_diry) / (v->ray_dirx * v->ray_dirx));
                v->deltay = sqrt(1 + (v->ray_dirx * v->ray_dirx) / (v->ray_diry * v->ray_diry));
                if (v->ray_dirx < 0)
                {
                        v->incx = -1;
                        v->sidex = (v->posx - v->mapx) * v->deltax;
                }
                else
                {
                        v->incx = 1;
                        v->sidex = (v->mapx + 1.0 - v->posx) * v->deltax;
                }
                if (v->ray_diry < 0)
                {
                        v->incy = -1;
                        v->sidey = (v->posy - v->mapy) * v->deltay;
                }
                else
                {
                        v->incy = 1;
                        v->sidey = (v->mapy + 1.0 - v->posy) * v->deltay;
                }
                //recherche du point de contact avec le prochain mur
                wall = 0;
                while (!wall)
                {
                        if (v->sidex < v->sidey)
                        {
                                v->sidex += v->deltax;
                                v->mapx += v->incx;
                                v->side = 0;
                        }
                        else
                        {
                                v->sidey += v->deltay;
                                v->mapy += v->incy;
                                v->side = 1;
                        }
                        //coordonnees du mur touche = [mapx][mapy]
                        if (v->map[v->mapx][v->mapy] == '1')
                                wall = 1;
                }
                //calcul de la distance perpendiculaire au plan de camera
                if (v->side == 1) //contact horizontal a la distance v->sidey
                {
                        v->dist = (v->mapy - v->posy + (1 - v->incy) / 2) / v->ray_diry;
                        v->wall_x = v->posx + v->dist * v->ray_dirx;
                }
                else // contact vertical a la distance v->sidex
                {
                        v->dist = (v->mapx - v->posx + (1 - v->incx) / 2) / v->ray_dirx;
                        v->wall_x = v->posy + v->dist * v->ray_diry;
                }
                v->wall_x -= floor((v->wall_x));
                v->w_height = (int)(HEIGHT / v->dist);
                v->first_px = -v->w_height / 2 + HEIGHT / 2;
                if (v->first_px < 0)
                        v->first_px = 0;
                v->last_px = v->w_height / 2 + HEIGHT / 2;
                if (v->last_px >= HEIGHT)
                        v->last_px = HEIGHT - 1;
		draw_px_col(v, cpt);
                //point d intersection avec le mur -> (posx + sideX , posy + sideY)
                /*if (v->side == 0 && v->ray_dirx > 0)       //texture = North
                        draw_px_col2(v, cpt, 'N');
                else if (v->side == 0 && v->ray_dirx <= 0) //texture = South
                        draw_px_col2(v, cpt, 'S');
                else if (v->side == 1 && v->ray_diry > 0)  //texture = East
                        draw_px_col2(v, cpt, 'E');
                else if (v->side == 1 && v->ray_diry <= 0) //texture = West
                        draw_px_col2(v, cpt, 'W');*/
        }
        return (SUCCESS);
}
