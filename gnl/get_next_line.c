#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 50
#endif

int	ft_free(char **f)
{
	if (*f)
		free(*f);
	*f = NULL;
	return (-1);
}

int	by_stock(char **stock, char **line)
{
	ssize_t	nl;
	char	*tmp;
	size_t	stock_len;

	if (!(*stock))
		return (-42);
	nl = gnl_strchr(*stock, '\n');
	if (nl != -1)
	{
		*line = ft_subnstr(*stock, 0, nl);
		if (!(*line))
			return (ft_free(stock));
		stock_len = gnl_strlen(*stock) - 1 - nl;
		if (stock_len == 0)
			return (-1 * ft_free(stock));
		tmp = *stock;
		*stock = ft_subnstr(*stock, nl + 1, stock_len);
		free(tmp);
		if (!(*stock))
			return (ft_free(line));
		return (1);
	}
	*line = *stock;
	*stock = NULL;
	return (42);
}

int	prepare_mem(int sign, char **line, char **buff)
{
	if (sign == -1 || sign == 1)
	{
		*buff = NULL;
		return (sign);
	}
	if (sign == -42)
	{
		*buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(*buff))
			return (-1);
		*line = (char *)malloc(sizeof(char) * 1);
		if (!(*line))
			return (ft_free(buff));
		(*line)[0] = '\0';
		sign = 42;
	}
	else if (sign == 42)
	{
		*buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(*buff))
			return (ft_free(line));
	}
	return (sign);
}

ssize_t	by_buff(char **buff, char **line, char **stock, ssize_t	nl)
{
	char	*tmp;
	size_t	stock_len;

	if (nl != -1)
	{
		tmp = *line;
		*line = ft_strnjoin(*line, *buff, nl);
		free(tmp);
		if (!(*line))
			return (-1);
		stock_len = gnl_strlen(*buff) - 1 - nl;
		if (stock_len > 0)
		{
			*stock = ft_strnjoin(0, *buff + nl + 1, stock_len);
			if (!(*stock))
				return (ft_free(line));
		}
		return (1);
	}
	tmp = *line;
	*line = ft_strnjoin(*line, *buff, gnl_strlen(*buff));
	free(tmp);
	if (!(*line))
		return (-1);
	return (42);
}

int	get_next_line(int fd, char **line)
{
	char		*buff;
	ssize_t		rc;
	static char	*stock;
	int			sign;

	if (!line || fd < 0)
		return (ft_free(&stock));
	sign = by_stock(&stock, line);
	sign = prepare_mem(sign, line, &buff);
	while (sign == 42)
	{
		rc = read(fd, buff, BUFFER_SIZE);
		if (rc == -1)
			sign = ft_free(line);
		else if (rc == 0)
			sign = 0;
		else
		{
			buff[rc] = '\0';
			sign = by_buff(&buff, line, &stock, gnl_strchr(buff, '\n'));
		}
	}
	free(buff);
	return (sign);
}
