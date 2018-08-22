/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 14:43:33 by srabah            #+#    #+#             */
/*   Updated: 2014/12/23 14:44:15 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static void	eco_display_size(struct stat sts, int nb[6])
{
	char *tmp;

	ft_putchar(' ');
	tmp = ft_itoa(major(sts.st_rdev));
	ft_putspace((nb[5]) - (ft_strlen(tmp)));
	ft_putnbr(major(sts.st_rdev));
	ft_memdel((void**)&tmp);
	ft_putstr(", ");
	tmp = ft_itoa(minor(sts.st_rdev));
	ft_putspace(nb[4] - (ft_strlen(tmp)));
	ft_putnbr(minor(sts.st_rdev));
	ft_memdel((void**)&tmp);
}

static void	eco_display_size_2(struct stat sts, int nb[6])
{
	if (sts.st_size == 0)
	{
		ft_putspace(nb[5] + 1);
		ft_putspace(nb[4] + 1);
	}
	else
		ft_putspace(nb[5] + 2);
	ft_putnbr(sts.st_size);
}

void		ft_display_size(struct stat sts, int nb[6])
{
	char *tmp;

	if (nb[6] == 1)
	{
		if (((sts.st_rdev && (sts.st_size) == 0)
			|| (!(S_ISDIR(sts.st_mode)) && (sts.st_size) == 0)))
		{
			if (!(S_ISLNK(sts.st_mode)) && (!(S_ISDIR(sts.st_mode))))
				eco_display_size(sts, nb);
			else
			{
				ft_putspace(nb[5] + 1 + nb[4] + 1);
				ft_putnbr(sts.st_size);
			}
		}
		else
			eco_display_size_2(sts, nb);
	}
	else
	{
		tmp = ft_itoa(sts.st_size);
		ft_putspace(nb[3] - (ft_strlen(tmp)));
		ft_memdel((void**)&tmp);
		ft_putnbr(sts.st_size);
	}
}

void		ft_display_uid(struct stat sts, int nb[6])
{
	struct passwd *get;

	get = getpwuid (sts.st_uid);
	if (get)
	{
		ft_putstr(get->pw_name);
		ft_putspace(nb[1] - (ft_strlen(get->pw_name)));
	}
	else
	{
		ft_putnbr(sts.st_uid);
	}
	ft_putspace(2);
}

void		ft_display_gid(struct stat sts, int nb[6])
{
	char			*tmp;
	struct group	*gr;

	gr = getgrgid (sts.st_gid);
	if (gr)
	{
		ft_putstr(gr->gr_name);
		ft_putspace(nb[2] - (ft_strlen(gr->gr_name)));
	}
	else
	{
		ft_putnbr(sts.st_gid);
		tmp = ft_itoa(sts.st_gid);
		ft_putspace(nb[2] - (ft_strlen(tmp)));
		ft_memdel((void**)&tmp);
	}
	ft_putspace(2);
}
