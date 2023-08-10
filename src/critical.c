#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "critical.h"

int critHandlerFillLevel = 0;

CritComponentName currComponent = "";

CritComponentName componentNames[MAX_CRITICAL_HANDLERS];

void (*handlers[MAX_CRITICAL_HANDLERS]) (BOOL finished);

void finishCriticalSec(void)
{
	BOOL componentFound;
	int index;

	if (strlen(currComponent) > 0)
	{
		for (componentFound = FALSE, index = 0;
			 index < critHandlerFillLevel && !componentFound;
			 index++)
		{
			if (!strcmp(currComponent, componentNames[index]))
			{
				handlers[index](TRUE);
				currComponent[0] = '\0';
			}
		}
	}
}

BOOL protectCriticalSec(const char *accessedComponent)
{
	BOOL componentFound = FALSE;
	int index;

	if (!strlen(currComponent) && accessedComponent != NULL)
	{
		for (index = 0; index < critHandlerFillLevel && !componentFound;
			 index++)
		{
			if (!strcmp(accessedComponent, componentNames[index]))
			{
				handlers[index](FALSE);
				memcpy(currComponent, accessedComponent,
					   sizeof(CritComponentName));
				componentFound = TRUE;
			}
		}
	}

	return componentFound;
}

BOOL setCriticalHandler(const char * component, void (*handler)(BOOL finished))
{
	BOOL status;

	if ((status = (
		critHandlerFillLevel <= MAX_CRITICAL_HANDLERS &&
		component != NULL && handler != NULL)
	   ))
	{
		strncpy(componentNames[critHandlerFillLevel], component,
				MAX_COMPONENT_NAME_LEN + 1);
		handlers[critHandlerFillLevel++] = handler;
	}

	return status;
}