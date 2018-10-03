#pragma once
#include "resource.h"
#include "InstrumentDetectionDlg.h"
// InstrumentDetectionDlg1 对话框

class InstrumentDetectionDlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(InstrumentDetectionDlg1)

public:
	InstrumentDetectionDlg1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InstrumentDetectionDlg1();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	double MaxRangeValue1;
	int m_MaxValueRange;
};
