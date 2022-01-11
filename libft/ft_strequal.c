/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuta <fyuta@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:18:49 by fyuta             #+#    #+#             */
/*   Updated: 2022/01/10 18:30:03 by fyuta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_strequal(char *s1, char *s2, size_t n)
{
	if (!s1 || !s2)
		return (false);
	if (ft_strncmp(s1, s2, n) == 0)
		return (true);
	return (false);
}
