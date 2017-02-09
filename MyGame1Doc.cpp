
// MyGame1Doc.cpp : реализация класса CMyGame1Doc
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MyGame1.h"
#endif

#include "MyGame1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyGame1Doc

IMPLEMENT_DYNCREATE(CMyGame1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMyGame1Doc, CDocument)
END_MESSAGE_MAP()


// создание/уничтожение CMyGame1Doc

CMyGame1Doc::CMyGame1Doc()
{
	// TODO: добавьте код для одноразового вызова конструктора
	//  There should always be a game board
	m_board = new CMyGame1Board();

}

CMyGame1Doc::~CMyGame1Doc()
{
	//  Delete the current game board
	delete m_board;
	//  Delete everything from the undo stack
	ClearUndo();
	//  Delete everything from the redo stack
	ClearRedo();
}

BOOL CMyGame1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	//  Set (or reset) the game board
	m_board->SetupBoard();
	//  Clear the undo/redo stacks
	ClearUndo();
	ClearRedo();

	return TRUE;
}




// сериализация CMyGame1Doc

void CMyGame1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

int CMyGame1Doc::DeleteBlocks(int row, int col)
{
	//  Save the current board in the undo stack
	m_undo.push(new CMyGame1Board(*m_board));
	//  Empty out the redo stack
	ClearRedo();
	//  Then delete the blocks
	int blocks = m_board->DeleteBlocks(row, col);
	//  Clear the undo stack at the end of a game
	if(m_board->IsGameOver())
		ClearUndo();
	//  Return the number of blocks
	return blocks;
}

void CMyGame1Doc::UndoLast()
{
	//  First make sure that there is a move to undo
	if(m_undo.empty())
		return;
	//  Take the current board and put it on the redo
	m_redo.push(m_board);
	//  Take the top undo and make it the current
	m_board = m_undo.top();
	m_undo.pop();
}

bool CMyGame1Doc::CanUndo()
{
	//  Can undo if the undo stack isn't empty
	return !m_undo.empty();
}

void CMyGame1Doc::RedoLast()
{
	//  First make sure that there is a move to redo
	if(m_redo.empty())
		return;
	//  Take the current board and put it on the undo
	m_undo.push(m_board);
	//  Take the top redo and make it the current
	m_board = m_redo.top();
	m_redo.pop();
}

bool CMyGame1Doc::CanRedo()
{
	//  Can redo if the redo stack isn't empty
	return !m_redo.empty();
}

void CMyGame1Doc::ClearUndo()
{
	//  Delete everything from the undo stack
	while(!m_undo.empty())
	{
		delete m_undo.top();
		m_undo.pop();
	}
}

void CMyGame1Doc::ClearRedo()
{
	//  Delete everything from the redo stack
	while(!m_redo.empty())
	{
		delete m_redo.top();
		m_redo.pop();
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CMyGame1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CMyGame1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задайте содержимое поиска из данных документа. 
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CMyGame1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// диагностика CMyGame1Doc

#ifdef _DEBUG
void CMyGame1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyGame1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// команды CMyGame1Doc
