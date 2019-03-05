/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:36:30 by pchadeni          #+#    #+#             */
/*   Updated: 2019/02/25 16:50:28 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*result;

	pthread_mutex_lock(&g_mutex);
	result = malloc_n(count * size);
	if (result)
		ft_bzero(result, count * size);
	pthread_mutex_unlock(&g_mutex);
	return (result);
}

void	*reallocf(void *ptr, size_t size)
{
	void	*res;

	res = realloc(ptr, size);
	if (!res && ptr)
		free(ptr);
	return (res);
}

size_t	malloc_size(void *ptr)
{
	t_alloc	type;
	t_block	*tmp;

	tmp = find_block_of_ptr(ptr, &type);
	if (tmp)
		return (tmp->size);
	return (0);
}

size_t	malloc_good_size(size_t size)
{
	return (align_size(size, 16));
}