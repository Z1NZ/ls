/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 16:39:29 by srabah            #+#    #+#             */
/*   Updated: 2014/11/13 02:14:41 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <string.h>
# include <dirent.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/xattr.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>

typedef struct	s_params
{
	int recursiv;
	int reverse;
	int list;
	int all;
	int modif_time;
}				t_params;

typedef struct	s_data
{
	char	*filename;
	time_t	last_timemodif;
}				t_data;

typedef struct	s_list
{
	t_data			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

void			ft_aff_type(mode_t sts);
void			ft_aff_right(mode_t sts);
void			ft_strlenbigger(t_list *list, int nb[4]);
void			routage_liste_dir(char **argv, int i, t_params *params, int j);
int				routage_liste_file(char **argv, int i, t_params *params);
void			ft_display_size(struct stat sts, int nb[6]);
void			ft_display_uid(struct stat sts, int nb[6]);
void			ft_display_gid(struct stat sts, int nb[6]);
void			ft_putsizeblock(t_list *list);
void			ft_putspace(int n);
void			ft_display_time(struct stat sts);
void			ft_display_xattr(char *file);
void			ft_display_name_lnk(char *name);
void			ft_diplay_nlink(struct stat sts, int nb[6]);
void			ft_display_name_lnk_2(char *name);
t_list			*ft_listfile(char **melange, t_params *params, int i);
t_list			*ft_listdir(char **melange, t_params *params, int i);
void			check_params(char *option, t_params *params);
void			ft_ls1(DIR *dossier, char *path, t_params *params);
void			ft_ls(DIR *dossier, char *path, t_params *params);
void			option_l(t_list *list);
void			ft_ls_info(DIR *dossier, char *path, t_list **list,
	t_params *params);
t_list			*ft_lstnew2(void const *content,
	size_t content_size);
int				ft_sort_lasttime(t_list **list, t_list *new);
int				ft_sort_ascii(t_list **list, t_list *new);
int				ft_lstadd_at_i(t_list **list, t_list *new, int i);
void			ls_r(char *path, t_params *params, int i, void (*f)(DIR *,
	char *, t_params *params));
void			ft_comptdir(DIR *dossier, char **path, t_list **list,
	t_params *params);
void			ft_delslist(t_list **alst);
void			error(int i, char *path);
t_list			*ft_revlist(t_list *list);
char			*test_path(char *path);
char			*notest_path(char *path);
void			balance_routage_liste_dir(t_params *params,
	char *path, DIR *dossier);
void			ini_params(t_params *params);

/*
**	List functions
*/
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstadd_end(t_list **alst, t_list *new);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));

#endif
