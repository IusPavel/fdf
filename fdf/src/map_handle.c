#include "fdf.h"
#include "get_next_line.h"
#include "libft.h"

static unsigned int	ft_hextoi(char *str)
{
	int		i;
	int		power;
	size_t	result;

	power = 0;
	result = 0;
	i = ft_strlen(str) - 1;
	while (str[i] != 'x' && str[i] != 'X')
	{
		if (str[i] >= 'A' && str[i] <= 'F')
			result += (str[i] - 55) * pow(16, power);
		else if (str[i] >= 'a' && str[i] <= 'f')
			result += (str[i] - 87) * pow(16, power);
		else if (str[i] >= '0' && str[i] <= '9')
			result += (str[i] - 48) * pow(16, power);
		else
			close_program("Are you kidding me? Explosion!");
		power++;
		i--;
	}
	return ((unsigned int)result);
}

static t_point	*list_new_element(char *argument, int axis, int ordinate)
{
	t_point	*new;

	new = (t_point *)ft_calloc(1, sizeof(t_point));
	new->axis = axis;
	new->ordinate = ordinate;
	new->altitude = ft_atoi(argument);
	argument = ft_strchr(argument, ',');
	if (argument != 0)
		new->color = ft_hextoi(argument + 1);
	else
		new->color = 0xFFFFFF;
	new->prev = new;
	new->next = new;
	return (new);
}

static void	list_fill(t_point **begin, char *argument,
						int axis, int ordinate)
{
	t_point	*new;

	if (*begin != 0)
	{
		new = list_new_element(argument, axis, ordinate);
		new->next = *begin;
		new->prev = (*begin)->prev;
		(*begin)->prev->next = new;
		(*begin)->prev = new;
		*begin = new;
	}
	else
		*begin = list_new_element(argument, axis, ordinate);
}

static void	line_handle(char *line, t_point **begin)
{
	int			axis;
	static int	ordinate = 0;
	char		**splitted;

	splitted = ft_split(line, ' ');
	axis = 0;
	while (splitted[axis] != NULL)
	{
		list_fill(begin, splitted[axis], axis, ordinate);
		free(splitted[axis]);
		axis++;
	}
	free(splitted);
	ordinate++;
}

void	map_handle(char *map, t_point **begin)
{
	int		eof;
	int		fd;
	char	*line;

	*begin = 0;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		close_program("Your bad behavior will be reported");
	while (1)
	{
		eof = get_next_line(fd, &line);
		if (eof >= 0)
		{
			line_handle(line, begin);
			free(line);
		}
		if (eof == 0)
			break ;
		if (eof == -1)
			close_program("Something got wrong");
	}
}
