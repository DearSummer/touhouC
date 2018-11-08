#pragma once
#include "MFCWindow.h"

class MFCApplication : CWinApp
{
public:
	MFCApplication() = default;
	~MFCApplication() = default;

private:
	BOOL InitInstance() override;
};
