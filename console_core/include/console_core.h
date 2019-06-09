/*
 * console_core.h
 *
 *  Created on: Jul 30, 2018
 *      Author: bhart
 */

#ifndef __CONSOLE_CORE_H__
#define __CONSOLE_CORE_H__

#include "console_core_symbols.h"

void ClearScreen(void);
void DisableBufferedConsoleIO();
void ErasePrevLine(void);
void ErasePrevText(void);
void FlushStdin(void);

/**
 * @brief Prompts the user for a line of text, and returns what the user
 * types after the user confirms the input by pressing the ENTER key.
 * @param pszPrompt String containing the prompt to be shown.
 * @param pszReplyBuffer Address of storage to which the typed text will
 * be copied.
 * @param nSize Length of the buffer referred to by pszReplyBuffer.
 * @returns OK or EXACTLY_CORRECT if user input was written correctly; these
 * constants are both defined to be either zero or 1, respectively.  A negative
 * number is returned if an error occurred.
 * @remarks Typically, the error is TOO_LONG indicating that the user typed
 * more characters than could all be placed into the reply buffer.  The
 * function tries to copy as much user input into the reply buffer as it
 * possibly can. If the user merely presses ENTER at the prompt without
 * typing anything, then the user will be shown the prompt over again.
 */
int GetLineFromUser(const char *pszPrompt, char *pszReplyBuffer, int nSize);

/**
 * @brief Prompts the user for a line of text, and returns what the user
 * types after the user confirms the input by pressing the ENTER key.
 * @param pszPrompt String containing the prompt to be shown.
 * @param pszReplyBuffer Address of storage to which the typed text will
 * be copied.
 * @param pszDefaultValue String containing the value to be copied to the
 * reply buffer in the event that the user does not type anything at the
 * prompt but merely presses ENTER.
 * @param nSize Length of the buffer referred to by pszReplyBuffer.
 * @returns OK or EXACTLY_CORRECT if user input was written correctly; these
 * constants are both defined to be either zero or 1, respectively.  A negative
 * number is returned if an error occurred.
 * @remarks Typically, the error is TOO_LONG indicating that the user typed
 * more characters than could all be placed into the reply buffer.  The
 * function tries to copy as much user input into the reply buffer as it
 * possibly can.
 */
int GetLineFromUserWithDefault(const char *pszPrompt, char *pszReplyBuffer,
        const char *pszDefaultValue, int nSize);
int IsNumbersOnly(const char* pszString);
void PrintStrings(char *ppszStrings[], int nCount);
void PromptForKeyPress(void);

#endif /* __CONSOLE_CORE_H__ */
