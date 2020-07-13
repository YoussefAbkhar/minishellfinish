/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:09:39 by yabakhar          #+#    #+#             */
/*   Updated: 2020/07/13 02:58:43 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void opt_error(char c)
{
	ft_putstr("42sh: fc: -");
	ft_putchar(c);
	ft_putendl(" : invalid option");
	ft_putendl("fc: usage: fc [-e ename] [-lnr] [first] [last] or fc -s [pat=rep] [command]");
}


int ft_isnumber(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
			return(0);
		i++;	
	}
	return(1);
}

int check_fc_num(t_opt *opt,char *key)
{
	if ((key[0] == '-') && (ft_isnumber(key + 1)))
	{
		opt->check = 1;
		return (1);
	}
	else if (ft_isnumber(key))
	{
		opt->check = 1;
		return (1);
	}
	return(0);
}

int		check_opt(t_opt *opt, char *hold)
{
	int i;

	if (!ft_strcmp("-0",hold) && opt->i == 1)
	{
		ft_putendl("bash: fc: history specaification out of range");
		return (0);
	}
	else if (check_fc_num(opt,hold))
		return(0);
	else if (hold[0] == '-')
	{
		i = 1;
		while (hold[i])
		{
			if (hold[i] == 'l')
				opt->l = 1;
			else if (hold[i] == 'n')
				opt->n = 1;
			else if (hold[i] == 'e')
				opt->e = 1;
			else if (hold[i] == 's')
				opt->s = 1;
			else if (hold[i] == 'r')
				opt->r = 1;
			else
    	    {
				if (!ft_strchr("lners",hold[i]))
				{
					opt_error(hold[i]);
					return(-1);
				}
			}
			i++;
		}
		return (1);
	}
	else
		opt->check = 1;
	return (0);
}

void printttt(t_opt opt)
{
    printf("e => %d\n",opt.e);
    printf("r => %d\n",opt.r);
    printf("l => %d\n",opt.l);
    printf("n => %d\n",opt.n);
    printf("s => %d\n",opt.s);
 	printf("i => %d\n",opt.i - 1);
}


void    ft_handel_fc(t_opt *opt,char **hold)
{
    if (opt->s == 1)
    {
        printf ("fc -s \n");
    }
    else if (opt->l == 1)
    {
        fc_l(opt,hold);
    }
    else if (opt->e == 1)
    {
        printf ("fc -e \n");
    }
    else if (opt->r == 1)
    {
        printf ("fc -r \n");
    }
	else if (opt->i == 1 || opt->r && (opt->i == 2) || opt->s && (opt->i == 2)) 
	{
    	printf ("l3adiya\n");
	}
}

// int				ft_calc(char **hold)
// {
// 	int i;

// 	i = 0;
// 	while (hold[i])
// 		i++;
// 	if (i > 0)
// 		i--;
// 	return (i);
// }

void    parce_param_fc(char **hold)
{
    t_opt	opt;

	ft_bzero(&opt, sizeof(t_opt));
	while (++opt.i < (ft_calc(hold) + 1))
	{
		if (check_opt(&opt, hold[opt.i]) == -1)
			return;
		else if (check_opt(&opt, hold[opt.i]) && opt.check == 1)
		{
			ft_putendl("bash: fc: history specification out of range");
			return;
		}	
	}
    ft_handel_fc(&opt,hold);
}
