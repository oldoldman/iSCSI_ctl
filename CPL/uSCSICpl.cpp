
#include <windows.h>
#include <cpl.h>

#include "resource.h"

HMODULE g_hModule = NULL;

extern "C" BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved )
{
	switch (ul_reason_for_call)
  	{
    	case DLL_PROCESS_ATTACH:
      		g_hModule = (HMODULE) hModule;

    	case DLL_THREAD_ATTACH:

    	case DLL_THREAD_DETACH:

    	case DLL_PROCESS_DETACH:
       		break;
    }
    return TRUE;
}

extern "C" LONG CALLBACK CPlApplet(HWND hwndCPL,
                  					UINT message, 
                  					LPARAM lParam1, 
                  					LPARAM lParam2)
{
  	switch (message)
  	{
    	case CPL_INIT:
      
      		return TRUE;

    	case CPL_GETCOUNT:
      
      		return 1;

    	case CPL_INQUIRE:
    		{
    			LPCPLINFO	Info = (LPCPLINFO)lParam2;
    			Info->idIcon = IDR_ICON;
    			Info->idName = IDR_USCSI;
    			Info->idInfo = IDR_DESC;
    		}
      		return 0;
      		
    	case CPL_DBLCLK:
    	{
     		PROCESS_INFORMATION pi = {0};
      		if (CreateProcess("\\WINDOWS\\NOTEPAD.exe", 
      							NULL, 
      							NULL,
                             	NULL, 
                             	FALSE, 
                             	0, 
                             	NULL, 
                             	NULL, 
                             	NULL, 
                             	&pi))
      		{
       	 		CloseHandle(pi.hThread);
        		CloseHandle(pi.hProcess);
        		return 0;
      		}
      		return 1;     // CPlApplet failed.
    	}

    	case CPL_STOP:
    	case CPL_EXIT:
    	
    	default:
     	 return 0;
  	}

}
 