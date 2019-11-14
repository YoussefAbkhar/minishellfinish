/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 20:01:34 by yabakhar          #+#    #+#             */
/*   Updated: 2019/11/10 11:00:00 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_node(t_node *node)
{
	if (node)
	{
		ft_strdel(&(node->content));
		free(node);
	}
	return ;
}

int			ft_unsetenv_suit(char **holder, char *str)
{
	if ((!(holder[1])) && (ft_strcmp(str, "unsetenv")) == 0)
	{
		ft_putendl("unsetenv: Too few arguments.");
		return (1);
	}
	return (0);
}

int			ft_unsetenv_suit1(char **holder, char *str)
{
	t_node	*node;
	t_node	*prev;

	node = ft_getter(0)->env;
	if (holder[1] && (ft_strcmp(str, "unsetenv") == 0))
	{
		prev = NULL;
		while (node)
		{
			if (ft_strncmp(node->content, (holder[1]),
					ft_len(node->content)) == 0)
			{
				if (prev)
					prev->next = node->next;
				else
					ft_getter(0)->env = node->next;
				free_node(node);
				break ;
			}
			prev = node;
			node = node->next;
		}
		return (1);
	}
	return (0);
}

int			ft_unsetenv(char **holder, char *str)
{
	if (ft_unsetenv_suit(holder, str))
		return (1);
	if (ft_unsetenv_suit1(holder, str))
		return (1);
	return (0);
}
