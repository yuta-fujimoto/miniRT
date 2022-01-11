/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuta <fyuta@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 13:01:18 by fyuta             #+#    #+#             */
/*   Updated: 2022/01/09 12:58:34 by fyuta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!new || !lst)
		return (false);
	if (*lst == NULL)
	{
		*lst = new;
		return (true);
	}
	ft_lstlast(*lst)->next = new;
	return (true);
}
