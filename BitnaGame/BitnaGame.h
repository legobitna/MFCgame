
// BitnaGame.h : BitnaGame ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CBitnaGameApp:
// �� Ŭ������ ������ ���ؼ��� BitnaGame.cpp�� �����Ͻʽÿ�.
//

class CBitnaGameApp : public CWinApp
{
public:
	CBitnaGameApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBitnaGameApp theApp;
