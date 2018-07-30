/*
 * console_core.h
 *
 *  Created on: Jul 30, 2018
 *      Author: bhart
 */

#ifndef __CONSOLE_CORE_H__
#define __CONSOLE_CORE_H__

#include "symbols.h"

void clear_screen(void);
void flush_stdin(void);
int get_line(const char *prmpt, char *buff, int size);
int get_line_with_default(const char *prmpt, char *buff, const char *default_value, int size);
int is_numbers_only(const char* string);
void print_strings(char** strings, int count);
void prompt_for_key_press(void);

#endif /* __CONSOLE_CORE_H__ */
