#include "fdf_bonus.h"

void	draw_plan(t_init fdf, t_data img)
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

void	fill_plan(t_point *map, t_align al)
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
			first_y += al.step;
		}
		ptr->x = al.start_x;
		ptr->y = al.start_y - ptr->altitude * al.alt_step;
		al.start_x += al.step;
		al.start_y -= al.step;
		ptr = ptr->prev;
		if (ptr == map->prev)
			break ;
	}
}
