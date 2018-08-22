/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 13:53:07 by srabah            #+#    #+#             */
/*   Updated: 2014/12/23 17:17:59 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_lstadd_end(t_list **alst, t_list *new)
{
	t_list *last_link;

	if (new && *alst)
	{
		last_link = *alst;
		while (last_link->next != NULL)
			last_link = last_link->next;
		last_link->next = new;
	}
	else if (new)
		*alst = new;
}
