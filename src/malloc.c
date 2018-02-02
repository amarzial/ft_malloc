/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:52:33 by amarzial          #+#    #+#             */
/*   Updated: 2018/02/02 22:58:23 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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
        return(malloc(size));
    else if (size == 0)
    {
        free(ptr);
        return (NULL);
    }
    else
        return reallocate_memory(ptr, size);
}
