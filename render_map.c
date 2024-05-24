#include "fdf.h"
#include <math.h>
#include <limits.h>

void rotate_x(t_point *p, double angle)
{
	int tmp_y = p->y;
	p->y = (int)(tmp_y * cos(angle) - p->z * sin(angle));
	p->z = (int)(tmp_y * sin(angle) + p->z * cos(angle));
}

void rotate_y(t_point *p, double angle)
{
	int tmp_x = p->x;
	p->x = (int)(tmp_x * cos(angle) + p->z * sin(angle));
	p->z = (int)(-tmp_x * sin(angle) + p->z * cos(angle));
}

void rotate_z(t_point *p, double angle)
{
	int tmp_x = p->x;
	p->x = (int)(tmp_x * cos(angle) - p->y * sin(angle));
	p->y = (int)(tmp_x * sin(angle) + p->y * cos(angle));
}

t_point project_point(int x, int y, int z, t_mlx_data *data)
{
	t_point point = {x, y, z};

	double angle_x = data->angle_x * M_PI / 180;
	double angle_y = data->angle_y * M_PI / 180;
	double angle_z = data->angle_z * M_PI / 180;

	// Apply rotations
	rotate_x(&point, angle_x);
	rotate_y(&point, angle_y);
	rotate_z(&point, angle_z);

	point.x += data->offx;
	point.y += data->offy;

	return point;
}

/* t_point project_isometric(int x, int y, int z, t_mlx_data *data)
{
	t_point point;
	double angle;

	angle = data->degrees * M_PI / 180; //calculate the angle

	//WORKING!!!
	//point.x = ((x - y) * cos(angle) + z * sin(angle)) + data->offx;
	//point.y = ((x + y) * sin(angle) - z * cos(angle)) + data->offy;

	//Z AXIS ROTATION
	//point.x = x * cos(angle) - y * sin(angle) + data->offx;
	//point.y = x * sin(angle) + y * cos(angle) + data->offy;

	//Y AXIS ROTATION!
	// point.x = (int)(x * cos(angle) + z * sin(angle)) + data->offx;
	// point.y = y + data->offy;

	//X AXIS ROTATION
	//point.y = (int)(y * cos(angle) + z * sin(angle)) + data->offy;
	//point.x = x + data->offx;

	return point;
} */

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

void calculate_boundries(t_map *map, int *min_x, int *max_x, int *min_y, int *max_y, t_mlx_data *data)
{
	t_point point;
	int	x;
	int	y;

	*min_x = INT_MAX;
	*max_x = INT_MIN;
	*min_y = INT_MAX;
	*max_y = INT_MIN;
	x = 0;
	y = 0;

	for (int i = 0; i < map->height * 15; i += 15)
	{
		for (int j = 0; j < map->width * 15; j += 15)
		{
			x = 0;
			point = project_point(j, i, map->map[y][x], data);

			if (point.x > *max_x) *max_x = point.x;
			if (point.y > *max_y) *max_y = point.y;
			if (point.x < *min_x) *min_x = point.x;
			if (point.y < *min_y) *min_y = point.y;
			x++;
		}
		y++;
	}
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

void draw_grid(t_mlx_data *data)
{
	draw_line(data, WIDTH/2, 0, WIDTH/2, HEIGHT);
	draw_line(data, 0, HEIGHT/2, WIDTH, HEIGHT/2);
	draw_line(data, WIDTH, 0, 0, HEIGHT);
}

void	draw_map(t_mlx_data *data, t_map *map)
{
	int	x = 0;
	int	y = 0;
	int	j, xe = 0, ye = 0, n = 0;
	int	max_x, max_y, min_x, min_y;
	t_point start, end;

	//calculate offset based on dimensions of rotated grid
	calculate_boundries(map, &min_x, &max_x, &min_y, &max_y, data);
	data->offx = (WIDTH - (max_x - min_x))/2 - min_x;
	data->offy = (HEIGHT - (max_y - min_y))/2 - min_y;

	for (int i = 0; i < (((map->height) * 15)); i += 15)
	{
		xe = 0;
		for (j = 0; j < (((map->width) * 15)); j += 15)
		{
			if (j + 15 < (((map->width) * 15)))
			{
				t_point p0 = project_point(j, i, map->map[ye][xe], data);
				t_point p1 = project_point(j + 15, i, map->map[ye][xe + 1], data);
				draw_line(data, p0.x, p0.y, p1.x, p1.y);
			}
			if (i  + 15 < (((map->height) * 15)))
			{
				t_point p0 = project_point(j, i, map->map[ye][xe], data);
				t_point p2 = project_point(j, i + 15, map->map[ye + 1][xe], data);
				draw_line(data, p0.x, p0.y, p2.x, p2.y);
			}
			xe ++;
		}
		ye ++;
	}
	data->offx = 0;
	data->offy = 0;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, data->offx, data->offy);
}

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_w)
		data->angle_x += 5;
	else if (keysym == XK_s)
		data->angle_x -= 5;
	else if (keysym == XK_d)
		data->angle_y += 5;
	else if (keysym == XK_a)
		data->angle_y -= 5;
	else if (keysym == XK_q)
		data->angle_z += 5;
	else if (keysym == XK_e)
		data->angle_z -= 5;
	else if (keysym == XK_Escape)
	{
		printf("Key %d ESQ has been pressed\n\n", keysym);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	printf("Key %d has been pressed\n\n", keysym);
	printf("Degree:%f \n\n", data->degrees);
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.img_pixels_ptr = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel,
												&data->img.line_len, &data->img.endian);
	draw_map(data, data->map);
	draw_grid(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, data->offx, data->offy);
	return (0);
}

int	handle_mouse_press(int button, int x, int y, t_mlx_data *data)
{
	if (button == 1) { // Left mouse button
		data->is_dragging = 1;
		data->last_x = x;
		data->last_y = y;
	}
	return 0;
}

int	handle_mouse_release(int button, int x, int y, t_mlx_data *data)
{
	if (button == 1)
		data->is_dragging = 0;
	return (0);
}

int	handle_mouse_move(int x, int y, t_mlx_data *data)
{
	int	dx;
	int	dy;
	if (data->is_dragging)
	{
		dx = x - data->last_x;
		dy = y - data->last_y;
		data->angle_x += dx * 0.07;
		data->angle_y += dy * 0.07;
		data->angle_z += (dx + dy) * 0.07;
		data->last_x = x;
		data->last_y = y;


		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
		data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
		data->img.img_pixels_ptr = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel,
												&data->img.line_len, &data->img.endian);
		draw_map(data, data->map);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	}
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
	data.map = map;
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "FDF PRO");

	data.height = map->height;
	data.width = map->width;
	data.offx = 0;
	data.offy = 0;
	data.angle_x = 0;
	data.angle_y = 0;
	data.angle_z = 0;
	data.is_dragging = 0;

	data.img.img_ptr = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.img.img_pixels_ptr = mlx_get_data_addr(data.img.img_ptr, &data.img.bits_per_pixel,
												&data.img.line_len, &data.img.endian);
	draw_map(&data, map);
	mlx_key_hook(data.win_ptr, handle_input, &data);
	mlx_hook(data.win_ptr, 4, 1L << 2, handle_mouse_press, &data); // ButtonPress
	mlx_hook(data.win_ptr, 5, 1L << 3, handle_mouse_release, &data); // ButtonRelease
	mlx_hook(data.win_ptr, 6, 1L << 6, handle_mouse_move, &data); // PointerMotion
	//mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, &button_press, &data);
	mlx_loop(data.mlx_ptr);
}
