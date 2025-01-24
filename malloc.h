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

#define METADATA 0x10
#define PAGE_SIZE 4096
#define INVALID_PTR ((void *)-1)
#define SBRK_CHECK(x) (x == INVALID_PTR)
#define ALIGN(x) (x + (METADATA - (x % METADATA)))


/**
 * struct heap_chunk_s - chunk of the heap
 * @start: ptr to the start of the heap chunk
 * @end: ptr to the end of the heap chunk
 * @next: ptr to the next heap chunk
 */
typedef struct heap_chunk_s
{
	void *start;
	void *end;
	struct heap_chunk_s *next;
} heap_chunk_t;

/* core functions */
void *naive_malloc(size_t size);

/* side functions */

/* utils */
void *get_current_break(void);

#endif
