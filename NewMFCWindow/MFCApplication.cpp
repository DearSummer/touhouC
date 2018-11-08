#include "MFCApplication.h"
#include "MFCWindow.h"

BOOL MFCApplication::InitInstance()
{
	MFCWindow * frame = new MFCWindow();
	frame->ShowWindow(m_nCmdShow);
	this->m_pMainWnd = frame;
	return TRUE;
}

