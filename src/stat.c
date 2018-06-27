/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:14:34 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/27 11:59:45 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

#include "libft.h"

extern t_mem_store		g_store;
extern pthread_mutex_t	g_mutex;

/*
static size_t			show_zone(t_mlist *lst)
{
	t_mlist *start;
	size_t	size;

	size = 0;
	while (lst && lst->next)
	{
		
		if (lst->used)
		{
			start = (t_mlist*)((char*)lst + sizeof(lst));
			ft_printf("%p - %p : %u bytes\n", start, start + lst->content_size,\
					lst->content_size);
		}
		
		//size += lst->content_size;
		lst = lst->next;
	}
	return (size);
}
*/

static void				hex_dump(void *ref, size_t size)
{
	char			*base;
	size_t			i;
	unsigned char	*ptr;

	base = "0123456789abcdef";
	ptr = (unsigned char*)ref;
	i = 0;
	while (i < size)
	{
		ft_putchar(base[ptr[i] / 0x10]);
		ft_putchar(base[ptr[i] % 0x10]);
		if ((i + 1) % 0x10 == 0)
			ft_putchar('\n');
		else if ((i + 1) % 0x8 == 0)
			ft_putstr("  ");
		else
			ft_putchar(' ');
		++i;
	}
	if (size % 0x10)
		ft_putchar('\n');
}

static void				show_chunk(t_clist *chunk)
{
	size_t	*pos;
	size_t	offset;

	offset = size_align(sizeof(t_clist));

	while (offset < chunk->content_size + size_align(sizeof(t_clist)))
	{
		pos = (size_t*)((char*)chunk + offset);
		ft_putstr("    block (");
		ft_putnbr(offset);
		ft_putstr(")\n");
		offset += size_align((*pos) & ~USED_FLAG);
	}
}

void					show_alloc_mem(void)
{
	t_clist *chunk;
	ft_putstr("TINY:\n");
	chunk = g_store.tiny_list;
	while (chunk != NULL)
	{
		ft_putstr("  chunk(");
		ft_putnbr(chunk->content_size);
		ft_putstr(")\n");
		show_chunk(chunk);
		chunk = chunk->next;
	}
	ft_putstr("SMALL:\n");
	chunk = g_store.small_list;
	while (chunk != NULL)
	{
		ft_putstr("  chunk(");
		ft_putnbr(chunk->content_size);
		ft_putstr(")\n");
		show_chunk(chunk);
		chunk = chunk->next;
	}
	return ;
}

void	dump_mem(void)
{
	t_clist *chunk;
	ft_putstr("TINY:\n");
	chunk = g_store.tiny_list;
	while (chunk != NULL)
	{
		ft_putstr("  chunk(");
		ft_putnbr(chunk->content_size);
		ft_putstr(")\n");
		hex_dump(chunk, sizeof(t_clist) + chunk->content_size);
		chunk = chunk->next;
	}
	ft_putstr("SMALL:\n");
	chunk = g_store.small_list;
	while (chunk != NULL)
	{
		ft_putstr("  chunk(");
		ft_putnbr(chunk->content_size);
		ft_putstr(")\n");
		hex_dump(chunk, sizeof(t_clist) + chunk->content_size);
		chunk = chunk->next;
	}
	return ;
}

