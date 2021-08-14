#include "fdf.h"

static void	loop_draw_line(t_draw *var, t_point *a)
{
	var->e2 = 2 * var->err;
	if (var->e2 >= var->dy)
	{
		var->err += var->dy;
		a->x += var->sx;
	}
	if (var->e2 <= var->dx)
	{
		var->err += var->dx;
		a->y += var->sy;
	}
}

int	regulator(t_point a, t_point b)
{
	int	divider;

	divider = abs(b.x - a.x);
	if (abs(b.y - a.y) > divider)
		divider = abs(b.y - a.y);
	if (divider == 0)
		divider = 1;
	a.color += (get_r(a, b) / divider << 16) + (get_g(a, b) / divider << 8)
		+ get_b(a, b) / divider;
	return (a.color);
}

void	draw_line(t_init fdf, t_data *img, t_point a, t_point b)
{
	t_draw	var;

	var.dx = abs(b.x - a.x);
	var.sx = -1;
	if (a.x < b.x)
		var.sx = 1;
	var.dy = -abs(b.y - a.y);
	var.sy = -1;
	if (a.y < b.y)
		var.sy = 1;
	var.err = var.dx + var.dy;
	while (1)
	{
		a.color = regulator(a, b);
		if (a.x >= 0 && a.x < fdf.width && a.y >= 0 && a.y < fdf.height)
			my_mlx_pixel_put(img, a.x, a.y, a.color);
		if (a.x == b.x && a.y == b.y)
			break ;
		loop_draw_line(&var, &a);
	}
}
