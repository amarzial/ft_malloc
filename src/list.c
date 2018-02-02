/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:36:48 by amarzial          #+#    #+#             */
/*   Updated: 2018/02/02 18:02:25 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

int 	init_free_list(t_flist **dest, size_t block_size, size_t block_count)
{
	char	*chunk;
	size_t	pos;
	t_flist	*tmp;

	chunk = (char*)allocate_page_multi(\
            (block_size + sizeof(t_flist)) * block_count);
    if (chunk == NULL)
		return (0);
	pos = 0;
	while (pos < block_count)
	{
		tmp = (t_flist*)(chunk + (pos * (block_size + sizeof(t_flist))));
		tmp->used = 0;
		tmp->content_size = block_size;
		++pos;
		tmp->next = (pos != block_count ? tmp + 1 : NULL);
	}
	*dest = (void*)chunk;
	return (1);
}

void    *find_free_block(t_flist *list)
{
	while (list != NULL)
	{
		if (!list->used)
			return (list);
		list = list->next;
	}
	return (NULL);
}

t_flist *alloc_list_insert(t_flist **lst, size_t size)
{
    t_flist *elem;

    if((elem = allocate_page_multi(size + sizeof(t_flist))) == NULL)
        return (NULL);
    elem->used = 1;
    elem->content_size = size;
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
