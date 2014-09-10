
#include "precomp.h"

class CSessionPage : public CWindowImpl<CSessionPage>
{
	public:
		DECLARE_WND_CLASS (_T("CSessionPage"))
		
		BEGIN_MSG_MAP(CSessionPage)
			MESSAGE_HANDLER(WM_CREATE, OnCreate)	
			MESSAGE_HANDLER(WM_SIZE, OnSize)				
		END_MSG_MAP()
		
		LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   		{
   			RECT	ClientRect;
   			::GetClientRect ( m_hWnd , &ClientRect);
   			
   			m_TxtSession.MoveWindow ( ClientRect.left + MARGIN,
   									 TABLE_TOP - 20,
   									 ClientRect.right - ClientRect.left - 2*MARGIN ,
   									 20 );
   			
   			m_Session.MoveWindow ( ClientRect.left + MARGIN , 
   								  TABLE_TOP , 
   								  ClientRect.right - ClientRect.left - 2*MARGIN,
   								  TABLE_HEIGHT);
   								  
   			m_TxtConnection.MoveWindow ( ClientRect.left + MARGIN , 
   								  TABLE_TOP + TABLE_HEIGHT +  TABLE_OFFSET - 20 , 
   								  ClientRect.right - ClientRect.left - 2*MARGIN,
   								  TABLE_HEIGHT);
   								  
   			m_Connection.MoveWindow ( ClientRect.left + MARGIN , 
   								  TABLE_TOP + TABLE_HEIGHT +  TABLE_OFFSET , 
   								  ClientRect.right - ClientRect.left - 2*MARGIN,
   								  TABLE_HEIGHT);
   								  
   			//
   			//
   			//
   			m_SessionAdd.MoveWindow ( ClientRect.right - MARGIN - 80, 
   								  TABLE_TOP + TABLE_HEIGHT  + 10, 
   								  80,
   								  21);
   								  
   			m_SessionRemove.MoveWindow ( ClientRect.right - MARGIN - 2*80 - 10, 
   								  TABLE_TOP + TABLE_HEIGHT + 10, 
   								  80,
   								  21);
   			//
   			//
   			//
   			m_ConAdd.MoveWindow ( ClientRect.right - MARGIN - 80, 
   								  TABLE_TOP + 2*TABLE_HEIGHT +  TABLE_OFFSET + 10, 
   								  80,
   								  21);
   			
   			m_ConRemove.MoveWindow ( ClientRect.right - MARGIN - 2*80 - 10, 
   								  TABLE_TOP + 2*TABLE_HEIGHT +  TABLE_OFFSET + 10, 
   								  80,
   								  21);
   			return 1;
   		}
   		
		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   		{
   			m_TxtSession.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_TxtSession.SetFont ( g_Font );
   			m_TxtSession.SetWindowText ("Session List");
   			
   			m_Session.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE |WS_BORDER|LVS_REPORT );
   			m_Session.SetFont ( g_Font );
   			m_Session.InsertColumn ( 0 , _T("Session#") , LVCFMT_LEFT , 70);  
   			m_Session.InsertColumn ( 1 , _T("Status") , LVCFMT_LEFT , 50);   			
   			m_Session.InsertColumn ( 2 , _T("Target") , LVCFMT_LEFT , 200);
   			
   			m_TxtConnection.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_TxtConnection.SetFont ( g_Font );
   			m_TxtConnection.SetWindowText ("Connection List");
   			
   			m_Connection.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE |WS_BORDER|LVS_REPORT );
   			m_Connection.SetFont ( g_Font );
   			m_Connection.InsertColumn ( 0 , _T("Connection#") , LVCFMT_LEFT , 100);   
   			m_Connection.InsertColumn ( 1 , _T("Status") , LVCFMT_LEFT , 50);			
   			m_Connection.InsertColumn ( 2 , _T("Adapter") , LVCFMT_RIGHT , 100);
   			
   			m_SessionRemove.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_SessionRemove.SetFont ( g_Font );
   			m_SessionRemove.SetWindowText ("Remove");
   			
   			m_SessionAdd.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_SessionAdd.SetFont ( g_Font );
   			m_SessionAdd.SetWindowText ("Add");
   			
   			m_ConRemove.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_ConRemove.SetFont ( g_Font );
   			m_ConRemove.SetWindowText ("Remove");
   			
   			m_ConAdd.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_ConAdd.SetFont ( g_Font );
   			m_ConAdd.SetWindowText ("Add");
   			
   			return 1;
   		} 		
		
	private:
		CStatic			m_TxtSession , m_TxtConnection;
		CListViewCtrl	m_Session , m_Connection;
		CButton			m_SessionAdd , m_SessionRemove;
		CButton			m_ConAdd , m_ConRemove;
		
};