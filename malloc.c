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

void *FIRST_CHUNK;
size_t AVAIL_SIZE;
size_t LEN;

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

void sbrk_size(void *ptr, size_t chunk_avail, size_t size)
{
	size_t temp, final_size = 0;

	temp = (LEN ? AVAIL_SIZE : PAGE_SIZE);
	/* basically align the wanted value to the PAGE_SIZE (4097 -> 8182) */
	/* final_size = size + (PAGE_SIZE - (size % PAGE_SIZE)); */
	do {
		final_size += PAGE_SIZE;
	} while (temp + final_size < size);
	temp += final_size;

	if (SBRK_CHECK(sbrk(temp)))
		return (NULL);

	AVAILABLE = temp - chunk_avail;
	*(size_t *)((char *)ptr + 0x8) = block;
	return (ptr);
}

int find_free_block(void **ptr)
{
	size_t index, temp, prev_size, used;

	for (index = 0; index < LEN; index++)
	{
		prev_size = *(size_t *)(*ptr);
		temp = (*(size_t *)((char *)(*ptr) + 0x8)) - 1 + (prev_size ? 1 : 0);
		used = (temp & 1);
		temp = ((!prev_size && used) ? temp + 1 : temp);
		if (prev_size && !used && prev_size >= temp)
			return (true);

		(*ptr) = (char *)(*ptr) + block_size;
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
	void *ptr = NULL;
	size_t chunk_size = ALIGN(size) + METADATA;
	/* size_t index, temp, prev_size, used; */

	if (!FIRST_CHUNK)
	{
		FIRST_CHUNK = sbrk_one_page();
		if (!FIRST_CHUNK)
			return (NULL);
	}

	ptr = FIRST_CHUNK;
	if (!find_free_block(&ptr))
	{
		ptr = sbrk_size(ptr, chunk_size, size);
		(*(size_t *)((char *)ptr + 0x8))++;
	}

	LEN++;
	return ((char *)ptr + METADATA);
}
