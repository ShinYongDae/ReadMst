
// ReadMst.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CReadMstApp:
// �� Ŭ������ ������ ���ؼ��� ReadMst.cpp�� �����Ͻʽÿ�.
//

class CReadMstApp : public CWinApp
{
public:
	CReadMstApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CReadMstApp theApp;