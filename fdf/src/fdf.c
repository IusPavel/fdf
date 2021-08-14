#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"

int	key_hook(int key, void *param)
{
	(void)param;
	if (key == 53)
	{
		write(1, "Thank you for watching!\n", 24);
		exit (EXIT_SUCCESS);
	}
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
	t_align	al;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: give as 1st parameter map *.fdf and no more", 1);
		return (0);
	}
	map_handle(argv[1], &fdf.map);
	count_align(fdf.map, &al);
	fdf.width = 2560;
	fdf.height = 1440;
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, fdf.width, fdf.height, "FdF");
	isometric_projection(fdf, al);
	mlx_key_hook(fdf.win_ptr, key_hook, (void *)0);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
