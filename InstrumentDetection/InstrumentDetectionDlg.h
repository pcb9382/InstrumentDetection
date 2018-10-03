
// InstrumentDetectionDlg.h : ͷ�ļ�
//

#pragma once
#include "stdafx.h"
#include <opencv2\opencv.hpp>  
#include <math.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "CvvImage.h"
#include "resource.h"
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>
#include "CvvImage.h"
#include "InstrumentDetectionDlg1.h"
#include "InstrumentDetectionDlg2.h"
#include "InstrumentDetectionDlg3.h"
#include "afxwin.h"



using namespace std;
using namespace cv;
// CInstrumentDetectionDlg �Ի���
class CInstrumentDetectionDlg : public CDialogEx
{
// ����
public:
	CInstrumentDetectionDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_INSTRUMENTDETECTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
//  ���ﶨ��һЩ���õĲ���
public:
	vector<double> PressureValue1;                                          //�洢ÿһ֡��ѹ��ֵ
	double FinalPressureValue1;                                             //���յõ���ѹ��ƽ��ֵ
	double PressureValueSum;                                                //����֡����ѹ��ֵ֮��
	double MaxPressureValue;                                                //����֡����ѹ��ֵ���ֵ�����ڴӴ�Сȡ������ѹ��ֵ���Ƚ�����õ���
	double MinPressureValue;                                                //����֡����ѹ��ֵ��Сֵ�����ڴ�С����ȡ������ѹ��ֵ

	double CentralPoint_x ;                                                 //�ҵ�Բ�ĵ�λ�õ�x����
	double CentralPoint_y ;                                                 //�ҵ�Բ�ĵ�λ�õ�y����
	double radius ;                                                         //�����Բ�İ뾶

	
	vector<Point>Coordinate;                                                //����Բ���ϵ��vector
    int angle ;                                                             //����С�Ҷ�ֵ������ĽǶ�
	Mat imageGray;                                                          //��ÿһ֡ͼ��ת��Ϊ�Ҷ�ֵ
	Mat frame;                                                              //����һ��Mat���������ڴ洢ÿһ֡��ͼ��
	vector<Vec3f>circles;                                                   //��⵽��Բȫ���洢��circles��
	CTime TheTime;                                                         //��ȡϵͳʱ��
	
  //�洢ͼƬʱ��Ҫ�б��ⷽ��
	int CallCamera;                                                         //�����ж��Ƿ���������
	int VideoDetection;                                                     //�����ж��Ƿ�����Ƶ���
	int PictureDetection;                                                   //�����ж��Ƿ���ͼ����
  //�����
	CString strCallCamera = "��������_";                                   
	CString strVideoDetection = "��Ƶ���_";
	CString strPictureDetection = "ͼ����_";
  //������Ƶʱ��������Ҫ�ı���
public:
	CString Ciecles, Radius;                                                //�洢Բ������Ͱ뾶CString
	CString strFilePath1;                                                   //���ڼ�����Ƶʱ�洢��Ƶ�ĵ�ַ
	String  strFilePath;                                                     //����Ƶ��ַ��CStringת����String
	CString Text1 = "Բ��:", Text2 = "�뾶:", Text3 = ",", Text4 = "  ";
	CString Digit1, Digit2, Digit3;

  //����ͼ��ʱ��������Ҫ�ı���
public:
	CString strFilePathPicture1;                                             //���ڼ���ͼ��ĵ�ַ
	String  strFilePathPicture;                                               //��ͼ���ַ��CStringת����String

public:
	CListBox m_List1;
	CString m_RangeValue;                                                    //���ڴ���б���ѡ��
	double  MaxRangeValue ;                                                  //���ڴ��ѡ����������
	double  MaxRangeValue2;                                                  //���ڴ��ѡ����������
public: 
    int HoughCirclesDetection(Mat image);                                    //����Բ��⺯��
	int FindPointerPosition(double  *Gray_Sum);                              //Ѱ��Բ�ܵ�ĺ�����������270���е�����С�Ҷ�ֵ
	int SearchingMinimumGrayValueIndex(double  *Gray_Sum);                   //Ѱ����С�Ҷ�ֵ��Ӧ�ĽǶ�����
	double AngleToPressureValue(int angle);                                  //���ýǶ��������趨�����̼����ѹ��ֵ
public:
	afx_msg void OnClickedButtoncallcamera();                                //�����������⺯�� 
    afx_msg void OnClickedButtoncallvideo();                                 //��Ƶ��⺯��
	afx_msg void OnClickedButtoncallpicture();                               //ͼ���⺯��
	afx_msg void OnClickedButtonExit();                                      //�˳�����                       
                              
	afx_msg void OnClickedButtonconfirmandpreservation();                    //����ȷ��֮���ͼ�񱣴�����־��д��
	int HoughCirclesVideoDetection(Mat image);                               //�����Ƶʱ��ר�û���Բ��⣬�������õĲ�����һ��
	int TerminationFilterJudgment();                                         //����ж���ֹ��������������ͼ��任��ΧС��ĳһ����ֵ��
	int HoughCirclesPictureDetection(Mat image);                             //����ͼ��Ļ���Բ���
	int Initialization();                                                    //��ʼ������
	void ShowImage(Mat img, UINT ID);                                        //ͼ����ͼ��ؼ�����ʾ����                            

	               
	afx_msg void OnClickedButtonInstall();
	int m_DetectionType;
	afx_msg void OnClickedButtonDetection();
//	afx_msg void OnBnClickedRadio1();
	CStatic m_static;
	CFont cfont;
};
