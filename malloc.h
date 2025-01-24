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

#include "brk_utils.c"

#define HEAP_OFFSET 0x10
#define INVALID_PTR ((void *)-1)
#define SBRK_CHECK(x) (x == INVALID_PTR)



/* core functions */
void *naive_malloc(size_t size);

/* side functions */

/* utils */
void *get_current_break(void);

#endif
