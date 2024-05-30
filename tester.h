#ifndef TESTER_H
# define TESTER_H

t_map	*read_map(char *filename);
int	**read_map_lines(char *filename, t_map *map);
char	*copy_map(int fd, t_map *map);
void free_map(t_map *map);
int	get_map_dimensions(char *filename, int *width, int *height);
int	map_width(char *line);
int	**atoi_loop(char **strings, int width, int height);
int	ft_strncmp(char *s1, char *s2);
int	ft_atoi(char *str);
int **allocate_map(int width, int height);

#endif
