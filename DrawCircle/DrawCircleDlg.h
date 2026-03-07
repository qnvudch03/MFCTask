
// DrawCircleDlg.h: 헤더 파일
//

#pragma once

#define MAX_POINT_CIRCLES 3

// CDrawCircleDlg 대화 상자
class CDrawCircleDlg : public CDialogEx
{

	struct Circle
	{
		CPoint center;
		int  radius;

		Circle() : center(0, 0), radius(-1)
		{
		}

		bool IsDefault() const
		{
			return (center.x == 0 && center.y == 0) && radius == -1;
		}

		void SetDefault()
		{
			center = CPoint(0, 0);
			radius = -1;
		}
	};

// 생성입니다.
public:
	CDrawCircleDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	~CDrawCircleDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAWCIRCLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedResetButton();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnBnClickedRandommoveButton();


private:

	bool m_IsMouseButtonDown = false;

	int m_FocusedPointCircleIndex = -1;

	int m_PullScreenWidth = 0;
	int m_PullScreenHeight = 0;
	int m_PixelGrayLevel = 8;

	CImage m_Image;
	unsigned char* fm;
	void InitDialog();

	CWnd* m_RestButton = nullptr;
	CWnd* m_RandomMoveButton = nullptr;
	void InitImage();


	void ShowImage();


	void DrawPointCircles();
	void DrawCircumscCircle();

	//Point Circle 관련
	Circle m_PointCircles[MAX_POINT_CIRCLES];
	CStatic* m_PointCircleCenterPosTextStatics[MAX_POINT_CIRCLES];

	void TryAddPointCircle(CPoint point);
	void AddPointCircle(CPoint point, int radius);
	void DrawCircle(unsigned char* fm, Circle circle, bool bIsFilled = true, int boundWidth = 0.0f);
	void PrintCircleCenterPos(Circle circle, int assignedIndex);

	void CreateCirclePosTextStatics();
	void HideTextStatic(int index);

	bool IsClickedOnPointCircle(CPoint point);

	//외접원
	Circle CircumscCircle;
	int m_catchedCircleWidth = 0;
	bool DrawCircumscribedCircle();
	void HandleCircumscCircleResult(bool isDrawn);


	//Util
	void ResetAll();

	bool CheckAllPointCircleValid();

	bool CheckIsValidMousePos(CPoint point);

	void SetVisibilityButton(CWnd* cnwd, bool bVisible);

	void PlayRandomCircleAnim();


public:

	void ChangeCirclePosToRandom();
	void UpdateDlg();

	void HideUserButtons();
	void ShowUserButtons();
};
