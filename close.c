/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorice <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 22:41:07 by mmorice           #+#    #+#             */
/*   Updated: 2017/02/10 22:41:38 by mmorice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libmlx/mlx.h"
#include <stdlib.h>
#include <math.h>

void	ft_hit(t_env *e)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (e->dx < e->dy)
		{
			e->dx += e->xa;
			e->mapx += e->stepx;
			e->side = 0;
		}
		else
		{
			e->dy += e->ya;
			e->mapy += e->stepy;
			e->side = 1;
		}
		if (e->tab[e->mapx][e->mapy] > 0)
			hit = 1;
	}
}

void	ft_fail(void)
{
	ft_putstr("wolf3d: error.\n");
	exit(0);
}

int		mouse_clic(void *param)
{
	param = 0;
	exit(1);
	return (0);
}

void	fct_moove(int keycode, t_env *e, double oldplanex, double olddirx)
{
	if (keycode == 123)
	{
		e->dirx = e->dirx * cos(0.1) - e->diry * sin(0.1);
		e->diry = olddirx * sin(0.1) + e->diry * cos(0.1);
		e->planex = e->planex * cos(0.1) - e->planey * sin(0.1);
		e->planey = oldplanex * sin(0.1) + e->planey * cos(0.1);
	}
	if (keycode == 124)
	{
		e->dirx = e->dirx * cos(-0.1) - e->diry * sin(-0.1);
		e->diry = olddirx * sin(-0.1) + e->diry * cos(-0.1);
		e->planex = e->planex * cos(-0.1) - e->planey * sin(-0.1);
		e->planey = oldplanex * sin(-0.1) + e->planey * cos(-0.1);
	}
}

int		fct_close(int keycode, t_env *e)
{
	double px;
	double dx;

	dx = e->dirx;
	px = e->planex;
	(keycode == 123 || keycode == 124) ? fct_moove(keycode, e, px, dx) : NULL;
	if (keycode == 126)
	{
		e->posx += e->dirx * 0.1;
		e->posy += e->diry * 0.1;
		if (e->tab[(int)e->posx][(int)e->posy] != 0)
			keycode = 125;
	}
	if (keycode == 125)
	{
		e->posx -= e->dirx * 0.1;
		e->posy -= e->diry * 0.1;
		if (e->tab[(int)e->posx][(int)e->posy] != 0)
			fct_close(126, e);
	}
	(keycode == 53) ? exit(1) : NULL;
	return (0);
}
