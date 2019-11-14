/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 04:51:33 by yabakhar          #+#    #+#             */
/*   Updated: 2019/11/10 10:50:06 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*ft_del_quote(char *s)
{
	int			i;
	int			j;
	int			c1;
	int			c2;

	i = 0;
	c1 = 0;
	c2 = 0;
	if (!s)
		return (NULL);
	j = ft_strlen(s) - 1;
	while (s[i] == '"')
	{
		i++;
		c1++;
	}
	while (s[j] == '"' && j > 0)
	{
		j--;
		c2++;
	}
	if (c1 == c2)
		return (ft_strsub(s, i, (size_t)((j - i + 1) >= 0 ? (j - i + 1) : 0)));
	return (NULL);
}

int				ft_calc(char **hold)
{
	int i;

	i = 0;
	while (hold[i])
		i++;
	if (i > 0)
		i--;
	return (i);
}

void			ft_node_push_back(t_node *content_new, char *str)
{
	t_node		*tmp;

	tmp = ft_getter(0)->env;
	if (!tmp)
	{
		ft_getter(0)->env = content_new;
		content_new->content = str;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = content_new;
		tmp->next->content = str;
	}
}

int				ft_switch(char *holder, char *str)
{
	t_node		*node;
	char		*tmp;

	node = ft_getter(0)->env;
	while (node)
	{
		if (ft_strncmp(node->content, holder, ft_len(node->content)) == 0)
		{
			tmp = node->content;
			node->content = ft_strdup(str);
			ft_strdel(&tmp);
			return (1);
		}
		node = node->next;
	}
	return (0);
}

void			ft_porompte(void)
{
	char		cwd[256];
	char		*cwd1;
	char		*str1;

	if (getcwd(cwd, sizeof(cwd)))
		cwd1 = getcwd(cwd, sizeof(cwd));
	else
	{
		ft_putstr4("\033[1;33m", " 😡 permission denied ", "\n", "\033[0m");
		exit(1);
	}
	if (ft_strcmp(cwd1, "/") == 0)
	{
		ft_putstr4("\033[1;33m", "😜 ", cwd1, " $> \033[0m");
		return ;
	}
	str1 = ft_strrchr(cwd1, '/');
	ft_putstr4("\033[1;33m", "😜 ", str1 + 1, " $> \033[0m");
}
