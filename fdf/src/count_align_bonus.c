#include "fdf_bonus.h"

void	count_align(t_point *map, t_align *al)
{
	t_point	*ptr;

	al->col = map->axis;
	al->row = map->ordinate;
	al->alt = abs(map->altitude);
	ptr = map->next;
	while (ptr != map)
	{
		if (ptr->axis > al->col)
			al->col = ptr->axis;
		if (ptr->ordinate > al->row)
			al->row = ptr->ordinate;
		if (abs(ptr->altitude) > al->alt)
			al->alt = abs(ptr->altitude);
		ptr = ptr->next;
	}
}
