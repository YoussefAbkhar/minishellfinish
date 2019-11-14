/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 20:27:42 by yabakhar          #+#    #+#             */
/*   Updated: 2019/11/02 20:32:50 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ft_convert_list_table(t_node *list)
{
	t_node	*tmp;
	char	**tab;
	int		i;

	i = 0;
	if (!((tab = (char**)malloc(sizeof(char *) * (count_list(list) + 1)))))
		return (NULL);
	tmp = list;
	while (tmp)
	{
		tab[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

t_node		*ft_stock(char **env)
{
	t_node	*list;
	t_node	*node;
	int		i;

	if (!(list = ft_memalloc(sizeof(t_node))))
		return (0);
	i = 0;
	node = list;
	while (env[i])
	{
		list->content = ft_strdup(env[i]);
		if (env[i + 1])
			list->next = ft_memalloc(sizeof(t_node));
		else
			list->next = NULL;
		list = list->next;
		i++;
	}
	return (node);
}

int			count_list(t_node *list)
{
	int		i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void		ft_putstr4(char *s, char *s1, char *s2, char *s3)
{
	ft_putstr(s);
	ft_putstr(s1);
	ft_putstr(s2);
	ft_putstr(s3);
}
