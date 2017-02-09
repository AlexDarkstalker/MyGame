
// MyGame1.h : главный файл заголовка для приложения MyGame1
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CMyGame1App:
// О реализации данного класса см. MyGame1.cpp
//

class CMyGame1App : public CWinApp
{
public:
	CMyGame1App();


// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyGame1App theApp;
