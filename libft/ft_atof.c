#include "libft.h"

bool	process_integer(double *rlt, const char *nptr, int *i)
{
	while (ft_isdigit(nptr[*i]))
	{
		if (*rlt > LONG_MAX / 10 || (*rlt == LONG_MAX / 10
				&& (nptr[*i] - '0') > LONG_MAX % 10)
			|| *rlt < LONG_MIN / 10 || (*rlt == LONG_MIN / 10
				&& (nptr[*i] - '0') > (LONG_MIN % 10) * (-1)))
			return (false);
		*rlt = *rlt * 10 + (nptr[*i] - '0');
		(*i)++;
	}
	return (true);
}

bool	process_decimal(double *rlt, const char *nptr, int *i)
{
	double d;

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
