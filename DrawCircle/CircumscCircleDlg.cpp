// CircumscCircleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "DrawCircle.h"
#include "afxdialogex.h"
#include "CircumscCircleDlg.h"


// CircumscCircleDlg 대화 상자

IMPLEMENT_DYNAMIC(CircumscCircleDlg, CDialogEx)

CircumscCircleDlg::CircumscCircleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CIRCUMSCCIRCLE_DIALOG, pParent)
{

}

CircumscCircleDlg::~CircumscCircleDlg()
{
}

void CircumscCircleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CircumscCircleDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CircumscCircleDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CircumscCircleDlg 메시지 처리기

void CircumscCircleDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_CircumscCircleBoundWidth = GetDlgItemInt(IDC_CIRCLEBOUNDWIDTH_EDIT);

	CDialogEx::OnOK();
}
