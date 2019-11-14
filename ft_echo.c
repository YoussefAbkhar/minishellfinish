/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 15:04:41 by yabakhar          #+#    #+#             */
/*   Updated: 2019/11/10 11:08:02 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_suit_hecho(char **holder)
{
	int		i;
	char	*tmp;

	i = 0;
	while (holder[i])
	{
		tmp = ft_del_quote(holder[i]);
		if (tmp == NULL)
		{
			ft_putendl("Unmatched \".");
			return (1);
		}
		ft_strdel(&tmp);
		i++;
	}
	return (0);
}

int			ft_suit_echo(char **holder, int i, t_node *node)
{
	char	*str;
	char	*tmp;
	int		k;
	int		l;

	l = i + 1;
	while ((*holder)[l] && (ft_isalnum((*holder)[l])))
		l++;
	tmp = ft_strsub((*holder), i + 1, l - i - 1);
	k = l - i - 1;
	*holder += k;
	if ((str = ft_suit(node, tmp, k)) != NULL)
	{
		free(tmp);
		ft_putstr(str + 1);
		ft_strdel(&str);
		return (1);
	}
	else if ((str = ft_suit(node, tmp, k)) == NULL)
	{
		ft_freee(tmp, str);
		return (1);
	}
	free(&tmp);
	return (0);
}

void		ft_echo_1(char *str1, t_node *node)
{
	int		i;

	i = 0;
	if ((str1[i]) == '~')
	{
		ft_putstr(ft_suit(node, "HOME=", 5));
		i++;
	}
	while (str1[i])
	{
		if (str1[i] == '$' && (ft_isalpha(str1[i + 1])))
			ft_suit_echo(&str1, i, node);
		else
			ft_putchar(str1[i]);
		i++;
	}
}

void		ft_echo_2(char *str1, char *str, t_node *node)
{
	if (ft_strncmp(str1, "~", 1) == 0 && ft_isalpha(str1[1]))
	{
		str = ft_strjoin("/Users/", str1 + 1);
		if (access(str, F_OK) == 0)
			ft_putstr(str);
		else
			ft_putstr4("minishell: ", "Unknown user:", " ", str1 + 1);
		ft_strdel(&str);
	}
	else if (ft_strncmp(str1, "~", 1) == 0)
		ft_putstr(ft_suit(node, "HOME=", 5));
	else if ((!ft_strchr(str1, '$')))
	{
		str = ft_del_quote(str1);
		ft_putstr(str);
		free(str);
	}
}

_Bool		ft_echo(char **holder)
{
	t_adenv	env;
	t_node	*node;

	node = ft_getter(0)->env;
	if (ft_suit_hecho(holder))
		return (1);
	env.j = 0;
	while (holder[++env.j])
	{
		env.str1 = ft_del_quote(holder[env.j]);
		if ((ft_strchr(env.str1, '$')))
			ft_echo_1(env.str1, node);
		else if (ft_strncmp(env.str1, "~/", 2) == 0)
		{
			env.str = ft_strjoin(ft_suit(node, "HOME=", 5), holder[1] + 1);
			ft_putstr(ft_cdsuit(holder[1] + 2, node));
			free(env.str);
		}
		else
			ft_echo_2(env.str1, env.str, node);
		write(1, " ", 1);
		free(env.str1);
	}
	write(1, "\n", 1);
	return (1);
}
