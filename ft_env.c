/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:04:12 by yabakhar          #+#    #+#             */
/*   Updated: 2019/11/07 18:12:42 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_env(char **holder, char *str)
{
	t_node	*list;

	list = ft_getter(0)->env;
	if (ft_calc(holder) > 0 && ft_strcmp(str, "env") == 0)
	{
		ft_putstr4("env: ", holder[1], ": No such file or directory", "\n");
		return (1);
	}
	else if (str && ft_strcmp(str, "env") == 0)
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

char		*ft_suit_d(char *holder, t_node *node)
{
	char	*str;

	while (node)
	{
		if (ft_strlen(holder + 1) == (size_t)ft_len(node->content))
		{
			if (!(ft_strncmp(node->content, holder + 1, ft_len(node->content))))
			{
				str = ft_sersh(node->content);
				return (str);
			}
		}
		node = node->next;
	}
	return (NULL);
}
