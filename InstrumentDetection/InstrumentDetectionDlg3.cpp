// InstrumentDetectionDlg3.cpp : 实现文件
//

#include "stdafx.h"
#include "InstrumentDetection.h"
#include "InstrumentDetectionDlg3.h"
#include "afxdialogex.h"
#include "resource.h"

// InstrumentDetectionDlg3 对话框

IMPLEMENT_DYNAMIC(InstrumentDetectionDlg3, CDialogEx)

InstrumentDetectionDlg3::InstrumentDetectionDlg3(CWnd* pParent /*=NULL*/)
	: CDialogEx(InstrumentDetectionDlg3::IDD, pParent)
{

}

InstrumentDetectionDlg3::~InstrumentDetectionDlg3()
{
}

void InstrumentDetectionDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InstrumentDetectionDlg3, CDialogEx)
	ON_BN_CLICKED(IDOK, &InstrumentDetectionDlg3::OnBnClickedOk)
END_MESSAGE_MAP()


// InstrumentDetectionDlg3 消息处理程序


void InstrumentDetectionDlg3::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int index1;
	index1 = ((CComboBox*)GetDlgItem(IDC_COMBO1Picture))->GetCurSel();
	switch (index1)
	{
	case 0:
		MaxRangeValue3 = 0.15;
		break;
	case 1:
		MaxRangeValue3 = 0.30;
		break;
	case 2:
		MaxRangeValue3 = 0.40;
		break;
	case 3:
		MaxRangeValue3 = 0.60;
		break;
	case 4:
		MaxRangeValue3 = 1.00;
		break;
	case 5:
		MaxRangeValue3 = 1.50;
		break;
	case 6:
		MaxRangeValue3 = 1.60;
		break;
	case 7:
		MaxRangeValue3 = 2.50;
		break;
	case 8:
		MaxRangeValue3 = 4.00;
		break;
	case 9:
		MaxRangeValue3 = 6.00;
		break;
	case 10:
		MaxRangeValue3 = 10.0;
		break;
	case 11:
		MaxRangeValue3 = 25.0;
		break;
	case 12:
		MaxRangeValue3 = 60.0;
		break;
	default:
		MaxRangeValue3 = 100;
		break;
	}
	CInstrumentDetectionDlg *pFatherDlg = (CInstrumentDetectionDlg*)GetParent();
	pFatherDlg->MaxRangeValue = MaxRangeValue3;

	CDialogEx::OnOK();
}

BOOL InstrumentDetectionDlg3::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CInstrumentDetectionDlg *pFatherDlg;
	pFatherDlg = (CInstrumentDetectionDlg*)GetParent();

	((CComboBox*)GetDlgItem(IDC_COMBO1Picture))->AddString("0.15");
	((CComboBox*)GetDlgItem(IDC_COMBO1Picture))->AddString("0.30");
	((CComboBox*)GetDlgItem(IDC_COMBO1Picture))->AddString("0.40");
	((CComboBox*)GetDlgItem(IDC_COMBO1Picture))->AddString("0.60");
	((CComboBox*)GetDlgItem(IDC_COMBO1Picture))->AddString("1.00");
	((CComboBox*)GetDlgItem(IDC_COMBO1Picture))->AddString("1.50");
	((CComboBox*)GetDlgItem(IDC_COMBO1Picture))->AddString("1.60");
	((CComboBox*)GetDlgItem(IDC_COMBO1Picture))->AddString("2.50");
	((CComboBox*)GetDlgItem(IDC_COMBO1Picture))->AddString("4.00");
	((CComboBox*)GetDlgItem(IDC_COMBO1Picture))->AddString("6.00");
	((CComboBox*)GetDlgItem(IDC_COMBO1Picture))->AddString("10.0");
	((CComboBox*)GetDlgItem(IDC_COMBO1Picture))->AddString("25.0");
	((CComboBox*)GetDlgItem(IDC_COMBO1Picture))->AddString("60.0");
	((CComboBox*)GetDlgItem(IDC_COMBO1Picture))->AddString("100");
	((CComboBox*)GetDlgItem(IDC_COMBO1Picture))->SetCurSel(3);


	return TRUE;
}

