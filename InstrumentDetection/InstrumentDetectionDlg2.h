#pragma once
#include "resource.h"
#include "InstrumentDetectionDlg.h"
// InstrumentDetectionDlg2 �Ի���

class InstrumentDetectionDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(InstrumentDetectionDlg2)

public:
	InstrumentDetectionDlg2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InstrumentDetectionDlg2();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	double MaxRangeValue2;
};
