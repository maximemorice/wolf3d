/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorice <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 01:54:34 by mmorice           #+#    #+#             */
/*   Updated: 2017/01/31 18:27:45 by mmorice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libmlx/mlx.h"

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
