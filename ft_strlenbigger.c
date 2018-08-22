/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenbigger.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 08:11:36 by srabah            #+#    #+#             */
/*   Updated: 2014/12/17 08:11:39 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static	void	eco_ft_strlenbigger(struct stat sts, int nb[6])
{
	char			*tmp;
	struct passwd	*get;

	tmp = ft_itoa(sts.st_nlink);
	nb[0] = ((ft_strlen(tmp)) > (unsigned int)nb[0])
	? (int)ft_strlen(tmp) : nb[0];
	ft_memdel((void**)&tmp);
	get = getpwuid (sts.st_uid);
	if (get)
		nb[1] = ((ft_strlen(get->pw_name)) > (unsigned int)nb[1])
		? (int)ft_strlen(get->pw_name) : nb[1];
	else
	{
		tmp = ft_itoa(sts.st_uid);
		if ((ft_strlen(tmp)) > (unsigned int)nb[1])
			nb[1] = ft_strlen(tmp);
		ft_memdel((void**)&tmp);
	}
}

static	void	eco_ft_strlenbigger2(struct stat sts, int nb[6])
{
	char			*tmp;
	struct group	*gr;

	gr = getgrgid (sts.st_gid);
	if (gr)
		nb[2] = ((ft_strlen(gr->gr_name)) > (unsigned int)nb[2])
		? (int)ft_strlen(gr->gr_name) : nb[2];
	else
	{
		tmp = ft_itoa(sts.st_gid);
		if ((ft_strlen(tmp)) > (unsigned int)nb[2])
			nb[2] = ft_strlen(tmp);
		ft_memdel((void**)&tmp);
	}
	tmp = ft_itoa(sts.st_size);
	nb[3] = ((ft_strlen(tmp)) > (unsigned int)nb[3])
	? (int)ft_strlen(tmp) : nb[3];
	ft_memdel((void**)&tmp);
	tmp = ft_itoa(minor(sts.st_rdev));
	nb[4] = ((ft_strlen(tmp)) > (unsigned int)nb[4])
	? (int)ft_strlen(tmp) : nb[4];
	ft_memdel((void**)&tmp);
}

void			ft_strlenbigger(t_list *list, int nb[6])

{
	struct stat		sts;
	char			*tmp;

	nb[0] = 0;
	nb[1] = 0;
	nb[2] = 0;
	nb[3] = 0;
	nb[4] = 0;
	nb[5] = 0;
	nb[6] = 0;
	while (list)
	{
		if ((lstat(((t_data *)list->content)->filename, &sts)) == -1)
			return ;
		eco_ft_strlenbigger(sts, nb);
		eco_ft_strlenbigger2(sts, nb);
		tmp = ft_itoa(major(sts.st_rdev));
		nb[5] = ((ft_strlen(tmp)) > (unsigned int)nb[5])
		? (int)ft_strlen(tmp) : nb[5];
		ft_memdel((void**)&tmp);
		if ((sts.st_rdev && (sts.st_size) == 0) ||
			(S_ISCHR(sts.st_mode) && (sts.st_size) == 0))
			nb[6] = 1;
		list = list->next;
	}
}

void			ft_ls(DIR *dossier, char *path, t_params *params)
{
	t_list		*list;
	struct stat	sts;
	char		*str;

	list = NULL;
	ft_ls_info(dossier, path, &list, params);
	if (params->reverse == 1)
		list = ft_revlist(list);
	while (list)
	{
		if ((lstat(((t_data *)list->content)->filename, &sts)) == -1)
			error(-2, ((t_data *)list->content)->filename);
		str = (((t_data *)list->content)->filename);
		ft_putstr(((ft_strrchr(str, '/')) + 1));
		ft_putchar('\n');
		list = list->next;
	}
}

void			check_params(char *option, t_params *params)
{
	int i;

	i = 0;
	while (option[i++])
		if (option[i] != 'r' && option[i] != 'l' && option[i] != 'a'
			&& option[i] != 't' && option[i] != 'R' && option[i] != '\0'
			&& option[i] != '1')
		{
			ft_putstr_fd("ft_ls: illegal option -- ", 2);
			ft_putchar_fd(option[+i], 2);
			ft_putstr_fd("\nusage: ft_ls [-Ralrt] [file ...]\n", 2);
			exit(-1);
		}
	if (ft_strchr(option, 'r'))
		params->reverse = 1;
	if (ft_strchr(option, 'l'))
		params->list = 1;
	if (ft_strchr(option, 'a'))
		params->all = 1;
	if (ft_strchr(option, 't'))
		params->modif_time = 1;
	if (ft_strchr(option, 'R'))
		params->recursiv = 1;
}
