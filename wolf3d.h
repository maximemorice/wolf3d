/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorice <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 18:34:07 by mmorice           #+#    #+#             */
/*   Updated: 2017/02/02 17:14:04 by mmorice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "./libft/libft.h"

typedef struct		s_axe
{
	int				dx;
	int				dy;
}					t_axe;

typedef struct		s_env
{
	unsigned int	img_color;
	void			*mlx;
	void			*win;
	void			*imag;
	int				bpp;
	int				s_line;
	char			*data;
	int				endian;
	int				height;
	int				len;
	int				use;
	double				**tab;
	double			posCamY;
	double			posCamX;
	double			sensCamY;
	double			sensCamX;
	double			planeX;
	double			planeY;
	int				hauteur;
}					t_env;

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
}					t_point;

void				put_pixel(t_env *e, int x, int y);
int					loop_hook(t_env *e);
int					mouse_mouv(int x, int y, t_env *e);
int					mouse_zoom(int bouton, int x, int y, t_env *e);
int					fct_close(int keycode, t_env *e);
#endif
