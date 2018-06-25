/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:36:48 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/25 16:20:18 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

int		init_free_list(t_mlist **dest, size_t block_size, size_t block_count)
{
	char	*chunk;
	size_t	pos;
	t_mlist	*tmp;
	t_mlist	*prev;

	chunk = (char*)allocate_page_multi(\
			(block_size + sizeof(t_mlist)) * block_count);
	if (chunk == NULL)
		return (0);
	pos = 0;
	prev = NULL;
	while (pos < block_count)
	{
		tmp = (t_mlist*)(chunk + (pos * (block_size + sizeof(t_mlist))));
		//tmp->used = 0;
		tmp->content_size = 0;
		++pos;
		tmp->next = (pos != block_count ? (t_mlist*)((char*)tmp + block_size + \
				sizeof(t_mlist)) : NULL);
		tmp->prev = prev;
		prev = tmp;
	}
	*dest = (void*)chunk;
	return (1);
}

void	*find_existing_block(void *ptr, t_mlist *list)
{
	while (list != NULL)
	{
		if (list == ptr)
			return (ptr);
		list = list->next;
	}
	return (NULL);
}

void	*find_free_block(t_mlist *list)
{
	while (list != NULL)
	{
		//if (!list->used)
		//	return (list);
		list = list->next;
	}
	return (NULL);
}

t_mlist	*alloc_list_insert(t_mlist **lst, size_t size)
{
	t_mlist	*elem;
	size_t	allocated_size;

	allocated_size = size + sizeof(t_mlist);
	if ((elem = allocate_page_multi(allocated_size)) == NULL)
		return (NULL);
	//elem->used = USED_LIST;
	elem->content_size = allocated_size - sizeof(t_mlist);
	elem->prev = NULL;
	elem->next = *lst;
	if (*lst != NULL)
	{
		elem->prev = (*lst)->prev;
		if (elem->prev != NULL)
			elem->prev->next = elem;
		(*lst)->prev = elem;
	}
	*lst = elem;
	return (elem);
}

void	alloc_list_delete(t_mlist **lst, t_mlist *elem)
{
	if (*lst == elem)
		*lst = elem->next;
	if (elem->next)
		elem->next->prev = elem->prev;
	if (elem->prev)
		elem->prev->next = elem->next;
}
