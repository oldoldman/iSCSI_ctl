
#include "precomp.h"

class CExtensionPage : public CWindowImpl<CExtensionPage>
{
	public:
		DECLARE_WND_CLASS (_T("CExtensionPage"))
		
		BEGIN_MSG_MAP(CExtensionPage)
			MESSAGE_HANDLER(WM_CREATE, OnCreate)
			MESSAGE_HANDLER(WM_SIZE, OnSize)
		END_MSG_MAP()
		
		LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   		{
   			RECT	ClientRect;
   			::GetClientRect ( m_hWnd , &ClientRect);
   			
   			m_TxtExt.MoveWindow ( ClientRect.left + MARGIN,
   									 TABLE_TOP - 20,
   									 ClientRect.right - ClientRect.left - 2*MARGIN ,
   									 20 );
   			
   			m_Ext.MoveWindow ( ClientRect.left + MARGIN , 
   								  TABLE_TOP , 
   								  ClientRect.right - ClientRect.left - 2*MARGIN,
   								  TABLE_HEIGHT);
   								  
   			m_TxtAuth.MoveWindow ( ClientRect.left + MARGIN , 
   								  TABLE_TOP + TABLE_HEIGHT +  TABLE_OFFSET - 20 , 
   								  ClientRect.right - ClientRect.left - 2*MARGIN,
   								  TABLE_HEIGHT);
   								  
   			m_Auth.MoveWindow ( ClientRect.left + MARGIN , 
   								  TABLE_TOP + TABLE_HEIGHT +  TABLE_OFFSET , 
   								  ClientRect.right - ClientRect.left - 2*MARGIN,
   								  TABLE_HEIGHT);
   			
   			//
   			//
   			//
   			m_ExtAdd.MoveWindow ( ClientRect.right - MARGIN - 80, 
   								  TABLE_TOP + TABLE_HEIGHT  + 10, 
   								  80,
   								  21);
   								  
   			m_ExtRemove.MoveWindow ( ClientRect.right - MARGIN - 2*80 - 10, 
   								  TABLE_TOP + TABLE_HEIGHT + 10, 
   								  80,
   								  21);
   			//
   			//
   			//
   			m_AuthAdd.MoveWindow ( ClientRect.right - MARGIN - 80, 
   								  TABLE_TOP + 2*TABLE_HEIGHT +  TABLE_OFFSET + 10, 
   								  80,
   								  21);
   			
   			m_AuthRemove.MoveWindow ( ClientRect.right - MARGIN - 2*80 - 10, 
   								  TABLE_TOP + 2*TABLE_HEIGHT +  TABLE_OFFSET + 10, 
   								  80,
   								  21);
   			return 1;
   		}
   		
		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   		{
   			m_TxtExt.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_TxtExt.SetFont ( g_Font );
   			m_TxtExt.SetWindowText ("ExtModule List");
   			
   			m_Ext.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE |WS_BORDER|LVS_REPORT );
   			m_Ext.SetFont ( g_Font );
   			m_Ext.InsertColumn ( 0 , _T("Command") , LVCFMT_LEFT , 100);   			
   			m_Ext.InsertColumn ( 1 , _T("Module") , LVCFMT_LEFT , 100);
   			
   			m_TxtAuth.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_TxtAuth.SetFont ( g_Font );
   			m_TxtAuth.SetWindowText ("AuthMethod List");
   			
   			m_Auth.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE |WS_BORDER|LVS_REPORT );
   			m_Auth.SetFont ( g_Font );
   			m_Auth.InsertColumn ( 0 , _T("AuthMethod") , LVCFMT_LEFT , 100);   			
   			m_Auth.InsertColumn ( 1 , _T("Status") , LVCFMT_LEFT , 100);
   			
   			
   			m_ExtRemove.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_ExtRemove.SetFont ( g_Font );
   			m_ExtRemove.SetWindowText ("Remove");
   			
   			m_ExtAdd.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_ExtAdd.SetFont ( g_Font );
   			m_ExtAdd.SetWindowText ("Add");
   			
   			m_AuthRemove.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_AuthRemove.SetFont ( g_Font );
   			m_AuthRemove.SetWindowText ("Remove");
   			
   			m_AuthAdd.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_AuthAdd.SetFont ( g_Font );
   			m_AuthAdd.SetWindowText ("Add");
   			
   			return 1;
   		} 
		
	private:
		CStatic			m_TxtExt , m_TxtAuth;
		CListViewCtrl	m_Ext , m_Auth;
		CButton			m_ExtRemove , m_ExtAdd ;
		CButton			m_AuthRemove , m_AuthAdd ;

};