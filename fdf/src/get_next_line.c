#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>

/* This function search for matches inside buffer */
int	estimator(char **line, char *buf, size_t is_read)
{
	size_t	pnt;

	pnt = 0;
	while (pnt < is_read)
	{
		if (buf[pnt] == '\n')
		{
			*line = gnl_strjoin(*line, gnl_substr(buf, 0, pnt));
			ft_substr_buf(buf, pnt + 1, is_read - pnt - 1);
			return (1);
		}
		pnt++;
	}
	*line = gnl_strjoin(*line, gnl_substr(buf, 0, pnt));
	ft_substr_buf(buf, pnt + 1, is_read - pnt - 1);
	return (0);
}

/* Auxiliary function. Always returns zero. If (line) is NULL, line[0] = 0 */
static int	empty_buffer(char **line)
{
	if (!(*line))
	{
		*line = (char *)malloc(sizeof(char));
		*line[0] = 0;
	}
	return (0);
}

/* Major function. Returns value eof or not */
int	get_next_line(int fd, char **line)
{
	static t_list	lst;
	ssize_t			is_read;

	if (fd < 0 || fd > 256)
		return (-1);
	*line = 0;
	if (gnl_strlen(lst.buf) > 0)
	{
		if (estimator(line, lst.buf, gnl_strlen(lst.buf)))
			return (1);
		if (lst.eof == 1)
			return (0);
	}
	while (1)
	{
		is_read = read(fd, lst.buf, 32768);
		if (is_read < 0)
			return (-1);
		if (is_read < 32768)
			lst.eof = 1;
		if (is_read == 0)
			return (empty_buffer(line));
		if (estimator(line, lst.buf, is_read))
			return (1);
	}
}
