
// DrawCircleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "DrawCircle.h"
#include "DrawCircleDlg.h"
#include "afxdialogex.h"

#include "PointCircleRadiusDlg.h"
#include "CircumscCircleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDrawCircleDlg 대화 상자



CDrawCircleDlg::CDrawCircleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRAWCIRCLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	CreateCirclePosTextStatics();
}

CDrawCircleDlg::~CDrawCircleDlg()
{
	for (CStatic*& textStatic : m_PointCircleCenterPosTextStatics)
	{
		if (textStatic != nullptr)
		{
			delete textStatic;
			textStatic = nullptr;
		}
	}
}

void CDrawCircleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDrawCircleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_RESET_BUTTON, &CDrawCircleDlg::OnBnClickedResetButton)
END_MESSAGE_MAP()


// CDrawCircleDlg 메시지 처리기

BOOL CDrawCircleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	InitImage();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CDrawCircleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDrawCircleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	ShowImage();
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDrawCircleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDrawCircleDlg::ShowImage()
{
	if (m_Image == nullptr)
		return;

	CClientDC dc(this);
	m_Image.Draw(dc, 0, 0);
}

void CDrawCircleDlg::InitImage()
{
	CRect rect;
	GetClientRect(&rect);

	m_PullScreenWidth = rect.Width();
	m_PullScreenHeight = rect.Height();

	if (m_Image != nullptr)
		m_Image.Destroy();



	//Height에 따라 할당되는 메모리 주소 값이 달라지기에, 아래 예제처럼 연속적으로 할 거면 반드시 지켜주어야 할 사항
	m_Image.Create(m_PullScreenWidth, -m_PullScreenHeight, 8);

	if (m_PixelGrayLevel == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
		{
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}

		m_Image.SetColorTable(0, 256, rgb);
	}

	fm = (unsigned char*)m_Image.GetBits();
	memset(fm, 255, m_PullScreenWidth * m_PullScreenHeight);

}

void CDrawCircleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (point.x < 0 || point.y < 0)
		return;

	for (int i = 0; i < sizeof(m_PointCircles) / sizeof(m_PointCircles[0]); i++)
	{
		Circle& targetPointCircle = m_PointCircles[i];

		if (targetPointCircle.IsDefault() == false)
			continue;

		PointCircleRadiusDlg pointCircleRadiusDlg;

		if (pointCircleRadiusDlg.DoModal() == IDOK)
		{
			int inputRadius = pointCircleRadiusDlg.m_Radius;

			if (inputRadius <= 0)
				return;

			TryAddPointCircle(point, inputRadius);

			UpdateDlg();

			return;
		}
	}



	CDialogEx::OnLButtonDown(nFlags, point);


}

void CDrawCircleDlg::UpdateDlg()
{
	memset(fm, 255, m_PullScreenWidth * m_PullScreenHeight);

	DrawPointCircles();

	if (CheckAllPointCircleValid())
	{
		bool circumscCircleResult = DrawCircumscribedCircle();
		HandleCircumscCircleResult(circumscCircleResult);
	}


	Invalidate();
}

void CDrawCircleDlg::DrawPointCircles()
{
	if (m_Image == nullptr)
		return;

	for (int i = 0; i < sizeof(m_PointCircles) / sizeof(m_PointCircles[0]); i++)
	{
		Circle targetPointCircle = m_PointCircles[i];

		if (targetPointCircle.IsDefault())
			continue;

		DrawCircle(fm, targetPointCircle, true);
		PrintCircleCenterPos(targetPointCircle, i);
	}
}

void CDrawCircleDlg::TryAddPointCircle(CPoint point, int radius)
{
	for (int i = 0; i < sizeof(m_PointCircles) / sizeof(m_PointCircles[0]); i++)
	{
		Circle& targetPointCircle = m_PointCircles[i];

		if (targetPointCircle.IsDefault())
		{
			targetPointCircle.center = point;
			targetPointCircle.radius = radius;
			break;
		}
	}
}

void CDrawCircleDlg::DrawCircle(unsigned char* fm, Circle circle, bool bIsFilled, int boundWidth)
{
	int nPitch = m_Image.GetPitch();

	int startPosX = circle.center.x - circle.radius;
	int startPosY = circle.center.y - circle.radius;

	int endPosX = circle.center.x + circle.radius;
	int endPosY = circle.center.y + circle.radius;

	int r2 = circle.radius * circle.radius;


	if (bIsFilled)
	{
		for (int y = startPosY; y <= endPosY; y++)
		{
			for (int x = startPosX; x <= endPosX; x++)
			{
				int dx = x - circle.center.x;
				int dy = y - circle.center.y;

				if ((x < 0 || y < 0) || ((x >= m_PullScreenWidth || y >= m_PullScreenHeight)))
					continue;

				if (dx * dx + dy * dy <= r2)
				{
					fm[y * nPitch + x] = 0;
				}
			}
		}
	}

	else
	{
		float halfWidth = boundWidth * 0.5f;

		int outer = (circle.radius + halfWidth);
		int inner = (circle.radius - halfWidth);

		int startPosX = circle.center.x - (circle.radius + halfWidth);
		int startPosY = circle.center.y - (circle.radius + halfWidth);

		int endPosX = circle.center.x + (circle.radius + halfWidth);
		int endPosY = circle.center.y + (circle.radius + halfWidth);

		for (int y = startPosY; y <= endPosY; y++)
		{
			for (int x = startPosX; x <= endPosX; x++)
			{
				if (x < 0 || y < 0 || x >= m_PullScreenWidth || y >= m_PullScreenHeight)
					continue;

				int dx = x - circle.center.x;
				int dy = y - circle.center.y;

				int dist2 = dx * dx + dy * dy;

				if (dist2 <= outer * outer && dist2 >= inner * inner)
				{
					fm[y * nPitch + x] = 0;
				}
			}
		}
	}
}

void CDrawCircleDlg::PrintCircleCenterPos(Circle circle, int assignedIndex)
{
	if (assignedIndex < 0 || assignedIndex >= MAX_POINT_CIRCLES)
		return;

	CStatic* pStatic = m_PointCircleCenterPosTextStatics[assignedIndex];
	if (pStatic == nullptr)
		return;

	const int offset_Y = 20;
	const int textWidth = 100;
	const int textHeight = 20;

	int textAnchor_X = (circle.center.x < m_PullScreenWidth / 2) ? 1 : -1;
	int textAnchor_Y = (circle.center.y < m_PullScreenHeight / 2) ? 1 : -1;

	int startPosX = circle.center.x + textAnchor_X * circle.radius;
	int startPosY = circle.center.y + textAnchor_Y * circle.radius;

	int left = startPosX;
	int top = startPosY - offset_Y * 2;

	if (left < 0)
		left = 0;

	if (left + textWidth > m_PullScreenWidth)
		left = m_PullScreenWidth - textWidth;

	if (top < 0)
		top = 0;

	if (top + textHeight > m_PullScreenHeight)
		top = m_PullScreenHeight - textHeight;

	CRect rect(left, top, left + textWidth, top + textHeight);

	if (::IsWindow(pStatic->GetSafeHwnd()) == false)
	{
		pStatic->Create(_T(""), WS_CHILD | WS_VISIBLE | SS_CENTER, rect, this);
	}
	else
	{
		pStatic->MoveWindow(rect);
		pStatic->ShowWindow(SW_SHOW);
	}

	CString str;
	str.Format(_T("X: %d, Y: %d"), circle.center.x, circle.center.y);
	pStatic->SetWindowText(str);
}

void CDrawCircleDlg::CreateCirclePosTextStatics()
{
	for (CStatic*& textStatic : m_PointCircleCenterPosTextStatics)
	{
		textStatic = new CStatic();
	}
}

void CDrawCircleDlg::HideTextStatic(int index)
{
	if (index < 0 || index >= MAX_POINT_CIRCLES)
		return;

	CStatic* targetStatic = m_PointCircleCenterPosTextStatics[index];

	if (targetStatic == nullptr)
		return;

	if (::IsWindow(targetStatic->GetSafeHwnd()) == false)
		return;

	targetStatic->SetWindowText(_T(""));

	targetStatic->MoveWindow(-100, -100, 0, 0);

	targetStatic->ShowWindow(SW_HIDE);
}

bool CDrawCircleDlg::DrawCircumscribedCircle()
{
	CircumscCircle.SetDefault();

	CPoint p1 = m_PointCircles[0].center;
	CPoint p2 = m_PointCircles[1].center;
	CPoint p3 = m_PointCircles[2].center;

	double x1 = p1.x;
	double y1 = p1.y;

	double x2 = p2.x;
	double y2 = p2.y;

	double x3 = p3.x;
	double y3 = p3.y;

	double D = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));

	if (fabs(D) < 0.0001)
		return false;

	double Ux =
		((x1 * x1 + y1 * y1) * (y2 - y3) +
			(x2 * x2 + y2 * y2) * (y3 - y1) +
			(x3 * x3 + y3 * y3) * (y1 - y2)) / D;

	double Uy =
		((x1 * x1 + y1 * y1) * (x3 - x2) +
			(x2 * x2 + y2 * y2) * (x1 - x3) +
			(x3 * x3 + y3 * y3) * (x2 - x1)) / D;

	double dx = Ux - x1;
	double dy = Uy - y1;

	double r = dx * dx + dy * dy;

	CircumscCircle.center = CPoint((int)Ux, (int)Uy);
	CircumscCircle.radius = (int)sqrt(r);

	//DrawCircle(fm, CircumscCircle, false, 5);

	return true;
}



bool CDrawCircleDlg::CheckAllPointCircleValid()
{
	for (Circle& pointCircle : m_PointCircles)
	{
		if (pointCircle.IsDefault())
			return false;
	}

	return true;
}

void CDrawCircleDlg::HandleCircumscCircleResult(bool isDrawn)
{
	if (isDrawn)
	{
		CircumscCircleDlg circumscCircleDlg;

		if (circumscCircleDlg.DoModal() == IDOK)
		{
			int inputRadius = circumscCircleDlg.m_CircumscCircleBoundWidth;

			if (inputRadius <= 0)
				return;

			if (CircumscCircle.IsDefault() == false)
			{
				DrawCircle(fm, CircumscCircle, false, inputRadius);
			}
				
		}
	}

	else
	{
		AfxMessageBox(_T("외접원 생성에 실패했습니다."), MB_OK | MB_ICONWARNING);

		ResetAll();
	}
}

void CDrawCircleDlg::ResetAll()
{
	CircumscCircle.SetDefault();

	for (Circle& pointCircle : m_PointCircles)
	{
		pointCircle.SetDefault();
	}

	for (int i = 0; i < sizeof(m_PointCircleCenterPosTextStatics) / sizeof(m_PointCircleCenterPosTextStatics[0]); i++)
	{
		HideTextStatic(i);
	}

	memset(fm, 255, m_PullScreenWidth * m_PullScreenHeight);

	Invalidate();
}

void CDrawCircleDlg::OnBnClickedResetButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ResetAll();
}
