#pragma once
#include "Animation.h"
#include "IGameLoop.h"


class MFCWindow : public CFrameWnd
{

	CDC * mdc;
	CDC * pDC = nullptr;

	IGameLoop * gameLoop;

	int x, y;

public:

	//BOOL PreTranslateMessage(MSG* pMsg) override;

	MFCWindow();
	~MFCWindow();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
