/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuta <fyuta@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:42:51 by fyuta             #+#    #+#             */
/*   Updated: 2022/01/13 19:46:29 by fyuta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_overflow(unsigned long num,
	int sign, long max)
{
	if (0 < num && ((sign == 1 && (unsigned long)max < num)
			|| (sign == -1 && (unsigned long)max < num - 1)))
		return (true);
	return (false);
}

static size_t	pass_isspace(const char *str, size_t i)
{
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	return (i);
}

bool	ft_atoi(const char *str, int *rlt)
{
	size_t			i;
	unsigned int	num;
	int				sign;

	i = 0;
	num = 0;
	sign = 1;
	i = pass_isspace(str, i);
	if (str[i] == '+')
		i++;
	else if (str[i] == '-' && ++i)
		sign = -1;
	while (str[i] && ('0' <= str[i] && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		if (is_overflow(num, sign, INT_MAX))
			break ;
		i++;
	}
	*rlt = (int)num * sign;
	i = pass_isspace(str, i);
	if (i == 0 || str[i] != '\0')
		return (false);
	return (true);
}
