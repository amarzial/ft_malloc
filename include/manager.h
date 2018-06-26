/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 15:22:04 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/27 13:17:58 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_H
# define MANAGER_H

# define TINY_SIZE 64
# define TINY_COUNT 100
# define SMALL_SIZE 4096
# define SMALL_COUNT 100
# define USED_FLAG 1
# define USED_ZONE 1
# define USED_LIST 2

# include <stddef.h>

//typedef size_t	t_block_head;

typedef struct	s_mem_list
{
	struct s_mem_list	*prev;
	struct s_mem_list	*next;
}				t_mlist;

typedef struct	s_chunk_list
{
	size_t				content_size;
	size_t				refcount;
	struct s_chunk_list	*prev;
	struct s_chunk_list	*next;
}				t_clist;

typedef struct	s_mem_store
{
	int				initialized;
	int				page_size;
	t_clist			*tiny_list;
	t_clist			*small_list;
	t_mlist			*big_list;
}				t_mem_store;

int				init_free_list(\
					t_mlist **dest, size_t block_size, size_t block_count);
void			*find_existing_block(void *ptr, t_mlist *list);
void			*find_free_block(t_mlist *list);
t_mlist			*alloc_list_insert(t_mlist **lst, size_t size);
void			alloc_list_delete(t_mlist **lst, t_mlist *elem);

void			*request_memory(size_t size);
void			deallocate_memory(void *ptr);
void			*reallocate_memory(void *ptr, size_t size);

void			*get_free(t_clist *chunk, size_t size);
void			*request_big(t_mlist **lst, size_t size);
int				mem_free(void *ptr, t_clist *lst);
void			free_big(void *ptr, t_mlist** lst);

size_t			page_aligned_size(size_t size);
size_t			size_align(size_t size);

void			*allocate_page_multi(size_t size);
void			deallocate_page(void *ptr, size_t size);

#endif
