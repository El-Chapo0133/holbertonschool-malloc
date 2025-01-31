/*
 * ==========================================================================
 *
 *       Filename:  malloc.c
 *
 *    Description:  own malloc function that allocates space in the heap
 *
 *        Version:  1.0
 *        Created:  01/29/2025 01:27:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Loris Leveque (9601@holbertonstudent.com)
 *   Organization:  Holberton
 *
 * ==========================================================================
 */

#include "malloc.h"

/**
 * sbrk_one_page - first call try to sbrk
 *
 * Return: ptr to the first chunk
 */
void *sbrk_one_page(void)
{
	void *ptr;

	ptr = sbrk(PAGE_SIZE);
	if (SBRK_CHECK(ptr))
	{
		fprintf(stderr, "sbrk_one_page sbrk error\n");
		return (NULL);
	}

	return (ptr);
}

/**
 * sbrk_size - sbrk if the size requires it
 * @ptr: ptr to currently allocated page
 * @aligned_size: size to allocated aligned to METADATA
 * @size: wanted size to allocated
 *
 * Return: ptr to the allocated memory
 */
void *sbrk_size(void *ptr, size_t aligned_size, size_t size,
		size_t heap_counter, size_t avail_size)
{
	size_t temp, final_size = 0;

	temp = (heap_counter ? avail_size : PAGE_SIZE);
	/* basically align the wanted value to the PAGE_SIZE (4097 -> 8182) */
	while (temp + final_size < size)
		final_size += PAGE_SIZE;
	temp += final_size;

	/* only occurs when final_size is set, otherwise AVAIL_SIZE is enough */
	if (final_size && SBRK_CHECK(sbrk(temp)))
		return (NULL);

	avail_size = temp - aligned_size;
	*(size_t *)((char *)ptr + 0x8) = temp;
	return (ptr);
}

/**
 * find_free_block - try to find a free block on the heap
 * @ptr: ptr to the first heap_chunk address
 * move that ptr to the found chunk
 *
 * Return: 1 if found 0 if not
 */
int find_free_block(void **ptr, size_t heap_counter)
{
	size_t index, temp, prev_size, used;

	for (index = 0; index < heap_counter; index++)
	{
		prev_size = *(size_t *)(*ptr);
		temp = (*(size_t *)((char *)(*ptr) + 0x8)) - 1 + (prev_size ? 1 : 0);
		used = (temp & 1);
		temp = ((!prev_size && used) ? temp + 1 : temp);
		if (prev_size && !used && prev_size >= temp)
			return (true);

		(*ptr) = (char *)(*ptr) + temp;
	}
	return (false);
}


/**
 * _malloc - own malloc function
 * @size: size wanted
 *
 * Return: ptr to allocated memory
 */
void *_malloc(size_t size)
{
	static void *first_heap_chunk;
	static size_t heap_counter = 0, avail_size = 0;
	void *ptr = NULL;
	size_t chunk_size = ALIGN(size) + METADATA;
	/* size_t index, temp, prev_size, used; */

	if (!first_heap_chunk)
	{
		first_heap_chunk = sbrk_one_page();
		if (!first_heap_chunk)
			return (NULL);
	}

	ptr = first_heap_chunk;
	if (!find_free_block(&ptr, heap_counter))
	{
		ptr = sbrk_size(ptr, chunk_size, size,
				heap_counter, avail_size);
		(*(size_t *)((char *)ptr + 0x8))++;
	}

	heap_counter++;
	return ((char *)ptr + METADATA);
}
