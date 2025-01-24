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
 * naive_malloc - allocate memory to store something
 * @size: size needed to be allocated for the user
 *
 * Return: ptr to the allocated memory
 */
void *naive_malloc(size_t size)
{
	void *ptr;

	/* TODO: check if the heap can allocate size */
	ptr = sbrk(size);
	if (SBRK_CHECK(ptr))
	{
		fprintf(stderr, "naive_malloc sbrk error\n");
		return (NULL);
	}
	return (ptr);
}
