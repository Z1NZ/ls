/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_liste_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 14:54:54 by srabah            #+#    #+#             */
/*   Updated: 2014/12/23 15:21:53 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static void		eco_ft_listfile(t_list **file, t_data *data, t_params *params)
{
	if (params->modif_time == 1)
		ft_sort_lasttime(&(*file), ft_lstnew2(data, sizeof(data)));
	else if (params->modif_time != 1)
		ft_sort_ascii(&(*file), ft_lstnew2(data, sizeof(data)));
}

static void		eco_ft_listdir(t_data **data, char *mix, struct stat sts)
{
	char *tmp;

	tmp = NULL;
	*data = (t_data *)malloc(sizeof(t_data) * 1);
	if (readlink(mix, tmp, 1024) > 0)
		(*data)->filename = tmp;
	else
		(*data)->filename = mix;
	(*data)->last_timemodif = sts.st_mtime;
}

static void		eco_ft_listdir2(char *mix, t_list **ldir, t_params *params)
{
	struct stat	sts;
	t_data		*data;
	char		*tmp;
	int			j[1];

	j[0] = -1;
	j[1] = 0;
	tmp = NULL;
	((lstat(mix, &sts)) == -1) ? j[1] = 1 : ' ';
	if (S_ISLNK(sts.st_mode) && params->list == 9999999 && j[1] != 1)
	{
		stat(mix, &sts);
		(S_ISDIR(sts.st_mode)) ? j[0] = readlink(mix, tmp, 1024) : ' ';
	}
	if ((S_ISDIR(sts.st_mode) && j[1] != 1) || (j[0] != -1 && j[1] != 1))
	{
		eco_ft_listdir(&data, mix, sts);
		if (!(*ldir))
			ft_lstadd(&(*ldir), ft_lstnew2(data, sizeof(data)));
		else if (*ldir)
			eco_ft_listfile(&(*ldir), data, params);
		ft_memdel((void**)&data);
	}
	(tmp) ? ft_memdel((void**)&data) : ' ';
}

t_list			*ft_listdir(char **mix, t_params *params, int i)
{
	t_list		*ldir;

	ldir = NULL;
	while (mix[i])
	{
		eco_ft_listdir2(mix[i], &ldir, params);
		i++;
	}
	return (ldir);
}
