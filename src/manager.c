/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:24:15 by amarzial          #+#    #+#             */
/*   Updated: 2018/01/31 16:12:57 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "manager.h"
#include "libft.h"

t_mem_store g_store;

static void* init_free_list(t_mem_zone* zone, size_t size)
{
	unsigned int parts;

	parts = zone->size / size;
	while (parts--)
	{

		ft_lstadd(
	}
}	

int	init_memory()
{
	g_store.page_size = getpagesize();
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
	return(1);
}
