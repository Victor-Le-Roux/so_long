/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:03:28 by vmyshko           #+#    #+#             */
/*   Updated: 2023/12/06 17:35:05 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>	// open
#include <unistd.h> // read, write, close
#include <stdlib.h> // malloc, free
#include <stdio.h>
#include <stdint.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

char	*read_from_file(char *main_buffer, int fd)
{
	ssize_t	bytes_read;
	char	*mini_buffer;

	mini_buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!mini_buffer)
		return (ft_free(main_buffer), NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(main_buffer, '\n'))
	{
		bytes_read = read(fd, mini_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			ft_free(mini_buffer);
			ft_free(main_buffer);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		mini_buffer[bytes_read] = '\0';
		main_buffer = ft_strjoin(main_buffer, mini_buffer);
		if (!main_buffer)
			return (ft_free(mini_buffer), NULL);
	}
	free(mini_buffer);
	return (main_buffer);
}

char	*ft_free(char *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	return (NULL);
}

char	*extract_line(char *main_buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!main_buffer[i])
		return (NULL);
	while (main_buffer[i] && main_buffer[i] != '\n')
		i++;
	if (main_buffer[i] == '\n')
		line = ft_calloc(i + 2, sizeof(char));
	else
		line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (free(main_buffer), NULL);
	i = -1;
	while (main_buffer[++i] && main_buffer[i] != '\n')
		line[i] = main_buffer[i];
	if (main_buffer[i] == '\n')
	{
		line[i] = main_buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*obtain_remaining(char *main_buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while ((main_buffer)[i] && (main_buffer)[i] != '\n')
		i++;
	if ((main_buffer)[i] == '\n')
		i++;
	if (!(main_buffer)[i])
		return (ft_free(main_buffer), NULL);
	line = ft_calloc(ft_strlen((main_buffer) + i) + 1, sizeof(char));
	if (!line)
		return (ft_free(main_buffer), NULL);
	while ((main_buffer)[i])
		line[j++] = (main_buffer)[i++];
	line[j] = '\0';
	free(main_buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*main_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	main_buffer = read_from_file(main_buffer, fd);
	if (!main_buffer)
	{
		return (NULL);
	}
	line = extract_line(main_buffer);
	if (!line)
	{
		main_buffer = NULL;
		return (NULL);
	}
	main_buffer = obtain_remaining(main_buffer);
	return (line);
}

