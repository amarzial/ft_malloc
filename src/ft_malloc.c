/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:52:33 by amarzial          #+#    #+#             */
/*   Updated: 2018/02/02 18:42:35 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ft_memory.h"
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
