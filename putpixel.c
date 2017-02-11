/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorice <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 22:35:40 by mmorice           #+#    #+#             */
/*   Updated: 2017/02/10 22:39:24 by mmorice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libmlx/mlx.h"

void	ft_put_pixels(t_env *e, int x, int y)
{
	put_pixel(e, x, y++);
	put_pixel(e, x, y++);
	put_pixel(e, x, y++);
	put_pixel(e, x++, y);
	put_pixel(e, x, y--);
	put_pixel(e, x, y--);
	put_pixel(e, x, y--);
	put_pixel(e, x++, y);
	put_pixel(e, x, y++);
	put_pixel(e, x, y++);
	put_pixel(e, x, y++);
	put_pixel(e, x++, y);
	put_pixel(e, x, y--);
	put_pixel(e, x, y--);
	put_pixel(e, x, y--);
	put_pixel(e, x--, y);
}

void	ft_draw2(t_env *e, int x, int y)
{
	int	xbis;
	int	ybis;

	while (y < e->height)
		put_pixel(e, x, y++);
	xbis = 10;
	x = -1;
	e->img_color = mlx_get_color_value(e->mlx, 0x000000);
	while (++x < e->malloc)
	{
		y = 0;
		ybis = 10;
		while (e->tab[x][y] != 42)
		{
			if (e->tab[x][y++] != 0)
				ft_put_pixels(e, xbis, ybis);
			ybis += 4;
		}
		xbis += 4;
	}
	e->img_color = mlx_get_color_value(e->mlx, 0xffffff);
	put_pixel(e, e->poscamx * 4 + 10, e->poscamy * 4 + 10);
	put_pixel(e, e->poscamx * 4 + 10, e->poscamy * 4 + 10 + 1);
	put_pixel(e, e->poscamx * 4 + 10 + 1, e->poscamy * 4 + 10 + 1);
	put_pixel(e, e->poscamx * 4 + 10 + 1, e->poscamy * 4 + 10);
}

void	ft_draw(int x, t_env *e)
{
	int y;

	y = 0;
	e->img_color = mlx_get_color_value(e->mlx, 0x0087ff);
	while (y < e->drawstart)
		put_pixel(e, x, y++);
	e->img_color = mlx_get_color_value(e->mlx, 0x66000a);
	y = e->drawstart;
	while (y < e->drawend)
	{
		e->img_color = mlx_get_color_value(e->mlx, 0x9a6c50);
		(e->stepy > 0 && e->side == 1) ? put_pixel(e, x, y++) : NULL;
		e->img_color = mlx_get_color_value(e->mlx, 0x5f4936);
		(e->stepy <= 0 && e->side == 1) ? put_pixel(e, x, y++) : NULL;
		e->img_color = mlx_get_color_value(e->mlx, 0x845422);
		(e->stepx > 0 && e->side != 1) ? put_pixel(e, x, y++) : NULL;
		e->img_color = mlx_get_color_value(e->mlx, 0x59391d);
		(e->stepx <= 0 && e->side != 1) ? put_pixel(e, x, y++) : NULL;
	}
	e->img_color = mlx_get_color_value(e->mlx, 0x256200);
	y = e->drawend;
	ft_draw2(e, x, y);
}

void	put_pixel(t_env *e, int x, int y)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	if (x > 0 && y > 0 && x < 1000 && y < 1000)
	{
		r = ((e->img_color & 0xFF0000) >> 16);
		g = ((e->img_color & 0xFF00) >> 8);
		b = ((e->img_color & 0xFF));
		e->data[y * e->s_line + x * e->bpp / 8] = b;
		e->data[y * e->s_line + x * e->bpp / 8 + 1] = g;
		e->data[y * e->s_line + x * e->bpp / 8 + 2] = r;
	}
}
