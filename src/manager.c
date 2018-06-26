/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:24:15 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/26 20:02:18 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "manager.h"
#include "libft.h"

#include <pthread.h>

t_mem_store g_store;
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void	*new_zone(size_t size)
{
	t_clist	**zone;
	t_clist	*new_zone;
	size_t	zone_size;

	if (size > SMALL_SIZE)
		return (NULL);
	zone_size = size <= TINY_SIZE ? \
		   TINY_SIZE * TINY_COUNT : SMALL_SIZE * SMALL_COUNT;
	zone_size = page_aligned_size(zone_size);
	if ((new_zone = (t_clist*)allocate_page_multi(zone_size)) == NULL)
		return (NULL);
	zone = size <= TINY_SIZE ? &g_store.tiny_list : &g_store.small_list;
	if (*zone)
		(*zone)->prev = new_zone;
	new_zone->next = (*zone);
	new_zone->prev = NULL;
	new_zone->refcount = 0;
	new_zone->content_size = zone_size - sizeof(t_clist);
	*zone = new_zone;
	return (new_zone);
}

void	*request_memory(size_t size)
{
	printf("mem_request(%lu)\n", size);
	size_t	*mem;
	t_clist	*chunk;

	if (size == 0)
		return (NULL);
	if (size <= SMALL_SIZE)
	{
		chunk = size <= TINY_SIZE ? g_store.tiny_list : g_store.small_list;
		while (chunk != NULL)
		{
			if ((mem = get_free(chunk, size)) != NULL)
				return (mem);
			chunk = chunk->next;
		}
		chunk = new_zone(size);
		return (get_free(chunk, size));
	}
	else
	{
		return (request_big(&g_store.big_list, size));
	}
}

void	*reallocate_memory(void *ptr, size_t size)
{
	printf("mem_realloc(%p)\n", ptr);
		void    *newptr;
		size_t	content_size;

		content_size = *(size_t*)((char*)ptr - sizeof(size_t)) & ~USED_FLAG;
		if (content_size >= size)
			return (ptr);
		if ((newptr = request_memory(size)) == NULL)
			return (NULL);
		ft_memcpy(newptr, ptr, content_size);
		deallocate_memory(ptr);
		return (newptr);
}

void	deallocate_memory(void *ptr)
{
	printf("mem_dealloc(%p)\n", ptr);
	if (!mem_free(ptr, g_store.tiny_list) && !mem_free(ptr, g_store.small_list))
	{
		free_big(ptr, &g_store.big_list);
	}
}
