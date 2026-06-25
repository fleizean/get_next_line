/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 20:34:57 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/25 20:35:04 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*join_stash(char *stash, char *buf)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = malloc(ft_strlen(stash) + ft_strlen(buf) + 1);
	if (!res)
	{
		free(stash);
		return (NULL);
	}
	i = 0;
	while (stash[i])
	{
		res[i] = stash[i];
		i++;
	}
	j = 0;
	while (buf[j])
		res[i++] = buf[j++];
	res[i] = '\0';
	free(stash);
	return (res);
}
