/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:24:15 by amarzial          #+#    #+#             */
/*   Updated: 2018/02/02 18:01:18 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "manager.h"
#include "libft.h"

t_mem_store g_store;

int			init_memory()
{
	if (g_store.initialized)
		return (1);
	init_free_list(&g_store.tiny_free_list, TINY_SIZE, TINY_COUNT);
	init_free_list(&g_store.small_free_list, SMALL_SIZE, SMALL_COUNT);
	return (1);
}

void		*request_memory(size_t size)
{
	t_flist	*mem;

    mem = NULL;
	if (size <= TINY_SIZE)
		mem = find_free_block(g_store.tiny_free_list);	
	else if (size <= SMALL_SIZE)
		mem = find_free_block(g_store.small_free_list);	
	if (mem == NULL || size > SMALL_SIZE)
		mem = alloc_list_insert(&g_store.alloc_list, size);
    if (mem == NULL)
        return (NULL);
    mem->used = 1;
	return (mem + sizeof(mem));
}
