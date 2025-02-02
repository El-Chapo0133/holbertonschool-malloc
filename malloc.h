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


#define align(offset, align) ((offset + (align - 1)) & -align)
#define ALIGNMENT sizeof(void *)
#define PADDING(n) ((ALIGNMENT - ((n) & (ALIGNMENT - 1))) & (ALIGNMENT - 1))
#define MIN_SIZE sizeof(void *)
#define PAGESIZE sysconf(_SC_PAGESIZE)
#define HDR_SZ sizeof(block_info)
#define align_up(num, align) (((num) + ((align) - 1)) & ~((align) - 1))
#define LSB_ZERO_MASK 0xfffffffffffffffe
#define _GET_SIZE(p) (((block_info *)(p))->size)
#define _GET_PREV(p) (((block_info *)(p))->prev)
#define GET_SIZE(p) ((((block_info *)(p))->size) & LSB_ZERO_MASK)
#define GET_PREV(p) ((((block_info *)(p))->prev) & LSB_ZERO_MASK)

/**
 * struct heap_info_s - stores info about heap
 * @heap_start: start of heap
 * @heap_end: end of heap
 */
typedef struct heap_info_s
{
	void *heap_start;
	void *heap_end;
} heap_info;

/**
 * struct block_info_s - stores info block
 * @prev: prev
 * @size: size
 */
typedef struct block_info_s
{
	size_t prev;
	size_t size;
} block_info;

/**
 * struct chunk_s - malloc chunk header
 *
 * @prev_size: size of the previous chunk (only if not in-use)
 * @size: size of the chunk and in-use bit of the previous chunk
 * @next_free: pointer to the next free chunk in a circular doubly-linked list
 * @prev_free: pointer to the prev free chunk in a circular doubly-linked list
 */
typedef struct chunk_s
{
	size_t prev_size;
	size_t size;
	struct chunk_s *next_free;
	struct chunk_s *prev_free;
} chunk_t;


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
