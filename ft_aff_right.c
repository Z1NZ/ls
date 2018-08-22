/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 11:51:10 by srabah            #+#    #+#             */
/*   Updated: 2014/12/23 17:25:18 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void			ft_aff_type(mode_t sts)
{
	if (S_ISREG(sts))
		ft_putchar('-');
	else if (S_ISDIR(sts))
		ft_putchar('d');
	else if (S_ISCHR(sts))
		ft_putchar('c');
	else if (S_ISBLK(sts))
		ft_putchar('b');
	else if (S_ISFIFO(sts))
		ft_putchar('p');
	else if (S_ISLNK(sts))
		ft_putchar('l');
	else if (S_ISSOCK(sts))
		ft_putchar('s');
	else
		ft_putchar('-');
}

void			ft_aff_right(mode_t sts)
{
	(sts & S_IRUSR) ? ft_putstr("r") : ft_putstr("-");
	(sts & S_IWUSR) ? ft_putstr("w") : ft_putstr("-");
	if ((sts & S_ISUID) && (!(sts & S_IWUSR)) && (!(sts & S_IRUSR)))
		ft_putstr("S");
	else if (sts & S_ISUID)
		ft_putstr("s");
	else
		(sts & S_IXUSR) ? ft_putstr("x") : ft_putstr("-");
	(sts & S_IRGRP) ? ft_putstr("r") : ft_putstr("-");
	(sts & S_IWGRP) ? ft_putstr("w") : ft_putstr("-");
	if ((sts & S_ISGID) && (!(sts & S_IWGRP)) && (!(sts & S_IRGRP)))
		ft_putstr("S");
	else if (sts & S_ISGID)
		ft_putstr("s");
	else
		(sts & S_IXGRP) ? ft_putstr("x") : ft_putstr("-");
	(sts & S_IROTH) ? ft_putstr("r") : ft_putstr("-");
	(sts & S_IWOTH) ? ft_putstr("w") : ft_putstr("-");
	if ((sts & S_ISTXT) && (!(sts & S_IWOTH)) && (!(sts & S_IROTH)))
		ft_putstr("T");
	else if (sts & S_ISTXT)
		ft_putstr("t");
	else
		(sts & S_IXOTH) ? ft_putstr("x") : ft_putstr("-");
}

static void		eco_ft_listfile(t_list **file, t_data *data, t_params *params)
{
	if (params->modif_time == 1)
		ft_sort_lasttime(&(*file), ft_lstnew2(data, sizeof(data)));
	else if (params->modif_time != 1)
		ft_sort_ascii(&(*file), ft_lstnew2(data, sizeof(data)));
}

static void		eco_ft_listfile2(struct stat *sts, char *mx, int j, char *tmp)
{
	if (S_ISLNK(sts->st_mode))
		if (stat(mx, sts) != -1)
			(S_ISDIR(sts->st_mode)) ? j = readlink(mx, tmp, 1024) : ' ';
}

t_list			*ft_listfile(char **mx, t_params *params, int i)
{
	t_list		*file;
	struct stat sts;
	t_data		*data;
	char		*tmp;
	int			j;

	file = NULL;
	while (mx[i])
	{
		j = -1;
		tmp = NULL;
		((lstat(mx[i], &sts)) == -1) ? error(-2, mx[i]) : ' ';
		(params->list != 1) ? eco_ft_listfile2(&sts, mx[i], j, tmp) : ' ';
		if (!S_ISDIR(sts.st_mode) && (lstat(mx[i], &sts) != -1))
		{
			data = (t_data *)malloc(sizeof(t_data) * 1);
			data->filename = (j != -1) ? tmp : mx[i];
			data->last_timemodif = sts.st_mtime;
			(!file) ? ft_lstadd(&file, ft_lstnew2(data, sizeof(data))) :
				eco_ft_listfile(&file, data, params);
			ft_memdel((void**)&data);
		}
		i++;
	}
	return ((params->reverse == 1) ? ft_revlist(file) : file);
}
