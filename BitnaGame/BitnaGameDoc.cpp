
// BitnaGameDoc.cpp : CBitnaGameDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "BitnaGame.h"
#endif

#include "BitnaGameDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBitnaGameDoc

IMPLEMENT_DYNCREATE(CBitnaGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CBitnaGameDoc, CDocument)
	
END_MESSAGE_MAP()


// CBitnaGameDoc 생성/소멸

CBitnaGameDoc::CBitnaGameDoc()
	: missedScore(0)
	
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CBitnaGameDoc::~CBitnaGameDoc()
{
}

BOOL CBitnaGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	gameOver = false;//모든값의 초기화 
	missedScore = 0;
	catchedScore = 0;
	count = 60;
	ballPosition.x = 190; 
	ballPosition.y = -200;  
	racketPosition.x = 500;  
	racketPosition.y = -780;  
	timerFrequency = 130;     
	
	return TRUE;
}




// CBitnaGameDoc serialization

void CBitnaGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CBitnaGameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CBitnaGameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CBitnaGameDoc::SetSearchContent(const CString& value)
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

// CBitnaGameDoc 진단

#ifdef _DEBUG
void CBitnaGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBitnaGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBitnaGameDoc 명령


void CBitnaGameDoc::setMissedScore(void)
{
	missedScore++;//공을 놓치면 ++
	
}
int CBitnaGameDoc::getMissedScore()
{
	return missedScore;//현재 놓친공 스코어 보내줌 
}

void CBitnaGameDoc::setCatchedScore()
{
	catchedScore++;//공을 잡음 
	
	
}
int CBitnaGameDoc::getCatchedScore()
{
	return catchedScore;//잡은공 정보 보내줌 
}

void CBitnaGameDoc::setCount()
{
	count--;//시간값을 계속 마이너스해줌 
	
	UpdateAllViews(NULL);//Invalidate같은 존재 
}
int CBitnaGameDoc::getCount()
{
	return count;//카운트값 보내줌 
}


void CBitnaGameDoc::setBallPosition(CPoint newPos)//공의 위치가 바뀔떄마다 좌표값 바꾸어줌 
{
	ballPosition = newPos;
	
	UpdateAllViews(NULL);
}
CPoint CBitnaGameDoc::getBallPosition()
{
	return ballPosition;//공의 위치값을 준다 
}


void CBitnaGameDoc::setRacketPosition(CPoint newPos)
{
	racketPosition = newPos;//키보드로 조절하면서 계속 바뀌는 시작값을 새로 계속 지정해준다 
	
	UpdateAllViews(NULL);//CChildview 에서의 invalidate의 역할이다 
	
}
CPoint CBitnaGameDoc::getRacketPosition()
{
	return racketPosition;//라켓 위치정보 가져옴 
}




void CBitnaGameDoc::setGameOver()//게임종료시 
{
	gameOver = true;

}
bool CBitnaGameDoc::getGameOver()
{
	return gameOver;
}

int CBitnaGameDoc::getFrequency(void)
{
	return timerFrequency;//게임 난의도 설정해주기 
}


void CBitnaGameDoc::setFrequency(int f)
{
	timerFrequency = f;
	

}
