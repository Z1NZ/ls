/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 04:42:51 by srabah            #+#    #+#             */
/*   Updated: 2014/11/11 21:04:33 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*scpy;
	size_t	i;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (len + start > size)
		len = size - start;
	scpy = ft_strnew (len + 1);
	if (scpy == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		scpy[i] = s[start + i];
		i++;
	}
	scpy[i] = 0;
	return (scpy);
}
