/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:24:15 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/15 19:39:20 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "manager.h"
#include "libft.h"

#include <pthread.h>

t_mem_store g_store;
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

int		init_memory(void)
{
	int status;

	pthread_mutex_lock(&g_mutex);
	status = 1;
	if (!g_store.initialized)
	{
		if (!init_free_list(&g_store.tiny_free_list, TINY_SIZE, TINY_COUNT) || \
				!init_free_list(&g_store.small_free_list, SMALL_SIZE, \
					SMALL_COUNT))
			status = 0;
		else
			g_store.initialized = 1;
	}
	pthread_mutex_unlock(&g_mutex);
	return (status);
}

void	*request_memory(size_t size)
{
	t_flist	*mem;
	t_used	allocation_type;

	if (!init_memory())
		return (NULL);
	allocation_type = USED_ZONE;
	mem = NULL;
	pthread_mutex_lock(&g_mutex);
	if (size <= TINY_SIZE)
		mem = find_free_block(g_store.tiny_free_list);
	else if (size <= SMALL_SIZE)
		mem = find_free_block(g_store.small_free_list);
	if (mem == NULL || size > SMALL_SIZE)
	{
		mem = alloc_list_insert(&g_store.alloc_list, size);
		allocation_type = USED_LIST;
	}
	pthread_mutex_unlock(&g_mutex);
	if (mem == NULL)
		return (NULL);
	mem->used = allocation_type;
	mem->content_size = size;
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
	pthread_mutex_lock(&g_mutex);
	if (find_existing_block(block, g_store.alloc_list))
	{
		alloc_list_delete(&g_store.alloc_list, block);
		deallocate_page(block, block->content_size + sizeof(t_flist));
	}
	else if (find_existing_block(block, g_store.tiny_free_list) || \
            find_existing_block(block, g_store.small_free_list))
	{
		block->content_size = 0;
		block->used = UNUSED;
	}
	pthread_mutex_unlock(&g_mutex);
}
