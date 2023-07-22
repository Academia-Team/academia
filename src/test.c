/**
 * @file test.c
 * @author Academia Team
 * @brief Contains constants and functions designed to assist in testing.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "bool.h"
#include "input.h"
#include "test.h"
#include "types.h"

#define MAX_CHARS_FOR_INPUT_PROMPT 80

#define TEST_PROMPT_INPUT_REQ "Press enter to continue or q to skip."

TestSuite regTests[MAX_NUM_TEST_SUITES];
UINT8 testFillLevel  = 0;
UINT8 suiteIdx       = 0;

TestSuiteID registerTestSuite(const char *description,
							  void (*tstMgr)(void (*tstFunc)(ArgList *args)))
{
	TestSuiteID suiteID = TEST_SUITE_ERR;

	if (testFillLevel < MAX_NUM_TEST_SUITES && description != NULL)
	{
		strncpy(regTests[testFillLevel].description, description,
				MAX_TEST_DESCRIPTION_LEN + 1);
		
		regTests[testFillLevel].tstMgr = tstMgr;
		regTests[testFillLevel].numTestCases = 0;
		regTests[testFillLevel].testCaseIdx = 0;

		suiteID = testFillLevel++;
	}

	return suiteID;
}

BOOL registerTestCase(TestSuiteID testSuite, const char *description,
					  void (*tstMgr)(void (*tstFunc)(ArgList *args)), 
					  void (*tstFunc)(ArgList *args))
{
	BOOL registerSuccess = FALSE;
	TestSuite *suiteObj  = NULL;
	UINT8 fillLevel;

	if (testSuite != TEST_SUITE_ERR && testSuite < testFillLevel &&
		testSuite >= 0 && description != NULL)
	{
		if (regTests[testSuite].numTestCases <= MAX_NUM_TEST_CASES)
		{
			if ((tstMgr != NULL || regTests[testSuite].tstMgr != NULL) &&
				tstFunc != NULL)
			{
				suiteObj = &regTests[testSuite];
			}
		}
	}

	if (suiteObj != NULL)
	{
		fillLevel = suiteObj->numTestCases;
		strncpy(suiteObj->tstCases[fillLevel].description, description,
				MAX_TEST_DESCRIPTION_LEN + 1);

		suiteObj->tstCases[fillLevel].tstMgr = (
			tstMgr == NULL ? suiteObj->tstMgr : tstMgr
		);

		suiteObj->tstCases[fillLevel].tstFunc = tstFunc;
		suiteObj->numTestCases++;
		suiteObj->tstCases[fillLevel].ID = suiteObj->numTestCases;
	}
}

void showTestSuiteInfo(FILE *stream, const TestSuite * const test)
{
	if (stream != NULL && test != NULL)
	{
		fprintf(stream, "Test Suite #%u:\n", suiteIdx);
		fputc('\n', stream);

		fprintf(stream, "%s\n", test->description);
		fputc('\n', stream);

		fprintf(stream, "Num of test cases: %u\n", test->numTestCases);
	}
}

void showTestCaseInfo(FILE *stream, const TestCase * const test)
{
	if (stream != NULL && test != NULL)
	{
		fprintf(stream, "Test Case #%u:\n", test->ID);
		fputc('\n', stream);

		fprintf(stream, "%s\n", test->description);
	}
}

void showTestPrompt(FILE *stream)
{
	if (stream != NULL)
	{
		fprintf(stream, "\n%s\n", TEST_PROMPT_INPUT_REQ);
	}
}

TestSuite *getNextTestSuite()
{
	TestSuite *nextTestSuite = NULL;

	if (suiteIdx < testFillLevel)
	{
		nextTestSuite = &regTests[suiteIdx++];
	}

	return nextTestSuite;
}

TestCase *getNextTestCase(TestSuite *suite)
{
	TestCase *nextTestCase = NULL;

	if (suite != NULL && suite->testCaseIdx < suite->numTestCases)
	{
		nextTestCase = &suite->tstCases[suite->testCaseIdx++];
	}

	return nextTestCase;
}

void runTest(TestCase *test)
{
	if (test != NULL)
	{
		test->tstMgr(test->tstFunc);
	}
}

char* getBoolName(BOOL val, char *boolName)
{
	switch(val)
	{
		case TRUE:
			boolName = "TRUE";
			break;
		case FALSE:
			boolName = "FALSE";
			break;
		default:
			boolName = "Unknown";
	}

	return boolName;
}