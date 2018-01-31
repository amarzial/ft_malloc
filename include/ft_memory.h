/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:56:06 by amarzial          #+#    #+#             */
/*   Updated: 2018/01/31 16:12:56 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEMORY_H
#define FT_MEMORY_H
# include "libft.h"

# include <stdlib.h>

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);

typedef struct	s_mem_zone
{
	size_t	size;
	void*	addr;
}				t_mem_zone;

typedef struct	s_mem_store
{
	int 		page_size;
	t_mem_zone	tiny;
	t_mem_zone	small;
	t_list* 	mem_big;
	t_list* 	tiny_free_list;
	t_list* 	small_free_list;
}				t_mem_store;
#endif
