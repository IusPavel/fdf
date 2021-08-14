#include "fdf.h"

void	close_program(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

int	get_r(t_point a, t_point b)
{
	return ((b.color >> 16 & 0xFF) - (a.color >> 16 & 0xFF));
}

int	get_g(t_point a, t_point b)
{
	return ((b.color >> 8 & 0xFF) - (a.color >> 8 & 0xFF));
}

int	get_b(t_point a, t_point b)
{
	return ((b.color & 0xFF) - (a.color & 0xFF));
}
