
// MyGame1View.cpp : реализация класса CMyGame1View
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MyGame1.h"
#endif

#include "OptionsDialog.h"
#include "MyGame1Doc.h"
#include "MyGame1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyGame1View

IMPLEMENT_DYNCREATE(CMyGame1View, CView)

BEGIN_MESSAGE_MAP(CMyGame1View, CView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_SETUP_BLOCKCOUNT, &CMyGame1View::OnSetupBlockcount)
	ON_COMMAND(ID_SETUP_BLOCKSIZE, &CMyGame1View::OnSetupBlocksize)
	ON_COMMAND(ID_EDIT_UNDO, &CMyGame1View::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CMyGame1View::OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, &CMyGame1View::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CMyGame1View::OnUpdateEditRedo)
END_MESSAGE_MAP()

// создание/уничтожение CMyGame1View

CMyGame1View::CMyGame1View()
{
	// TODO: добавьте код создания

}

CMyGame1View::~CMyGame1View()
{
}

BOOL CMyGame1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// рисование CMyGame1View

void CMyGame1View::OnDraw(CDC* pDC) // MFC will comment out the argument name by default; uncomment it
{
	//  First get a pointer to the document
	CMyGame1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Save the current state of the device context
	int nDCSave = pDC->SaveDC();
	//  Get the client rectangle
	CRect rcClient;
	GetClientRect(&rcClient);
	//  Get the background color of the board
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);
	//	Draw the background first
	pDC->FillSolidRect(&rcClient, clr);
	//  Create the brush for drawing
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);
	//	Draw the squares
	
	for (int row = 0; row < pDoc->GetRows(); row++)
	{
		for (int col = 0; col < pDoc->GetColumns(); col++)
		{
			//  Get the color for this board space
			clr = pDoc->GetBoardSpace(row, col);
			//  Calculate the size and position of this space
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();
			//  Fill in the block with the correct color
			pDC->FillSolidRect(&rcBlock, clr);
			//  Draw the block outline
			pDC->Rectangle(&rcBlock);
		}
	}
	//  Restore the device context settings
	pDC->RestoreDC(nDCSave);
	br.DeleteObject();
}


// диагностика CMyGame1View

#ifdef _DEBUG
void CMyGame1View::AssertValid() const
{
	CView::AssertValid();
}

void CMyGame1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyGame1Doc* CMyGame1View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyGame1Doc)));
	return (CMyGame1Doc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений CMyGame1View
void CMyGame1View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//  Resize the window
	ResizeWindow();
}


void CMyGame1View::ResizeWindow()
{
	//  First get a pointer to the document
	CMyGame1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Get the size of the client area and the window
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	//  Calculate the difference
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();
	//  Change the window size based on the size of the game board
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;
	//  The MoveWindow function resizes the frame window
	GetParentFrame()->MoveWindow(&rcWindow);
}

void CMyGame1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	//  First get a pointer to the document
	CMyGame1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Get the row and column of the block that was clicked on
	int row = point.y / pDoc->GetHeight();
	int col = point.x / pDoc->GetWidth();
	//  Delete the blocks from the document
	int count = pDoc->DeleteBlocks(row, col);
	//  Check if there were any blocks deleted
	if (count > 0)
	{
		//  Force the view to redraw
		Invalidate();
		UpdateWindow();
		//  Check if the game is over
		if (pDoc->IsGameOver())
		{
			//  Get the count remaining
			CString message;
			int remaining = pDoc->GetRemainingCount();
			if (remaining){
				
				message.Format(_T("No more moves left\nBlocks remaining: %d"),
					remaining);
				//  Display the results to the user
				MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				message.Format(_T("Great job!"));
				MessageBox(message, _T("You win!!!"), MB_OK | MB_ICONINFORMATION);
			}
		}
	}
	//  Default OnLButtonDown
	CView::OnLButtonDown(nFlags, point);
}


void CMyGame1View::OnSetupBlockcount()
{
	// TODO: добавьте свой код обработчика команд
	//  First get a pointer to the document
	CMyGame1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Create the options dialog
	COptionsDialog dlg(true, this);
	//  Set the row and column values
	dlg.m_nValue1 = pDoc->GetRows();
	dlg.m_nValue2 = pDoc->GetColumns();
	//  Display the dialog
	if (dlg.DoModal() == IDOK)
	{
		//  First delete the board
		pDoc->DeleteBoard();
		//  Get the user selected values
		pDoc->SetRows(dlg.m_nValue1);
		pDoc->SetColumns(dlg.m_nValue2);
		//  Update the board
		pDoc->SetupBoard();
		//  Resize the view
		ResizeWindow();
	}
}


void CMyGame1View::OnSetupBlocksize()
{
	// TODO: добавьте свой код обработчика команд
	//  First get a pointer to the document
	CMyGame1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Create the options dialog
	COptionsDialog dlg(false, this);
	//  Set the width and height values
	dlg.m_nValue1 = pDoc->GetWidth();
	dlg.m_nValue2 = pDoc->GetHeight();
	//  Display the dialog
	if (dlg.DoModal() == IDOK)
	{
		//  First delete the board
		pDoc->DeleteBoard();
		//  Get the user selected values
		pDoc->SetWidth(dlg.m_nValue1);
		pDoc->SetHeight(dlg.m_nValue2);
		//  Update the board
		pDoc->SetupBoard();
		//  Resize the view
		ResizeWindow();
	}
}


void CMyGame1View::OnEditUndo()
{
	//  First get a pointer to the document
	CMyGame1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Call undo on the document
	pDoc->UndoLast();
	//  Force the view to redraw
	Invalidate();
	UpdateWindow();
	// TODO: добавьте свой код обработчика команд
}


void CMyGame1View::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CMyGame1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Enable option if it is available
	pCmdUI->Enable(pDoc->CanUndo());
	// TODO: добавьте свой код обработчика ИП обновления команд
}


void CMyGame1View::OnEditRedo()
{
	//  First get a pointer to the document
	CMyGame1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Call redo on the document
	pDoc->RedoLast();
	//  Force the view to redraw
	Invalidate();
	UpdateWindow();
	// TODO: добавьте свой код обработчика команд
}


void CMyGame1View::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CMyGame1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Enable option if it is available
	pCmdUI->Enable(pDoc->CanRedo());
	// TODO: добавьте свой код обработчика ИП обновления команд
}
