/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaballe <dcaballe@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:38:00 by dcaballe          #+#    #+#             */
/*   Updated: 2022/09/20 15:50:52 by dcaballe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h> 
# include <stdlib.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd, char	**line);
char	*ft_extract_line(char *fd_read);
size_t	ft_get_strlen(const char *s);
char	*ft_get_strchr(const char *str, int c);
char	*ft_get_strjoin(char *s1, char *s2);
char	*ft_delete_line(char *fd_read);
int		ft_check_bad_parameters(int fd, char *fd_read);
char	*ft_readfd(int fd, char *fd_read);
#endif