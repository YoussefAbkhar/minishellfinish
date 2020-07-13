/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:49:10 by yabakhar          #+#    #+#             */
/*   Updated: 2020/05/28 06:41:47 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				ft_fork(char **holder, t_node *list)
{
	int				i;
	char			*str;
	char			*str1;
	char			**tab;

	i = 0;
	if (fork() > 0)
		wait(0);
	else
	{
		str = ft_del_quote(holder[0]);
		tab = ft_convert_list_table(list);
		str1 = ft_suit1(list, str);
		i = execve(str1, holder, tab);
		ft_delsplite(&tab);
		if (i == -1)
			ft_putstr4("minisell: ", "command not found: ", holder[0], "\n");
		ft_strdel(&str1);
		ft_strdel(&str);
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

// t_his				*ft_getter_history(t_his *node)
// {
// 	static	t_his	*n;

// 	if (node)
// 		n = node;
// 	return (n);
// }

int					ft_suit_main(t_node *list, char **holder)
{
	char			*str;
	char			*str1;

	str1 = NULL;
	str = ft_del_quote(holder[0]);
	if (ft_suit_hecho(holder))
	{
		ft_strdel(&str);
		return (1);
	}
	else if (str && ft_strncmp(str, "$", 1) == 0)
	{
		if (ft_suit_main2(list, holder, &str))
			return (1);
	}
	if (ft_suit_main1(holder, str))
	{
		ft_strdel(&str);
		return (1);
	}
	ft_strdel(&str);
	return (0);
}

int					ft_main(t_node *list)
{
	int				rd;
	char			buff[BUFF_SIZE + 1];
	char			**holder;

	if ((rd = read(0, buff, BUFF_SIZE)) > 0)
	{
		buff[rd - 1] = '\0';
		holder = ft_strspliti(buff);
		if (ft_suit_main(list, holder))
		{
			ft_delsplite(&holder);
			return (1);
		}
		ft_fork(holder, list);
		ft_delsplite(&holder);
	}
	return (0);
}
