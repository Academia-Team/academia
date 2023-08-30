/**
 * @file arg_list.c
 * @author Academia Team
 * @brief Provides structures and functionality to allow for the creation and
 * management of lists of function arguments.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stddef.h>
#include <string.h>

#include "arg_list.h"
#include "bool.h"

void initArgList(ArgList *argList)
{
	if (argList != NULL)
	{
		argList->numArgs = 0;
	}
}

BOOL appendArgToList(const char *argName, const void * const arg,
					 ArgList *argList)
{
	int  index;
	BOOL status = FALSE;

	if (argList->numArgs < MAX_ARGS_IN_LIST && argName != NULL && arg != NULL &&
		argList != NULL)
	{
		status = TRUE;
		
		for (index = 0; index < argList->numArgs && !status; index++)
		{
			status = (strcmp(argName, argList->names[index]));
		}
	}

	if (status)
	{
		argList->args[argList->numArgs] = arg;
		strncpy(argList->names[argList->numArgs], argName, MAX_ARG_NAME_LEN);
		argList->numArgs++;
	}

	return status;
}

void *getArgFromList(const char *argName, const ArgList * const argList)
{
	int  index;
	void *arg = NULL;

	if (argName != NULL && argList != NULL)
	{
		for (index = 0; index < argList->numArgs && arg == NULL; index++)
		{
			if (!strcmp(argName, argList->names[index]))
			{
				arg = argList->args[index];
			}
		}
	}

	return arg;
}