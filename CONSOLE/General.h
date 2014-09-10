
#include "precomp.h"

class CGeneralPage : public CWindowImpl<CGeneralPage>
{
	public:
		DECLARE_WND_CLASS (_T("CGeneralPage"))
		
		BEGIN_MSG_MAP(CGeneralPage)
			MESSAGE_HANDLER(WM_CREATE, OnCreate)
			MESSAGE_HANDLER(WM_PAINT, OnPaint)
			MESSAGE_HANDLER(WM_SIZE, OnSize)
		END_MSG_MAP()
		
		LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   		{
   			RECT	ClientRect;
   			::GetClientRect ( m_hWnd , &ClientRect);
   			
   			m_GeneralInfo.MoveWindow ( ClientRect.left + MARGIN,
   									   10,	
   									   ClientRect.right - ClientRect.left - 2*MARGIN ,
   									   280);
   			
   			m_About.MoveWindow ( ClientRect.left + MARGIN,
   									   300,	
   									   ClientRect.right - ClientRect.left - 2*MARGIN ,
   									   110);
   									   
   			m_Info.MoveWindow ( LOGO_X + m_Logo.GetWidth() + MARGIN,
   								300 + 2*MARGIN,	
   								ClientRect.right - ClientRect.left - 5*MARGIN - m_Logo.GetWidth(),
   								70);
   			return 1;
   		}
   		
		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   		{
   			IStream	*Stream;
   			HRSRC	Logo;
   			DWORD	LogoSize;
   			LPVOID	LogoData , LogoData2;
   			HGLOBAL	LogoHandle;
   			
   			Logo = ::FindResource ( NULL , "LOGO" , "PNG");
   			LogoSize = ::SizeofResource ( NULL , Logo );
   			LogoData = ::LockResource ( ::LoadResource ( NULL , Logo ) );
   			if ( LogoData )
   			{
   				LogoHandle = ::GlobalAlloc(GMEM_MOVEABLE, LogoSize);
   				if ( LogoHandle )
   				{
   					LogoData2 = ::GlobalLock( LogoHandle );
   					CopyMemory ( LogoData2, LogoData , LogoSize);
   					::CreateStreamOnHGlobal ( LogoHandle , FALSE , &Stream );
   				}
   			}  			
   			m_Logo.Load ( Stream );
  			
   			m_GeneralInfo.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE |BS_GROUPBOX );
   			m_GeneralInfo.SetFont ( g_Font );
   			m_GeneralInfo.SetWindowText ("Initiator Settings");
   			
   			m_About.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE |BS_GROUPBOX );
   			m_About.SetFont ( g_Font );
   			m_About.SetWindowText ("About");
   			
   			m_Info.Create ( m_hWnd , NULL , NULL , WS_CHILD | WS_VISIBLE );
   			m_Info.SetFont ( g_Font );
   			m_Info.SetWindowText ("uSCSI Mamagement Console\nVersion: 1.0.0.0\nAuthor: yushang");
   			
   			if (LogoHandle)
	   			::GlobalFree (LogoHandle);
   			return 1;
   		}
   		
   		LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   		{
   			RECT		Rect;
   			CClientDC 	Dc(m_hWnd);
   			   			
   			m_Logo.Draw ( Dc , LOGO_X ,  LOGO_Y);   			
   			::SetRect ( &Rect , LOGO_X , LOGO_Y , LOGO_X+m_Logo.GetWidth() ,LOGO_Y+ m_Logo.GetHeight() );
   			ValidateRect ( &Rect );
   			bHandled = FALSE;
   			
   			return 0;
   		}
		
	private:
		CButton		m_GeneralInfo , m_About;
		CImage		m_Logo;
		CStatic		m_Info;
};