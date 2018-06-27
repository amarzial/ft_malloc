/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 17:18:03 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/27 11:58:24 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

#include <unistd.h>

size_t	page_aligned_size(size_t size)
{
	int		page_size;

	page_size = getpagesize();
	return (page_size * ((size / page_size) + (size % page_size ? 1 : 0)));
}

size_t	size_align(size_t size)
{
	return (size % sizeof(size_t) ? (sizeof(size_t) - \
				size % sizeof(size_t)) + size : size);
}

void	put_hex(void *ptr, int fd)
{
	char	str[sizeof(size_t) * 2];
	size_t	val;
	size_t	i;
	char	*base;

	base = "0123456789abcdef";
	val = (size_t)ptr;
	i = 0;
	while (i < sizeof(size_t) * 2)
	{
		str[sizeof(size_t) * 2 - 1 - i] = base[val % 0x10];
		val /= 0x10;
		++i;
	}
	write(fd, str, sizeof(size_t)*2);
}
