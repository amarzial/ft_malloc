/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:24:15 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/25 16:34:18 by amarzial         ###   ########.fr       */
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
	return (0);
}

void	*get_free(t_clist *chunk, size_t size)
{
	
	return (NULL);
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
		//new_zone();
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
