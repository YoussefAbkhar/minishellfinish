/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspliti.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:59:41 by yabakhar          #+#    #+#             */
/*   Updated: 2019/11/06 18:59:46 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_gworde(char const *s)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (*s)
	{
		if (*s == '\t' || *s == ' ')
			i = 0;
		else if (++i == 1)
			len++;
		s++;
	}
	return (len);
}

int			ft_strspliti_suit(char *s, int j)
{
	if (!s)
		return (j);
	while (s[j] && s[j] != '\t' && s[j] != ' ')
	{
		if (s[j] && s[j] == 34)
		{
			j++;
			while (s[j] && s[j] != 34)
				j++;
		}
		if (s[j])
			j++;
	}
	return (j);
}

char		**ft_strspliti(char *s)
{
	int		i;
	int		j;
	int		l;
	char	**tab;
	int		k;

	i = 0;
	l = 0;
	k = 0;
	if (!s || !((tab = (char**)malloc(sizeof(char *) * (ft_gworde(s) + 1)))))
		return (NULL);
	while (s[i])
	{
		j = i;
		j = ft_strspliti_suit(s, j);
		if (j > i)
		{
			tab[l++] = ft_strsub(s, i, j - i);
			i = j;
		}
		else
			i++;
	}
	tab[l] = NULL;
	return (tab);
}
