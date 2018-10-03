#pragma once
#include "resource.h"
#include "InstrumentDetectionDlg.h"
// InstrumentDetectionDlg3 对话框

class InstrumentDetectionDlg3 : public CDialogEx
{
	DECLARE_DYNAMIC(InstrumentDetectionDlg3)

public:
	InstrumentDetectionDlg3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InstrumentDetectionDlg3();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	double MaxRangeValue3;
};
