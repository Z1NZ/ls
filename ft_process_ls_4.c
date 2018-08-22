/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_ls_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 17:06:18 by srabah            #+#    #+#             */
/*   Updated: 2014/12/23 17:06:20 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void		ft_delslist(t_list **alst)
{
	t_list *ptr;
	t_list *tmp;

	ptr = *alst;
	while (ptr)
	{
		tmp = ptr;
		free(tmp->content->filename);
		tmp->content->filename = NULL;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
		ptr = ptr->next;
	}
}

void		error(int i, char *path)
{
	ft_putstr_fd("ft_ls: ", 2);
	i = i;
	if ((ft_strcmp(path, "")) == 0)
		ft_putstr_fd(": ", 2);
	perror(path);
	if (i != -2)
		exit(-1);
}

t_list		*ft_revlist(t_list *list)
{
	t_list	*ptr;
	t_list	*newlist;

	newlist = NULL;
	while (list)
	{
		ptr = list->next;
		if (!newlist)
			list->next = NULL;
		ft_lstadd(&newlist, list);
		list = ptr;
	}
	return (newlist);
}

char		*test_path(char *path)
{
	int len;

	len = ft_strlen(path);
	if (path[len - 1] != '/')
		path = ft_strjoin(path, "/");
	return (path);
}

char		*notest_path(char *path)
{
	int len;

	len = ft_strlen(path);
	if (path[len - 1] == '/')
		path[len - 1] = '\0';
	return (path);
}
