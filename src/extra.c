/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:14:34 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/15 17:13:42 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

#include "libft.h"

extern t_mem_store g_store;

static size_t	show_zone(t_flist* lst)
{
	t_flist *start;
	size_t	size;

	size = 0;
	while (lst && lst->next)
	{
		if (lst->used)
		{
			start = (t_flist*)((char*)lst + sizeof(lst));
			ft_printf("%p - %p : %u bytes\n", start, start + lst->content_size, \
					lst->content_size);
		}
		size += lst->content_size;
		lst = lst->next;
	}
	return (size);
}

void			show_alloc_mem()
{
	size_t count;

	count = 0;
	ft_printf("TINY : %p\n", g_store.tiny_free_list);
	count += show_zone(g_store.tiny_free_list);
	ft_printf("SMALL : %p\n", g_store.small_free_list);
	count += show_zone(g_store.small_free_list);
	ft_printf("LARGE : %p\n", g_store.alloc_list);
	count += show_zone(g_store.alloc_list);
	ft_printf("Total : %u bytes\n", count);
}
