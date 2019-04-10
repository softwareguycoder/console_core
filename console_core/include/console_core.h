/*
 * console_core.h
 *
 *  Created on: Jul 30, 2018
 *      Author: bhart
 */

#ifndef __CONSOLE_CORE_H__
#define __CONSOLE_CORE_H__

#include "symbols.h"

void ClearScreen(void);
void FlushStdin(void);
int GetLineFromUser(const char *prmpt, char *buff, int size);
int GetLineFromUserWithDefault(const char *prmpt, char *buff, const char *default_value, int size);
int IsNumbersOnly(const char* string);
void PrintStrings(char *ppszStrings[], int count);
void PromptForKeyPress(void);

#endif /* __CONSOLE_CORE_H__ */
