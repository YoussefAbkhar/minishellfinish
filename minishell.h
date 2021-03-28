/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:51:53 by yabakhar          #+#    #+#             */
/*   Updated: 2019/11/06 03:50:31 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include <dirent.h>
# define BUFF_SIZE 1500000

typedef struct		s_suit
{
	char			**splite;
	char			*tmp;
	char			*str;
	char			*tmp2;
	char			*tmp3;
	int				i;
}					t_suit;

typedef struct		s_node
{
	char			*content;
	struct s_node	*next;
}					t_node;

typedef struct		s_adenv
{
	char			*str;
	char			*str1;
	char			*str2;
	int				j;
}					t_adenv;

typedef struct		s_env
{
	int				i;
	int				j;
	int				x;
	char			*tmp;
	char			*var;
	char			*tmp2;
}					t_env;

typedef struct		s_mini
{
	t_node		*env;
}					t_mini;

void				ft_putstr4(char *s, char *s1, char *s2, char *s3);
_Bool				ft_cd(char **holder, char *tmp);
_Bool				ft_echo(char **holder);
char				*ft_suit(t_node *list, char *str, int i);
int					ft_addenv(char **holder, char *tmp);
t_node				*ft_stock(char **env);
char				**ft_convert_list_table(t_node *list);
int					ft_unsetenv(char **holder, char *str);
char				*ft_sersh(char *str);
int					ft_len(char *str);
int					ft_calc(char **hold);
int					ft_switch(char *holder, char *str);
char				*ft_del_quote(char *s);
int					ft_hecho(char *holder);
char				*ft_cdsuit(char *holder, t_node *list);
char				*ft_suit_d(char *holder, t_node *node);
void				ft_free_list(t_node *head);
void				ft_delsplite(char ***splite);
int					count_list(t_node *list);
int					ft_suit_hecho(char **holder);
void				ft_node_push_back(t_node *content_new, char *str);
int					ft_fork1(char **holder, t_node *list);
void				ft_switch_pwd(t_node *list);
void				ft_fork(char **holder, t_node *list);
char				*ft_suit1(t_node *list, char *hold);
char				*ft_f_strjoin(char *s1, char *s2);
int					ft_ch_env(t_env	*env, char **str2);
char				**ft_strspliti(char *s);
int					ft_env(char **holder, char *str);
void				ft_freee(char *str, char *str2);
t_mini				*ft_getter(t_mini *node);
void				ft_porompte(void);
void				check_dash(char **holder, t_node *list);
char				*ft_suit_d(char *holder, t_node *node);
int					ft_main(t_node *list);
int					ft_suit_main(t_node *list, char **holder);
int					ft_suit_main2(t_node *list, char **holder, char **str);
int					builtins(char **holder, char *str);
void				ft_fork3(char **holder, t_node *list, char *str1);
int					ft_tools(char *tmp, char **str, char **holder,
t_node *list);
#endif
