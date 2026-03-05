// PointCircleRadiusDlg.cpp: 구현 파일
//

#include "pch.h"
#include "DrawCircle.h"
#include "afxdialogex.h"
#include "PointCircleRadiusDlg.h"


// PointCircleRadiusDlg 대화 상자

IMPLEMENT_DYNAMIC(PointCircleRadiusDlg, CDialogEx)

PointCircleRadiusDlg::PointCircleRadiusDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POINTCIRCLERADIUS_DIALOG, pParent)
{

}

PointCircleRadiusDlg::~PointCircleRadiusDlg()
{
}

void PointCircleRadiusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PointCircleRadiusDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &PointCircleRadiusDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// PointCircleRadiusDlg 메시지 처리기

void PointCircleRadiusDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString radiusText;
	GetDlgItemText(IDC_RADIUS_EDIT, radiusText);

	TCHAR* endPtr;
	float inputRadius = _tcstod(radiusText, &endPtr);

	if (*endPtr != '\0')
		m_Radius = -1;

	else
		m_Radius = inputRadius;
	

	CDialogEx::OnOK();
}
