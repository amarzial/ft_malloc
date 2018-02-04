/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:52:33 by amarzial          #+#    #+#             */
/*   Updated: 2018/02/04 19:59:25 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"

#include "ft_malloc.h"
#include "manager.h"

void	*malloc(size_t size)
{
	if (!size || !init_memory())
		return (NULL);
	return (request_memory(size));
}

void	free(void *ptr)
{
	if (!ptr)
		return ;
	deallocate_memory(ptr);
}

void	*realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return (malloc(size));
	else if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else
		return (reallocate_memory(ptr, size));
}

void	*calloc(size_t nmemb, size_t size)
{
	void	*ret;

	if (!(ret = malloc(nmemb * size)))
		return (NULL);
	return (ft_memset(ret, 0, nmemb * size));
}

void	*reallocarray(void *ptr, size_t nmemb, size_t size)
{
	size_t	total;

	total = nmemb * size;
	if (nmemb != 0 && total / nmemb != size)
		return (NULL);
	return (realloc(ptr, total));
}
