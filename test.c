#include "fdf.h"

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

int	image_create(t_mlx_data *data)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			put_pixel_to_image(&data->img, x, y, 0x00000000);
		}
	}

	for (int k = WIDTH * 0.2; k < WIDTH * 0.8; k ++)
	{
		int j = HEIGHT * 0.8;
		/* for (int j = HEIGHT * 0.8; j > 0; j--)
		{
			if (HEIGHT - k == (j))
				put_pixel_to_image(&data->img, k, j, 0x00fff00);
		} */
		put_pixel_to_image(&data->img, k, j, 0x00fff00);
	}
	for (int j = HEIGHT * 0.8; j > HEIGHT * 0.2; j--)
	{
		for (int k = WIDTH * 0.8; k > WIDTH * 0.2; k --)
		{
			if (j == k)
				put_pixel_to_image(&data->img, j, k, 0x00fff00);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, data->offx, data->offy);
	return 0;
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
	image_create(data);
	return (0);
}

int	button_press(int button, int x, int y, t_mlx_data *data)
{
	if (button == 1)
		printf("Left mouse press at (%d, %d)\n", x, y);
	else if (button == 1)
		printf("Right mouse press at (%d, %d)\n", x, y);
	return (0);
}

int	main()
{
	t_mlx_data	data;
	t_map	*map;

	map = read_map("map.txt");
	if (!map)
	{
		printf("ERROR");
		return (0);
	}
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "FDF PRO");

	data.offx = 0;
	data.offy = 0;

	data.img.img_ptr = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.img.img_pixels_ptr = mlx_get_data_addr(data.img.img_ptr, &data.img.bits_per_pixel,
												&data.img.line_len, &data.img.endian);
	image_create(&data);
	mlx_key_hook(data.win_ptr, handle_input, &data);
	//mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, &button_press, &data);
	mlx_loop(data.mlx_ptr);
}
