/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:15:08 by daduarte          #+#    #+#             */
/*   Updated: 2024/05/10 12:25:12 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*save_str(char *buffer);
char	*get_lines(char *buffer);
char	*read_file(int fd, char *buffer, int bytes_read);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			bytes_read;

	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (buffer)
			free(buffer);
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (NULL);
	}
	buffer = read_file(fd, buffer, bytes_read);
	if (!buffer)
		return (NULL);
	line = get_lines(buffer);
	buffer = save_str(buffer);
	return (line);
}

char	*save_str(char *buffer)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i ++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	temp = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!temp)
	{
		free(buffer);
		return (NULL);
	}
	i ++;
	while (buffer[i])
		temp[j++] = buffer[i++];
	temp[j] = 0;
	free(buffer);
	return (temp);
}

char	*get_lines(char *buffer)
{
	char	*temp;
	int		i;

	i = 0;
	if (!*buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i ++;
	if (buffer[i] && buffer[i] == '\n')
		i ++;
	temp = malloc(sizeof(char) * (i + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		temp[i] = buffer[i];
		i ++;
	}
	if (buffer[i] && buffer[i] == '\n')
		temp[i++] = '\n';
	temp[i] = 0;
	return (temp);
}

char	*read_file(int fd, char *buffer, int bytes_read)
{
	char	*small_buff;

	small_buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!small_buff)
		return (NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, small_buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(small_buff);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		small_buff[bytes_read] = 0;
		buffer = ft_strjoin(buffer, small_buff);
		if (!buffer)
			return (NULL);
		if (ft_strchr(buffer))
			break ;
	}
	free(small_buff);
	return (buffer);
}
