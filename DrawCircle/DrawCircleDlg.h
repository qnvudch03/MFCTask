
// DrawCircleDlg.h: 헤더 파일
//

#pragma once

// CDrawCircleDlg 대화 상자
class CDrawCircleDlg : public CDialogEx
{

	struct Circle
	{
		CPoint center;
		float  radius;

		Circle() : center(0, 0), radius(-1.0f)
		{
		}

		bool IsDefault() const
		{
			return (center.x == 0 && center.y == 0) && radius == -1.0f;
		}
	};

// 생성입니다.
public:
	CDrawCircleDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

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


private:

	int m_PullScreenWidth = 0;
	int m_PullScreenHeight = 0;
	int m_PixelGrayLevel = 8;

	CImage m_Image;
	unsigned char* fm;
	void InitImage();

	void DrawCircle(unsigned char* fm, Circle circle, bool bIsFilled = true, float boundWidth = 0.0f);
	void ShowImage();

	void UpdateDlg();
	void DrawPointCircles();

	// 유저 Point Circle 관련
	Circle m_PointCircles[3];

	void TryAddPointCircle(CPoint point, float radius);

	//Util
};
