
// BitnaGameDoc.h : CBitnaGameDoc Ŭ������ �������̽�
//


#pragma once


class CBitnaGameDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CBitnaGameDoc();
	DECLARE_DYNCREATE(CBitnaGameDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CBitnaGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int missedScore;
	int catchedScore;
	int count;
	CPoint ballPosition;
	CPoint racketPosition;
	UINT timerFrequency;
	bool gameOver;
	void setMissedScore(void);
	int getMissedScore(void);
	void setCatchedScore(void);
	int getCatchedScore(void);
	void setCount(void);
	int getCount(void);
	void setBallPosition(CPoint);
	void setRacketPosition(CPoint);
	CPoint getBallPosition(void);
	CPoint getRacketPosition(void);	
	
	
	void setGameOver(void);
	bool getGameOver(void);
	


	
	int getFrequency(void);
	void setFrequency(int f);
};
