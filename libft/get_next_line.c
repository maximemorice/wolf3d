/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorice <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 16:28:39 by mmorice           #+#    #+#             */
/*   Updated: 2017/02/10 23:40:33 by mmorice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int		resultat(char **line, char *buf_save)
{
	char	*eol;

	eol = ft_strchr(buf_save, '\n');
	if (NULL != eol)
	{
		*eol = '\0';
		*line = ft_strdup(buf_save);
		ft_memmove(buf_save, &eol[1], ft_strlen(&eol[1]) + 1);
		return (1);
	}
	if (0 < ft_strlen(buf_save))
	{
		*line = ft_strdup(buf_save);
		*buf_save = '\0';
		return (1);
	}
	return (0);
}

int		get_next_line(int const fd, char **line)
{
	static char	*buf_save = NULL;
	char		buffer[BUFF_SIZE + 1];
	char		*line_tmp;
	int			ret;

	if (NULL == line || 0 > fd || BUFF_SIZE <= 0)
		return (-1);
	if (NULL == buf_save)
		buf_save = ft_strnew(0);
	while (!ft_strchr(buf_save, '\n'))
	{
		ret = read(fd, buffer, BUFF_SIZE);
		if (-1 == ret)
			return (-1);
		if (0 == ret)
			break ;
		buffer[ret] = '\0';
		line_tmp = ft_strjoin(buf_save, buffer);
		free(buf_save);
		buf_save = line_tmp;
	}
	return (resultat(line, buf_save));
}
