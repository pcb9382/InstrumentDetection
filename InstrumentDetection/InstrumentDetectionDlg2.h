#pragma once
#include "resource.h"
#include "InstrumentDetectionDlg.h"
// InstrumentDetectionDlg2 对话框

class InstrumentDetectionDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(InstrumentDetectionDlg2)

public:
	InstrumentDetectionDlg2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InstrumentDetectionDlg2();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	double MaxRangeValue2;
};
