/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:42:55 by vmyshko           #+#    #+#             */
/*   Updated: 2023/11/28 13:39:03 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>	// open
# include <unistd.h> // read, write, close
# include <stdlib.h> // malloc, free
# include <stdio.h>

size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*read_from_file(char *main_buffer, int fd);
char	*get_next_line(int fd);
char	*extract_line(char *main_buffer);
char	*obtain_remaining(char *main_buffer);
char	*ft_free(char *buffer);
char	*ft_strdup(char *s);

#endif
