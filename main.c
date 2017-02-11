/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorice <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 22:38:34 by mmorice           #+#    #+#             */
/*   Updated: 2017/02/10 22:42:50 by mmorice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmlx/mlx.h"
#include "wolf3d.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int		ft_dda(t_env *e)
{
	e->xa = sqrt(1 + (e->senscamy * e->senscamy) / (e->senscamx * e->senscamx));
	e->ya = sqrt(1 + (e->senscamx * e->senscamx) / (e->senscamy * e->senscamy));
	e->mapx = (int)e->poscamx;
	e->mapy = (int)e->poscamy;
	if (e->senscamx < 0)
	{
		e->stepx = -1;
		e->dx = (e->poscamx - e->mapx) * e->xa;
	}
	else
	{
		e->stepx = 1;
		e->dx = (e->mapx + 1.0 - e->poscamx) * e->xa;
	}
	if (e->senscamy < 0)
	{
		e->stepy = -1;
		e->dy = (e->poscamy - e->mapy) * e->ya;
	}
	else
	{
		e->stepy = 1;
		e->dy = (e->mapy + 1.0 - e->poscamy) * e->ya;
	}
	return (1);
}

void	ft_height(t_env *e, int x)
{
	double	perpwalldist;
	int		lineheight;

	if (e->side == 0)
		perpwalldist = fabs((e->mapx - e->poscamx + (1 - e->stepx) / 2)
		/ e->senscamx);
	else
		perpwalldist = fabs((e->mapy - e->poscamy + (1 - e->stepy) / 2)
		/ e->senscamy);
	lineheight = abs((int)(e->height / perpwalldist));
	e->drawstart = -lineheight / 2 + e->height / 2;
	if (e->drawstart < 0)
		e->drawstart = 0;
	e->drawend = lineheight / 2 + e->height / 2;
	if (e->drawend >= e->height)
		e->drawend = e->height - 1;
	ft_draw(x, e);
}

int		loop_hook(t_env *e)
{
	double	camerax;
	int		x;

	x = 0;
	e->imag = mlx_new_image(e->mlx, e->len, e->height);
	e->data = mlx_get_data_addr(e->imag, &e->bpp, &e->s_line, &e->endian);
	e->img_color = mlx_get_color_value(e->mlx, 0xffffff);
	while (x < e->len)
	{
		camerax = 2 * x / (double)e->len - 1;
		e->poscamx = e->posx;
		e->poscamy = e->posy;
		e->senscamx = e->dirx + e->planex * camerax;
		e->senscamy = e->diry + e->planey * camerax;
		ft_dda(e);
		ft_hit(e);
		ft_height(e, x);
		x++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->imag, 0, 0);
	mlx_destroy_image(e->mlx, e->imag);
	return (0);
}

double	**ft_readmap(double **t, t_env *e, int i, int y)
{
	e->fd = open(e->argv[1], O_RDONLY);
	while (get_next_line(e->fd, &e->line) > 0 && ++e->malloc)
	{
		e->mlen = ft_strlen(e->line);
		ft_strdel(&e->line);
	}
	(e->malloc == 0) ? ft_fail() : NULL;
	t = (double **)malloc(sizeof(double *) * e->malloc);
	close(e->fd);
	e->fd = open(e->argv[1], O_RDONLY);
	e->line = NULL;
	while (get_next_line(e->fd, &e->line) > 0 && (y = -1))
	{
		t[i] = (double *)malloc(sizeof(double ) * e->mlen + 1);
		while (e->mlen > ++y)
			t[i][y] = e->line[y] - 48;
		t[i][y] = 42;
		(t[i][y - 1] != 1 || t[i++][0] != 1) ? ft_fail() : NULL;
		free(e->line);
	}
	close(e->fd);
	while (y != 0)
		(t[0][--y] != 1 || t[i - 1][y] != 1 || t[2][1] != 0) ? ft_fail() : NULL;
	(t[2][2] != 0 || t[1][2] != 0 || t[1][1] != 0) ? ft_fail() : NULL;
	return (t);
}

int		main(int argc, char **argv)
{
	t_env	e;

	e.line = NULL;
	(argc != 2) ? ft_fail() : NULL;
	e.height = 480;
	e.len = 640;
	e.tab = NULL;
	e.i = 0;
	e.malloc = 0;
	e.argv = argv;
	e.tab = ft_readmap(e.tab, &e, e.i, e.y);
	e.posx = 2;
	e.posy = 2;
	e.diry = 0;
	e.dirx = -1;
	e.planex = 0;
	e.planey = 0.66;
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, e.len, e.height, "wolf3d");
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_hook(e.win, 17, (1l << 17), mouse_clic, 0);
	mlx_hook(e.win, 2, (1l << 0), fct_close, &e);
	mlx_loop(e.mlx);
	return (0);
}
