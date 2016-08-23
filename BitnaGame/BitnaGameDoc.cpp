
// BitnaGameDoc.cpp : CBitnaGameDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// CBitnaGameDoc ����/�Ҹ�

CBitnaGameDoc::CBitnaGameDoc()
	: missedScore(0)
	
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CBitnaGameDoc::~CBitnaGameDoc()
{
}

BOOL CBitnaGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.
	gameOver = false;//��簪�� �ʱ�ȭ 
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
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CBitnaGameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CBitnaGameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CBitnaGameDoc ����

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


// CBitnaGameDoc ���


void CBitnaGameDoc::setMissedScore(void)
{
	missedScore++;//���� ��ġ�� ++
	
}
int CBitnaGameDoc::getMissedScore()
{
	return missedScore;//���� ��ģ�� ���ھ� ������ 
}

void CBitnaGameDoc::setCatchedScore()
{
	catchedScore++;//���� ���� 
	
	
}
int CBitnaGameDoc::getCatchedScore()
{
	return catchedScore;//������ ���� ������ 
}

void CBitnaGameDoc::setCount()
{
	count--;//�ð����� ��� ���̳ʽ����� 
	
	UpdateAllViews(NULL);//Invalidate���� ���� 
}
int CBitnaGameDoc::getCount()
{
	return count;//ī��Ʈ�� ������ 
}


void CBitnaGameDoc::setBallPosition(CPoint newPos)//���� ��ġ�� �ٲ������� ��ǥ�� �ٲپ��� 
{
	ballPosition = newPos;
	
	UpdateAllViews(NULL);
}
CPoint CBitnaGameDoc::getBallPosition()
{
	return ballPosition;//���� ��ġ���� �ش� 
}


void CBitnaGameDoc::setRacketPosition(CPoint newPos)
{
	racketPosition = newPos;//Ű����� �����ϸ鼭 ��� �ٲ�� ���۰��� ���� ��� �������ش� 
	
	UpdateAllViews(NULL);//CChildview ������ invalidate�� �����̴� 
	
}
CPoint CBitnaGameDoc::getRacketPosition()
{
	return racketPosition;//���� ��ġ���� ������ 
}




void CBitnaGameDoc::setGameOver()//��������� 
{
	gameOver = true;

}
bool CBitnaGameDoc::getGameOver()
{
	return gameOver;
}

int CBitnaGameDoc::getFrequency(void)
{
	return timerFrequency;//���� ���ǵ� �������ֱ� 
}


void CBitnaGameDoc::setFrequency(int f)
{
	timerFrequency = f;
	

}
