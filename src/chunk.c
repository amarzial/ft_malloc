/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:56:45 by ale               #+#    #+#             */
/*   Updated: 2018/06/26 18:35:37 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

void	*get_free(t_clist *chunk, size_t size)
{
	size_t	offset;
	size_t	*cursor;

	offset = size_align(sizeof(t_clist));
	if (chunk->refcount == 0)
	{
		cursor = (size_t*)((char*)chunk + offset);
		*cursor = (chunk->content_size - sizeof(size_t)) & ~USED_FLAG;
	}
	while (chunk->content_size - offset >= size_align(size) + sizeof(size_t))
	{
		cursor = (size_t*)((char*)chunk + offset);
		if (!(*cursor & USED_FLAG) && ((*cursor & ~USED_FLAG) >= size))
		{
			if (*cursor - size_align(size) >= sizeof(size_t))
			{
				*(size_t*)((char*)cursor + sizeof(size_t) + size_align(size)) = \
					(*cursor - size_align(size)) & ~USED_FLAG;
			}
			*cursor = size;
			*cursor |= USED_FLAG;
			chunk->refcount += 1;
			return ((char*)cursor + sizeof(size_t));
		}
		offset += size_align(*cursor & ~USED_FLAG) + sizeof(size_t);
	}
	return (NULL);
}

int		mem_free(void *ptr, t_clist *lst)
{
	void	*begin;

	ptr = (char*)ptr - sizeof(size_t);
	if (lst == NULL)
		return (0);
	while (lst != NULL)
	{
		begin = (char*)lst + size_align(sizeof(t_clist));
		if (ptr >= begin && ptr < (begin + lst->content_size))
		{
			if (*(size_t*)ptr & USED_FLAG)
			{
				*(size_t*)ptr &= ~USED_FLAG;
				lst->refcount -= 1;
				return (1);
			}
			return (0);
		}
		lst = lst->next;
	}
	return (0);
}
