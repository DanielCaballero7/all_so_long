/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaballe <dcaballe@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:21:23 by dcaballe          #+#    #+#             */
/*   Updated: 2022/10/03 16:21:28 by dcaballe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*fd_read[4096];

	if (BUFFER_SIZE < 1 || fd < 0 || fd > 4095 || read(fd, 0, 0) < 0)
	{
		free(fd_read[fd]);
		fd_read[fd] = NULL;
		return (NULL);
	}
	if (!ft_strchr(fd_read[fd], '\n'))
		fd_read[fd] = ft_readfd(fd, fd_read[fd]);
	if (!fd_read[fd])
		return (NULL);
	line = ft_extract_line(fd_read[fd]);
	fd_read[fd] = ft_delete_line(fd_read[fd]);
	return (line);
}

char	*ft_extract_line(char *fd_read)
{
	unsigned int	i;
	char			*line;

	i = 0;
	if (!fd_read[i])
		return (NULL);
	while (fd_read[i] && fd_read[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (fd_read[i] && fd_read[i] != '\n')
	{
		line[i] = fd_read[i];
		i++;
	}
	if (fd_read[i] == '\n')
	{
		line[i] = fd_read[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_delete_line(char *fd_read)
{
	unsigned int	i;
	unsigned int	j;
	char			*new_fd_read;

	i = 0;
	while (fd_read[i] && fd_read[i] != '\n')
		i++;
	if (!fd_read[i])
	{
		free(fd_read);
		return (NULL);
	}
	new_fd_read = (char *)malloc(sizeof(char) * (ft_strlen(fd_read) - i + 1));
	if (!new_fd_read)
		return (NULL);
	i++;
	j = 0;
	while (fd_read[i])
		new_fd_read[j++] = fd_read[i++];
	new_fd_read[j] = '\0';
	free(fd_read);
	return (new_fd_read);
}

char	*ft_readfd(int fd, char *fd_read)
{
	int		buffer_len;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer_len = 1;
	while (!ft_strchr(fd_read, '\n') && buffer_len != 0)
	{
		buffer_len = read(fd, buffer, BUFFER_SIZE);
		if (buffer_len == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[buffer_len] = '\0';
		fd_read = ft_get_strjoin(fd_read, buffer);
	}
	free(buffer);
	return (fd_read);
}
