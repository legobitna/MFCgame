
// BitnaGameView.h : CBitnaGameView 클래스의 인터페이스
//

#pragma once
#include "atltypes.h"


class CBitnaGameView : public CView
{
protected: // serialization에서만 만들어집니다.
	CBitnaGameView();
	DECLARE_DYNCREATE(CBitnaGameView)

// 특성입니다.
public:
	CBitnaGameDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CBitnaGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수

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

#ifndef _DEBUG  // BitnaGameView.cpp의 디버그 버전
inline CBitnaGameDoc* CBitnaGameView::GetDocument() const
   { return reinterpret_cast<CBitnaGameDoc*>(m_pDocument); }
#endif

