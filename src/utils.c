/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 17:18:03 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/25 17:48:54 by amarzial         ###   ########.fr       */
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
