/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:56:06 by amarzial          #+#    #+#             */
/*   Updated: 2018/02/01 14:30:47 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEMORY_H
#define FT_MEMORY_H
# include "libft.h"

# include <stdlib.h>

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);

#endif
