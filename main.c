/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:09:39 by yabakhar          #+#    #+#             */
/*   Updated: 2020/07/13 02:54:51 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char			*ft_slash(char *tmp, char *tmp2, char **splite)
{
	if (access(tmp2, F_OK) == 0)
	{
		free(tmp);
		ft_delsplite(&splite);
		return (tmp2);
	}
	else if (access(tmp2, F_OK) != 0)
	{
		free(tmp);
		free(tmp2);
	}
	return (NULL);
}

char			*ft_suit1(t_node *list, char *hold)
{
	t_suit		suit;

	suit.i = -1;
	suit.tmp3 = ft_suit(list, "PATH=", 5);
	if (!(suit.tmp3) ||
	((ft_strncmp(hold, "/", 1) == 0) && (access(hold, F_OK) != 0)))
		return (NULL);
	suit.splite = ft_strsplit(suit.tmp3, ':');
	while (suit.splite && suit.splite[++suit.i])
	{
		ft_strdel(&suit.tmp3);
		suit.tmp2 = ft_strjoin(suit.splite[suit.i], "/");
		suit.str = ft_strjoin(suit.tmp2, hold);
		if ((suit.tmp = ft_slash(suit.tmp2, suit.str, suit.splite)))
			return (suit.tmp);
	}
	ft_strdel(&suit.tmp3);
	ft_delsplite(&suit.splite);
	return (NULL);
}

char *ft_getpath(void)
{
	char *str;
	char *tmp;

	str = ft_strjoin("/home/",getlogin());
	tmp = ft_strjoin(str,"/Desktop/minishellfinish/txt");
	free(str);
	return (tmp);
}

void	ft_check_stock(t_history **history,int fd)
{
	char *str;

	while (get_next_line(fd,&str) > 0)
	{
		(*history)->content = ft_strdup(str);
		(*history)->next = ft_memalloc(sizeof(t_node));
		(*history) = (*history)->next;
		ft_strdel(&(str));
	}
	(*history)->next = NULL;
	ft_strdel(&(str));
}

char **ft_get_line_in_file(int fd)
{
	char	*str;
	char	**tab;
	int		i;
	
	str = NULL;
	i = 0;
	*tab = NULL;
	
	return (tab);
}

// void					kook(t_node *list, char *str)
// {
// 	int		i = 0;
// 	char	*str1;
// 	int		fd;
// 	char *line;
// 	if (ft_suit1(list, str))
// 		str1 = ft_suit1(list, str);
// 	else
// 	{
// 		ft_putstr("42sh: ");
// 		ft_putstr(str);
// 		ft_putendl(": Command not found");
// 		return;
// 	}
// 	ft_open_editeur(list,str,str1);
// 	fd = open(".42sh-fc",O_RDONLY);
// 	while (get_next_line(fd,&line))
// 	{
// 		// execute commande
// 		ft_putendl(line);
// 		// add_to_history(line);
// 		ft_strdel(&line);
// 	}
// 	ft_strdel(&line);
// 	//rm .42sh-fc
// }

void usage_fc()
{
	ft_putendl("42sh: fc: -e: option requires an argument");
	ft_putendl("fc: usage: fc [-e ename] [-lnr] [first] [last] or fc -s [pat=rep] [command]");
}

t_history *ft_get_tail(t_history *history)
{
	while (history)
	{
		if (history->next == NULL)
			return (history);
		history = history->next;
	}
	return (history);
}

// void 			ft_fc_l_r(int n,int k)
// {
// 	t_history *history;
// 	int i;

// 	history = add_to_history(NULL);
// 	i = 0;
// 	while (history)
// 	{
// 		if (i == k)
// 		{
// 			while (history)
// 			{
// 				if (n)
// 					ft_putnbr_fd(i++,0);
// 				// ft_putchar('\t');
// 				ft_putendl_fd(history->content,0);
// 				history = history->next;
// 			}
// 			break;
// 		}
// 		i++;
// 		history = history->next;
// 	}
// }

// void 			ft_fc_l(int n,int k)
// {
// 	t_history *history;
// 	int i;

// 	history = ft_get_tail(add_to_history(NULL));
// 	// k = 0;//k = (ft_lstlen(count) > 16) ? (ft_lstlen(count) - 16) : 0;
// 	i = 0;
// 	while (history)
// 	{
// 		if (i == k)
// 		{
// 			while (history)
// 			{
// 				if (n)
// 					ft_putnbr_fd(i++,0);
// 				ft_putstr_fd("     ",0);
// 				ft_putendl_fd(history->content,0);
// 				history = history->prev;
// 			}
// 			break;
// 		}
// 		i++;
// 		history = history->prev;
// 	}
// }


// int				ft_suit_main1(char **holder, char *str)
// {
// 	t_node *list = ft_getter(0)->env;

// 	char *str1;
// 	if (str)
// 	{
// 		if (ft_strcmp(str, "fc") == 0)
// 		{
// 			if (!holder[1])
// 				kook(list,"vim");
// 			if (holder[2] && ft_strcmp(holder[1], "-e") == 0)
// 			{
// 				kook(list,holder[2]);
// 			}
// 			else if (holder[1] && !holder[2] && ft_strcmp(holder[1], "-e") == 0)
// 				usage_fc();
// 			return (1);
// 		}
// 		else if (ft_strcmp(str, "ll") == 0)
// 		{
// 			// ft_fc_l(1);
// 			return(1);
// 		}
// 		else if (ft_strcmp(str, "lll") == 0)
// 		{
// 			// ft_fc_l_r(0);
// 			return(1);
// 		}
// 		else if (ft_strcmp(str, "exit") == 0)
// 		{
// 			t_history *history = ft_get_tail(add_to_history(NULL));
// 			while (history)
// 			{
// 				ft_putendl(history->content);
// 				history = history->prev;
// 			}
// 			exit(0);
// 		}
// 	}
	
// 	return (0);
// }

int				ft_suit_main1(char **holder, char *str)
{
	t_node *list = ft_getter(0)->env;
	if (ft_strcmp(str, "fc") == 0)
	{
		parce_param_fc(holder);
		return(1);
	}
	else if (ft_strcmp(str, "exit") == 0)
		exit(0);
	return (0);
}

int				ft_suit_main2(t_node *list, char **holder, char **str)
{
	char		*tmp;

	if ((tmp = (ft_suit_d((*str), list))) == NULL)
	{
		ft_putstr4((*str) + 1, ": ", "Undefined variable.", "\n");
		{
			ft_strdel(str);
			return (1);
		}
	}
	else if ((tmp = (ft_suit_d((*str), list))) != NULL)
	{
		if (ft_suit_main1(holder, tmp))
		{
			ft_strdel(str);
			return (1);
		}
		else
		{
			ft_putstr4(tmp, ":", " Permission denied.", "\n");
			ft_strdel(str);
			return (1);
		}
	}
	return (0);
}

int				main(int ac, char **av, char **env)
{
	t_mini		mini;
	t_node		*list;

	ac = 1;
	av = NULL;

	list = ft_stock(env);
	ft_getter(&mini);
	mini.env = list;
	load_hsitory("./txt");
	while (1)
	{
		ft_porompte();
		if (ft_main(list))
			continue;
	}
	ft_free_list(list);
	return (0);
}
