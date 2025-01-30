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

/**
 * _malloc - own malloc function
 * @size: size wanted
 *
 * Return: ptr to allocated memory
 */
void *_malloc(size_t size)
{
	void *ptr = NULL;
	/* size_t chunk_size = ALIGN(size) + METADATA;
	size_t index, temp, prev_size, used; */

	if (!FIRST_CHUNK)
	{
		FIRST_CHUNK = sbrk_one_page();
		if (!FIRST_CHUNK)
			return (NULL);
	}

	ptr = FIRST_CHUNK;
	

	LEN++;
	return ((char *)ptr + METADATA);
}
