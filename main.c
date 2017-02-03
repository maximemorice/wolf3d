/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorice <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 18:41:17 by mmorice           #+#    #+#             */
/*   Updated: 2017/02/02 17:17:01 by mmorice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmlx/mlx.h"
#include "wolf3d.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int		ft_dda(t_env *c)
{
	int		len;
	double		x;
	double		y;
	int		i;
	float	dx;
	float	dy;

	x = c->posCamX;
	y = c->posCamY;
	dx = c->sensCamX;
	dy = c->sensCamY;

/*
	if ((c->sensCamX - c->posCamX) >= (c->sensCamY - c->posCamY))
		len = c->sensCamX - c->posCamX;
	else
		len = c->sensCamY - c->posCamY;
	dx = (c->sensCamX - c->posCamX) / len;
	dy = (c->sensCamX - c->posCamX) / len;
	x = c->posCamX + 0.5;
	y = c->posCamY + 0.5;
	i = 0;
	ft_putnbr(x);
	ft_putchar(';');
	ft_putnbr(y);
	ft_putchar('\n');
	while (i <= len || c->tab[(int)x][(int)y] == 48)
	{
		x = x + dx;
		y = y + dy;
		i++;
	}
//	ft_putchar('=');
//	ft_putnbr(c->tab[(int)x][(int)y]);*/
	return (1);
}

int		loop_hook(t_env *e)
{
	e->imag = mlx_new_image(e->mlx, e->len, e->height);
	e->data = mlx_get_data_addr(e->imag, &e->bpp, &e->s_line, &e->endian);
	e->img_color = mlx_get_color_value(e->mlx, 0xffffff);
	ft_dda(e);
	mlx_put_image_to_window(e->mlx, e->win, e->imag, 0, 0);
	mlx_destroy_image(e->mlx, e->imag);
	return (0);
}

double		**ft_readmap(char **argv, char *line)
{
	int		fd;
	double		**tmp;
	int		i;
	int		len;
	int		y;

	line = NULL;
	i = 0;
	tmp = NULL;
	fd = open(argv[1], O_RDONLY);
	tmp = (double **)malloc(sizeof(double *) * 24);
	while (get_next_line(fd, &line) > 0)
	{
		y = 0;
		len = ft_strlen(line);
		tmp[i] = (double *)malloc(sizeof(double ) * len);
		while (len > y)
		{
			tmp[i][y] = line[y] - 48;
			y++;
		}
		free(line);
		i++;
	}
	close(fd);
	if (tmp == NULL)
	{
		ft_putstr("wolf3d: no such file: ");
		ft_putendl(argv[1]);
	}
	return (tmp);
}

int		main(int argc, char **argv)
{
	t_env	e;
	char	*line;

	line = NULL;
	if (argc != 2)
	{
		ft_putendl("usage: ./wolf3d mapname.c.");
		return (1);
	}
	e.height = 200;
	e.len = 320;
	e.tab = NULL;
	e.tab = ft_readmap(argv, line);
	if (e.tab == NULL)
		return (0);
	free(line);
	e.posCamX = 22;
	e.posCamY = 12;
	e.sensCamY = 0;
	e.sensCamX = -1;
	e.planeX = 0;
	e.planeY = 0.66;
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, e.len, e.height, "wolf3d");
	mlx_key_hook(e.win, fct_close, &e);
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
