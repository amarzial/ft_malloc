/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 17:18:03 by amarzial          #+#    #+#             */
/*   Updated: 2018/02/04 16:45:51 by amarzial         ###   ########.fr       */
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
