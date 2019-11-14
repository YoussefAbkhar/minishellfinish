/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 15:00:49 by yabakhar          #+#    #+#             */
/*   Updated: 2019/11/10 10:51:49 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_cdsuit(char *holder, t_node *list)
{
	char	*str;
	char	*str1;
	char	*tmp;

	str = NULL;
	tmp = ft_suit(list, "HOME=", 5);
	if (tmp)
	{
		str = ft_strjoin(tmp, "/");
		str1 = ft_strcat(str, holder);
		ft_strdel(&tmp);
		ft_strdel(&str);
		return (str1);
	}
	return (NULL);
}

void		ft_cd_suit(char **holder, t_node *list)
{
	char	*tmp;
	DIR		*dir;

	dir = opendir(holder[1]);
	if (holder[1] && access(holder[1], F_OK) == 0 && dir == NULL)
		ft_putstr4(holder[1], " ", "Not a directory.", "\n");
	else if (holder[1] && ft_strcmp(holder[1], "-") == 0)
		check_dash(holder, list);
	else if ((holder[1] && ft_strcmp(holder[1], "~") == 0) || holder[1] == NULL)
	{
		tmp = ft_suit(list, "HOME=", 5);
		if (tmp)
			chdir(tmp);
		else
			ft_putstr4("minishell$: ", holder[0], ": HOME not set", "\n");
		ft_strdel(&tmp);
	}
	else if (access(holder[1], F_OK) == 0)
		chdir(holder[1]);
	else if (access(holder[1], F_OK) == -1)
		ft_putstr4("cd: ", "no such file or directory: ", holder[1], "\n");
	if (dir)
		closedir(dir);
}

int			ft_checkopen(char **holder, t_node *list)
{
	DIR		*dir;
	char	*str1;

	if (holder[1] && ft_strncmp(holder[1], "$", 1) == 0)
	{
		str1 = ft_suit_d(holder[1], list);
		if ((dir = opendir(str1)) != NULL)
		{
			chdir(str1);
			closedir(dir);
		}
		else
			ft_putstr4(holder[1] + 1, ": ", "Undefined variable.", "\n");
		return (1);
	}
	return (0);
}

int			ft_cd_suit_1(char **holder, t_node *list)
{
	char	*str;
	char	*tmp;
	DIR		*dir;

	if (holder[1] && ft_strncmp(holder[1], "~/", 2) == 0)
	{
		tmp = ft_suit(list, "HOME=", 5);
		str = ft_strjoin(tmp, holder[1] + 1);
		if ((dir = opendir(str)) != NULL)
		{
			chdir(ft_cdsuit(holder[1] + 2, list));
			closedir(dir);
		}
		else
			ft_putstr4("cd: ", "no such file or directory: ", str, "\n");
		ft_freee(str, tmp);
		return (0);
	}
	if (ft_checkopen(holder, list))
		return (0);
	return (1);
}

_Bool		ft_cd(char **holder, char *tmp)
{
	t_node	*list;

	list = ft_getter(0)->env;
	if (tmp && ft_strcmp(tmp, "cd") == 0 && ft_calc(holder) > 1)
	{
		ft_putendl("cd: Too many arguments.");
		return (1);
	}
	else if (tmp && (ft_strcmp(tmp, "cd") == 0))
	{
		if (ft_cd_suit_1(holder, list))
			ft_cd_suit(holder, list);
		ft_switch_pwd(list);
		return (1);
	}
	return (0);
}
