/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 15:22:04 by amarzial          #+#    #+#             */
/*   Updated: 2018/02/01 15:20:24 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_H
#define MANAGER_H

# define TINY_SIZE 64
# define TINY_COUNT 100
# define SMALL_SIZE 1024
# define SMALL_COUNT 100

typedef struct	s_mem_block
{
	void*	ref;
	void*	next;
}				t_mem_block;

typedef struct	s_mem_zone
{
	size_t	size;
	void*	addr;
}				t_mem_zone;

typedef struct	s_mem_store
{
	int				initialized;
	int 			page_size;
	t_mem_zone		tiny;
	t_mem_zone		small;
	t_mem_block*	mem_big;
	void*			tiny_free_list;
	void*	 		small_free_list;

}				t_mem_store;

int			init_memory();
void		*request_memory(size_t size);

#endif
