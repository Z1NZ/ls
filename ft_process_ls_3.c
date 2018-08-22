/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_ls_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 16:02:05 by srabah            #+#    #+#             */
/*   Updated: 2014/12/23 16:02:07 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static void	ft_print_path(char *path)
{
	ft_putstr("\n");
	ft_putstr(notest_path(path));
	ft_putstr(":\n");
}

void		ls_r(char *path, t_params *params, int i, void (*f)(DIR *,
	char *, t_params *params))
{
	DIR		*dossier;
	t_list	*t;
	t_list	*tmp;

	t = NULL;
	(!(dossier = opendir(path))) ? error(-2, path) : ' ';
	if (i > 0)
		ft_print_path(path);
	i++;
	if (dossier)
	{
		(*f)(dossier, path, params);
		(closedir(dossier) == -1) ? error(-2, path) : ' ';
		(!(dossier = opendir(path))) ? error(-2, path) : ' ';
		ft_comptdir(dossier, &path, &t, params);
	}
	if (dossier)
		(closedir(dossier) == -1) ? error(-2, path) : ' ';
	tmp = t;
	while (t)
	{
		ls_r(((t_data *)(t)->content)->filename, params, i, f);
		t = t->next;
	}
	ft_delslist(&tmp);
}

static void eco_ft_comptdir(t_data *data, t_list **list, t_params *params)
{
	if (params->reverse == 1)
		ft_lstadd(&(*list), ft_lstnew(data, sizeof(data)));
	else
		ft_lstadd_end(&(*list), ft_lstnew(data, sizeof(data)));
}

static void eco_ft_comptdir2(t_data **data, struct dirent *ptr,
	char *path, struct stat sts)
{
	*data = (t_data *)malloc(sizeof(t_data) * 1);
	(*data)->filename = ft_strjoin(path, ptr->d_name);
	(*data)->last_timemodif = sts.st_mtime;
}

void		ft_comptdir(DIR *dossier, char **path, t_list **list,
t_params *params)
{
	struct dirent	*ptr;
	struct stat		sts;
	t_data			*data;
	char			*str;

	if (*path)
		*path = test_path(*path);
	while ((ptr = readdir(dossier)) != NULL)
	{
		str = ft_strjoin(*path, ptr->d_name);
		(lstat(str, &sts) == -1) ? error(-2, ptr->d_name) : ' ';
		if (ft_strncmp(ptr->d_name, ".", 1) && S_ISDIR(sts.st_mode))
		{
			eco_ft_comptdir2(&data, ptr, *path, sts);
			eco_ft_comptdir(data, list, params);
		}
		else if (params->all == 1 && (S_ISDIR(sts.st_mode) &&
			ft_strcmp(ptr->d_name, ".") && ft_strcmp(ptr->d_name, "..")))
		{
			eco_ft_comptdir2(&data, ptr, *path, sts);
			eco_ft_comptdir(data, list, params);
		}
		ft_memdel((void**)&data);
		ft_memdel((void**)&str);
	}
}
