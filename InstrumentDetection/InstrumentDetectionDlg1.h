#pragma once
#include "resource.h"
#include "InstrumentDetectionDlg.h"
// InstrumentDetectionDlg1 �Ի���

class InstrumentDetectionDlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(InstrumentDetectionDlg1)

public:
	InstrumentDetectionDlg1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InstrumentDetectionDlg1();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	double MaxRangeValue1;
	int m_MaxValueRange;
};
