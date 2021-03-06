﻿
// AROMADlg.h: 헤더 파일
//

#pragma once

#include "tw_direct_show.h"

// CAROMADlg 대화 상자
class CAROMADlg : public CDialogEx
{

private:
	CPoint m_prev_pos;
	BOOL m_is_clicked = FALSE;
	TW_LiveCam mLiveCam;
	TW_PreviewGraphBuilder* mpPreview = NULL;
	TW_CaptureGraphBuilder* mcPreview = NULL;

// 생성입니다.
public:
	CAROMADlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AROMA_DIALOG };
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
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnClickedButton2();
	afx_msg void OnClickedButton1();
	virtual void saveImg();
	virtual void ConnectDB();
};
