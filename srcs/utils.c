#include "miniRT.h"

t_world *end_world(t_world *w)
{
	ft_lstclear(&w->obj_list, free);
	free(w);
	return (NULL);
}

void safe_free(void *p)
{
	if (p)
		free(p);
}

void	ft_str_arr_free(char **str_arr)
{
	int	i;

	i = 0;
	if (!str_arr)
		return ;
	while (str_arr[i])
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

int	ft_str_arr_len(char **str_arr)
{
	int	i;

	i = 0;
	if (!str_arr)
		return (0);
	while (str_arr[i])
		i++;
	return (i);
}
