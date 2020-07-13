/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 05:23:08 by yabakhar          #+#    #+#             */
/*   Updated: 2020/05/27 01:59:53 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*ft_rest(char *s, char **line)
{
	size_t		i;
	char		*tmp;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s)
	{
		*line = ft_strsub(s, 0, i);
		i = s[i] == '\n' ? i + 1 : i;
		tmp = ft_strdup(s + i);
		free(s);
		return (tmp);
	}
	return (s);
}

void			ft_ft(char *buff, char **holder, int rd)
{
	char *tmp;

	buff[rd] = '\0';
	tmp = ft_strjoin(*holder, buff);
	free(*holder);
	*holder = tmp;
}

int				get_next_line(const int fd, char **line)
{
	char static	*holder[1];
	char		buff[BUFF_SIZE + 1];
	char		*tmp;
	int			rd;

	if ((fd < 0 || line == NULL))
		return (-1);
	if (!holder[fd])
		holder[fd] = ft_strnew(0);
	while ((rd = read(fd, buff, BUFF_SIZE)) > 0)
	{
		ft_ft(buff, &(holder[fd]), rd);
		if (ft_strchr((holder[fd]), '\n'))
			break ;
	}
	if (rd < 0)
		return (-1);
	if (rd == 0 && (line == NULL || holder[fd][0] == '\0'))
		return (0);
	tmp = ft_rest(ft_strdup(holder[fd]), line);
	free(holder[fd]);
	holder[fd] = tmp;
	return (1);
}
