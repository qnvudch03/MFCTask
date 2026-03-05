#pragma once
#include "afxdialogex.h"


// CircumscCircleDlg 대화 상자

class CircumscCircleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CircumscCircleDlg)

public:
	CircumscCircleDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CircumscCircleDlg();

	int m_CircumscCircleBoundWidth = 0;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CIRCUMSCCIRCLE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
