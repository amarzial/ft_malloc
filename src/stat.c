/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:14:34 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/26 19:38:39 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

#include "libft.h"

extern t_mem_store		g_store;
extern pthread_mutex_t	g_mutex;

/*
static size_t			show_zone(t_mlist *lst)
{
	t_mlist *start;
	size_t	size;

	size = 0;
	while (lst && lst->next)
	{
		
		if (lst->used)
		{
			start = (t_mlist*)((char*)lst + sizeof(lst));
			ft_printf("%p - %p : %u bytes\n", start, start + lst->content_size,\
					lst->content_size);
		}
		
		//size += lst->content_size;
		lst = lst->next;
	}
	return (size);
}
*/


void					show_alloc_mem(void)
{
	return ;
}

