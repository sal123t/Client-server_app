//Orshak Ivan, 2018

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <conio.h>

/* Debug memory allocation support */
#ifdef _DEBUG
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#define SetDbgMemHooks() \
_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | \
_CRTDBG_CHECK_ALWAYS_DF | \
_CRTDBG_ALLOC_MEM_DF | \
_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else /* _DEBUG */
# define SetDbgMemHooks() ((VOID)0)
#endif /* _DEBUG */

#endif /* MAIN_H */