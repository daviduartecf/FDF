#include "fdf.h"

int **allocate_map(int width, int height)
{
	int	**map;
	int	i;
	int	j;

	i = 0;
	j = 0;
	map = malloc(height * sizeof(int *));
	if (!map)
		return (NULL);
	while (i < height)
	{
		map[i] = malloc(width * sizeof(int));
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
	return map;
}

int	ft_atoi(char *str)
{
	int	i;
	int	neg;
	int	number;

	i = 0;
	neg = 1;
	number = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i ++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i ++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i ++;
	}
	return (number * neg);
}

int	ft_strncmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s1) && (s1[i] || s2[i]))
	{
		if (((unsigned char)s1[i] != (unsigned char)s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i ++;
	}
	return (0);
}

int	**atoi_loop(char **strings, int width, int height)
{
	int 	i;
	int 	j;
	int	k;
	int	**map;

	i = 0;
	j = 0;
	k = 0;
	map = allocate_map(width, height);
	while (i < height - 1)
	{
		k = 0;
		while (k < width)
		{
			map[i][k] = ft_atoi(strings[j]);
			k ++;
			j ++;
		}
		i ++;
	}
	return (map);
}

int	get_map_dimensions(char *filename, int *width, int *height)
{
	int	fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	if (!line)
		return (0);
	*width = (ft_strlen(line)/2); // \n char doesnt count
	*height = 0;
	while (line)
	{
		*height += 1;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}

void free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (i < map->height)
		{
			free(map->map[i]);
			i ++;
		}
		free(map->map);
		free(map);
	}
}

int	**read_map_lines(char *filename, t_map *map)
{
	int	fd;
	int	i;
	int	j;
	char	*line;
	char	*big_string;
	char	**split_res;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	big_string = ft_calloc(1, 1);
	while (i < map->height)
	{
		j = 0;
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			return(NULL);
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = ' ';
		big_string = ft_strjoin(big_string, line);
		free(line);
		i++;
	}
	split_res = ft_split(big_string, ' ');
	map->map = atoi_loop(split_res, map->width, map->height);
	close(fd);
	return (map->map);
}

t_map	*read_map(char *filename)
{
	int	height;
	int	width;
	t_map	*map;

	if (get_map_dimensions(filename, &width, &height) < 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->height = height;
	map->width = width;
	//map->map = allocate_map(width, height);
	//if (!map->map)
	//	return (NULL);
	map->map = read_map_lines(filename, map);
	if (!map->map)
		return (NULL);
	/* if (read_map_lines(filename, map) < 0)
	{
		free_map(map);
		return (NULL);
	} */
	return (map);
}

/* int main()
{
	int	i = 0, j;
	t_map *map;

	map = read_map("map.txt");
	if (!map)
	{
		printf("ERROR");
		return (0);
	}
	printf("Width: %d\n", map->width);
	printf("Height: %d\n", map->height);
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			printf("| %d |", map->map[i][j]);
			j ++;
		}
		printf("\n");
		i ++;
	}
}
 */
