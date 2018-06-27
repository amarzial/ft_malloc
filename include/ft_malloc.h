/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:56:06 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/27 11:57:34 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stddef.h>

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	*calloc(size_t nmemb, size_t size);
void	*reallocarray(void *ptr, size_t nmemb, size_t size);

void	show_alloc_mem(void);
void	dump_mem(void);


#endif
