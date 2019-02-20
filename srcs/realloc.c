#include "lib_alloc.h"

void	*new_malloc(size_t size, void *ptr, t_alloc type)
{
	void	*new_ptr;
	t_block	*new_block;

	new_ptr = malloc_n(size);
	if (!new_ptr)
		return (NULL);
	new_block = find_block_of_ptr(new_ptr, &type);
	new_ptr = ft_memcpy(new_ptr, ptr, size);
	free_n(ptr);
	return (new_ptr);
}

void	*handle_realloc_block(void *ptr, size_t s, t_block *block, t_alloc t)
{
	size_t	aligned_size;

	aligned_size = align_size(s, 4);
	if (block->size >= aligned_size)
	{
		if (block->size - aligned_size >= sizeof(t_block))
			split_block(aligned_size, block);
	}
	else
	{
		if (block->next && block->next->free &&
			block->size + sizeof(t_block) + block->next->size >= aligned_size)
		{
			defragment_around(block);
			if (block->size - aligned_size >= sizeof(t_block))
				split_block(aligned_size, block);
		}
		else
			return (new_malloc(aligned_size, ptr, t));
	}
	return ((void *)((char *)block + sizeof(t_block)));
}

void	*realloc_n(void *ptr, size_t size)
{
	t_block	*block;
	t_alloc	type;

	if (!ptr)
		return (malloc_n(size));
	if (ptr && !size)
	{
		free_n(ptr);
		return (malloc_n(TINY));
	}
	type = TINY_TYPE;
	block = find_block_of_ptr(ptr, &type);
	if (block)
		return (handle_realloc_block(ptr, size, block, type));
	return (NULL);
}

void	*realloc(void *ptr, size_t size)
{
	void	*res;

	res = realloc_n(ptr, size);

	return (res);
}
