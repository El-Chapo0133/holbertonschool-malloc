/*
 * ==========================================================================
 *
 *       Filename:  brk_utils.c
 *
 *    Description:  utils functions for brk and sbrk
 *
 *        Version:  1.0
 *        Created:  24.01.2025 09:40:19
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
 * get_current_break - get the current break line
 *
 * Return: ptr to the current break line, -1 on error
 */
void *get_current_break()
{
	/**
	 * 0 means to not move the break line
	 * meaning it will return the current break line
	 */
	return (sbrk(0));
}
