/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:24:15 by amarzial          #+#    #+#             */
/*   Updated: 2018/02/01 17:30:57 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "manager.h"
#include "libft.h"

#include <sys/mman.h>

t_mem_store g_store;

static int 	init_free_list(t_flist **dest, size_t block_size, size_t block_count)
{
	char	*chunk;
	size_t	pos;
	t_flist	*tmp;

	chunk = (char*)mmap(0, \
			page_aligned_size((block_size + sizeof(t_flist)) * block_count), \
			PROT_READ | PROT_WRITE | PROT_EXEC,	MAP_PRIVATE | MAP_ANON, -1, 0);
	if ((void*)chunk == MAP_FAILED)
		return (0);
	pos = 0;
	while (pos < block_count)
	{
		tmp = (t_flist*)(chunk + (pos * (block_size + sizeof(t_flist))));
		tmp->used = 0;
		tmp->content_size = block_size;
		tmp->content = ((char*)tmp) + sizeof(t_flist);
		++pos;
		tmp->next = (pos != block_count ? tmp + 1 : NULL);
	}
	*dest = (void*)chunk;
	return (1);
}

static void *find_free_block(t_flist *list)
{
	while (list != NULL)
	{
		if (!list->used)
			return (list);
		list = list->next;
	}
	return (NULL);
}

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

	if (size <= TINY_SIZE)
		mem = find_free_block(g_store.tiny_free_list);	
	else if (size <= SMALL_SIZE)
		mem = find_free_block(g_store.small_free_list);	
	else
	{
		mem = NULL;
	}
	if (mem == NULL && size <= SMALL_SIZE)
		mem = NULL; //make_allocation();
	mem->used = 1;
	return (mem->content);
}
