#pragma once
#include "resource.h"
#include "InstrumentDetectionDlg.h"
// InstrumentDetectionDlg3 �Ի���

class InstrumentDetectionDlg3 : public CDialogEx
{
	DECLARE_DYNAMIC(InstrumentDetectionDlg3)

public:
	InstrumentDetectionDlg3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InstrumentDetectionDlg3();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	double MaxRangeValue3;
};
