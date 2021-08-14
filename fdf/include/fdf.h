#ifndef FDF_H
# define FDF_H

/* open - fcntl.h; read/write - unistd.h; malloc/free - stdlib.h;
   perror - stdio.h */
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "mlx.h"

typedef struct s_data
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;
typedef struct s_point
{
	int				axis;
	int				ordinate;
	int				altitude;
	int				x;
	int				y;
	unsigned int	color;
	struct s_point	*prev;
	struct s_point	*next;
}	t_point;
typedef struct s_init
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
	t_point	*map;
}			t_init;
typedef struct s_align
{
	int	col;
	int	row;
	int	alt;
	int	start_x;
	int	start_y;
	int	step;
	int	alt_step;
}		t_align;
typedef struct s_draw
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;
}		t_draw;
void	close_program(char *message);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_line(t_init fdf, t_data *img, t_point a, t_point b);
void	map_handle(char *map, t_point **begin);
void	count_align(t_point *map, t_align *al);
void	isometric_projection(t_init fdf, t_align al);
int		get_r(t_point a, t_point b);
int		get_g(t_point a, t_point b);
int		get_b(t_point a, t_point b);

#endif
