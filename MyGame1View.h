
// MyGame1View.h : интерфейс класса CMyGame1View
//

#pragma once


class CMyGame1View : public CView
{
protected: // создать только из сериализации
	CMyGame1View();
	DECLARE_DYNCREATE(CMyGame1View)

// Атрибуты
public:
	CMyGame1Doc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	void ResizeWindow();
	virtual ~CMyGame1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public: 
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetupBlockcount();
	afx_msg void OnSetupBlocksize();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // отладочная версия в MyGame1View.cpp
inline CMyGame1Doc* CMyGame1View::GetDocument() const
   { return reinterpret_cast<CMyGame1Doc*>(m_pDocument); }
#endif

