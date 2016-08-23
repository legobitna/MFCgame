
// BitnaGameView.cpp : CBitnaGameView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "BitnaGame.h"
#endif

#include "BitnaGameDoc.h"
#include "BitnaGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBitnaGameView

IMPLEMENT_DYNCREATE(CBitnaGameView, CView)

BEGIN_MESSAGE_MAP(CBitnaGameView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_32771, &CBitnaGameView::OnEasy)
	ON_COMMAND(ID_32772, &CBitnaGameView::OnMidum)
	ON_COMMAND(ID_32773, &CBitnaGameView::Onhard)
END_MESSAGE_MAP()

// CBitnaGameView ����/�Ҹ�

CBitnaGameView::CBitnaGameView()
	: ballStartPoint(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	stepsOf.cx = 25; //���� ������ǥ�� ����ش� 
	stepsOf.cy = -25;
	
	racket.SetRect(0, 0, 100, 10);// ������ rect�� �����Ѵ� 
	isTimerSet = false;//Ÿ�̸Ӹ� ���д� 
	
	close = false;//������ ������ ���� 

}

CBitnaGameView::~CBitnaGameView()
{
}

BOOL CBitnaGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	
	 CBitmap heart;//wallpaper�� ������ 
        heart.LoadBitmapA(bbb);
		CBrush brush(&heart);
		 cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
  ::LoadCursor(NULL, IDC_ARROW), 
  //reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), 
  (HBRUSH)brush.Detach(),NULL);
  
	return CView::PreCreateWindow(cs);
}

// CBitnaGameView �׸���

void CBitnaGameView::OnDraw(CDC* pDC)
{
	CBitnaGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (!close) //���� ������ ���� �ȵ� 
	{
		
		
		CBitmap h;//�� ��Ʈ���� ������  
        h.LoadBitmapA(bbbb);
		BITMAP info;
		h.GetBitmap(&info);
		CDC menDC;
		menDC.CreateCompatibleDC(pDC);
	    menDC.SelectObject(&h);
	
	

		pDC->SetMapMode (MM_LOENGLISH);//�ʸ�� �������ֱ� 

		ballStartPoint = pDoc->getBallPosition();//�������� �����´� 
		ballEndPoint.x = ballStartPoint.x + info.bmWidth;
		ballEndPoint.y = ballStartPoint.y - info.bmHeight;
		pDC->BitBlt(ballStartPoint.x, ballStartPoint.y,info.bmWidth,info.bmHeight,&menDC,0,0,SRCCOPY);//���� �׷��� 
		

		CBrush racketBrush (RGB(0, 255, 0));	
		pDC->SelectObject(&racketBrush);	
	
		CSize racketSize(100,10);	//���� ũ�� ����� 
		racketStartPoint = pDoc->getRacketPosition();//���� ��ǥ������ 
		racketEndPoint.x = racketStartPoint.x + racketSize.cx; 
		racketEndPoint.y = racketStartPoint.y - racketSize.cy;	
		racket.SetRect(racketStartPoint.x, racketStartPoint.y, racketEndPoint.x, racketEndPoint.y);//������ ������ ����ְ� 
		pDC->Rectangle(racketStartPoint.x, racketStartPoint.y, racketEndPoint.x, racketEndPoint.y);//������ �׷��ش� 
	
		CFont fontW;//��ģ���� ���� �� ǥ�����ִ� �κ� 
		fontW.CreatePointFont(300,"�ü�");
		pDC->SelectObject(&fontW);
	
		CRect missedScreen;//�������� �۾� ǥ������ ���� 
		CRect catchedScreen;//��Ѵ� �۾� ǥ������ ���� 
		missedScreen.SetRect(1000, 0, 1220, -40 );
		catchedScreen.SetRect(20,0, 100, -40 );	
		pDC->DrawText(_T("�ƽ� ���ƴ�"), missedScreen, DT_RIGHT);
		pDC->DrawText(_T("�ƽ�! ��Ҵ�"), catchedScreen, DT_LEFT);

		CFont fontS;//���ھ� ���� ǥ���ϱ����� 
		fontS.CreatePointFont(500,"�ü�");
		pDC->SelectObject(&fontS);
		
		CRect screenNumMissed(1000,-50, 1220, -125 );//��ģ�� ���ھ� ǥ�� 
		CRect screenNumCatched(18,-50, 100, -125 );//������ ���ھ� ǥ��
		CRect screenCount(540,-15, 700, -100 );//�ð��� ǥ�� 
		
		CString num;
		num.Format(_T("%d"), pDoc->getMissedScore());
		pDC->DrawText(num, screenNumMissed, DT_RIGHT);
		num.Format(_T("%d"), pDoc->getCatchedScore());
		pDC->DrawText(num, screenNumCatched, DT_LEFT);
		num.Format(_T("%d"), pDoc->getCount());
		pDC->DrawText(num, screenCount, DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_NOCLIP);
	}
	
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CBitnaGameView �μ�

BOOL CBitnaGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CBitnaGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CBitnaGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CBitnaGameView ����

#ifdef _DEBUG
void CBitnaGameView::AssertValid() const
{
	CView::AssertValid();
}

void CBitnaGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBitnaGameDoc* CBitnaGameView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBitnaGameDoc)));
	return (CBitnaGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CBitnaGameView �޽��� ó����


void CBitnaGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CBitnaGameDoc* pDoc = GetDocument();		
	CSize offset(40,40); //�ѹ��� �����̴� �� 
            
    if (nChar == VK_LEFT)//�¿� �����̴� �� ���ֱ� 
	{    
		if (racketStartPoint.x >= 0) 
		{
			racketStartPoint.x -= offset.cx;//�������ΰ��� ���۰��� ���̳ʽ��ȴ� 
			racketStartPoint.y = -780;//���̰��� �شܰ����� �����̴� 
			pDoc->setRacketPosition(racketStartPoint);//��ȭ�Ǵ� ��ǥ���� ��� ������Ʈ���ش� 
			
		}
	}                   
 
    if (nChar == VK_RIGHT)  
	{           
		if (racketEndPoint.x <= 1230) //0���� �۰Ŵ� 1230���� ũ�� �������� �ʴ´�  
		{
			racketStartPoint.x += offset.cx;//���������ΰ��� ���۰��� �÷����ȴ� 
			racketStartPoint.y = -780;
			pDoc->setRacketPosition(racketStartPoint);
		
		}	
	}
	if(nChar==VK_SPACE){//�����̽��� ������ ������ ���۵ȴ� 
		CBitnaGameDoc* pDoc = GetDocument();
	if (!isTimerSet && !pDoc->getGameOver())  // ������ ���۰��� true�� �ٲپ��ش� 
		{
			frequency = pDoc->getFrequency();//���ǵ� ������ �ð��ʰ��� �޾ƿ� 
			SetTimer(1, frequency, NULL);//���ǵ� ������ ���� frequency �� �޾ƿ´� ���̵��� ���� �����⸦ ��ȭ��Ų�� 	
			SetTimer(2, 1000, NULL);//1�ʸ��� �ð��� count ���� �ٲٱ� ���� 
			isTimerSet = true;
		
		}	

	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}





void CBitnaGameView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CBitnaGameDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
	
		if (nIDEvent == 1) // Ÿ�̸� 1�̶�� 
		{	
			CClientDC dc (this);
			dc.SetMapMode (MM_LOENGLISH);    
	
			CRect rcClient;
			GetClientRect(&rcClient);	
			dc.DPtoLP(&rcClient);
			CPoint racketTop(0,-770);//���� �β��� ��ġ ������ �β��� 10�� 
			CPoint racketBottom(0, -780);
			CPoint ballMidPoint(ballStartPoint.x + 25, ballStartPoint.y + 25);//���� �߰���ǥ 
			CPoint racketMidPoint(racketStartPoint.x + 50, racketStartPoint.y + 5);//������ �߰���ǥ 
			CSize xSteps(30,0);	
	
			if (ballStartPoint.x <= 0)//���� ȭ������� �ȳ��������ش�
			{
				if (stepsOf.cx < 0) //���� ���� ������ǥ�� -�γ������ԵǸ� -�� ��� �������� ���� ȭ������� �������� 
				{
					stepsOf.cx = -stepsOf.cx;  	//�÷����� �ٲپ��ش� 
				}
			}
			if (ballEndPoint.x >= 1250) //���� �׷����� ����ǥ�� ȭ���� �ִ밪�� ���Ѿ�� �Ѵ� 
				//(������ǥ�� ������ ����ȭ������� ��¦ �����ٰ� ƨ�����ٱ׷��� ������ �������� ����������� �ֳ� ������ �����ʸ鿡�����ϱ� )
			{
				if (stepsOf.cx > 0) 
				{
					stepsOf.cx = -stepsOf.cx;  	
				}
			}

	
			if (ballStartPoint.y >= 0)//���� ȭ�� ���� ������� ������ �ʰ��ϱ� ���� ����ش� x�� ��������
			{
				if (stepsOf.cy > 0) 
				{
					stepsOf.cy = -stepsOf.cy;	
				}
			}
			if (ballEndPoint.y <= -880)//���� ���� �ϴ����� ���������Ѵ� 
			{
				if (stepsOf.cy < 0) 
				{
					stepsOf.cy = -stepsOf.cy;	
					pDoc->setMissedScore(); //���� ���� y���� ȭ���� ���� �ϴ��� ��ǥ�� ��ġ�ϸ� ��ģ�ɷ� ���� 	
				}
			}
	


			if ((ballEndPoint.x >= racketStartPoint.x) && (ballStartPoint.x <= racketEndPoint.x) && (ballStartPoint.y <= racketTop.y))
			{		//���� ���� ������ǥ�� ������ ������ǥ�� ���ų� (���� ���� ���ʸ鿡 �ε�������), ���� ������ǥ�� ������ ������ ���ų�(�����ʸ鿡 �ε���)
				    //���� ������ ������ ��� ��ǥ�� ���ٸ� (��, ��, �� �ε�������츦 ����)
				if (stepsOf.cy < 0) 
				{
					pDoc->setCatchedScore(); // ���ϰ� �ε����� ���� �����ɷ� ���� 
					stepsOf.cy = -stepsOf.cy;  //ƨ��� ȿ���� ���� �������� �� ���� �÷��� 	
					stepsOf.cx = xSteps.cx * ( (ballMidPoint.x - racketMidPoint.x) / (float)40); //�ٽ� ƨ��°Ϳ����� x���� ���� �˰���
					
				}    
			}	

			ballStartPoint.x += stepsOf.cx;//���ٿ�� � ������ǥ �ٽ� ����� 
			ballStartPoint.y += stepsOf.cy;
			pDoc->setBallPosition(ballStartPoint);//������ǥ�� �ٽ� ���� 
		}
		else if(nIDEvent == 2) // SERVICE COUNTDOWN TIMER
		{
			if (pDoc->getCount() > 0)//Ÿ�̸ӽð��� ��� ���� ������ 
			{
				pDoc->setCount();	//�ð����� ���̳ʽ����� 			
			}
			else // �ð��� ������ 
			{			
				KillTimer(2); //Ÿ�̸ӵ� �����Ŵ 
				KillTimer(1); 
				isTimerSet = false;
				pDoc->setGameOver(); // ���ӿ�����Ų�� 
			}
		}
	
	CView::OnTimer(nIDEvent);
}



void CBitnaGameView::OnEasy()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CBitnaGameDoc* pDoc = GetDocument();	
		pDoc->setFrequency(130);//���� ���ǵ� ������ 130ms���� ���� �ѹ��� ������ 
		frequency=pDoc->getFrequency();
		 if (isTimerSet)
	{
		SetTimer(1, frequency, NULL);
	}
}


void CBitnaGameView::OnMidum()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�	
	CBitnaGameDoc* pDoc = GetDocument();	
		pDoc->setFrequency(90);//Ÿ�̸� 90ms���� ���� �ѹ��� ������ 
		frequency=pDoc->getFrequency();
	 if (isTimerSet)
	{
		SetTimer(1, frequency, NULL);
	}

}


void CBitnaGameView::Onhard()
{
	
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CBitnaGameDoc* pDoc = GetDocument();	
		
		pDoc->setFrequency(50);//50ms ���� ���� �ѹ��� ������ 
		frequency=pDoc->getFrequency();
     if (isTimerSet)
	{
		SetTimer(1, frequency, NULL);
	}
		
}
