/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_ls_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 15:45:05 by srabah            #+#    #+#             */
/*   Updated: 2014/12/23 15:45:07 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

int		ft_lstadd_at_i(t_list **list, t_list *new, int i)
{
	t_list	*nav;
	int		j;

	if (i == -1)
	{
		new->next = *list;
		*list = new;
		return (0);
	}
	nav = *list;
	j = 0;
	while (nav->next && j++ < i)
		nav = nav->next;
	new->next = nav->next;
	nav->next = new;
	return (0);
}

int		ft_sort_ascii(t_list **list, t_list *new)
{
	t_list	*nav;
	int		i;

	nav = *list;
	if (ft_strcmp(((t_data *)nav->content)->filename,
		((t_data *)new->content)->filename) > 0)
	{
		ft_lstadd_at_i(list, new, -1);
		return (0);
	}
	i = -1;
	while (nav && ((ft_strcmp(((t_data *)nav->content)->filename,
		((t_data *)new->content)->filename)) < 0))
	{
		nav = nav->next;
		i++;
	}
	ft_lstadd_at_i(list, new, i);
	return (0);
}

int		ft_sort_lasttime(t_list **list, t_list *new)
{
	t_list	*nav;
	int		i;

	nav = *list;
	if (((nav->content->last_timemodif) < (new->content->last_timemodif)))
	{
		ft_lstadd_at_i(list, new, -1);
		return (0);
	}
	i = -1;
	while (nav && ((nav->content->last_timemodif) >
		(new->content->last_timemodif)))
	{
		nav = nav->next;
		i++;
	}
	while (nav && ((nav->content->last_timemodif) == (new->content->
	last_timemodif)) && ((ft_strcmp(nav->content->filename, new->
	content->filename)) < 0))
	{
		nav = nav->next;
		i++;
	}
	ft_lstadd_at_i(list, new, i);
	return (0);
}

t_list	*ft_lstnew2(void const *content, size_t content_size)
{
	t_list *ptr;

	if (!content || !content_size)
	{
		if ((ptr = (t_list *)malloc(sizeof(t_list))) == NULL)
			return (NULL);
		if ((ptr->content = (void *)malloc(sizeof(content_size))) == NULL)
			return (NULL);
		ptr->content = NULL;
		ptr->content_size = 0;
		ptr->next = NULL;
		return (ptr);
	}
	if (content != NULL)
	{
		if ((ptr = (t_list *)malloc(sizeof(t_list))) == NULL)
			return (NULL);
		if ((ptr->content = (void *)malloc(sizeof(content_size))) == NULL)
			return (NULL);
		((t_data *)ptr->content)->filename = ((t_data *)content)->filename;
		((t_data *)ptr->content)->last_timemodif =
		((t_data *)content)->last_timemodif;
		ptr->next = NULL;
	}
	return (ptr);
}

void	option_l(t_list *list)
{
	struct stat	sts;
	int			nb[6];

	ft_strlenbigger(list, nb);
	while (list)
	{
		if ((lstat(list->content->filename, &sts)) == -1)
			error(0, ((t_data *)list->content)->filename);
		ft_aff_type(sts.st_mode);
		ft_aff_right(sts.st_mode);
		ft_display_xattr(((t_data *)list->content)->filename);
		ft_diplay_nlink(sts, nb);
		ft_display_uid(sts, nb);
		ft_display_gid(sts, nb);
		ft_display_size(sts, nb);
		ft_display_time(sts);
		ft_display_name_lnk(list->content->filename);
		list = list->next;
	}
}
