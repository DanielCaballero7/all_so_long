/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaballe <dcaballe@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:47:38 by dcaballe          #+#    #+#             */
/*   Updated: 2023/02/09 19:47:40 by dcaballe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*make_str(char *s1, char *s2, size_t len)
{
	char	*s;
	int		i;

	i = 0;
	s = (char *) malloc(sizeof(char) * len);
	if (s == 0)
		return (0);
	while (s1[i] != '\0')
	{
		*s++ = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		*s++ = s2[i];
		i++;
	}
	*s = '\0';
	return (s + 1 - len);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	len;
	char	*s;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	s = make_str(s1, s2, len);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	s1 = NULL;
	s2 = NULL;
	return (s);
}
