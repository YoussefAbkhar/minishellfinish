/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_l.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:09:39 by yabakhar          #+#    #+#             */
/*   Updated: 2020/07/13 03:17:48 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    check_index_fc(char *str,int *opt)
{
    if ((str[0] == '-') && (ft_isnumber(str + 1)))
    {
        (*opt) = ft_atoi(str);
		return (1);
    }
    else if (ft_isnumber(str))
    {
        (*opt) = ft_atoi(str);
		return (1);
    }
    return (0);
}

int    index2_fc(char *str,int *check)
{
   	t_history *list;
    int i;

    list = add_to_history(NULL);
    i = 0;
    while (list)
    {
        if(!ft_strncmp(str,list->content,ft_strlen(str)))
        {
            (*check) = i;
            return (1);
        }
        list = list->next;
        i++;
    }
    return(0);
}

int get_index_fc(t_opt *opt,char **hold)
{
    int calc;
    
    calc = ft_calc(hold);
    if (calc > 1)
    {
        if (!(index2_fc(hold[2],&opt->debut)) && !(check_index_fc(hold[2],&opt->debut)))
        {
            ft_putendl("error");
            return (0);
        }
    }
    if (calc > 2)
    {
        if (!(index2_fc(hold[3],&opt->fin)) && !(check_index_fc(hold[3],&opt->fin)))
        {
            ft_putendl("error");
            return (0);
        }
    }
    return(1);
}



void 			ft_fc_l(t_opt *opt,int calc,int fd)
{
	t_history *history;
	int i;

	history = ft_get_tail(add_to_history(NULL));
	i = 0;
	while (history)
	{
		if (i == opt->debut)
		{
			while (history)
			{
				if (!opt->n)
					ft_putnbr_fd(i,fd);
				ft_putchar_fd('\t',fd);
				ft_putendl_fd(history->content,fd);
                if (opt->fin == i && calc > 2)
                   return(1);
				history = history->prev;
                i--;
			}
            return(1);
		}
		i--;
		history = history->prev;
	}
    return (0);
}

int 			ft_fc_l_r(t_opt *opt,int calc,int fd)
{
	t_history *history;
	int i;

	history = add_to_history(NULL);
	i = 0;
	while (history)
	{
		if (i == opt->debut)
		{
			while (history)
			{
				if (!opt->n)
					ft_putnbr_fd(i,fd);
				ft_putchar_fd('\t',fd);
				ft_putendl_fd(history->content,fd);
                if (opt->fin == i && calc > 2)
                   return(1);
				history = history->next;
                i++;
			}
            return (1);
		}
		i++;
		history = history->next;
	}
    return (0);
}

int fc_l(t_opt *opt,char **hold)
{
    int calc;
    t_history *history;
	history = add_to_history(NULL);
    if (!(get_index_fc(opt,hold)))
        return (0);
    calc = ft_calc(hold);
    if (calc > 2)
    {
        ft_fc_l_r(opt,calc,0);
        // if (opt->fin >= opt->debut && opt->r)
            // Dcroisent
        // else if (opt->fin >= opt->debut && !opt->r)
            // croisent
        // if (opt->debut >= opt->fin && opt->r)
            // croisen t
        // else if (opt->debut >= opt->debutopt->fin && !opt->r)
            // Dcroisent
    }
    else if (calc > 1)
    {
        ft_fc_l_r(opt,calc,0);
        // if (opt->debut && opt->r)
            // Dcroisent
        // else if (opt->debut && !opt->r)
            // croisent
    }
    else
    {
        t_history *history;
	    int i;

	history = ft_get_tail(add_to_history(NULL));
    ft_putendl(history->content);
        // opt->debut = (ft_lstlen(history) > 16) ? (ft_lstlen(history) - 16) : 0;
        // if (opt->r)
        //    ft_fc_l_r(opt,calc,0);
        // else if (!opt->r)
        //    ft_fc_l(opt,calc,0);
    }
    return (0);
}