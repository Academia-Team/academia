/**
 * @file tst_hndl.c
 * @author Academia Team
 * @brief Provides an interface around the test functions to run through all
 * registered tests.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stddef.h>

#include "bool.h"
#include "input.h"
#include "test.h"
#include "tst_hndl.h"
#include "vector.h"

void handleTests()
{
	TestSuite *tstSuite;
	TestCase  *tstCase;

	int promptResponse;
	BOOL validResponse;

	Vector origKybd;

	putc('\n', stdout);

	while ((tstSuite = getNextTestSuite()) != NULL)
	{
		showTestSuiteInfo(stdout, tstSuite);

		origKybd = initKybd();
		do
		{
			showTestPrompt(stdout);
			promptResponse = getBAscii();
			validResponse = (promptResponse == '\r' || promptResponse == 'q');
		} while (!validResponse);
		restoreKybd(origKybd);

		if (promptResponse == '\r')
		{
			while ((tstCase = getNextTestCase(tstSuite)) != NULL)
			{
				putc('\n', stdout);
				showTestCaseInfo(stdout, tstCase);

				origKybd = initKybd();
				do
				{
					showTestPrompt(stdout);
					promptResponse = getBAscii();
					validResponse = (promptResponse == '\r' ||
									 promptResponse == 'q');
				} while (!validResponse);
				restoreKybd(origKybd);
				
				if (promptResponse == '\r')
				{
					putc('\n', stdout);
					runTest(tstCase);
				}

				putc('\n', stdout);
			}
		}
		else
		{
			putc('\n', stdout);
		}
	}
}