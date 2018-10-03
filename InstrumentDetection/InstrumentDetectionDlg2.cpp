// InstrumentDetectionDlg2.cpp : 实现文件
//

#include "stdafx.h"
#include "InstrumentDetection.h"
#include "InstrumentDetectionDlg2.h"
#include "afxdialogex.h"
#include "resource.h"

// InstrumentDetectionDlg2 对话框

IMPLEMENT_DYNAMIC(InstrumentDetectionDlg2, CDialogEx)

InstrumentDetectionDlg2::InstrumentDetectionDlg2(CWnd* pParent /*=NULL*/)
	: CDialogEx(InstrumentDetectionDlg2::IDD, pParent)
{

}

InstrumentDetectionDlg2::~InstrumentDetectionDlg2()
{
}

void InstrumentDetectionDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InstrumentDetectionDlg2, CDialogEx)
	ON_BN_CLICKED(IDOK, &InstrumentDetectionDlg2::OnBnClickedOk)
END_MESSAGE_MAP()


// InstrumentDetectionDlg2 消息处理程序


void InstrumentDetectionDlg2::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int index1;
	index1 = ((CComboBox*)GetDlgItem(IDC_COMBO1Video))->GetCurSel();
	switch (index1)
	{
	case 0:
		MaxRangeValue2 = 0.15;
		break;
	case 1:
		MaxRangeValue2 = 0.30;
		break;
	case 2:
		MaxRangeValue2 = 0.40;
		break;
	case 3:
		MaxRangeValue2 = 0.60;
		break;
	case 4:
		MaxRangeValue2 = 1.00;
		break;
	case 5:
		MaxRangeValue2 = 1.50;
		break;
	case 6:
		MaxRangeValue2 = 1.60;
		break;
	case 7:
		MaxRangeValue2 = 2.50;
		break;
	case 8:
		MaxRangeValue2 = 4.00;
		break;
	case 9:
		MaxRangeValue2 = 6.00;
		break;
	case 10:
		MaxRangeValue2 = 10.0;
		break;
	case 11:
		MaxRangeValue2 = 25.0;
		break;
	case 12:
		MaxRangeValue2 = 60.0;
		break;
	default:
		MaxRangeValue2 = 100;
		break;
	}
	CInstrumentDetectionDlg *pFatherDlg = (CInstrumentDetectionDlg*)GetParent();
	pFatherDlg->MaxRangeValue = MaxRangeValue2;
	CDialogEx::OnOK();
}

BOOL InstrumentDetectionDlg2::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CInstrumentDetectionDlg *pFatherDlg;
	pFatherDlg = (CInstrumentDetectionDlg*)GetParent();

	((CComboBox*)GetDlgItem(IDC_COMBO1Video))->AddString("0.15");
	((CComboBox*)GetDlgItem(IDC_COMBO1Video))->AddString("0.30");
	((CComboBox*)GetDlgItem(IDC_COMBO1Video))->AddString("0.40");
	((CComboBox*)GetDlgItem(IDC_COMBO1Video))->AddString("0.60");
	((CComboBox*)GetDlgItem(IDC_COMBO1Video))->AddString("1.00");
	((CComboBox*)GetDlgItem(IDC_COMBO1Video))->AddString("1.50");
	((CComboBox*)GetDlgItem(IDC_COMBO1Video))->AddString("1.60");
	((CComboBox*)GetDlgItem(IDC_COMBO1Video))->AddString("2.50");
	((CComboBox*)GetDlgItem(IDC_COMBO1Video))->AddString("4.00");
	((CComboBox*)GetDlgItem(IDC_COMBO1Video))->AddString("6.00");
	((CComboBox*)GetDlgItem(IDC_COMBO1Video))->AddString("10.0");
	((CComboBox*)GetDlgItem(IDC_COMBO1Video))->AddString("25.0");
	((CComboBox*)GetDlgItem(IDC_COMBO1Video))->AddString("60.0");
	((CComboBox*)GetDlgItem(IDC_COMBO1Video))->AddString("100.0");
	((CComboBox*)GetDlgItem(IDC_COMBO1Video))->SetCurSel(3);


	return TRUE;
}