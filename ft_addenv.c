/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 17:31:48 by yabakhar          #+#    #+#             */
/*   Updated: 2019/11/08 10:12:30 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_addenv1(char **holder, t_node *list)
{
	if (ft_calc(holder) > 2)
	{
		ft_putendl("setenv: Too many arguments.");
		return (1);
	}
	else if ((holder[1]) && ((ft_isdigit(holder[1][0])) ||
		ft_strcmp(holder[1], "$") == 0))
	{
		ft_putendl("setenv: Variable name must begin with a letter.");
		return (1);
	}
	if ((!(holder[1])))
	{
		while (list)
		{
			ft_putendl(list->content);
			list = list->next;
		}
		return (1);
	}
	return (0);
}

int			check_addenv(char **holder)
{
	int		i;

	if ((holder[1]))
	{
		i = 0;
		while (holder[1][i])
		{
			if (!(ft_isalnum(holder[1][i])))
			{
				ft_putstr("setenv: Variable name must");
				ft_putendl(" contain alphanumeric characters.");
				return (1);
			}
			i++;
		}
	}
	return (0);
}

char		*ft_f_strjoin(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (str);
}

int			ft_addenv2(char **holder, char **str2)
{
	char	str[2];
	t_env	env;

	env.tmp = ft_del_quote(holder[2]);
	env.i = -1;
	*str2 = ft_strdup("");
	env.x = 0;
	str[1] = '\0';
	while (env.tmp && env.tmp[++env.i])
	{
		if (env.tmp[env.i] == '$')
		{
			if (ft_ch_env(&env, str2))
				return (1);
		}
		else
		{
			str[0] = env.tmp[env.i];
			*str2 = ft_f_strjoin(*str2, ft_strdup(str));
		}
	}
	free(env.tmp);
	return (0);
}

int			ft_addenv(char **holder, char *tmp)
{
	t_node	*node;
	t_node	*list;
	t_adenv	add;

	list = ft_getter(0)->env;
	if (((ft_strcmp(tmp, "setenv"))) == 0)
	{
		if (ft_addenv1(holder, list) || (check_addenv(holder)))
			return (1);
		if (holder[1])
			add.str = ft_strjoin(holder[1], "=");
		if (ft_addenv2(holder, &add.str2))
			return (1);
		add.str1 = (add.str2) ? ft_strjoin(add.str, add.str2) : add.str;
		ft_freee(add.str, add.str2);
		if (ft_switch(holder[1], add.str1))
		{
			free(add.str1);
			return (1);
		}
		node = ft_memalloc(sizeof(t_node));
		ft_node_push_back(node, add.str1);
		return (1);
	}
	return (0);
}
