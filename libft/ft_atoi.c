/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuta <fyuta@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:42:51 by fyuta             #+#    #+#             */
/*   Updated: 2022/01/09 13:27:13 by fyuta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool ft_atoi(const char *nptr, int *rlt)
{
	int	i;
	int	minus;

	i = 0;
	*rlt = 0;
	minus = 1;
	if (nptr[i] == '-')
	{
		minus *= -1;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		if (*rlt > INT_MAX / 10 || (*rlt == INT_MAX / 10
				&& (nptr[i] - '0') > INT_MAX % 10)
			|| *rlt < INT_MIN / 10 || (*rlt == INT_MIN / 10
				&& (nptr[i] - '0') > (INT_MIN % 10) * (-1)))
			return (false);
		*rlt = *rlt * 10 + (nptr[i++] - '0') * minus;
	}
	if (nptr[i] != '\0')
		return (false);
	return (true);
}
