/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuta <fyuta@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:19:24 by fyuta             #+#    #+#             */
/*   Updated: 2021/04/27 19:04:57 by fyuta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	copy_memo(char **memo, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*memo)[i] != '\0')
	{
		if ((*memo)[i] == '\n')
			break ;
		i++;
	}
	if ((*memo)[i] != '\n')
		return (0);
	*line = ft_substr(*memo, 0, i);
	tmp = ft_substr(*memo, i + 1, ft_strlen(*memo));
	free(*memo);
	*memo = tmp;
	return (1);
}

int	process_after_reading(char **memo, char **line, int size)
{
	if (size < 0)
		return (-1);
	if (!(*memo))
	{
		*line = ft_strdup("");
		return (0);
	}
	if (copy_memo(memo, line))
		return (1);
	*line = *memo;
	*memo = NULL;
	return (0);
}

int	initial_process(int fd, char **buff, char **line)
{
	if (fd < 0 || MAXFD <= fd || !line)
		return (0);
	*buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*memory[MAXFD];
	char		*buff;
	char		*tmp;
	ssize_t		size;

	if (!initial_process(fd, &buff, line))
		return (-1);
	size = read(fd, buff, BUFFER_SIZE);
	while (size > 0)
	{
		buff[size] = '\0';
		tmp = memory[fd];
		memory[fd] = ft_strjoin(memory[fd], buff);
		free(tmp);
		if (copy_memo(&memory[fd], line))
		{
			free(buff);
			return (1);
		}
		size = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (process_after_reading(&memory[fd], line, size));
}
