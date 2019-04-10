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
int GetLineFromUser(const char *pszPrompt, char *pszReplyBuffer, int nSize);
int GetLineFromUserWithDefault(const char *pszPrompt, char *pszReplyBuffer, const char *pszDefaultValue, int nSize);
int IsNumbersOnly(const char* pszString);
void PrintStrings(char *ppszStrings[], int nCount);
void PromptForKeyPress(void);

#endif /* __CONSOLE_CORE_H__ */
