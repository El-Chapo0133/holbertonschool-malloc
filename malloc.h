#ifndef H_MALLOC
#define H_MALLOC
/*
 * ==========================================================================
 *
 *       Filename:  malloc.h
 *
 *    Description:  malloc header file
 *
 *        Version:  1.0
 *        Created:  20.01.2025 12:01:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Loris Levêque (9601), loris@leveque.website
 *   Organization:  Holberton
 *
 * ==========================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define true 1
#define false 0

#define METADATA 0x10
#define METADATA_USED 0x8
#define PAGE_SIZE 4096
#define INVALID_PTR ((void *)-1)
#define SBRK_CHECK(x) (x == INVALID_PTR)
#define ALIGN(x) (x + (8 - (x % 8)))


/**
 * struct heap_chunk_s - chunk of the heap
 * @span: distance to the next heap_chunk_t
 * @stored: amount of bytes currently stored
 */
typedef struct heap_chunk_s
{
	size_t span;
	size_t stored;
} heap_chunk_t;

/* core functions */
void *naive_malloc(size_t size);
void *_malloc(size_t size);

/* side functions */

/* utils */
void *get_current_break(void);

#endif
