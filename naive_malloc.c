/*
 * ==========================================================================
 *
 *       Filename:  naive_malloc.c
 *
 *    Description:  naive malloc
 *
 *        Version:  1.0
 *        Created:  20.01.2025 12:00:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Loris Levêque (9601), loris@leveque.website
 *   Organization:  Holberton
 *
 * ==========================================================================
 */

#include "malloc.h"

/**
 * sbrk_one_page - first call try to sbrk
 * @page: page number ptr
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
 * naive_malloc - allocate memory to store something
 * @size: size needed to be allocated for the user
 *
 * Return: ptr to the allocated memory
 */
void *naive_malloc(size_t size)
{
	static size_t avail_mem;
	static void *start, *end;
	void *ptr = NULL;
	size_t h_size = sizeof(size_t);

	if (!start)
		start = sbrk(0);
	size = ALIGN(size);

	while (avail_mem < size + h_size)
	{
		if (!sbrk_one_page())
			return (NULL);
		avail_mem += PAGE_SIZE;
	}

	ptr = start;
	if (!end)
		end = ptr;
	else
	{
		while (ptr != end)
			*(size_t *)ptr += h_size + *(size_t *)ptr;
		*(size_t *)ptr += h_size + *(size_t *)ptr;
		end = ptr;
	}

	*(size_t *)ptr = size;
	return ((size_t *)ptr + h_size));
}
