
#include "precomp.h"

class CTargetPage : public CWindowImpl<CTargetPage>
{
	public:
		DECLARE_WND_CLASS (_T("CTargetPage"))
		
		BEGIN_MSG_MAP(CTargetPage)
			MESSAGE_HANDLER(WM_CREATE, OnCreate)
			MESSAGE_HANDLER(WM_SIZE, OnSize)	
			MESSAGE_HANDLER(WM_COMMAND, OnCommand)		
		END_MSG_MAP()
		
		LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   		{
   			::EndDialog ( GetParent().GetParent() , 0);
   			return 0;
   		}
   		
   		LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   		{
   			RECT	ClientRect;
   			::GetClientRect ( m_hWnd , &ClientRect);
   			
   			m_TxtPortal.MoveWindow ( ClientRect.left + MARGIN,
   									 TABLE_TOP - 20,
   									 ClientRect.right - ClientRect.left - 2*MARGIN ,
   									 20 );
   			
   			m_Portal.MoveWindow ( ClientRect.left + MARGIN , 
   								  TABLE_TOP , 
   								  ClientRect.right - ClientRect.left - 2*MARGIN,
   								  TABLE_HEIGHT);
   								  
   			m_TxtTarget.MoveWindow ( ClientRect.left + MARGIN , 
   								  TABLE_TOP + TABLE_HEIGHT +  TABLE_OFFSET - 20 , 
   								  ClientRect.right - ClientRect.left - 2*MARGIN,
   								  TABLE_HEIGHT);
   								  
   			m_Target.MoveWindow ( ClientRect.left + MARGIN , 
   								  TABLE_TOP + TABLE_HEIGHT +  TABLE_OFFSET , 
   								  ClientRect.right - ClientRect.left - 2*MARGIN,
   								  TABLE_HEIGHT);
   			
   			m_TgtAdd.MoveWindow ( ClientRect.right - MARGIN - 80, 
   								  TABLE_TOP + 2*TABLE_HEIGHT +  TABLE_OFFSET + 10, 
   								  80,
   								  21);
   			
   			m_TgtRemove.MoveWindow ( ClientRect.right - MARGIN - 2*80 - 10, 
   								  TABLE_TOP + 2*TABLE_HEIGHT +  TABLE_OFFSET + 10, 
   								  80,
   								  21);
   			
   			m_PAdd.MoveWindow ( ClientRect.right - MARGIN - 80, 
   								  TABLE_TOP + TABLE_HEIGHT  + 10, 
   								  80,
   								  21);
   								  
   			m_PRemove.MoveWindow ( ClientRect.right - MARGIN - 2*80 - 10, 
   								  TABLE_TOP + TABLE_HEIGHT + 10, 
   								  80,
   								  21);
   			
   			m_PRefresh.MoveWindow ( ClientRect.right - MARGIN - 3*80 - 2*10, 
   								  TABLE_TOP + TABLE_HEIGHT + 10, 
   								  80,
   								  21);
   								  					  
   			return 1;
   		}
   		
		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   		{
   			RECT	ClientRect;
   			::GetClientRect ( m_hWnd , &ClientRect);
  			
   			m_TxtPortal.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_TxtPortal.SetFont ( g_Font );
   			m_TxtPortal.SetWindowText ("Portal List");
   			
   			m_Portal.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE |WS_BORDER|LVS_REPORT );
   			m_Portal.SetFont ( g_Font );
   			m_Portal.InsertColumn ( 0 , _T("Address") , LVCFMT_LEFT , 100);
   			m_Portal.InsertColumn ( 1 , _T("Port") , LVCFMT_LEFT , 100);
   			m_Portal.InsertColumn ( 2 , _T("IpAddress") , LVCFMT_LEFT , 100);
   			
   			m_TxtTarget.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_TxtTarget.SetFont ( g_Font );
   			m_TxtTarget.SetWindowText ("Target List");
   			
   			m_Target.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE |WS_BORDER|LVS_REPORT );
   			m_Target.SetFont ( g_Font );
   			m_Target.InsertColumn ( 0 , _T("Target") , LVCFMT_LEFT , 150);
   			m_Target.InsertColumn ( 1 , _T("Status") , LVCFMT_LEFT , 100);
   			m_Target.InsertColumn ( 2 , _T("Address") , LVCFMT_LEFT , 100);
   			m_Target.InsertColumn ( 3 , _T("Port") , LVCFMT_LEFT , 100);
   			
   			m_TgtRemove.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_TgtRemove.SetFont ( g_Font );
   			m_TgtRemove.SetWindowText ("Remove");
   			
   			m_TgtAdd.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_TgtAdd.SetFont ( g_Font );
   			m_TgtAdd.SetWindowText ("Add");
   			
   			//
   			//
   			//
   			m_PRefresh.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_PRefresh.SetFont ( g_Font );
   			m_PRefresh.SetWindowText ("Refresh");
   			
   			m_PRemove.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_PRemove.SetFont ( g_Font );
   			m_PRemove.SetWindowText ("Remove");
   			
   			m_PAdd.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_PAdd.SetFont ( g_Font );
   			m_PAdd.SetWindowText ("Add");
   			
   			return 1;
   		}
		
	private:
		CStatic			m_TxtPortal , m_TxtTarget;
		CListViewCtrl	m_Portal , m_Target;
		CButton			m_TgtAdd , m_TgtRemove;
		CButton			m_PRefresh , m_PAdd , m_PRemove;
};