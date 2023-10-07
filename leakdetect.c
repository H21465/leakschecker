/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leakdetect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 07:26:05 by hayato            #+#    #+#             */
/*   Updated: 2023/10/08 07:27:12 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "leakdetect.h"

#define N 500

t_mem mem_info[N];

void	leak_detect_init(void)
{
	int	idx;

	idx = -1;
	while (++idx < N)
	{
		mem_info[idx].ptr = NULL;
		mem_info[idx].size = 0;
		mem_info[idx].file = NULL;
		mem_info[idx].line = 0;
	}
}

void	*leak_detelc_malloc(size_t size, const char *file, unsigned int line)
{
	int		idx;
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	idx = -1;
	while (++idx < N)
	{
		if (mem_info[idx].ptr == NULL)
		{
			mem_info[idx].ptr = ptr;
			mem_info[idx].size = size;
			mem_info[idx].file = file;
			mem_info[idx].line = line;
			break ;
		}
	}
	return (ptr);
}

void	leak_detect_free(void *ptr)
{
	int	idx;

	idx = -1;
	while (++idx < N)
	{
		if (mem_info[idx].ptr == ptr)
		{
			mem_info[idx].ptr = NULL;
			mem_info[idx].size = 0;
			mem_info[idx].file = NULL;
			mem_info[idx].line = 0;
			break ;
		}
	}
	free(ptr);
}

void	leak_detect_check(void)
{
	int	idx;
	int	count;

	idx = -1;
	count = 0;
	while (++idx < N)
	{
		if (mem_info[idx].ptr != NULL)
		{
			++count;
			if (count == 1)
				printf("メモリリークを検出\n");
			printf("\x1b[31m=== %d ===\n\x1b[0m", count);
			printf(" address\t: %p\n", mem_info[idx].ptr);
			printf(" size\t\t: %zu\n", mem_info[idx].size);
			printf(" area\t\t: %s:%u\n", mem_info[idx].file, mem_info[idx].line);
			printf("\n");
		}
	}
	printf("total: \x1b[31m%d\x1b[0m leaks\n", count);
	if (count == 0)
		printf ("%d leaks but you need to check your code!!\n", count);
}
