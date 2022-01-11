/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuta <fyuta@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:54:17 by fyuta             #+#    #+#             */
/*   Updated: 2022/01/09 12:59:34 by fyuta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return (false);
	new->next = (*lst);
	(*lst) = new;
	return (true);
}
