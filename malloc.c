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
 * _malloc - own malloc function
 * @size: size wanted
 *
 * Return: ptr to allocated memory
 */
void *_malloc(size_t size)
{
	static char *start, *end;
	static size_t avail_size;
	size_t h_size = sizeof(size_t);
	char *ptr;
	heap_chunk_t *current, *next;

	size = ALIGN(size);
	if (!start)
		start = sbrk(0), end = start;

	ptr = start;
	while (ptr < end)
	{
		current = (heap_chunk_t *)ptr;
		if (current->stored == 0)
			break;
		if (current->span - current->stored >= size)
		{
			next = (heap_chunk_t *)(ptr + current->stored + h_size);
			next->span = current->span - current->stored - h_size;
			current->span = current->stored;
			ptr = (char *)next;
			break;
		}
		ptr += h_size + current->span;
	}

	current = (heap_chunk_t *)ptr;
	if (ptr == end)
	{
		for (; avail_size < size + h_size; avail_size += PAGE_SIZE)
			if (!sbrk_one_page())
				return (NULL);
		current->span = size;
		end = ptr + size + h_size;
		avail_size = avail_size - size - h_size;
	}
	current->stored = size;
	return (ptr + h_size);
}
