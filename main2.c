/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:04:25 by yabakhar          #+#    #+#             */
/*   Updated: 2019/11/15 15:04:49 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (builtins(holder, str))
	{
		ft_strdel(&str);
		return (1);
	}
	ft_strdel(&str);
	return (0);
}

int					ft_tools(char *tmp, char **str, char **holder, t_node *list)
{
	char			*str1;

	if (builtins(holder, tmp))
	{
		ft_strdel(str);
		return (1);
	}
	else if ((str1 = ft_suit1(list, tmp)))
	{
		ft_fork3(holder, list, str1);
		ft_strdel(&str1);
		ft_strdel(str);
		return (1);
	}
	else
	{
		ft_putstr4(tmp, ":", " Command not found.", "\n");
		ft_strdel(str);
		return (1);
	}
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
		if (ft_suit_main(list, holder) || ft_fork1(holder, list))
		{
			ft_delsplite(&holder);
			return (1);
		}
		ft_fork(holder, list);
		ft_delsplite(&holder);
	}
	ft_strclr(buff);
	return (0);
}
