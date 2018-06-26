/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 17:26:24 by ale               #+#    #+#             */
/*   Updated: 2018/06/26 18:29:16 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

void	*request_big(t_mlist **lst, size_t size)
{
	t_mlist	*mem;
	size_t	*content_size;

	if ((mem = (t_mlist*)allocate_page_multi(\
		page_aligned_size(size + sizeof(t_mlist) + sizeof(size_t)))) == NULL)
		return (NULL);
	mem->next = *lst;
	mem->prev = NULL;
	content_size = (size_t*)((char*)mem + sizeof(t_mlist));
	*content_size = size;
	if (*lst)
		(*lst)->prev = mem;
	*lst = mem;
	return ((char*)mem + sizeof(t_mlist));
}

static void	unlink_node(t_mlist **lst, t_mlist *node)
{
	if (node == *lst)
	{
		*lst = (*lst)->next;
		(*lst)->prev = NULL;
	}
	else
	{
		if (node->next != NULL)
			node->next->prev = node->prev;
		node->prev->next = node->next;
	}
}

void	free_big(void *ptr, t_mlist** lst)
{
	t_mlist	*cursor;
	size_t	*content_size;

	if (*lst == NULL)
		return ;
	cursor = *lst;
	while (cursor != NULL)
	{
		if ((char*)cursor + sizeof(t_mlist) + sizeof(size_t) == ptr)
		{
			content_size = (size_t*)((char*)cursor + sizeof(t_mlist));
			unlink_node(lst, cursor);
			deallocate_page(cursor, page_aligned_size(\
				*content_size + sizeof(t_mlist) + sizeof(size_t)));
			return ;
		}
		cursor = cursor->next;
	}
}
