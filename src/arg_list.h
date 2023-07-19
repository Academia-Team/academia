/**
 * @file arg_list.h
 * @author Academia Team
 * @brief Provides structures and functionality to allow for the creation and
 * management of lists of function arguments.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef ARG_LIST_H
#define ARG_LIST_H

#include "bool.h"

/**
 * @brief The maximum number of arguments that can be placed in a ArgList.
 */
#define MAX_ARGS_IN_LIST 8

/**
 * @brief The maximum length (excluding the null terminator) of a string
 * describing a parameter placed within a ArgList.
 */
#define MAX_ARG_NAME_LEN 40

/**
 * @brief A null-terminated string representing the name of a function argument.
 */
typedef char ArgName[MAX_ARG_NAME_LEN + 1];

/**
 * @brief A object that stores information related to function arguments.
 * @details Must be initialized before use.
 */
typedef struct
{
	int numArgs;
	void *args[MAX_ARGS_IN_LIST];
	ArgName names[MAX_ARGS_IN_LIST];
} ArgList;

/**
 * @brief Initializes a ArgList object.
 * 
 * @param argList The ArgList object to initialize.
 */
void initArgList(ArgList *argList);

/**
 * @brief Add an argument to the given ArgList.
 * 
 * @param argName The name of the argument. Cannot be NULL or already in use.
 * @param arg The value to store in the argList (as an address).
 * @param argList The ArgList to add the argument to.
 * @return TRUE if the argument was successfully added to the ArgList; FALSE
 * otherwise.
 */
BOOL appendArgToList(const char *argName, const void * const arg,
					 ArgList *argList);

/**
 * @brief Gets the value associated with the given argument name from an ArgList
 * object.
 * 
 * @param argName The name of the argument desired.
 * @param argList The ArgList to search for the argument in.
 * @return The address stored associated with the argument name or NULL if the
 * argument isn't recognized.
 */
void *getArgFromList(const char *argName, const ArgList * const argList);

#endif
