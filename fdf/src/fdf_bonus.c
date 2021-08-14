#include "fdf_bonus.h"
#include "libft.h"
#include "get_next_line.h"

static void	text_map(t_init fdf, char *name)
{
	if (name != 0)
	{
		mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, 10, 0xFFFFFF, "map: ");
		mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 55, 10, 0xFFFFFF, name);
	}
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, 40, 0xFFFFFF,
		"press scroll: change projection (isometric, plan, parallel)");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, 60, 0xFFFFFF,
		"spin scroll: zoom in/out");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, 80, 0xFFFFFF,
		"ESC: close program");
}

static int	key_hook(int key, t_init *fdf)
{
	if (key == 53)
	{
		write(1, "Thank you for watching!\n", 24);
		exit (EXIT_SUCCESS);
	}
	text_map(*fdf, 0);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_init *fdf)
{
	static int	proj;
	static int	zoom1;

	(void)x, (void)y;
	if (button == 3)
	{
		proj++;
		zoom1 = 0;
		if (proj == 3)
			proj = 0;
	}
	else if (button == 4)
		zoom1 -= 5;
	else if (button == 5)
		zoom1 += 5;
	if (zoom1 < -40)
		zoom1 = -40;
	show_projection(fdf, proj, zoom1);
	text_map(*fdf, 0);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(int argc, char **argv)
{
	t_init	fdf;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: give as first parameter map *.fdf", 1);
		return (0);
	}
	map_handle(argv[1], &fdf.map);
	count_align(fdf.map, &fdf.al);
	fdf.width = 2560;
	fdf.height = 1440;
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, fdf.width, fdf.height, "FdF");
	fdf.img.img_ptr = mlx_new_image(fdf.mlx_ptr, fdf.width, fdf.height);
	fdf.img.addr = mlx_get_data_addr(fdf.img.img_ptr, &fdf.img.bits_per_pixel,
			&fdf.img.line_length, &fdf.img.endian);
	text_map(fdf, argv[1]);
	mlx_key_hook(fdf.win_ptr, key_hook, &fdf);
	mlx_hook(fdf.win_ptr, 04, 1L << 2, mouse_hook, &fdf);
	mlx_loop(fdf.mlx_ptr);
}
