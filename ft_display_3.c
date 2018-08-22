/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 17:58:23 by srabah            #+#    #+#             */
/*   Updated: 2014/12/23 18:00:07 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void	ft_putsizeblock(t_list *list)
{
	unsigned long	nb;
	struct stat		sts;

	nb = 0;
	if (!list)
		return ;
	while (list)
	{
		if ((lstat(((t_data *)list->content)->filename, &sts)) == -1)
			error(-2, ((t_data *)list->content)->filename);
		nb = nb + (sts.st_blocks);
		list = list->next;
	}
	ft_putstr("total ");
	ft_putnbr((int)nb);
	ft_putstr("\n");
}

void	ft_putspace(int n)
{
	if (n > 0)
	{
		while (n--)
			ft_putchar(' ');
	}
}
