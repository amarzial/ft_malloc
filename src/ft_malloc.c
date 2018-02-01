/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:52:33 by amarzial          #+#    #+#             */
/*   Updated: 2018/02/01 14:33:34 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ft_memory.h"
#include "manager.h"

//for mmap
#include <sys/mman.h>

void	*malloc(size_t size)
{
	if (!init_memory())
		return (NULL);
	return (request_memory(size));	
}
