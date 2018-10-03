
// InstrumentDetectionDlg.h : 头文件
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
// CInstrumentDetectionDlg 对话框
class CInstrumentDetectionDlg : public CDialogEx
{
// 构造
public:
	CInstrumentDetectionDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_INSTRUMENTDETECTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
//  这里定义一些公用的参数
public:
	vector<double> PressureValue1;                                          //存储每一帧的压力值
	double FinalPressureValue1;                                             //最终得到的压力平均值
	double PressureValueSum;                                                //处理帧数的压力值之和
	double MaxPressureValue;                                                //处理帧数的压力值最大值，后期从大到小取第三个压力值（比较排序得到）
	double MinPressureValue;                                                //处理帧数的压力值最小值，后期从小到大取第三个压力值

	double CentralPoint_x ;                                                 //找到圆心的位置的x坐标
	double CentralPoint_y ;                                                 //找到圆心的位置的y坐标
	double radius ;                                                         //计算出圆的半径

	
	vector<Point>Coordinate;                                                //所有圆周上点的vector
    int angle ;                                                             //由最小灰度值计算出的角度
	Mat imageGray;                                                          //由每一帧图像转换为灰度值
	Mat frame;                                                              //定义一个Mat变量，用于存储每一帧的图像
	vector<Vec3f>circles;                                                   //检测到的圆全部存储在circles中
	CTime TheTime;                                                         //获取系统时间
	
  //存储图片时需要判别检测方法
	int CallCamera;                                                         //用于判断是否是相机检测
	int VideoDetection;                                                     //用于判断是否是视频检测
	int PictureDetection;                                                   //用于判断是否是图像检测
  //摄像机
	CString strCallCamera = "摄像机检测_";                                   
	CString strVideoDetection = "视频检测_";
	CString strPictureDetection = "图像检测_";
  //调用视频时处理所需要的变量
public:
	CString Ciecles, Radius;                                                //存储圆心坐标和半径CString
	CString strFilePath1;                                                   //用于加载视频时存储视频的地址
	String  strFilePath;                                                     //把视频地址由CString转换成String
	CString Text1 = "圆心:", Text2 = "半径:", Text3 = ",", Text4 = "  ";
	CString Digit1, Digit2, Digit3;

  //调用图像时处理所需要的变量
public:
	CString strFilePathPicture1;                                             //用于加载图像的地址
	String  strFilePathPicture;                                               //把图像地址由CString转换成String

public:
	CListBox m_List1;
	CString m_RangeValue;                                                    //用于存放列表框的选择
	double  MaxRangeValue ;                                                  //用于存放选择的最大量程
	double  MaxRangeValue2;                                                  //用于存放选择的最大量程
public: 
    int HoughCirclesDetection(Mat image);                                    //霍夫圆检测函数
	int FindPointerPosition(double  *Gray_Sum);                              //寻找圆周点的函数，并计算270度中的其最小灰度值
	int SearchingMinimumGrayValueIndex(double  *Gray_Sum);                   //寻找最小灰度值对应的角度索引
	double AngleToPressureValue(int angle);                                  //利用角度索引和设定的量程计算出压力值
public:
	afx_msg void OnClickedButtoncallcamera();                                //调用摄像机检测函数 
    afx_msg void OnClickedButtoncallvideo();                                 //视频检测函数
	afx_msg void OnClickedButtoncallpicture();                               //图像检测函数
	afx_msg void OnClickedButtonExit();                                      //退出函数                       
                              
	afx_msg void OnClickedButtonconfirmandpreservation();                    //用于确认之后的图像保存与日志的写入
	int HoughCirclesVideoDetection(Mat image);                               //检测视频时的专用霍夫圆检测，里面设置的参数不一样
	int TerminationFilterJudgment();                                         //检测判断终止函数（连续五张图像变换范围小于某一个阈值）
	int HoughCirclesPictureDetection(Mat image);                             //用于图像的霍夫圆检测
	int Initialization();                                                    //初始化函数
	void ShowImage(Mat img, UINT ID);                                        //图像在图像控件中显示函数                            

	               
	afx_msg void OnClickedButtonInstall();
	int m_DetectionType;
	afx_msg void OnClickedButtonDetection();
//	afx_msg void OnBnClickedRadio1();
	CStatic m_static;
	CFont cfont;
};
