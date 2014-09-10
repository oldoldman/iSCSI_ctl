

#include "precomp.h"

class CMonitorPage : public CWindowImpl<CMonitorPage>
{
	public:
		DECLARE_WND_CLASS (_T("CMonitorPage") )
		
		BEGIN_MSG_MAP(CMonitorPage)
			MESSAGE_HANDLER(WM_CREATE, OnCreate)			
		END_MSG_MAP()
		
		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   		{
   			return 0;
   		}		
	private:
		
};