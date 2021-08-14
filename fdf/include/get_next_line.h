#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>

int		get_next_line(int fd, char **line);
int		gnl_strlen(const char *s);
char	*gnl_strdup(const char *s1);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_substr(char const *s, int start, int len);
void	ft_substr_buf(char *s, int start, int len);
typedef struct s_list
{
	char	buf[32768];
	int		eof;
}			t_list;

#endif
