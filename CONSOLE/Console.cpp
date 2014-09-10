
#include "console.h"

CAppModule _Module;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR lpCmdLine, int nCmdShow)
{
	CConsole Console;
	::InitCommonControls();
	_Module.Init(NULL, hInstance);

	int nRet = Console.DoModal();
	
	_Module.Term();
	return nRet;
}