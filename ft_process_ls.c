/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_ls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 15:22:15 by srabah            #+#    #+#             */
/*   Updated: 2014/12/23 15:22:17 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static void	ecoft_ls1(struct stat sts, int nb[6])
{
	ft_diplay_nlink(sts, nb);
	ft_display_uid(sts, nb);
	ft_display_gid(sts, nb);
	ft_display_size(sts, nb);
	ft_display_time(sts);
}

void		ft_ls1(DIR *dossier, char *path, t_params *params)
{
	t_list		*list;
	struct stat	sts;
	int			nb[6];
	t_list		*lsttmp;

	list = NULL;
	ft_ls_info(dossier, path, &list, params);
	if (params->reverse == 1)
		list = ft_revlist(list);
	ft_strlenbigger(list, nb);
	ft_putsizeblock(list);
	lsttmp = list;
	while (list)
	{
		if ((lstat(((t_data *)list->content)->filename, &sts)) == -1)
			error(0, ((t_data *)list->content)->filename);
		ft_aff_type(sts.st_mode);
		ft_aff_right(sts.st_mode);
		ft_display_xattr(((t_data *)list->content)->filename);
		ecoft_ls1(sts, nb);
		ft_display_name_lnk_2(((t_data *)list->content)->filename);
		list = list->next;
	}
	ft_delslist(&lsttmp);
}

static void eco_ft_ls_info(t_data *data, t_list **list, t_params *params)
{
	if (!*list)
		ft_lstadd(list, ft_lstnew2(data, sizeof(data)));
	else if (*list)
	{
		if (params->modif_time == 1)
			ft_sort_lasttime(&(*list), ft_lstnew2(data, sizeof(data)));
		else if (params->modif_time != 1)
			ft_sort_ascii(&(*list), ft_lstnew2(data, sizeof(data)));
	}
}

static void eco_ft_ls_info2(t_data **data, struct dirent *ptr,
	char *path, struct stat sts)
{
	*data = (t_data *)malloc(sizeof(t_data) * 1);
	(*data)->filename = ft_strjoin(path, ptr->d_name);
	(*data)->last_timemodif = sts.st_mtime;
}

void		ft_ls_info(DIR *dossier, char *path, t_list **list,
	t_params *params)
{
	struct dirent	*ptr;
	struct stat		sts;
	t_data			*data;
	char			*tmp;

	path = test_path(path);
	while ((ptr = readdir(dossier)) != NULL)
	{
		tmp = ft_strjoin(path, ptr->d_name);
		(lstat(tmp, &sts) == -1) ? error(-2, ptr->d_name) : ' ';
		ft_memdel((void**)&tmp);
		if (params->all != 1)
			if (ft_strncmp(ptr->d_name, ".", 1))
			{
				eco_ft_ls_info2(&data, ptr, path, sts);
				eco_ft_ls_info(data, list, params);
			}
		if (params->all == 1)
		{
			eco_ft_ls_info2(&data, ptr, path, sts);
			eco_ft_ls_info(data, list, params);
		}
		ft_memdel((void**)&data);
	}
}
