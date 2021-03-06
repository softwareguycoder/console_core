/*
 * console_core.c
 *
 *  Created on: Jul 30, 2018
 *      Author: bhart
 */

#include "stdafx.h"
#include "console_core.h"

void ClearScreen(void){
	/* clear the terminal window */

	printf("\033[H\033[J");
}

void DisableBufferedConsoleIO(){
    setbuf(stdout, NULL);
}

void ErasePrevLine(void) {
    printf("\x1B[A");   // move cursor up and to beginning of line
    printf("\x1B[K");   // erase everything on current line
}

void ErasePrevText(void) {
    printf("\x1B[F");   // move cursor to beginning of current line
    printf("\x1B[K");   // erase everything on current line
}

void FlushStdin(void) {
	// make stdin non-blocking
	int nFlags = fcntl(0, F_GETFL);
	fcntl(0, F_SETFL, O_NONBLOCK);
	char ch;

	// remove all characters from stdin
	while ((ch = getchar()) != '\n' && ch != EOF) {
	}

	// restore original flags
	fcntl(0, F_SETFL, nFlags);
}

int GetLineFromUser(const char *pszPrompt, char *pszReplyBuffer, int nSize) {
	char ch;
	int nExtra = 0;

	FlushStdin();

	// Get line with buffer overrun protection.  We also display a prompt.
	// To not display a prompt, just pass an empty string ("") for pszPrompt.

	if (!IsNullOrWhiteSpace(pszPrompt)) {
		printf("%s", pszPrompt);
		fflush(stdout);
	}

	// Use nSize + 1 below to allow for the null-terminator
	if (fgets(pszReplyBuffer, nSize + 1, stdin) == NULL)
		return NO_INPUT;

	// If it was too long, there'll be no newline. In that case, we flush
	// to end of line so that excess doesn't affect the next call.
	if (pszReplyBuffer[strlen(pszReplyBuffer) - 1] != '\n') {
		nExtra = 0;
		while (((ch = getchar()) != '\n') && (ch != EOF) && nExtra != 1)
			nExtra = 1;
		return (nExtra == 1) ? TOO_LONG : OK;
	}

	// Otherwise remove newline and give string back to caller.
	pszReplyBuffer[strlen(pszReplyBuffer) - 1] = '\0';

	return (strlen(pszReplyBuffer) == nSize) ? EXACTLY_CORRECT : OK;
}

int GetLineFromUserWithDefault(const char *pszPrompt, char *pszReplyBuffer,
		const char *pszDefaultValue, int nSize) {
	char ch;
	int nExtra = 0;

	FlushStdin();

	// Get line with buffer overrun protection.

	if (pszPrompt != NULL) {
		printf("%s [%s]", pszPrompt, pszDefaultValue);
		fflush(stdout);
	}

	/* Ask fgets for nSize + 1 chars so that the +1'th char is the null-terminator */
	if (fgets(pszReplyBuffer, nSize + 1, stdin) == NULL) {
		/* If we are here and there is no input by the user, then
		 * give the default_value; make sure that buff is big enough
		 * to hold the default_value.   We assume that the size parameter
		 * is filled with the length of the array pointed to by buff. */

		if (nSize < strlen(pszDefaultValue)) {
			return NO_INPUT;
		}
		strcpy(pszReplyBuffer, pszDefaultValue);
		return OK;
	}

	// If the response was too long, there'll be no newline. In that case, we flush
	// to end of line so that excess doesn't affect the next call.
	if (pszReplyBuffer[strlen(pszReplyBuffer) - 1] != '\n') {
		nExtra = 0;
		while (((ch = getchar()) != '\n') && (ch != EOF) && nExtra != 1)
			nExtra = 1;
		return (nExtra == 1) ? TOO_LONG : OK;
	}

	// Otherwise remove newline and give string back to caller.
	pszReplyBuffer[strlen(pszReplyBuffer) - 1] = '\0';

	return (strlen(pszReplyBuffer) == nSize) ? EXACTLY_CORRECT : OK;
}

/** Checks the specified string whether the string contains
 * only numbers or a period. */
int IsNumbersOnly(const char* pszString) {
	int nResult = 0;
	int fContainsOnePeriodOnly = 0;

	if (pszString == NULL || pszString[0] == '\0' || strlen(pszString) == 0)
		return nResult;

	for(int i=0; i<strlen(pszString); i++){
			if(46 != pszString[i] && (57 < pszString[i] || 48 > pszString[i])){
				return nResult;			/* stop on the first non-numeric char with a
				                      'false' result */
			} else if (46 == pszString[i]) {
				if (fContainsOnePeriodOnly == 0) {
					fContainsOnePeriodOnly = 1;
				} else if (fContainsOnePeriodOnly == 1) {
					fContainsOnePeriodOnly = 2;		/* contains more than one period */
				}
			}
		}
	return (int)(fContainsOnePeriodOnly <= 1);		/* indicates that a string
	  is all digits, and has at most one period (i.e. for a decimal) */
}

void PromptForKeyPress(void){
	printf("\nPress any key to continue...\n");
	getchar();
}

void PrintStrings(char* ppszStrings[], int nCount) {
	// The value of count must be greater than or equal to zero
	if (nCount <= 0)
		return;

	for (int i = 0; i < nCount; i++) {
		printf("%s\r\n", ppszStrings[i]);
	}
}
