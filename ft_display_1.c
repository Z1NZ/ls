/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 14:26:06 by srabah            #+#    #+#             */
/*   Updated: 2014/12/23 14:26:08 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void	ft_display_name_lnk_2(char *name)
{
	char *tmp;
	char tmp1[1024];

	tmp = NULL;
	tmp = ((ft_strrchr(name, '/')) + 1);
	ft_putstr(tmp);
	ft_bzero(tmp1, 1024);
	if (readlink((name), tmp1, 1023) > 0)
	{
		ft_putstr(" -> ");
		ft_putstr(tmp1);
	}
	ft_putchar('\n');
}

void	ft_diplay_nlink(struct stat sts, int nb[6])
{
	char *tmp;

	tmp = ft_itoa(sts.st_nlink);
	ft_putspace(nb[0] - (ft_strlen(tmp)));
	ft_memdel((void**)&tmp);
	ft_putnbr(sts.st_nlink);
	ft_putspace(1);
}

void	ft_display_name_lnk(char *name)
{
	char tmp[1024];

	ft_putstr(name);
	ft_bzero(tmp, 1024);
	if (readlink((name), tmp, 1023) > 0)
	{
		ft_putstr(" -> ");
		ft_putstr(tmp);
	}
	ft_putchar('\n');
}

void	ft_display_xattr(char *file)
{
	if (listxattr(file, NULL, 5, XATTR_NOFOLLOW) > 0)
	{
		ft_putchar('@');
		ft_putstr(" ");
	}
	else
		ft_putstr("  ");
}

void	ft_display_time(struct stat sts)
{
	char	*tmp[3];
	time_t	tab[2];

	tab[1] = sts.st_mtime;
	tmp[0] = ctime(&tab[1]);
	if (time(&tab[0]))
	{
		if (tab[1] > (tab[0] + 15778463) || tab[1] < (tab[0] - 15778463))
		{
			tmp[1] = ft_strsub(tmp[0], 3, 8);
			tmp[2] = ft_strsub(tmp[0], 20, 4);
			ft_putstr(tmp[1]);
			ft_putchar(' ');
			ft_putstr(tmp[2]);
			ft_memdel((void**)&tmp[1]);
			ft_memdel((void**)&tmp[2]);
		}
		else
		{
			tmp[1] = ft_strsub(tmp[0], 3, 13);
			ft_putstr(tmp[1]);
			ft_memdel((void**)&tmp[1]);
		}
	}
	ft_putchar(' ');
}
