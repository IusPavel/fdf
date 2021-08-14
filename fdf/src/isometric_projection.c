#include "fdf.h"

static void	draw_isometric(t_init fdf, t_data img)
{
	t_point	*ptr;
	t_point	*start;

	ptr = fdf.map->prev;
	start = fdf.map;
	fdf.map = fdf.map->prev->prev;
	while (fdf.map != start->prev)
	{
		while (ptr != start)
		{
			if (fdf.map->axis == (ptr->axis) + 1
				&& fdf.map->ordinate == ptr->ordinate)
				draw_line(fdf, &img, *ptr, *fdf.map);
			else if (fdf.map->axis == ptr->axis
				&& fdf.map->ordinate == (ptr->ordinate) + 1)
			{
				draw_line(fdf, &img, *ptr, *fdf.map);
				break ;
			}
			ptr = ptr->next;
		}
		fdf.map = fdf.map->prev;
		ptr = fdf.map->next;
	}
}

static void	fill_isometric(t_point *map, t_align al)
{
	int		first_x;
	int		first_y;
	t_point	*ptr;

	first_x = al.start_x;
	first_y = al.start_y;
	ptr = map->prev;
	while (1)
	{
		if (ptr->axis == 0)
		{
			al.start_x = first_x;
			al.start_y = first_y;
			first_x += al.step;
			first_y += lround(al.step * tan(M_PI / 6));
		}
		ptr->x = al.start_x;
		ptr->y = al.start_y - ptr->altitude * al.alt_step;
		al.start_x += al.step;
		al.start_y -= lround(al.step * tan(M_PI / 6));
		ptr = ptr->prev;
		if (ptr == map->prev)
			break ;
	}
}

void	isometric_projection(t_init fdf, t_align al)
{
	t_data	img;

	al.step = 40;
	while (al.step * (al.col + al.row) > fdf.width * .60f && al.step != 2)
		al.step--;
	al.alt_step = al.step / 2;
	if (al.alt_step * al.alt > fdf.height / 4)
		al.alt_step = (fdf.height - 2) / 4 / al.alt;
	if (al.alt_step == 0)
		al.alt_step = 1;
	al.start_x = fdf.width / 2 - al.step * ((al.col + al.row) / 2);
	al.start_y = fdf.height / 2
		+ al.step * tan(M_PI / 6) * (al.col - al.row) / 2;
	img.img_ptr = mlx_new_image(fdf.mlx_ptr, fdf.width, fdf.height);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	fill_isometric(fdf.map, al);
	draw_isometric(fdf, img);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, img.img_ptr, 0, 0);
}
