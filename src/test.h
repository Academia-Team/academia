/**
 * @file test.h
 * @author Academia Team
 * @brief Contains constants and functions designed to assist in testing.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef TEST_H
#define TEST_H

#include <osbind.h>
#include <stdio.h>

#include "arg_list.h"
#include "bool.h"
#include "raster.h"
#include "super.h"
#include "types.h"

#define MAX_BOOL_NAME_LEN 7
typedef char BoolName[MAX_BOOL_NAME_LEN + 1];

/**
 * @brief Returns the friendly name of a boolean (TRUE/FALSE).
 * 
 * @param val The boolean value to read.
 * @param boolName The boolean name to return.
 * @return The name of the boolean value given.
 */
char* getBoolName(BOOL val, char *boolName);

/**
 * @brief The maximum number of test cases per test suite.
 */
#define MAX_NUM_TEST_CASES 128

/**
 * @brief The maximum number of test suites.
 */
#define MAX_NUM_TEST_SUITES 20

/**
 * @brief The maximum length of a test description (excluding the NULL
 * terminator).
 */
#define MAX_TEST_DESCRIPTION_LEN 120

/**
 * @brief Stores information used to test specific functionality.
 */
typedef struct
{
	char description[MAX_TEST_DESCRIPTION_LEN + 1];
	void (*tstMgr)(void (*tstFunc)(ArgList *args));
	void (*tstFunc)();
	UINT8 ID;
} TestCase;

/**
 * @brief Holds several TestCases and default options for those TestCases.
 */
typedef struct
{
	char description[MAX_TEST_DESCRIPTION_LEN + 1];
	void (*tstMgr)(void (*tstFunc)(ArgList *args));
	TestCase tstCases[MAX_NUM_TEST_CASES];
	UINT8 numTestCases;
	UINT8 testCaseIdx;
} TestSuite;

/**
 * @brief A unique identifier for every TestSuite registered.
 */
typedef UINT8 TestSuiteID;

/**
 * @brief Indicates an invalid TestSuite.
 */
#define TEST_SUITE_ERR -1

/**
 * @brief Registers a TestSuite.
 * 
 * @param description A string describing the purpose of the Test Suite. Cannot
 * be NULL.
 * @param tstMgr A function that prepares for (and cleans up) after any test
 * functions run. Can be NULL.
 * @return A unique identifier for the registered TestSuite or TEST_SUITE_ERR
 * if the TestSuite could not be registered.
 */
TestSuiteID registerTestSuite(const char *description,
							  void (*tstMgr)(void (*tstFunc)(ArgList *args)));

/**
 * @brief Registers a Test Case.
 * 
 * @param testSuite A identifier describing the Test Suite that the Test Case
 * should be associated with.
 * @param description A string describing the purpose of the Test Suite. Cannot
 * be NULL.
 * @param tstMgr A function that prepares for (and cleans up) after any test
 * functions run. Can be NULL if and only if the parent Test Suite has a tstMgr
 * that is not NULL.
 * @param tstFunc A function that tests specific functionality.
 * 
 * @return TRUE if the test case could be registered; FALSE otherwise.
 */
BOOL registerTestCase(TestSuiteID testSuite, const char *description,
					  void (*tstMgr)(void (*tstFunc)(ArgList *args)), 
					  void (*tstFunc)(ArgList *args));

/**
 * @brief Displays information on the Test Suite to the given stream.
 * @details The information shown includes a numerical sequential identifier,
 * a description of the Test Suite, and the number of test cases contained
 * within the suite.
 * 
 * @param stream The file to write the information to.
 * @param test The TestSuite to display the information of.
 */
void showTestSuiteInfo(FILE *stream, const TestSuite * const test);

/**
 * @brief Displays information on the Test Case to the given stream.
 * @details The information shown includes a numerical sequential identifier and
 * a description of the Test Case.
 * 
 * @param stream The file to write the information to.
 * @param test The TestCase to display the information of.
 */
void showTestCaseInfo(FILE *stream, const TestCase * const test);

/**
 * @brief Displays a prompt for input to the given stream.
 * 
 * @param stream The file to write the prompt to.
 */
void showTestPrompt(FILE *stream);

/**
 * @brief Get the next registered Test Suite object
 * @details The Test Suites are returned in the order they were registered.
 * 
 * @return A pointer to a TestSuite or NULL if there are no more TestSuites to
 * return.
 */
TestSuite *getNextTestSuite();

/**
 * @brief Get the next Test Suite object associated with the given Test Suite.
 * @details The Test Cases are returned in the order they were registered with
 * their parent Test Suite.
 * 
 * @param suite The TestSuite that contains the desired TestCase.
 * @return A pointer to a TestCase or NULL if there are no more TestCases to
 * return.
 */
TestCase *getNextTestCase(TestSuite *suite);

/**
 * @brief Runs the test from the given TestCase.
 * 
 * @param test The TestCase that contains information on what to test.
 */
void runTest(TestCase *test);

/**
 * @brief Prompts the user to execute the given test function.
 * @details As part of running, it will clear the screen to ensure that the
 * text can be properly printed.
 * 
 * @param func The function call to execute.
 */
#define run_test(func) \
	clr_scrn((UINT32 *)Physbase()); \
	printf("Next test func: %s\n", #func); \
	printf("Press enter to continue or q to skip.\n"); \
	if ((Cnecin() & 0xFF) != 'q') \
	{ \
		clr_scrn((UINT32 *)Physbase()); \
		func; \
	} \
	else \
	{ \
		clr_scrn((UINT32 *)Physbase()); \
	}

/**
 * @brief Disables the cursor.
 */
void off_curs();

/**
 * @brief Enables the cursor.
 */
void on_curs();

#endif
