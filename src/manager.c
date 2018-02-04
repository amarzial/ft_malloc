/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:24:15 by amarzial          #+#    #+#             */
/*   Updated: 2018/02/04 20:02:25 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "manager.h"
#include "libft.h"

t_mem_store g_store;

int		init_memory(void)
{
	if (g_store.initialized)
		return (1);
	init_free_list(&g_store.tiny_free_list, TINY_SIZE, TINY_COUNT);
	init_free_list(&g_store.small_free_list, SMALL_SIZE, SMALL_COUNT);
	g_store.initialized = 1;
	return (1);
}

void	*request_memory(size_t size)
{
	t_flist	*mem;
	t_used	allocation_type;

	allocation_type = USED_ZONE;
	mem = NULL;
	if (size <= TINY_SIZE)
		mem = find_free_block(g_store.tiny_free_list);
	else if (size <= SMALL_SIZE)
		mem = find_free_block(g_store.small_free_list);
	if (mem == NULL || size > SMALL_SIZE)
	{
		mem = alloc_list_insert(&g_store.alloc_list, size);
		allocation_type = USED_LIST;
	}
	if (mem == NULL)
		return (NULL);
	mem->used = allocation_type;
	return ((char*)mem + sizeof(t_flist));
}

void	*reallocate_memory(void *ptr, size_t size)
{
	void	*newptr;
	t_flist *block;

	block = (t_flist*)((char*)ptr - sizeof(t_flist));
	if (block->content_size >= size)
		return (ptr);
	if ((newptr = request_memory(size)) == NULL)
		return (NULL);
	ft_memcpy(newptr, ptr, block->content_size);
	deallocate_memory(ptr);
	return (newptr);
}

void	deallocate_memory(void *ptr)
{
	t_flist *block;

	block = (t_flist*)((char*)ptr - sizeof(t_flist));
	if (block->used == USED_LIST)
	{
		alloc_list_delete(&g_store.alloc_list, block);
		deallocate_page(block, block->content_size + sizeof(t_flist));
	}
	else
		block->used = UNUSED;
}
