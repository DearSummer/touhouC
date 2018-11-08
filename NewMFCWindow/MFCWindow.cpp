#include "MFCWindow.h"
#include <string>
#include "Time.h"
#include "BaseGameLoop.h"
#include "Input.h"
#include "InputSignal.h"
#include "BulletManager.h"
#include "MusicManager.h"


#define GAME_LOOP_TIMER 0
#define FPS(x) (1000.0f / static_cast<float>(x))



MFCWindow::MFCWindow()
{
	CFrameWnd::Create(nullptr, "MFCWindow", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,CRect(0,0,/*392*/620,615));
	//Create(nullptr, "MFCWindow");
	CClientDC dc(this);

	mdc = new CDC();
	mdc->CreateCompatibleDC(&dc);

	//scoreText->Create("", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(500, 100, 600, 200), this);

	gameLoop = new BaseGameLoop();
	gameLoop->onStart();
	//anim = new Animation("res/hero_die", 100, 124, 4);

	MusicManager::getInstance().setWND(GetSafeHwnd());

	SetTimer(GAME_LOOP_TIMER, FPS(30), nullptr);
}


MFCWindow::~MFCWindow()
{
	if (pDC != nullptr)
		ReleaseDC(pDC);
	if (mdc != nullptr)
		ReleaseDC(mdc);
}

BEGIN_MESSAGE_MAP(MFCWindow, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYUP()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void MFCWindow::OnPaint()
{
	PAINTSTRUCT ps;
	pDC = BeginPaint(&ps);
	//pDC = GetDC();
	CRect rect;
	GetClientRect(&rect);

	float time = GetTickCount();
	//init cache dc
	CDC dcCache;
	dcCache.CreateCompatibleDC(pDC);
	CBitmap canvas;
	canvas.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	dcCache.SelectObject(&canvas);
	dcCache.FillSolidRect(rect, RGB(255, 255, 255));

	gameLoop->update(mdc, &dcCache);

	
	pDC->BitBlt(0, 0, rect.Width(), rect.Width(), &dcCache, 0, 0, SRCCOPY);
	Time.detlaTime = FPS(30);

	//release dc
	canvas.DeleteObject();
	//ReleaseDC(pDC);
	EndPaint(&ps);
}




void MFCWindow::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case GAME_LOOP_TIMER:
		Invalidate(FALSE);
		break;
	default:
		break;
	}
	
	// TODO: Add your message handler code here and/or call default
	CFrameWnd::OnTimer(nIDEvent);
}


void MFCWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if(VK_ESCAPE == nChar)
	{
		PostMessage(0);
	}

	if (nChar == VK_DOWN)
		Input::getInstance().keyDownDown = true;

	if (nChar == VK_UP)
		Input::getInstance().keyUpDown = true;

	if (nChar == VK_LEFT)
		Input::getInstance().keyLeftDown = true;

	if (nChar == VK_RIGHT)
		Input::getInstance().keyRightDown = true;

	if (nChar == 'A' || nChar == 'a')
		Input::getInstance().keyADown = true;

	if (nChar == 'S' || nChar == 's')
		Input::getInstance().keySDown = true;

	if (nChar == 'D' || nChar == 'd')
		Input::getInstance().keyDDown = true;

	if (nChar == 'W'  || nChar == 'w')
		Input::getInstance().keyWDown = true;

	if (nChar == 'Z' || nChar == 'z')
		Input::getInstance().keyZDown = true;

	if (nChar == 'X' || nChar == 'x')
		Input::getInstance().keyXDown = true;

	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void MFCWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	Input::getInstance().lButtonDown = true;
	CFrameWnd::OnLButtonDown(nFlags, point);
}


void MFCWindow::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	Input::getInstance().rButtonDown = true;
	CFrameWnd::OnRButtonDown(nFlags, point);
}


void MFCWindow::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	Input::getInstance().mouseX = point.x;
	Input::getInstance().mouseY = point.y;

	CFrameWnd::OnMouseMove(nFlags, point);
}


void MFCWindow::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_DOWN)
		Input::getInstance().keyDownDown = false;

	if (nChar == VK_UP)
		Input::getInstance().keyUpDown = false;

	if (nChar == VK_LEFT)
		Input::getInstance().keyLeftDown = false;

	if (nChar == VK_RIGHT)
		Input::getInstance().keyRightDown = false;

	if (nChar == 'A' || nChar == 'a')
		Input::getInstance().keyADown = false;

	if (nChar == 'S' || nChar == 's')
		Input::getInstance().keySDown = false;

	if (nChar == 'D' || nChar == 'd')
		Input::getInstance().keyDDown = false;

	if (nChar == 'W' || nChar == 'w')
		Input::getInstance().keyWDown = false;

	if (nChar == 'Z' || nChar == 'z')
		Input::getInstance().keyZDown = false;

	if (nChar == 'X' || nChar == 'x')
		Input::getInstance().keyXDown = false;

	CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}


void MFCWindow::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	Input::getInstance().lButtonDown = false;
	CFrameWnd::OnLButtonUp(nFlags, point);
}
