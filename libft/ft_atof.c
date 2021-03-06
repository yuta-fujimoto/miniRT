/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuta <fyuta@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:46:04 by fyuta             #+#    #+#             */
/*   Updated: 2022/01/28 09:35:29 by fyuta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	process_integer(double *rlt, const char *nptr, int *i)
{
	while (ft_isdigit(nptr[*i]))
	{
		if (*rlt > INT_MAX / 10 || (*rlt == INT_MAX / 10
				&& (nptr[*i] - '0') > INT_MAX % 10)
			|| *rlt < INT_MIN / 10 || (*rlt == INT_MIN / 10
				&& (nptr[*i] - '0') > (INT_MIN % 10) * (-1)))
			return (false);
		*rlt = *rlt * 10 + (nptr[*i] - '0');
		(*i)++;
	}
	return (true);
}

bool	process_decimal(double *rlt, const char *nptr, int *i)
{
	double	d;

	d = 0.1;
	if (nptr[*i] == '.')
	{
		(*i)++;
		if (!nptr[*i])
			return (false);
		while (ft_isdigit(nptr[*i]))
		{
			*rlt += (nptr[*i] - '0') * d;
			d *= 0.1;
			(*i)++;
		}
	}
	return (true);
}

bool	ft_atof(const char *nptr, double *rlt)
{
	int		i;
	double	sign;

	i = 0;
	*rlt = 0;
	sign = 1.0;
	if (nptr[i] == '-')
	{
		sign = -1.0;
		i++;
	}
	if (!process_integer(rlt, nptr, &i))
		return (false);
	if (!process_decimal(rlt, nptr, &i))
		return (false);
	if (nptr[i] != '\0' || i == 0 || (i == 1 && nptr[0] == '-'))
		return (false);
	*rlt *= sign;
	return (true);
}

// #include <stdio.h>

// int main(int ac, char **av)
// {
// 	double a;

// 	if (!ft_atof(av[1], &a))
// 		printf("ERROR %le\n", a);
// 	else
// 		printf("%le\n", a);
// }
