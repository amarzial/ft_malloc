/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 15:22:04 by amarzial          #+#    #+#             */
/*   Updated: 2018/02/21 15:29:49 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_H
# define MANAGER_H

# define TINY_SIZE 64
# define TINY_COUNT 100
# define SMALL_SIZE 1024
# define SMALL_COUNT 100
# define UNUSED 0
# define USED_ZONE 1
# define USED_LIST 2

# include <stddef.h>

typedef char	t_used;

typedef struct	s_free_list
{
	t_used				used;
	size_t				content_size;
	struct s_free_list	*prev;
	struct s_free_list	*next;
}				t_alist;

typedef t_alist	t_flist;

typedef struct	s_mem_block
{
	void*	ref;
	void*	next;
}				t_mem_block;

typedef struct	s_mem_store
{
	int				initialized;
	int				page_size;
	t_mem_block		*mem_big;
	t_flist			*tiny_free_list;
	t_flist			*small_free_list;
	t_flist			*alloc_list;

}				t_mem_store;

int				init_free_list(\
					t_flist **dest, size_t block_size, size_t block_count);
void            *find_existing_block(void* ptr, t_flist *list);
void			*find_free_block(t_flist *list);
t_flist			*alloc_list_insert(t_flist **lst, size_t size);
void			alloc_list_delete(t_flist **lst, t_flist *elem);

int				init_memory();
void			*request_memory(size_t size);
void			deallocate_memory(void *ptr);
void			*reallocate_memory(void *ptr, size_t size);

size_t			page_aligned_size(size_t size);

void			*allocate_page_multi(size_t size);
void			deallocate_page(void *ptr, size_t size);

#endif
