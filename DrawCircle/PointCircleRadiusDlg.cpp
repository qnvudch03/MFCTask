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
END_MESSAGE_MAP()


// PointCircleRadiusDlg 메시지 처리기
