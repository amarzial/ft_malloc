/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test01_sizes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 20:11:20 by amarzial          #+#    #+#             */
/*   Updated: 2018/02/04 21:01:54 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "manager.h"
#include "libft.h"

#include <assert.h>

int	main(void)
{
	char	*buff;

	buff = NULL;
	assert(!(buff = (char*)malloc(0)));
	free(buff);
	assert(buff = (char*)malloc(TINY_SIZE));
	free(buff);
	assert(buff = (char*)malloc(SMALL_SIZE));
	free(buff);
	assert(buff = (char*)malloc(SMALL_SIZE * 10));
	free(buff);
	return (0);
}
