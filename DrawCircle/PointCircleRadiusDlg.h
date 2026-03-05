#pragma once
#include "afxdialogex.h"


// PointCircleRadiusDlg 대화 상자

class PointCircleRadiusDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PointCircleRadiusDlg)

public:
	PointCircleRadiusDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~PointCircleRadiusDlg();

	int m_Radius = 0;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POINTCIRCLERADIUS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
