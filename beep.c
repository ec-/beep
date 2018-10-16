#pragma comment(linker, "/ENTRY:MainProc /NOD")
#pragma comment(linker, "/SUBSYSTEM:windows")
#pragma comment(linker, "/STACK:8192")

#define UNICODE
#include <windows.h>

#define DEFAULT_FREQ 1000
#define DEFAULT_DURATION 500

#define MAX_FREQ 20000
#define MAX_DURATION 30000

static DWORD dwFreq = DEFAULT_FREQ;
static DWORD dwDuration = DEFAULT_DURATION;

static TCHAR *strchrW( LPTSTR str, TCHAR ch ) 
{
	TCHAR *s = str;

	while ( *s != '\0' && *s != ch )
		s++;

	if ( *s != '\0' )
		return s;
	else
		return NULL;
}

static VOID GetParams( VOID ) 
{
	LPTSTR CmdLine;
	TCHAR *params;

	CmdLine = GetCommandLine();
	
	if ( CmdLine[0] == '"' )
		params = strchrW( CmdLine+1, '"' );
	else
		params = strchrW( CmdLine+1, ' ' );

	if ( params == NULL ) 
		return;

	params++; // skip " or space

	// skip whitespace
	while ( *params != '\0' && *params <= ' ' )
		params++;

	if ( *params == '-' || *params < '0' || *params > '9' ) 
	{
		*params++; // skip frequency
	}
	else 
	{
		dwFreq = *params++ - '0';
		while ( *params != '\0' && *params >= '0' && *params <= '9' ) 
			dwFreq = dwFreq * 10 + (*params++ - '0'); 
	}

	// skip whitespace
	while ( *params != '\0' && *params <= ' ' )
		params++;

	if ( *params >= '0' && *params <= '9' ) 
	{
		dwDuration = *params++ - '0';
		while ( *params != '\0' && *params >= '0' && *params <= '9' ) 
			dwDuration = dwDuration * 10 + (*params++ - '0'); 
	}

	if ( dwFreq > MAX_FREQ )
		dwFreq = MAX_FREQ;
	else if ( dwFreq == 0 )
		dwFreq = DEFAULT_FREQ;

	if ( dwDuration > MAX_DURATION )
		dwDuration = MAX_DURATION;
	else if ( dwDuration == 0 )
		dwDuration = DEFAULT_DURATION;
}


VOID WINAPI MainProc( VOID )
{
	BOOL bRes;
	GetParams();
	bRes = Beep( dwFreq, dwDuration );
	ExitProcess( bRes == 0 );
}
