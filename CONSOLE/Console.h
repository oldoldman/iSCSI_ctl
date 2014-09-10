
#include "precomp.h"

#include "General.h"
#include "Target.h"
#include "Session.h"
#include "Extension.h"
#include "Monitor.h"
   		
class CConsole : public CDialogImpl<CConsole>
{
	public:
	
		enum {IDD = IDD_MAIN_DIALOG };
		
		BEGIN_MSG_MAP(CConsole)
			MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
			MESSAGE_HANDLER(WM_CREATE, OnCreate)
			MESSAGE_HANDLER(WM_COMMAND, OnCommand)			
			NOTIFY_CODE_HANDLER(TCN_SELCHANGE , OnPageChanged)			
			NOTIFY_CODE_HANDLER(TCN_SELCHANGING , OnPageChanging)
		END_MSG_MAP()
		
		CConsole():m_CurrentPage(0)
		{
			LOGFONT LogFont;
			
			memset ( &LogFont , 0 , sizeof (LOGFONT));
			LogFont.lfHeight = 15;
			strcpy ( LogFont.lfFaceName  , "Arial");
			
			g_Font.CreateFontIndirect( &LogFont );
			
			for (int i = 0 ; i < NumPages ; i++ )
				m_Pages[i] = NULL;
			
		}
		
		VOID LayOutDialogBox()
		{
			CWindow	DialogBox = m_hWnd;			
			RECT	rect;
			UINT	i;
						
			DialogBox.GetClientRect (&m_ClientBound);
			
			m_MainTab.rcDefault.left 	= m_ClientBound.left + 10;
			m_MainTab.rcDefault.top 	= m_ClientBound.top + 10;
			m_MainTab.rcDefault.right 	= m_ClientBound.right - 10;
			m_MainTab.rcDefault.bottom  = m_ClientBound.bottom - 40;
			
			m_MainTab.Create ( DialogBox , 
							   NULL , 
							   NULL , 
							   WS_CHILD | WS_VISIBLE | TCS_MULTILINE );
			m_MainTab.SetFont ( g_Font );
							   
			m_MainTab.AddItem("General");
			m_MainTab.AddItem("Targets");
			m_MainTab.AddItem("Session");			
			m_MainTab.AddItem("Extension");
			m_MainTab.AddItem("Monitor");
			
			m_MainTab.GetClientRect( &m_TabBound );
			m_MainTab.GetItemRect ( 0 , &rect);
			
			m_TabBound.left += 5;
			m_TabBound.top += ( (rect.bottom - rect.top ) *m_MainTab.GetRowCount() + 5 );
			m_TabBound.right -= 5;
			m_TabBound.bottom -= 5;
						
			PAGE(General) 	= new CGeneralPage;
			PAGE(Target) 	= new CTargetPage;
			PAGE(Session) 	= new CSessionPage;			
			PAGE(Extension) = new CExtensionPage;
			PAGE(Monitor) 	= new CMonitorPage;
			//
			GeneralPage->Create ( m_MainTab , NULL , NULL , WS_CHILD | WS_VISIBLE );			
			GeneralPage->MoveWindow ( m_TabBound.left , 
									  m_TabBound.top , 
									  m_TabBound.right - m_TabBound.left , 
									  m_TabBound.bottom - m_TabBound.top );
			//
			TargetPage->Create ( m_MainTab , NULL , NULL , WS_CHILD );
			TargetPage->MoveWindow	 (m_TabBound.left , 
									  m_TabBound.top , 
									  m_TabBound.right - m_TabBound.left , 
									  m_TabBound.bottom - m_TabBound.top);
			//
			SessionPage->Create ( m_MainTab , NULL , NULL , WS_CHILD );
			SessionPage->SetWindowPos ( NULL , 									  
									  m_TabBound.left , 
									  m_TabBound.top , 
									  m_TabBound.right - m_TabBound.left , 
									  m_TabBound.bottom - m_TabBound.top ,
									  SWP_HIDEWINDOW);
			//
			ExtensionPage->Create ( m_MainTab , NULL , NULL , WS_CHILD );
			ExtensionPage->SetWindowPos ( NULL , 									  
									  m_TabBound.left , 
									  m_TabBound.top , 
									  m_TabBound.right - m_TabBound.left , 
									  m_TabBound.bottom - m_TabBound.top ,
									  SWP_HIDEWINDOW);
			//
			
			MonitorPage->Create ( m_MainTab , NULL , NULL , WS_CHILD );			
			MonitorPage->SetWindowPos ( NULL , 									  
									  m_TabBound.left , 
									  m_TabBound.top , 
									  m_TabBound.right - m_TabBound.left , 
									  m_TabBound.bottom - m_TabBound.top ,
									  SWP_HIDEWINDOW);
			//
			
			//
			
			m_Ok.rcDefault.right = m_ClientBound.right - 10;
			m_Ok.rcDefault.left = m_Ok.rcDefault.right - 80;
			m_Ok.rcDefault.bottom = m_ClientBound.bottom - 10;
			m_Ok.rcDefault.top = m_Ok.rcDefault.bottom - 21;
			m_Ok.Create ( DialogBox , 
							   NULL , 
							   NULL , 
							   WS_CHILD | WS_VISIBLE );
			m_Ok.SetFont ( g_Font );
			m_Ok.SetWindowText(_T("OK"));			
			
		}
		
		
		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   		{  			 			
   			SetFont (  g_Font );
   			SetIcon( ::LoadIcon(NULL , "APP") , FALSE );  			
   			return 1;   			
   		}
   		
		LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   		{   			
   			LayOutDialogBox();
      		return 1;
   		}
   		
   		LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   		{
   			EndDialog (0);
   			return 1;
   		}
   		
   		VOID ShowPage(int ShowHide )
   		{
   			CWindow*	CurrentPage;
   			CurrentPage = PAGE(m_CurrentPage);
   			
   			if (CurrentPage)
   				CurrentPage->ShowWindow( ShowHide );
   		}
   		
   		LRESULT OnPageChanged(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
   		{
   			m_CurrentPage = m_MainTab.GetCurSel();
   			ShowPage(SW_SHOW);
   			return 0;
   		}
   		
   		LRESULT OnPageChanging(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
   		{
   			//Returns TRUE to prevent the selection from changing, 
   			//    or FALSE to allow the selection to change
   			ShowPage(SW_HIDE);
   			return FALSE;
   		}
   		
   	private:
   		UINT		m_CurrentPage;
   		RECT		m_ClientBound , m_TabBound;
   		CButton		m_Ok;
   		CTabCtrl	m_MainTab;   		
   		CWindow		*m_Pages[NumPages];
};