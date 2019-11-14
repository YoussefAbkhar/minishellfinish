/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suit_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 05:49:07 by yabakhar          #+#    #+#             */
/*   Updated: 2019/11/10 11:04:29 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_len(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

char		*ft_sersh(char *str)
{
	char	*s;

	s = ft_strchr(str, '=');
	return (s + 1);
}

char		*ft_suit(t_node *tmp, char *str, int i)
{
	char *str1;

	while (tmp)
	{
		if (ft_strncmp(tmp->content, str, i) == 0)
		{
			str1 = ft_strdup(&tmp->content[i]);
			return (str1);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void		ft_switch_pwd(t_node *list)
{
	char	cwd[256];
	char	*str;
	char	*str1;
	char	*cwd1;
	char	*str2;

	if (getcwd(cwd, sizeof(cwd)))
		cwd1 = getcwd(cwd, sizeof(cwd));
	str = ft_strjoin("PWD=", cwd1);
	str2 = ft_suit(list, "PWD", 3);
	str1 = ft_strjoin("OLDPWD", str2);
	ft_switch("PWD", str);
	ft_switch("OLDPWD", str1);
	ft_strdel(&str);
	ft_strdel(&str1);
	ft_strdel(&str2);
}

void		check_dash(char **holder, t_node *list)
{
	char	*tmp;

	tmp = ft_suit(list, "OLDPWD=", 7);
	if (tmp)
		chdir(tmp);
	else
		ft_putstr4("minishell$: ", holder[0], ": OLDPWD not set", "\n");
	ft_strdel(&tmp);
}
