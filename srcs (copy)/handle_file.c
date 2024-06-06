#include "../includes/fdf.h"
#include "../tester.h"

t_pt **allocate_map(int *width, int height)
{
	t_pt	**map;
	int	i;
	int	j;

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
	return map;
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i ++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

int	get_digit(char c)
{
	int	i;

	if (c >= 'A' && c <= 'Z')
		c += 32;
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (10 + c - 'a');
	else
		return (-1);
}

int	ft_atoibase_fdf(char *str)
{
	int	i;
	int	result;

	i = 1;
	result = 0;
	printf("string: %s\n", str);
	while (get_digit(str[i]) >= 0 && str[i])
	{
		result = result * 16;
		result = result + get_digit(str[i]);
		i ++;
	}
	printf("result: %d\n", result);
	return (result);
}

void	get_altitude_and_color(char *str, t_pt *point, int *color_flag)
{
	char	*color;

	color = ft_strchr(str, 'x');
	point->z = ft_atoi(str);
	if (color)
	{
		point->color = ft_atoibase_fdf(color);
		*color_flag = 1;
	}
	else
		point->color = 0xFFFFFF;
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

t_pt	**atoi_loop(char **strings, int *width, int height, int *color_flag)
{
	int 	i;
	int 	j;
	int	k;
	t_pt	**map;

	i = 0;
	j = 0;
	k = 0;
	map = allocate_map(width, height);
	while (i < height)
	{
		k = 0;
		while (k < width[i] && strings[j])
		{
			//map[i][k].color = 0xFFFFFF;
			//map[i][k].z = ft_atoi(strings[j]);
			get_altitude_and_color(strings[j], &map[i][k], color_flag);
			printf("ATOI line %d ---\n", k);
			k ++;
			j ++;
		}
		i ++;
	}
	return (map);
}

int	map_width(char *line)
{
	int	line_width;
	int	result;
	char	**split_result;

	line_width = 0;
	split_result = ft_split(line, ' ');
	if (!split_result)
		return (0);
	while (split_result[line_width] && split_result[line_width][0] != '\n')
		line_width ++;
	result = line_width;
	while (line_width >= 0)
	{
		free(split_result[line_width]);
		line_width --;
	}
	free(split_result);
	return (result);
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

int	get_max_value(int *width, int height)
{
	int	i;
	int	max;

	i = 0;
	max = INT_MIN;
	while (i < height)
	{
		if (width[i] > max)
			max = width[i];
		i ++;
	}
	return (max);
}

int	get_map_dimensions(char *filename, int *width, int *height, int max_width)
{
	int	fd;
	int	false_height;
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
		(width)[*height] = map_width(line);
		*height += 1;
		free(line);
		printf("Line %d read---\n", *height);
		line = get_next_line(fd);
	}
	max_width = get_max_value(width, *height);
	printf("Got max width---\n");
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

char	*copy_map(int fd, t_map *map)
{
	int	i;
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
			return(NULL);
		}
		/* if (map_width(line) != map->width[0])
		{
			printf("MAP WIDTH IS NOT THE SAME IN EVERY LINE\n");
			free(line);
			free(big_string);
			return (NULL);
		} */
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = ' ';
		big_string = ft_strjoin(big_string, line);
		printf("Copy map line %d read---\n", i);
		free(line);
		i++;
	}
	return (big_string);
}

t_pt	**read_map_lines(char *filename, t_map *map)
{
	int	fd;
	int	i;
	char	*line;
	char	*big_string;
	char	**split_res;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	big_string = copy_map(fd, map);
	if (!big_string)
		return (NULL);
	printf("ended copy map ---\n");
	split_res = ft_split(big_string, ' ');
	printf("ended split map ---\n");
	map->map = atoi_loop(split_res, map->width, map->height, &map->color_flag);
	close(fd);
	free(big_string);
	while (i < map->height)
	{
		free(split_res[i]);
		i ++;
	}
	free(split_res);
	printf("int: %d\n", map->height);
	return (map->map);
}

t_map	*read_map(char *filename)
{
	int height;
	int	width[1024];
	int	max_width;
	t_map	*map;

	max_width = 0;
	if (get_map_dimensions(filename, width, &height, max_width) < 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->max_width = max_width;
	map->color_flag = 0;
	map->height = height;
	map->width = width;
	//map->map = allocate_map(width, height);
	//if (!map->map)
	//	return (NULL);
	map->map = read_map_lines(filename, map);
	if (!map->map)
		return (NULL);
	printf("ENDED\n");
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

	map = read_map("my_maps/2x2map.txt");
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
} */
