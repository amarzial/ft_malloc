/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test03_random_allocations.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 20:11:20 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/26 19:38:03 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "manager.h"
#include "libft.h"

#include <assert.h>

#define SAMPLES 100

int	main(void)
{
	char	*buff[SAMPLES];
	int		i;

	srand(0);
	while(i < SAMPLES)
	{
		int size;
		switch (rand() % 3) {
			case 0:
				size = rand() % TINY_SIZE + 1;
				break;
			case 1:
				size = rand() % (SMALL_SIZE - TINY_SIZE) + 1 + TINY_SIZE;
				break;
			case 2:
				size = rand() % (SMALL_SIZE * 100 - SMALL_SIZE) + 1 + SMALL_SIZE;
				break;
		}
		buff[i++] = (char*)malloc(size);
	}
	show_alloc_mem();
	i = 0;
	while (i < SAMPLES)
	{
		free(buff[i++]);
	}
	show_alloc_mem();
	return (0);
}
