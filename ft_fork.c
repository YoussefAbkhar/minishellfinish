/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:49:10 by yabakhar          #+#    #+#             */
/*   Updated: 2019/11/05 06:04:36 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				ft_fork(char **holder, t_node *list)
{
	char			*str;
	char			*str1;
	char			**tab;

	if (fork() > 0)
		wait(0);
	else
	{
		str = ft_del_quote(holder[0]);
		tab = ft_convert_list_table(list);
		str1 = ft_suit1(list, str);
		execve(str1, holder, tab);
		ft_delsplite(&tab);
		if (str && !str1)
			ft_putstr4("minisell: ", "command not found: ", str, "\n");
		ft_strdel(&str1);
		ft_strdel(&str);
		exit(1);
	}
}

void				ft_fork3(char **holder, t_node *list, char *str1)
{
	int				i;
	char			**tab;

	i = 0;
	if (fork() > 0)
		wait(0);
	else
	{
		tab = ft_convert_list_table(list);
		i = execve(str1, holder, tab);
		ft_delsplite(&tab);
		ft_strdel(&str1);
		exit(1);
	}
}

int					ft_fork1(char **holder, t_node *list)
{
	int				i;

	if (holder[0] && (access(holder[0], F_OK) == 0)
		&& (access(holder[0], X_OK) == 0))
	{
		if (fork() > 0)
			wait(0);
		else
		{
			i = execve(holder[0], holder,
					ft_convert_list_table(list));
			if (i == -1)
				ft_putstr4("minishell: ", "command not found: ",
						holder[0], "\n");
			exit(1);
		}
		return (1);
	}
	return (0);
}

t_mini				*ft_getter(t_mini *node)
{
	static	t_mini	*n;

	if (node)
		n = node;
	return (n);
}
