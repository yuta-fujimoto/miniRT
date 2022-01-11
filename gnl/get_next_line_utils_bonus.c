/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuta <fyuta@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:56:44 by fyuta             #+#    #+#             */
/*   Updated: 2022/01/10 12:31:12 by fyuta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s++))
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*ptr;
	int			i;
	size_t		slen1;
	size_t		slen2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	slen1 = ft_strlen(s1);
	slen2 = ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (slen1 + slen2 + 1));
	if (!ptr)
		return (0);
	i = 0;
	while (*s1)
		ptr[i++] = *(s1++);
	while (*s2)
		ptr[i++] = *(s2++);
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strdup(const char *src)
{
	char	*str;
	int		i;
	size_t	srclen;

	srclen = ft_strlen((char *)src);
	str = (char *)malloc(sizeof(char) * srclen + 1);
	if (!str)
		return (0);
	i = 0;
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*empty(void)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[0] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			slen;
	size_t			size;
	char			*ptr;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	i = -1;
	if (start >= (unsigned int)slen)
		return (empty());
	if (start + len >= slen)
		size = slen - start + 1;
	else
		size = len + 1;
	ptr = (char *)malloc(sizeof(char) * size);
	if (!ptr)
		return (NULL);
	while (++i < size - 1)
		ptr[i] = s[i + start];
	ptr[i] = 0;
	return (ptr);
}
