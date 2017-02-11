/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorice <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 22:42:18 by mmorice           #+#    #+#             */
/*   Updated: 2017/02/10 22:42:26 by mmorice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "./libft/libft.h"

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
	double			**tab;
	double			posy;
	double			posx;
	double			diry;
	double			dirx;
	double			poscamy;
	double			poscamx;
	double			senscamy;
	double			senscamx;
	double			dx;
	double			dy;
	double			xa;
	double			ya;
	int				mapx;
	int				mapy;
	int				stepx;
	int				stepy;
	double			planex;
	double			planey;
	int				malloc;
	int				side;
	int				drawend;
	int				drawstart;
	char			*line;
	int				fd;
	int				mlen;
	int				y;
	int				i;
	char			**argv;
}					t_env;

void				put_pixel(t_env *e, int x, int y);
void				ft_draw(int x, t_env *e);
int					loop_hook(t_env *e);
void				ft_hit(t_env *e);
void				ft_fail(void);
int					mouse_clic(void *param);
int					mouse_mouv(int x, int y, t_env *e);
int					mouse_zoom(int bouton, int x, int y, t_env *e);
int					fct_close(int keycode, t_env *e);
#endif
