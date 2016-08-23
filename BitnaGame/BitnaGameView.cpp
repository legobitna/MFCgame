
// BitnaGameView.cpp : CBitnaGameView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
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

// CBitnaGameView 생성/소멸

CBitnaGameView::CBitnaGameView()
	: ballStartPoint(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	stepsOf.cx = 25; //공의 시작좌표를 잡아준다 
	stepsOf.cy = -25;
	
	racket.SetRect(0, 0, 100, 10);// 라켓의 rect를 설정한다 
	isTimerSet = false;//타이머를 꺼둔다 
	
	close = false;//게임을 끝낼때 쓴다 

}

CBitnaGameView::~CBitnaGameView()
{
}

BOOL CBitnaGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	
	 CBitmap heart;//wallpaper를 입혀줌 
        heart.LoadBitmapA(bbb);
		CBrush brush(&heart);
		 cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
  ::LoadCursor(NULL, IDC_ARROW), 
  //reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), 
  (HBRUSH)brush.Detach(),NULL);
  
	return CView::PreCreateWindow(cs);
}

// CBitnaGameView 그리기

void CBitnaGameView::OnDraw(CDC* pDC)
{
	CBitnaGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (!close) //아직 게임이 시작 안됨 
	{
		
		
		CBitmap h;//공 비트맵을 가져옴  
        h.LoadBitmapA(bbbb);
		BITMAP info;
		h.GetBitmap(&info);
		CDC menDC;
		menDC.CreateCompatibleDC(pDC);
	    menDC.SelectObject(&h);
	
	

		pDC->SetMapMode (MM_LOENGLISH);//맵모드 설정해주기 

		ballStartPoint = pDoc->getBallPosition();//시작점을 가져온다 
		ballEndPoint.x = ballStartPoint.x + info.bmWidth;
		ballEndPoint.y = ballStartPoint.y - info.bmHeight;
		pDC->BitBlt(ballStartPoint.x, ballStartPoint.y,info.bmWidth,info.bmHeight,&menDC,0,0,SRCCOPY);//공을 그려줌 
		

		CBrush racketBrush (RGB(0, 255, 0));	
		pDC->SelectObject(&racketBrush);	
	
		CSize racketSize(100,10);	//라켓 크기 잡아줌 
		racketStartPoint = pDoc->getRacketPosition();//라켓 좌표가져옴 
		racketEndPoint.x = racketStartPoint.x + racketSize.cx; 
		racketEndPoint.y = racketStartPoint.y - racketSize.cy;	
		racket.SetRect(racketStartPoint.x, racketStartPoint.y, racketEndPoint.x, racketEndPoint.y);//라켓의 영역을 잡아주고 
		pDC->Rectangle(racketStartPoint.x, racketStartPoint.y, racketEndPoint.x, racketEndPoint.y);//라켓을 그려준다 
	
		CFont fontW;//놓친공과 잡은 공 표시해주는 부분 
		fontW.CreatePointFont(300,"궁서");
		pDC->SelectObject(&fontW);
	
		CRect missedScreen;//놓쳤을때 글씨 표시해줄 영역 
		CRect catchedScreen;//잡앗다 글씨 표시해줄 영역 
		missedScreen.SetRect(1000, 0, 1220, -40 );
		catchedScreen.SetRect(20,0, 100, -40 );	
		pDC->DrawText(_T("아쉽 놓쳤다"), missedScreen, DT_RIGHT);
		pDC->DrawText(_T("아싸! 잡았다"), catchedScreen, DT_LEFT);

		CFont fontS;//스코어 숫자 표시하기위해 
		fontS.CreatePointFont(500,"궁서");
		pDC->SelectObject(&fontS);
		
		CRect screenNumMissed(1000,-50, 1220, -125 );//놓친것 스코어 표시 
		CRect screenNumCatched(18,-50, 100, -125 );//잡은것 스코어 표시
		CRect screenCount(540,-15, 700, -100 );//시간초 표시 
		
		CString num;
		num.Format(_T("%d"), pDoc->getMissedScore());
		pDC->DrawText(num, screenNumMissed, DT_RIGHT);
		num.Format(_T("%d"), pDoc->getCatchedScore());
		pDC->DrawText(num, screenNumCatched, DT_LEFT);
		num.Format(_T("%d"), pDoc->getCount());
		pDC->DrawText(num, screenCount, DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_NOCLIP);
	}
	
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CBitnaGameView 인쇄

BOOL CBitnaGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CBitnaGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CBitnaGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CBitnaGameView 진단

#ifdef _DEBUG
void CBitnaGameView::AssertValid() const
{
	CView::AssertValid();
}

void CBitnaGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBitnaGameDoc* CBitnaGameView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBitnaGameDoc)));
	return (CBitnaGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CBitnaGameView 메시지 처리기


void CBitnaGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CBitnaGameDoc* pDoc = GetDocument();		
	CSize offset(40,40); //한번에 움직이는 양 
            
    if (nChar == VK_LEFT)//좌우 움직이는 거 해주기 
	{    
		if (racketStartPoint.x >= 0) 
		{
			racketStartPoint.x -= offset.cx;//왼쪽으로가면 시작값은 마이너스된다 
			racketStartPoint.y = -780;//와이값은 밑단값으로 고정이다 
			pDoc->setRacketPosition(racketStartPoint);//변화되는 좌표값을 계속 업데이트해준다 
			
		}
	}                   
 
    if (nChar == VK_RIGHT)  
	{           
		if (racketEndPoint.x <= 1230) //0보다 작거다 1230보다 크면 움직이지 않는다  
		{
			racketStartPoint.x += offset.cx;//오른쪽으로가면 시작값은 플러스된다 
			racketStartPoint.y = -780;
			pDoc->setRacketPosition(racketStartPoint);
		
		}	
	}
	if(nChar==VK_SPACE){//스페이스를 누르면 게임이 시작된다 
		CBitnaGameDoc* pDoc = GetDocument();
	if (!isTimerSet && !pDoc->getGameOver())  // 게임의 시작값을 true로 바꾸어준다 
		{
			frequency = pDoc->getFrequency();//난의도 에따른 시간초값을 받아옴 
			SetTimer(1, frequency, NULL);//난의도 조절을 위해 frequency 로 받아온다 난이도에 따라 빠르기를 변화시킨다 	
			SetTimer(2, 1000, NULL);//1초마다 시간초 count 값을 바꾸기 위해 
			isTimerSet = true;
		
		}	

	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}





void CBitnaGameView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CBitnaGameDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
	
		if (nIDEvent == 1) // 타이머 1이라면 
		{	
			CClientDC dc (this);
			dc.SetMapMode (MM_LOENGLISH);    
	
			CRect rcClient;
			GetClientRect(&rcClient);	
			dc.DPtoLP(&rcClient);
			CPoint racketTop(0,-770);//라켓 두께와 위치 정해줌 두께는 10임 
			CPoint racketBottom(0, -780);
			CPoint ballMidPoint(ballStartPoint.x + 25, ballStartPoint.y + 25);//공의 중간좌표 
			CPoint racketMidPoint(racketStartPoint.x + 50, racketStartPoint.y + 5);//라켓의 중간좌표 
			CSize xSteps(30,0);	
	
			if (ballStartPoint.x <= 0)//공이 화면밖으로 안나가게해준다
			{
				if (stepsOf.cx < 0) //만약 공의 엑스좌표가 -로내려가게되면 -로 계속 내려가면 공이 화면밖으로 나가버림 
				{
					stepsOf.cx = -stepsOf.cx;  	//플러스로 바꾸어준다 
				}
			}
			if (ballEndPoint.x >= 1250) //공이 그려지는 끝좌표가 화면의 최대값을 못넘어가게 한다 
				//(시작좌표로 잡으면 공이화면밖으로 살짝 나갔다가 튕겨진다그래서 마지막 끝점으로 지정해줘야함 왜냐 끝점이 오른쪽면에닿으니까 )
			{
				if (stepsOf.cx > 0) 
				{
					stepsOf.cx = -stepsOf.cx;  	
				}
			}

	
			if (ballStartPoint.y >= 0)//공이 화면 제일 상단으로 나가지 않게하기 위해 잡아준다 x와 같은원리
			{
				if (stepsOf.cy > 0) 
				{
					stepsOf.cy = -stepsOf.cy;	
				}
			}
			if (ballEndPoint.y <= -880)//공이 제일 하단으로 못나가게한다 
			{
				if (stepsOf.cy < 0) 
				{
					stepsOf.cy = -stepsOf.cy;	
					pDoc->setMissedScore(); //만약 공의 y값이 화면의 제일 하단의 좌표와 일치하면 놓친걸로 간주 	
				}
			}
	


			if ((ballEndPoint.x >= racketStartPoint.x) && (ballStartPoint.x <= racketEndPoint.x) && (ballStartPoint.y <= racketTop.y))
			{		//만약 공의 끝점좌표와 라켓으 시작좌표와 같거나 (공이 라켓 왼쪽면에 부딛혔을때), 공의 시작좌표와 라켓의 끝점이 같거나(오른쪽면에 부딛힘)
				    //공의 끝점이 라켓의 상단 좌표와 같다면 (좌, 우, 위 부딛혔을경우를 해줌)
				if (stepsOf.cy < 0) 
				{
					pDoc->setCatchedScore(); // 라켓가 부딛히면 공을 잡은걸로 인정 
					stepsOf.cy = -stepsOf.cy;  //튕기는 효과를 위해 떨어지는 걸 위로 올려줌 	
					stepsOf.cx = xSteps.cx * ( (ballMidPoint.x - racketMidPoint.x) / (float)40); //다시 튕기는것에대한 x값을 위한 알고리즘
					
				}    
			}	

			ballStartPoint.x += stepsOf.cx;//리바운드 댈떄 시작좌표 다시 잡아줌 
			ballStartPoint.y += stepsOf.cy;
			pDoc->setBallPosition(ballStartPoint);//시작좌표료 다시 세팅 
		}
		else if(nIDEvent == 2) // SERVICE COUNTDOWN TIMER
		{
			if (pDoc->getCount() > 0)//타이머시간이 계속 남아 있으면 
			{
				pDoc->setCount();	//시간값을 마이너스해줌 			
			}
			else // 시간이 끝나면 
			{			
				KillTimer(2); //타이머들 종료시킴 
				KillTimer(1); 
				isTimerSet = false;
				pDoc->setGameOver(); // 게임오버시킨다 
			}
		}
	
	CView::OnTimer(nIDEvent);
}



void CBitnaGameView::OnEasy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CBitnaGameDoc* pDoc = GetDocument();	
		pDoc->setFrequency(130);//게임 난의도 조절임 130ms마다 공이 한번씩 떨어짐 
		frequency=pDoc->getFrequency();
		 if (isTimerSet)
	{
		SetTimer(1, frequency, NULL);
	}
}


void CBitnaGameView::OnMidum()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다	
	CBitnaGameDoc* pDoc = GetDocument();	
		pDoc->setFrequency(90);//타이머 90ms마다 공이 한번씩 떨어짐 
		frequency=pDoc->getFrequency();
	 if (isTimerSet)
	{
		SetTimer(1, frequency, NULL);
	}

}


void CBitnaGameView::Onhard()
{
	
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CBitnaGameDoc* pDoc = GetDocument();	
		
		pDoc->setFrequency(50);//50ms 마다 공이 한번씩 떨어짐 
		frequency=pDoc->getFrequency();
     if (isTimerSet)
	{
		SetTimer(1, frequency, NULL);
	}
		
}
