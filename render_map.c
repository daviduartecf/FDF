#include "fdf.h"
#include <math.h>

t_point project_isometric(int x, int y, int z, t_mlx_data *data) {
	t_point point;
	point.x = ((x - y) * cos(M_PI / 6)) + (WIDTH - (data->width) * 10)/2; // 30 degrees
	point.y = ((x + y) * sin(M_PI / 6) - z) + (HEIGHT - (data->height * 10))/2;
	//point.x = x + (WIDTH - (data->width) * 10)/2;
	//point.y = y + (HEIGHT - (data->height * 10))/2;
	return point;
}

void put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char *pixel;
	int pixel_index;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;

	pixel_index = (y * img->line_len) + (x * (img->bits_per_pixel / 8));
	pixel = img->img_pixels_ptr + pixel_index;
	*(unsigned int*)pixel = color;
}

void	draw_line(t_mlx_data *data, int x0, int y0, int x1, int y1)
{
	int sx, sy, dx, dy, e, e2;

	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	e = dx - dy;

	while (1)
	{
		//put_pixel_to_image(&data->img, x0, y0, 0xfffff00);
		put_pixel_to_image(&data->img, x0, y0, 0xfffff00);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * e;
		if (e2 > -dy)
		{
			e -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			e += dx;
			y0 += sy;
		}
	}
}

void	draw_map(t_mlx_data *data, t_map *map)
{
	int	x = 0;
	int	y = 0;
	int	j, xe = 0, ye = 0, n = 0;
	t_point start, end;

	for (int i = 0; i < (((map->height) * 10)); i += 10)
	{
		xe = 0;
		for (j = 0; j < (((map->width) * 10)); j += 10)
		{
			if (j + 10 < (((map->width) * 10)))
			{
				start = project_isometric(j, i, map->map[ye][xe], data);
				end = project_isometric(j + 10, i, map->map[ye][xe + 1], data);
				draw_line(data, start.x, start.y, end.x, end.y);
			}
			if (i  + 10 < (((map->height) * 10)))
			{
				start = project_isometric(j, i, map->map[ye][xe], data);
				end = project_isometric(j, i + 10, map->map[ye + 1][xe], data);
				draw_line(data, start.x, start.y, end.x, end.y);
			}
			xe ++;
		}
		ye ++;
	}
	draw_line(data, 0, 0, WIDTH, 0);
	draw_line(data, 0, HEIGHT, 0, 0);
	draw_line(data, 0, HEIGHT - 1, WIDTH, HEIGHT - 1);
	draw_line(data, WIDTH - 1, HEIGHT, WIDTH - 1, 0);
	draw_line(data, 0, 0, WIDTH, HEIGHT);
	draw_line(data, WIDTH, 0, 0, HEIGHT);
	//mlx_string_put(data->mlx_ptr, data->win_ptr, HEIGHT/2, WIDTH/2, 0xfffff00, "FUCK OFOOOFOFOFFMATE");
	// IMPORTANTE mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, data->offx, data->offy);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, data->offx, data->offy);
}

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_w)
		data->offy -= 10;
	else if (keysym == XK_s)
		data->offy += 10;
	else if (keysym == XK_a)
		data->offx -= 10;
	else if (keysym == XK_d)
		data->offx += 10;
	else if (keysym == XK_Escape)
	{
		printf("Key %d ESQ has been pressed\n\n", keysym);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	printf("Key %d has been pressed\n\n", keysym);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, data->offx, data->offy);
	return (0);
}

int	main()
{
	t_mlx_data	data;
	t_map	*map;

	map = read_map("map2.txt");
	if (!map)
	{
		printf("ERROR");
		return (0);
	}
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "FDF PRO");

	data.height = map->height;
	data.width = map->width;
	/* data.offx = (WIDTH - (map->width * 10))/2;
	data.offy = (HEIGHT - (map->height * 10))/2; */
	data.offx = 0;
	data.offy = 0;

	data.img.img_ptr = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.img.img_pixels_ptr = mlx_get_data_addr(data.img.img_ptr, &data.img.bits_per_pixel,
												&data.img.line_len, &data.img.endian);
	draw_map(&data, map);
	mlx_key_hook(data.win_ptr, handle_input, &data);
	//mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, &button_press, &data);
	mlx_loop(data.mlx_ptr);
}
