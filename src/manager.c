/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:24:15 by amarzial          #+#    #+#             */
/*   Updated: 2018/02/01 15:20:23 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "manager.h"
#include "libft.h"

#include <sys/mman.h>

t_mem_store g_store;

static int	init_free_list(const t_mem_zone *zone, void** target, size_t size)
{
	size_t	parts;
	void*	list;
	size_t	pos;

	if ((list = mmap(0, g_store.tiny.size, \
					PROT_READ | PROT_WRITE | PROT_EXEC, \
					MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		return (0);
	parts = zone->size / size;
	pos = 0;
	while (pos < parts)
	{
		((void**)list)[pos] = zone->addr + (pos * sizeof(void*));
		--pos;		
	}
	*target = list;
	return (1);
}

int			init_memory()
{
	int page_size;

	if (g_store.initialized)
		return (1);
	page_size = getpagesize();
	g_store.page_size = page_size;
	g_store.tiny.size = (TINY_SIZE * TINY_COUNT) / page_size + \
						((TINY_SIZE * TINY_COUNT) % page_size ? page_size : 0); 
	if ((g_store.tiny.addr = mmap(0, g_store.tiny.size, \
					PROT_READ | PROT_WRITE | PROT_EXEC, \
					MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		return (0);
	g_store.small.size = (SMALL_SIZE * SMALL_COUNT) / page_size + \
						((SMALL_SIZE * SMALL_COUNT) % page_size ? \
						 page_size : 0); 
	if ((g_store.small.addr = mmap(0, g_store.small.size, \
					PROT_READ | PROT_WRITE | PROT_EXEC, \
					MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		return (0);
	g_store.initialized = \
				(init_free_list(&(g_store.tiny), &(g_store.tiny_free_list), \
				TINY_SIZE) && init_free_list(&(g_store.small), \
					&(g_store.small_free_list),	SMALL_SIZE));
	return (1);
}

void		*request_memory(size_t size)
{
	return (size ? 0 : NULL);
}
