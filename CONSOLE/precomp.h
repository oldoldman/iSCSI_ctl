#ifndef _PRECOMP_H
#define _PRECOMP_H

#include <atlbase.h>
#include <atlapp.h>

#include <atlctrls.h>
#include <shellapi.h>
#pragma comment(lib,"shell32.lib")
#include <atlctrlx.h>
#include <atldlgs.h>
#include <atlgdi.h>
#include <atlimage.h>
#include "resource.h"

CFont	g_Font;


#define MARGIN			10
#define TABLE_TOP		30
#define TABLE_WIDTH		350
#define TABLE_HEIGHT	140
#define TABLE_OFFSET	50

#define LOGO_X			2*MARGIN
#define LOGO_Y			300 + 2*MARGIN

typedef enum _PAGE
{
	General,
	Target,
	Session,
	Extension,
	Monitor,
	NumPages	
}PAGE;

#define PAGE(p)			m_Pages[p]

#define GeneralPage		((CGeneralPage*)PAGE(General))
#define TargetPage		((CTargetPage*)PAGE(Target))
#define SessionPage		((CSessionPage*)PAGE(Session))
#define ExtensionPage	((CExtensionPage*)PAGE(Extension))
#define MonitorPage		((CMonitorPage*)PAGE(Monitor))

#endif