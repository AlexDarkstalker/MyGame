
// MyGame1Doc.h : интерфейс класса CMyGame1Doc
//


#pragma once
#include"MyGame1Board.h"
#include <stack>
class CMyGame1Doc : public CDocument
{
protected: // создать только из сериализации
	CMyGame1Doc();
	DECLARE_DYNCREATE(CMyGame1Doc)

// Атрибуты
public:

// Операции
public:
	/*  Functions for accessing the game board */
	COLORREF GetBoardSpace(int row, int col)
	{
		return m_board->GetBoardSpace(row, col);
	}
	void SetupBoard(void)   { m_board->SetupBoard(); }
	int GetWidth(void)            { return m_board->GetWidth(); }
	void SetWidth(int nWidth)     { m_board->SetWidth(nWidth); }
	int GetHeight(void)           { return m_board->GetHeight(); }
	void SetHeight(int nHeight)   { m_board->SetHeight(nHeight); }
	int GetColumns(void)          { return m_board->GetColumns(); }
	void SetColumns(int nColumns) { m_board->SetColumns(nColumns); }
	int GetRows(void)             { return m_board->GetRows(); }
	void SetRows(int nRows)       { m_board->SetRows(nRows); }
	void DeleteBoard(void)  { m_board->DeleteBoard(); }
	int DeleteBlocks(int row, int col);
	bool IsGameOver()       { return m_board->IsGameOver(); }
	int GetRemainingCount()
	{ return m_board->GetRemainingCount(); }
	void UndoLast();
	bool CanUndo();
	void RedoLast();
	bool CanRedo();
// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CMyGame1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	/*  Functions to clear undo/redo stacks */
	void ClearUndo();
	void ClearRedo();
	/*  Instance of the game board--notice that we made it a pointer */
	CMyGame1Board* m_board;
	/*  Undo stack */
	std::stack<CMyGame1Board*> m_undo;
	/*  Redo stack */
	std::stack<CMyGame1Board*> m_redo;
	/*  Instance of the game board */
// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
