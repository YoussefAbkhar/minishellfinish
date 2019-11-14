/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:44:33 by yabakhar          #+#    #+#             */
/*   Updated: 2019/11/10 10:49:38 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_free_list(t_node *head)
{
	t_node	*tmp;

	while (head)
	{
		tmp = head->next;
		ft_strdel(&(head->content));
		ft_memdel((void **)&head);
		head = tmp;
	}
}

void		ft_freee(char *str, char *str2)
{
	ft_strdel(&str);
	ft_strdel(&str2);
}

void		ft_delsplite(char ***splite)
{
	int		i;

	i = 0;
	while ((*splite)[i])
	{
		free((*splite)[i]);
		(*splite)[i] = NULL;
		i++;
	}
	free(*splite);
}

int			ft_ch_env(t_env *env, char **str2)
{
	t_node	*list;

	list = ft_getter(0)->env;
	env->j = 1;
	while (env->tmp[env->i + env->j] && ft_isalnum(env->tmp[env->i + env->j]))
		env->j++;
	env->tmp2 = ft_strsub(env->tmp, env->i, env->j);
	env->var = ft_suit_d(env->tmp2, list);
	free(env->tmp2);
	*str2 = env->var ? ft_f_strjoin(*str2, ft_strdup(env->var)) : *str2;
	if (!(env->var))
	{
		ft_putstr4(env->tmp2 + 1, ": ", "Undefined variable.", "\n");
		free(*str2);
		free(env->tmp);
		return (1);
	}
	env->i += env->j - 1;
	return (0);
}
