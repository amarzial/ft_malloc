/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:26:06 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/18 17:03:32 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

#include <sys/mman.h>

void	*allocate_page_multi(size_t size)
{
	void	*res;

	res = mmap(0, page_aligned_size(size), \
			PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (res == MAP_FAILED)
		return (NULL);
	return (res);
}

void	deallocate_page(void *ptr, size_t size)
{
	(void)munmap(ptr, size);
}
