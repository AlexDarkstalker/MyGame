
// MyGame1.h : ������� ���� ��������� ��� ���������� MyGame1
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������


// CMyGame1App:
// � ���������� ������� ������ ��. MyGame1.cpp
//

class CMyGame1App : public CWinApp
{
public:
	CMyGame1App();


// ���������������
public:
	virtual BOOL InitInstance();

// ����������
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyGame1App theApp;
