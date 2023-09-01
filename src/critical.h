#ifndef CRITICAL_H
#define CRITICAL_H

#include "bool.h"

#define MAX_CRITICAL_HANDLERS 20

#define MAX_COMPONENT_NAME_LEN 23

typedef char CritComponentName[MAX_COMPONENT_NAME_LEN + 1];

void finishCriticalSec(void);

BOOL protectCriticalSec(const char * accessedComponent);

BOOL setCriticalHandler(const char *component, void (*handler)(BOOL finished));

#endif
