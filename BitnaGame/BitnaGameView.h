
// BitnaGameView.h : CBitnaGameView Ŭ������ �������̽�
//

#pragma once
#include "atltypes.h"


class CBitnaGameView : public CView
{
protected: // serialization������ ��������ϴ�.
	CBitnaGameView();
	DECLARE_DYNCREATE(CBitnaGameView)

// Ư���Դϴ�.
public:
	CBitnaGameDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CBitnaGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�

protected:
	DECLARE_MESSAGE_MAP()
public:
	CPoint ballStartPoint;
	CPoint ballEndPoint;
	CPoint racketStartPoint; 
	CPoint racketEndPoint;	
	CSize stepsOf;
	CRect racket;

	bool mouseCaptured;
	bool isTimerSet;
	UINT frequency;
	bool gameMaxed;
	bool close;
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEasy();
	afx_msg void OnMidum();
	afx_msg void Onhard();
};

#ifndef _DEBUG  // BitnaGameView.cpp�� ����� ����
inline CBitnaGameDoc* CBitnaGameView::GetDocument() const
   { return reinterpret_cast<CBitnaGameDoc*>(m_pDocument); }
#endif

