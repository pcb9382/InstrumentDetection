// InstrumentDetectionDlg1.cpp : 实现文件
//

#include "stdafx.h"
#include "InstrumentDetection.h"
#include "InstrumentDetectionDlg1.h"
#include "InstrumentDetectionDlg.h"
#include "afxdialogex.h"


// InstrumentDetectionDlg1 对话框

IMPLEMENT_DYNAMIC(InstrumentDetectionDlg1, CDialogEx)

InstrumentDetectionDlg1::InstrumentDetectionDlg1(CWnd* pParent /*=NULL*/)
	: CDialogEx(InstrumentDetectionDlg1::IDD, pParent)
	, m_MaxValueRange(3)
{
	
}

InstrumentDetectionDlg1::~InstrumentDetectionDlg1()
{
}

void InstrumentDetectionDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_MaxValueRange);
}


BEGIN_MESSAGE_MAP(InstrumentDetectionDlg1, CDialogEx)
	ON_BN_CLICKED(IDOK, &InstrumentDetectionDlg1::OnBnClickedOk)
	
END_MESSAGE_MAP()


// InstrumentDetectionDlg1 消息处理程序


void InstrumentDetectionDlg1::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	switch (m_MaxValueRange)
	{
	case 0:
		MaxRangeValue1 = 0.15;
		break;
	case 1:
		MaxRangeValue1 = 0.30;
		break;
	case 2:
		MaxRangeValue1 = 0.40;
		break;
	case 3:
		MaxRangeValue1 = 0.60;
		break;
	case 4:
		MaxRangeValue1 = 1.00;
		break;
	case 5:
		MaxRangeValue1 = 1.50;
		break;
	case 6:
		MaxRangeValue1 = 1.60;
		break;
	case 7:
		MaxRangeValue1 = 2.50;
		break;
	case 8:
		MaxRangeValue1 = 4.00;
		break;
	case 9:
		MaxRangeValue1 = 6.00;
		break;
	case 10:
		MaxRangeValue1 = 10.0;
		break;
	case 11:
		MaxRangeValue1 = 25.0;
		break;
	default:
		MessageBox("请选择检测方法！");
		break;
	}
	CInstrumentDetectionDlg *pFatherDlg = (CInstrumentDetectionDlg*)GetParent();
	pFatherDlg->MaxRangeValue = MaxRangeValue1;
 
	CDialogEx::OnOK();
}

BOOL InstrumentDetectionDlg1::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CInstrumentDetectionDlg *pFatherDlg;
	pFatherDlg = (CInstrumentDetectionDlg*)GetParent();

	
	
	return TRUE;
}


