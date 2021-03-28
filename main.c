/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:09:39 by yabakhar          #+#    #+#             */
/*   Updated: 2019/11/12 02:30:43 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*ft_slash(char *tmp, char *tmp2, char **splite)
{
	if ((access(tmp2, F_OK) == 0) && (access(tmp2, X_OK) == 0))
	{
		free(tmp);
		ft_delsplite(&splite);
		return (tmp2);
	}
	else if (access(tmp2, F_OK) != 0)
	{
		free(tmp);
		free(tmp2);
	}
	return (NULL);
}

char			*ft_suit1(t_node *list, char *hold)
{
	t_suit		suit;

	suit.i = -1;
	suit.tmp3 = ft_suit(list, "PATH=", 5);
	if (!(suit.tmp3) ||
	((ft_strncmp(hold, "/", 1) == 0) && (access(hold, F_OK) != 0)))
		return (NULL);
	suit.splite = ft_strsplit(suit.tmp3, ':');
	while (suit.splite && suit.splite[++suit.i])
	{
		ft_strdel(&suit.tmp3);
		suit.tmp2 = ft_strjoin(suit.splite[suit.i], "/");
		suit.str = ft_strjoin(suit.tmp2, hold);
		if ((suit.tmp = ft_slash(suit.tmp2, suit.str, suit.splite)))
			return (suit.tmp);
	}
	ft_strdel(&suit.tmp3);
	ft_delsplite(&suit.splite);
	return (NULL);
}

int				builtins(char **holder, char *str)
{
	if (str)
	{
		if (ft_strcmp(str, "echo") == 0 && (ft_echo(holder)))
			return (1);
		else if (ft_strcmp(str, "exit") == 0)
		{
			ft_free_list(ft_getter(0)->env);
			exit(0);
		}
		else if (ft_cd(holder, str) && (ft_strcmp(str, "cd")) == 0)
			return (1);
		else if (ft_env(holder, str) && ft_strcmp(str, "env") == 0)
			return (1);
		else if (ft_unsetenv(holder, str)
				&& ft_strcmp(str, "unsetenv") == 0)
			return (1);
		else if (ft_addenv(holder, str) && ft_strcmp(str, "setenv") == 0)
			return (1);
	}
	return (0);
}

int				ft_suit_main2(t_node *list, char **holder, char **str)
{
	char		*tmp;

	if ((tmp = (ft_suit_d((*str), list))) == NULL)
	{
		ft_putstr4((*str) + 1, ": ", "Undefined variable.", "\n");
		{
			ft_strdel(str);
			return (1);
		}
	}
	else if ((tmp = (ft_suit_d((*str), list))) != NULL)
	{
		if (ft_tools(tmp, str, holder, list))
			return (1);
	}
	return (0);
}

int				main(int ac, char **av, char **env)
{
	t_mini		mini;
	t_node		*list;

	ac = 1;
	av = NULL;
	if (!(*env))
	{
		ft_putstr4("\033[1;33m", " 😡  you didn't give me ", "env\n", "\033[0m");
		exit(1);
	}
	list = ft_stock(env);
	ft_getter(&mini);
	mini.env = list;
	while (1)
	{
		ft_porompte();
		ft_main(list);
	}
	ft_free_list(list);
	return (0);
}
