/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:52:33 by amarzial          #+#    #+#             */
/*   Updated: 2018/01/31 14:07:25 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ft_memory.h"

//for mmap
#include <sys/mman.h>

void	*malloc(size_t size)
{
	int ps;
	size_t pagecount;
	void *ret;

	ps = getpagesize();
	pagecount = size / ps + ((size % ps) ? 1 : 0);
	ret = mmap(0, pagecount * ps, PROT_READ | PROT_WRITE | PROT_EXEC, \
			MAP_PRIVATE | MAP_ANON, -1, 0);
	return ((ret == MAP_FAILED) ? NULL : ret);
}
