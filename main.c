/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 05:55:36 by srabah            #+#    #+#             */
/*   Updated: 2014/12/17 05:55:39 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void	balance_routage_liste_dir(t_params *params, char *path, DIR *dossier)
{
	if (params->recursiv == 1)
	{
		if (params->list == 1)
			ls_r(path, params, 0, ft_ls1);
		else
			ls_r(path, params, 0, ft_ls);
	}
	else if (params->list == 1)
		ft_ls1(dossier, path, params);
	else
		ft_ls(dossier, path, params);
}

void	routage_liste_dir(char **argv, int i, t_params *params, int j)
{
	t_list		*ldir;
	t_list		*tmp;
	DIR			*dossier;

	ldir = ft_listdir(argv, params, i);
	tmp = ldir;
	i = 1;
	while (ldir)
	{
		if (i != 1 || j != 0)
			ft_putchar('\n');
		if (tmp->next != NULL || j != 0)
		{
			ft_putstr(ldir->content->filename);
			ft_putstr(":\n");
		}
		if (!(dossier = opendir(((t_data *)ldir->content)->filename)))
			error(-1, ((t_data *)ldir->content)->filename);
		balance_routage_liste_dir(params, ldir->content->filename, dossier);
		i++;
		ldir = ldir->next;
	}
}

int		routage_liste_file(char **argv, int i, t_params *params)
{
	t_list		*file;

	if (!argv[i])
	{
		argv[i] = "./";
		argv[i + 1] = '\0';
	}
	file = ft_listfile(argv, params, i);
	if (file)
	{
		if (params->list == 1)
			option_l(file);
		else
		{
			while (file)
			{
				ft_putendl(file->content->filename);
				file = file->next;
			}
		}
		return (1);
	}
	return (0);
}

void	ini_params(t_params *params)
{
	params->reverse = 9999999;
	params->list = 9999999;
	params->all = 9999999;
	params->modif_time = 9999999;
	params->recursiv = 9999999;
}

int		main(int argc, char **argv)
{
	t_params	params;
	DIR			*dossier;
	int			i;
	int			j;

	ini_params(&params);
	if (!argv[1])
	{
		if (!(dossier = opendir(".")))
			error(-1, ".");
		ft_ls(dossier, ".", &params);
		if (closedir(dossier) == -1)
			error(-2, ".");
		exit(-1);
	}
	i = 1;
	while (i < argc && argv[i][0] == '-' && (ft_strcmp(argv[i], "-") != 0)
	&& (ft_strcmp(argv[i], "--") != 0))
		check_params(argv[i++], &params);
	if (i < argc && (ft_strcmp(argv[i], "--") == 0))
		i++;
	j = routage_liste_file(argv, i, &params);
	routage_liste_dir(argv, i, &params, j);
	return (0);
}
