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
 * @heap_counter: counter of heap chunks
 * @avail_size: counter of available size
 *
 * Return: ptr to the allocated memory
 */
void *sbrk_size(void *ptr, size_t aligned_size, size_t size,
		size_t heap_counter, size_t avail_size)
{
	size_t temp, adder_size = 0;

	temp = (heap_counter ? avail_size : PAGE_SIZE);
	/* add pages when the size to bigger than the available size */ 
	while (temp + adder_size < size)
		adder_size += PAGE_SIZE;
	temp += adder_size;

	/* only occurs when adder_size is set, otherwise AVAIL_SIZE is enough */
	if (adder_size && SBRK_CHECK(sbrk(temp)))
		return (NULL);

	avail_size = temp - aligned_size;
	fprintf(stdout, "%ld\n", avail_size);
	/* set the temp value on the ptr chunk */
	*(size_t *)((char *)ptr + METADATA_USED) = temp;
	return (ptr);
}

/**
 * find_free_block - try to find a free block on the heap
 * @ptr: ptr to the first heap_chunk address
 * move that ptr to the found chunk
 * @heap_counter: counter of heap chunks
 *
 * Return: 1 if found 0 if not
 */
int find_free_block(void **ptr, size_t heap_counter)
{
	size_t index, temp, prev_size, used;

	/* loop over all chunks */
	for (index = 0; index < heap_counter; index++)
	{
		/* if the chunk is not used and has enough size */
		prev_size = *(size_t *)(*ptr);
		temp = (*(size_t *)((char *)(*ptr) + METADATA_USED)) - 1 + (prev_size ? 1 : 0);
		used = (temp & 1);
		temp = ((!prev_size && used) ? temp + 1 : temp);
		if (prev_size && !used && prev_size >= temp)
			return (true);

		/* move ptr to the next chunk */
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
	/* ptr to the first chunk on the heap */
	static void *first_heap_chunk;
	/* counter of the chunks and available size */
	static size_t heap_counter, avail_size;
	void *ptr = NULL;
	size_t chunk_size = ALIGN(size) + METADATA;

	/* first call, must sbrk one page */
	if (!first_heap_chunk)
	{
		first_heap_chunk = sbrk_one_page();
		if (!first_heap_chunk)
			return (NULL);
	}

	/* next calls, look for a free chunk, if not found allocate new page */
	ptr = first_heap_chunk;
	if (!find_free_block(&ptr, heap_counter))
	{
		ptr = sbrk_size(ptr, chunk_size, size,
				heap_counter, avail_size);
		/* indicate that the chunk on the ptr is used */
		(*(size_t *)((char *)ptr + METADATA_USED))++;
	}

	heap_counter++;
	return ((char *)ptr + METADATA);
}
