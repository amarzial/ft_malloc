/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:24:15 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/25 18:47:11 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "manager.h"
#include "libft.h"

#include <pthread.h>

t_mem_store g_store;
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void	*get_free(t_clist *chunk, size_t size)
{
	size_t	offset;
	size_t	*cursor;

	offset = size_align(sizeof(t_clist));
	if (chunk->refcount == 0)
	{
		cursor = (size_t*)((char*)chunk + offset);
		*cursor = chunk->content_size - sizeof(size_t) & ~USED_FLAG;
	}
	while (chunk->content_size - offset >= size_align(size) + sizeof(size_t))
	{
		cursor = (size_t*)((char*)chunk + offset);
		if (!(*cursor & USED_FLAG) && ((*cursor & ~USED_FLAG) >= size))
		{
			if (*cursor - size_align(size) >= sizeof(size_t))
			{
				*(size_t*)((char*)cursor + sizeof(size_t) + size_align(size)) = \
					(*cursor - size_align(size)) & ~USED_FLAG;
			}
			*cursor = size;
			*cursor |= USED_FLAG;
			chunk->refcount += 1;
			return ((char*)cursor + sizeof(size_t));
		}
		offset += size_align(*cursor & ~USED_FLAG) + sizeof(size_t);
	}
	return (NULL);
}

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
	size_t	*mem;
	t_clist	*chunk;

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
		//return (request_big(size));
		return (NULL);
	}
}

void	*reallocate_memory(void *ptr, size_t size)
{
		return (NULL);
}

void	deallocate_memory(void *ptr)
{
}
