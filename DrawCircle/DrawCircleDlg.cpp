
// DrawCircleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "DrawCircle.h"
#include "DrawCircleDlg.h"
#include "afxdialogex.h"

#include "PointCircleRadiusDlg.h"

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
			float inputRadius = pointCircleRadiusDlg.m_Radius;

			if (inputRadius <= 0)
				return;

			TryAddPointCircle(point, inputRadius);

			UpdateDlg();

			return;
		}
	}

	

	CDialogEx::OnLButtonDown(nFlags, point);
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


	//Invalidate();
	//ShowImage();
}

void CDrawCircleDlg::DrawCircle(unsigned char* fm, Circle circle, bool bIsFilled, float boundWidth)
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

				if (dx * dx + dy * dy <= r2)
				{
					fm[y * nPitch + x] = 0;
				}
			}
		}
	}

	else
	{
		for (int y = startPosY; y <= endPosY; y++)
		{
			for (int x = startPosX; x <= endPosX; x++)
			{
				int dx = x - circle.center.x;
				int dy = y - circle.center.y;

				int dist2 = dx * dx + dy * dy;

				int outer = r2;
				int inner = (circle.radius - boundWidth) * (circle.radius - boundWidth);

				if (dist2 <= outer && dist2 >= inner)
				{
					fm[y * nPitch + x] = 255;
				}
			}
		}
	}
}

void CDrawCircleDlg::ShowImage()
{
	if (m_Image == nullptr)
		return;

	CClientDC dc(this);
	m_Image.Draw(dc, 0, 0);
}

void CDrawCircleDlg::UpdateDlg()
{
	//memset(fm, 255, m_Image.GetWidth() * m_Image.GetHeight());
	memset(fm, 255, m_PullScreenWidth * m_PullScreenHeight);

	DrawPointCircles();

	ShowImage();
}

void CDrawCircleDlg::DrawPointCircles()
{
	if (m_Image == nullptr)
		return;

	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	for (int i = 0; i < sizeof(m_PointCircles) / sizeof(m_PointCircles[0]); i++)
	{
		Circle targetPointCircle = m_PointCircles[i];

		if (targetPointCircle.IsDefault())
			continue;

		DrawCircle(fm, targetPointCircle, true);

	}
}

void CDrawCircleDlg::TryAddPointCircle(CPoint point, float radius)
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
