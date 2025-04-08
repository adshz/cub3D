/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:13:07 by aalissa           #+#    #+#             */
/*   Updated: 2023/12/07 14:02:42 by aalissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*ptr;
	char		*line;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	ptr = ft_fill_buffer(fd, ptr);
	if (!ptr)
		return (NULL);
	line = ft_extract_line(ptr);
	ptr = ft_new_line(ptr);
	return (line);
}

char	*ft_fill_buffer(int fd, char *ptr)
{
	long int	bytes_read;
	char		*buffer;

	buffer = (char *) malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(ptr, '\n') && bytes_read != 0)
	{
		bytes_read = read (fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		ptr = ft_strjoin(ptr, buffer);
	}
	free(buffer);
	return (ptr);
}

char	*ft_extract_line(char *ptr)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!ptr[i])
		return (NULL);
	while ((ptr[i]) && (ptr[i] != '\n'))
		++i;
	line = (char *) malloc (sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while ((ptr[i]) && (ptr[i] != '\n'))
	{
		line[i] = ptr[i];
		++i;
	}
	if (ptr[i] == '\n')
	{
		line[i] = ptr[i];
		++i;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_new_line(char *ptr)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	while ((ptr[i]) && (ptr[i] != '\n'))
		++i;
	if (!ptr[i])
	{
		free(ptr);
		return (NULL);
	}
	line = (char *) malloc (sizeof(char) * (ft_strlen(ptr) - i + 1));
	if (!line)
		return (NULL);
	i++;
	j = 0;
	while (ptr[i])
		line[j++] = ptr[i++];
	line[j] = '\0';
	free(ptr);
	return (line);
}
