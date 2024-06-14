/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:10:30 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/13 11:24:47 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_pt	**allocate_map(int *width, int height)
{
	int		i;
	int		j;
	t_pt	**map;

	i = 0;
	j = 0;
	map = malloc(height * sizeof(t_pt *));
	if (!map)
		return (NULL);
	while (i < height)
	{
		map[i] = malloc(width[i] * sizeof(t_pt));
		if (!map[i])
		{
			while (j < i)
			{
				free(map[j]);
				j++;
			}
			free(map);
			return (NULL);
		}
		i ++;
	}
	return (map);
}

int	get_map_dimensions(char *filename, int *width, int *height, char ***big_str)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	if (!line)
		return (-1);
	*height = 0;
	while (line)
	{
		(width)[*height] = map_width(line, big_str);
		*height += 1;
		free(line);
		line = get_next_line(fd);
	}
	if (*height > 1024)
		return (-1);
	free(line);
	close(fd);
	return (0);
}

char	*copy_map(int fd, t_map *map)
{
	int		i;
	char	*line;
	char	*big_string;

	i = 0;
	big_string = ft_calloc(1, 1);
	while (i < map->height)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			free(big_string);
			return (NULL);
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = ' ';
		big_string = ft_strjoin_free(big_string, line);
		free(line);
		i++;
	}
	return (big_string);
}

t_pt	**read_map_lines(char *filename, t_map *map, char **big_str)
{
	int		i;
	int		j;
	int		len;
	int		fd;

	i = 0;
	j = 0;
	len = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while (j < map->height)
	{
		len += (map->width[j]);
		j ++;
	}
	map->map = atoi_loop(big_str, map->width, map->height, &map->color_flag);
	close(fd);
	while (i < len)
	{
		free(big_str[i]);
		i ++;
	}
	free(big_str);
	return (map->map);
}

t_map	*read_map(char *filename)
{
	t_map	*map;
	int		height;
	char	**big_str;
	int		width[1024];

	initialize_array(width, 1024);
	big_str = ft_calloc(1, sizeof(char *));
	if (!big_str)
		return (NULL);
	if (get_map_dimensions(filename, width, &height, &big_str) < 0)
		return (return_null(NULL, big_str, 4));
	map = malloc(sizeof(t_map));
	if (!map)
		return (return_null(NULL, big_str, 3));
	map_init(map, height, width);
	if (!map->width)
		return (return_null(map, big_str, 1));
	map->map = read_map_lines(filename, map, big_str);
	if (!map->map)
		return (return_null(map, big_str, 2));
	return (map);
}
