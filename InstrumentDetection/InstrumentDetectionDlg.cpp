
// InstrumentDetectionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "InstrumentDetection.h"
#include "InstrumentDetectionDlg.h"
#include "resource.h"
#include <vector>
#include "resource.h"
#include "CvvImage.h"
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "InstrumentDetectionDlg1.h"
#include "InstrumentDetectionDlg2.h"
#include "InstrumentDetectionDlg3.h"


#define PI  3.1415926
#define CameraWidth 640
#define CameraHeight 480
double  Angle = 270;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace cv;
using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:

};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CInstrumentDetectionDlg 对话框



CInstrumentDetectionDlg::CInstrumentDetectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInstrumentDetectionDlg::IDD, pParent)
	, m_DetectionType(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInstrumentDetectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_RADIO1, m_DetectionType);
	DDX_Control(pDX, IDC_STATIC1, m_static);
}

BEGIN_MESSAGE_MAP(CInstrumentDetectionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONExit, &CInstrumentDetectionDlg::OnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTONConfirmAndPreservation, &CInstrumentDetectionDlg::OnClickedButtonconfirmandpreservation)
	ON_BN_CLICKED(IDC_BUTTONInstall, &CInstrumentDetectionDlg::OnClickedButtonInstall)
	ON_BN_CLICKED(IDC_BUTTONDetection, &CInstrumentDetectionDlg::OnClickedButtonDetection)
	
//	ON_BN_CLICKED(IDC_RADIO1, &CInstrumentDetectionDlg::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CInstrumentDetectionDlg 消息处理程序

BOOL CInstrumentDetectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	

	CString InitResetZzeo = "0.00";
	
	GetDlgItem(IDC_EDIT3)->SetWindowText(InitResetZzeo+"MPa");

	//设置最大量程的初始值，用于判断是否选择量程
	MaxRangeValue = -1;  
	cfont.CreatePointFont(150, _T("隶书"), NULL);
	GetDlgItem(IDC_STATIC1)->SetFont(&cfont);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CInstrumentDetectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CInstrumentDetectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CInstrumentDetectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



/**********************************************************************************************************
*此函数的功能为寻找图像或者摄像机目标图像帧中的圆
*输入为摄像机抓捕的图像，输出为灰度化之后的图像，圆的中心点的坐标以及圆的半径
**********************************************************************************************************
*/
int CInstrumentDetectionDlg::HoughCirclesDetection(Mat image)
{    


	cvtColor(image, imageGray, CV_RGB2GRAY);                                //由RGB图像转换为灰度图像
	GaussianBlur(imageGray, imageGray, Size(3, 3), 1, 2);                   //高斯滤波     Size(3, 3)为滤波器模板大小           
	//imshow("Gaussian Image", imageGray);
	//imwrite("imageGray.jpg", imageGray);
	                                                                        //存储霍夫圆检测算法检测到的所有圆的圆心以及半径

	//霍夫圆变换中的350（经过实验测得350为最佳参数）是指检测阶段圆心的累加器阈值，越小则表示可以检测出更多本不存在的圆，越大，能通过检测的圆就更加接近完美的圆形

	HoughCircles(imageGray, circles, CV_HOUGH_GRADIENT, 1, 5, 200,230, 0);//输入8位单通道灰度图像，circles由圆心和半径组成

	//由于判断是否检测到圆或者这一帧中没有圆
	if (circles.size() == 0)
	{
		
		return 0;
	}

	//对所有找到的圆心和半径进行取平均值
	for (int i = 0; i < circles.size(); i++)
	{
		CentralPoint_x += circles[i][0];
		CentralPoint_y += circles[i][1];
		radius += circles[i][2];
	}
	CentralPoint_x = CentralPoint_x / circles.size();                       //得到最终的圆心坐标和半径
	CentralPoint_y = CentralPoint_y / circles.size();
	radius = radius / circles.size();
   



	if ((CameraWidth / 2 - CentralPoint_x) >= 8 | (CameraHeight / 2 - CentralPoint_y) >= 8)
	{
		
		return 0;

	}

	Point circleCenter(CentralPoint_x, CentralPoint_y);                     //以图像像素坐标系左上角为原点坐标
	circle(image, circleCenter, radius, Scalar(0, 0, 255), 3);              //在灰度图像上画出（蓝色）
	circle(image, circleCenter, 3, Scalar(255, 0, 0), 3);                   //在灰度图像上画出圆心（红色） 



	//***********************下面实现一些显示功能******************************************************

	/**************************************************************************************************
	*         是否画出并显示霍夫圆变化所找到的圆
	***************************************************************************************************
	*/
	//imshow("Circle Image", image);
	//imwrite("Circle_Image.bmp", image);                                   //保存带有画出的圆的图像

	

	return 1;
}


/**********************************************************************************************************
*此函数的功能为寻找视频目标图像帧中的圆
*输入为摄像机抓捕的图像，输出为灰度化之后的图像，圆的中心点的坐标以及圆的半径
**********************************************************************************************************
*/
//为视频准备检测圆准备的霍夫圆检测函数
int CInstrumentDetectionDlg::HoughCirclesVideoDetection(Mat image)
{
	cvtColor(image, imageGray, CV_RGB2GRAY);                                //由RGB图像转换为灰度图像
	GaussianBlur(imageGray, imageGray, Size(3, 3), 1, 2);                   //高斯滤波     Size(3, 3)为滤波器模板大小           
	//imshow("Gaussian Image", imageGray);
	//imwrite("imageGray.jpg", imageGray);
	//存储霍夫圆检测算法检测到的所有圆的圆心以及半径

	//霍夫圆变换中的350（经过实验测得350为最佳参数）是指检测阶段圆心的累加器阈值，越小则表示可以检测出更多本不存在的圆，越大，能通过检测的圆就更加接近完美的圆形

	HoughCircles(imageGray, circles, CV_HOUGH_GRADIENT, 1, 5, 200, 300, 0);//输入8位单通道灰度图像，circles由圆心和半径组成

	//由于判断是否检测到圆或者这一帧中没有圆
	if (circles.size() == 0)
	{
		//cout << "没有检测到圆，请调整参数！" << endl;
		return 0;
	}

	//对所有找到的圆心和半径进行取平均值
	for (int i = 0; i < circles.size(); i++)
	{
		CentralPoint_x += circles[i][0];
		CentralPoint_y += circles[i][1];
		radius += circles[i][2];
	}
	CentralPoint_x = CentralPoint_x / circles.size();                       //得到最终的圆心坐标和半径
	CentralPoint_y = CentralPoint_y / circles.size();
	radius = radius / circles.size();




	if ((CameraWidth / 2 - CentralPoint_x) >= 10 | (CameraHeight / 2 - CentralPoint_y) >= 10)
	{
		cout << "请把表盘的中心和图像的中心对准" << endl;
		return 0;

	}

	Point circleCenter(CentralPoint_x, CentralPoint_y);                     //以图像像素坐标系左上角为原点坐标
	circle(image, circleCenter, radius, Scalar(0, 0, 255), 3);              //在灰度图像上画出（蓝色）
	circle(image, circleCenter, 3, Scalar(255, 0, 0), 3);                   //在灰度图像上画出圆心（红色） 



	//***********************下面实现一些显示功能******************************************************

	/**************************************************************************************************
	*         是否画出并显示霍夫圆变化所找到的圆
	***************************************************************************************************
	*/
	//imshow("Circle Image", image);
	//imwrite("Circle_Image.bmp", image);                                   //保存带有画出的圆的图像



	return 1;
}

/**********************************************************************************************************
*此函数的功能为寻找图像目标图像帧中的圆
*输入为摄像机抓捕的图像，输出为灰度化之后的图像，圆的中心点的坐标以及圆的半径
**********************************************************************************************************
*/
//为图像准备检测圆准备的霍夫圆检测函数
int CInstrumentDetectionDlg::HoughCirclesPictureDetection(Mat image)
{
	cvtColor(image, imageGray, CV_RGB2GRAY);                                //由RGB图像转换为灰度图像
	GaussianBlur(imageGray, imageGray, Size(3, 3), 1, 2);                   //高斯滤波     Size(3, 3)为滤波器模板大小           
	//imshow("Gaussian Image", imageGray);
	//imwrite("imageGray.jpg", imageGray);
	//存储霍夫圆检测算法检测到的所有圆的圆心以及半径

	//霍夫圆变换中的350（经过实验测得350为最佳参数）是指检测阶段圆心的累加器阈值，越小则表示可以检测出更多本不存在的圆，越大，能通过检测的圆就更加接近完美的圆形

	HoughCircles(imageGray, circles, CV_HOUGH_GRADIENT, 1, 5, 200, 160, 0);//输入8位单通道灰度图像，circles由圆心和半径组成

	//由于判断是否检测到圆或者这一帧中没有圆
	if (circles.size() == 0)
	{
		//cout << "没有检测到圆，请调整参数！" << endl;
		return 0;
	}

	//对所有找到的圆心和半径进行取平均值
	for (int i = 0; i < circles.size(); i++)
	{
		CentralPoint_x += circles[i][0];
		CentralPoint_y += circles[i][1];
		radius += circles[i][2];
	}
	CentralPoint_x = CentralPoint_x / circles.size();                       //得到最终的圆心坐标和半径
	CentralPoint_y = CentralPoint_y / circles.size();
	radius = radius / circles.size();




	if ((CameraWidth / 2 - CentralPoint_x) >= 10 | (CameraHeight / 2 - CentralPoint_y) >= 10)
	{
		cout << "请把表盘的中心和图像的中心对准" << endl;
		return 0;

	}

	Point circleCenter(CentralPoint_x, CentralPoint_y);                     //以图像像素坐标系左上角为原点坐标
	circle(image, circleCenter, radius, Scalar(0, 0, 255), 3);              //在灰度图像上画出（蓝色）
	circle(image, circleCenter, 3, Scalar(255, 0, 0), 3);                   //在灰度图像上画出圆心（红色） 



	//***********************下面实现一些显示功能******************************************************

	/**************************************************************************************************
	*         是否画出并显示霍夫圆变化所找到的圆
	***************************************************************************************************
	*/
	//imshow("Circle Image", image);
	//imwrite("Circle_Image.bmp", image);                                   //保存带有画出的圆的图像



	return 1;
}


/**********************************************************************************************************
*此函数的功能为寻找指针的位置
*输入为摄像机抓捕的图像的灰度化图像，输出为每度的灰度值之和
**********************************************************************************************************
*/
int CInstrumentDetectionDlg::FindPointerPosition(double  *Gray_Sum)
{   

	//Gray_Sum[271] = { 0 };
	IplImage* src = &IplImage(imageGray);                                //把Mat格式的灰度图像转换为IplImage图像指针                
	int width = src->width;                                              //获取灰度图像的宽度                          
	int height = src->height;                                            //获取灰度图像的高度
	double  coordinate_x;                                                //圆周上的x坐标
	double  coordinate_y;                                                //圆周上的y坐标
	double  k = 0;                                                       //直线的斜率                                             //每条直线的灰度值之和
	int t = 0;
	for (int j = 0; j < 270; j = j + 1)

	{

		int coordinate_x = radius*cos(j*PI / 180 -PI / 4) + CentralPoint_x;     //循环计算圆周上的(x,y)坐标
		int coordinate_y = -radius*sin(j*PI / 180 - PI / 4) + CentralPoint_y;    //y行
		Point coordinate(coordinate_x, coordinate_y);
		Coordinate.push_back(coordinate);                               //把作坐标存入到Coordinate中


		/**************************************************************************************************
		*         是否画出图像中0-270度寻找的线
		*************************************************************************************************
		*/
		//Point circleCenter(CentralPoint_x, CentralPoint_y);
		//line(image, circleCenter, coordinate, Scalar(255, 255, 255), 1, 8);
		//imwrite("Image.jpg", image);



		if (coordinate_x >= CentralPoint_x && coordinate_y <= CentralPoint_y&&coordinate_y>0) //第一象限
		{

			for (double p = CentralPoint_x; p < coordinate_x; p = p + (coordinate_x - CentralPoint_x) / radius)
			{
				k = (CentralPoint_y - (double)coordinate_y) / ((double)coordinate_x - CentralPoint_x);
				int cols = p;
				//确定哪一个像素的灰度值
				int row = -k*(p - CentralPoint_x) + CentralPoint_y;
				uchar* ptr = (uchar*)src->imageData + row*src->width;        //确定像素行数
				int intensity = ptr[cols];                                   //行数确定后确定列数，并提取该像素的灰度值
				Gray_Sum[t] = Gray_Sum[t] + intensity;                       //对像素值进行累加
			}

		}
		if (coordinate_x > CentralPoint_x && coordinate_y > CentralPoint_y&&coordinate_y>0)                         //第四象限
		{

			for (double p = CentralPoint_x; p < coordinate_x; p = p + (coordinate_x - CentralPoint_x) / radius)
			{
				k = (CentralPoint_y - (double)coordinate_y) / ((double)coordinate_x - CentralPoint_x);
				int cols = p;
				int row = -k*(p - CentralPoint_x) + CentralPoint_y;
				uchar* ptr = (uchar*)src->imageData + row*src->width;
				int intensity = ptr[cols];
				Gray_Sum[t] = Gray_Sum[t] + intensity;
			}

		}
		if (coordinate_x < CentralPoint_x && coordinate_y >CentralPoint_y&&coordinate_y>0)                         //第三象限
		{

			for (double p = CentralPoint_x; p > coordinate_x; p = p - (-coordinate_x + CentralPoint_x) / radius)
			{
				k = (CentralPoint_y - (double)coordinate_y) / ((double)coordinate_x - CentralPoint_x);
				int cols = p;
				int row = -k*(p - CentralPoint_x) + CentralPoint_y;
				uchar* ptr = (uchar*)src->imageData + row*src->width;
				int intensity = ptr[cols];
				Gray_Sum[t] = Gray_Sum[t] + intensity;
			}

		}
		if (coordinate_x < CentralPoint_x && coordinate_y <CentralPoint_y&&coordinate_y>0)                         //第二象限
		{

			for (double p = CentralPoint_x; p > coordinate_x; p = p - (-coordinate_x + CentralPoint_x) / radius)
			{
				k = (CentralPoint_y - (double)coordinate_y) / ((double)coordinate_x - CentralPoint_x);
				int cols = p;
				int row = -k*(p - CentralPoint_x) + CentralPoint_y;
				uchar* ptr = (uchar*)src->imageData + row*src->width;
				int intensity = ptr[cols];
				Gray_Sum[t] = Gray_Sum[t] + intensity;
			}
		}
		t++;
	}

	return 1;
	
}

/**********************************************************************************************************
*此函数的功能为寻找灰度值最小的索引，则表示指针指示的度数
*输入为灰度值组数，输出为最小灰度值的索引
**********************************************************************************************************
*/

int CInstrumentDetectionDlg::SearchingMinimumGrayValueIndex(double  *Gray_Sum)
{

	int index = 0;
	int i = 0;
	double m = Gray_Sum[0];
	for (i = 1; i<270; i++)
	{
		if (m > Gray_Sum[i] && Gray_Sum[i] != 0)
		{
			m = Gray_Sum[i];
			index = i;
		}
		
	}

	/**************************************************************************************************
	*        这里决定是否要画出寻找到的指针的那条线
	*************************************************************************************************
	*/
	Point circleCenter(CentralPoint_x, CentralPoint_y);
	line(frame, Point(CentralPoint_x, CentralPoint_y), Coordinate[index], Scalar(255, 255, 255), 5, 8);
	ShowImage(frame, IDC_STATIC_PIC1);
	
	//waitKey(1000);
	int angle = index;
	return angle;

}

/**********************************************************************************************************
*此函数的功能是由计算出的角度值换成成对应的压力值
*输入角度，输出为换算的压力值
**********************************************************************************************************
*/

double CInstrumentDetectionDlg::AngleToPressureValue(int angle)

{
	double PressureValue = 0;
	double angle_MPa = MaxRangeValue / Angle;
	if (angle >= 0 && angle <= 270)
	{
		PressureValue = MaxRangeValue - angle*angle_MPa;
		//cout << "压力值是：" << PressureValue << endl;
	}

	return PressureValue;
	
}

//用于在PictureBox框中显示图片
void CInstrumentDetectionDlg::ShowImage(Mat Img, UINT ID)
{
	//把Mat转换成IplImage*的形式用于在控件中显示
	IplImage* pBinary = &IplImage(Img);                                                          //浅拷贝
	IplImage *img = cvCloneImage(pBinary);                                                       //由浅拷贝转换为深拷贝

	CDC* pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	SetRect(rect, rect.left, rect.top, rect.right, rect.bottom);
	CvvImage cimg;
	cimg.CopyOf(img);
	cimg.DrawToHDC(hDC, &rect);
	ReleaseDC(pDC);

}




//调用摄像机检测
void CInstrumentDetectionDlg::OnClickedButtoncallcamera()
{
	// TODO:  在此添加控件通知处理程序代码
	Initialization();                                                          //调用初始化函数，使得之前检测的vector中的数值清零
	CallCamera = 1;                                                            //确定检测的方式，此处表示摄像头检测

	//启动摄像机
	if (MaxRangeValue == -1)
	{
		MaxRangeValue=0.6;
		//return;

	}
	VideoCapture capture(0);

	//摄像头打开失败
	if (!capture.isOpened())                          
	{
		MessageBox("打开摄像头失败，退出");
		exit(-1);
	}
	//设置相机窗口的大小
    capture.set(CV_CAP_PROP_FRAME_WIDTH, CameraWidth);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, CameraHeight);

	//在摄像机窗口中确定十字光标的位置并且画出对准中心
	Point circleCenter(CameraWidth / 2, CameraHeight / 2);

	//左下角圆周上的点（表上零点的位置）
	Point ZeroPoint(CameraWidth / 2 - CameraHeight / 2 * sin(PI / 4), CameraHeight / 2 + CameraHeight / 2 * sin(PI / 4));
	//右下角圆周上上的点（表示终点的位置）
	Point FinalPoint(CameraWidth / 2 + CameraHeight / 2 * sin(PI / 4), CameraHeight / 2 + CameraHeight / 2 * sin(PI / 4));
	//相机标志圆界面宽上下的中心点
	Point WidthCenterPoint1(CameraWidth / 2, (CameraHeight / 2) - 20);
	Point WidthCenterPoint2(CameraWidth / 2, (CameraHeight / 2) + 20);
	//相机标志圆界面高的左右中心点
	Point HeightCenterPoint1(CameraWidth / 2 - 20, CameraHeight / 2);
	Point HeightCenterPoint2(CameraWidth / 2 + 20, CameraHeight / 2);

	int i = 0;
	while (1)
	{
	
		capture >> frame;  //读取当前帧

		//读入图像为空
		if (frame.empty())
		{
			break;

		}

        circle(frame, circleCenter, CameraHeight / 2, Scalar(0, 0, 255), 3);                      //在灰度图像上画出（蓝色）
		circle(frame, circleCenter, 3, Scalar(255, 0, 0), 3);                                     //在灰度图像上画出圆心（红色） 

	    line(frame, WidthCenterPoint1, WidthCenterPoint2, Scalar(0, 0, 255), 2, 8);               //从画的圆心到零点的直线作为标志线
		line(frame, HeightCenterPoint1, HeightCenterPoint2, Scalar(0, 0, 255), 2, 8);             //从画的圆心到零点的直线作为标志线
		//line(frame, circleCenter, ZeroPoint, Scalar(255, 255, 255), 1, 8);
		//line(frame, circleCenter, FinalPoint, Scalar(255, 255, 255), 1, 8);
		ShowImage(frame, IDC_STATIC_PIC1);                                                        //在Picture控件中显示当前采集的图像
		waitKey(30);                                                                              //延时30ms 

		
		//********************************************************************************
		//         下面程序是对图像进行处理（寻找圆并得到其直径）
		//********************************************************************************
		CentralPoint_x = 0;
		CentralPoint_y = 0;
		radius = 0;
		int CheckCircle = HoughCirclesDetection(frame);
		//判断是否检测到圆，如果没有检测到，说明是参数有问题或者是图像中没有圆(也就是没有表，此时跳过此帧，进行下一帧)
		
		if (CheckCircle == 0)
		{
			frame = 0;
			circles.clear();
			continue;
		}

		/**************************************************************************************************
		*        把圆心以及半径信息显示到列表框中
		***************************************************************************************************
		*/
		/*
		CString Text1 = "圆心:", Text2 = "半径:", Text3 = ",", Text4 = "  ", Digit1, Digit2, Digit3;
		Digit1.Format(_T("%lf"), CentralPoint_x);                               //得到
		Digit2.Format(_T("%lf"), CentralPoint_y);
		Digit3.Format(_T("%lf"), radius);
		
		*/

		//********************************************************************************
		//         下面程序是寻找指针
		//********************************************************************************
		double  Gray_Sum[271] = { 0 };
		int CheckPointer = FindPointerPosition(Gray_Sum);

		//********************************************************************************
		// 下面程序是对灰度值数组进行排序，找到最小的那个数组所代表的索引就是指针旋转的度数
		//********************************************************************************
		int angle = 0;                                                                   //指针的旋转角度
		angle = SearchingMinimumGrayValueIndex(Gray_Sum);


		//********************************************************************************
		// 根据计算的指针的角度值，换算出压力值并输出
		//********************************************************************************
		double PressureValue = AngleToPressureValue(angle);
		//CString FinalStr;
		//CString Title = "压力值为：";
		//CString ShowPressureValue ;
		//ShowPressureValue.Format(_T("%lf"), PressureValue);
		//FinalStr = Title + ShowPressureValue;
		//ShowMessage(FinalStr);
		PressureValue1.push_back(PressureValue);                                           //存储所有检测到的压力值
		
		int check1 = 0;
		if ((check1 = TerminationFilterJudgment()) == 1)
		{
			break;
		}


     	circle(frame, circleCenter, 3, Scalar(255, 0, 0), 3);                              //在灰度图像上画出圆心（红色）
		//imshow("读取视频", frame);  //显示当前帧
		//waitKey(30);  //延时30ms 

		

		
	}
	int n = PressureValue1.size();
	PressureValueSum = 0;                                                                 //把所有的帧处理的压力加起来，取平均值        
	MaxPressureValue = PressureValue1[n - 1];                                              //先把第一帧的值赋给MaxPressureValue对帧数进行排序，取最大值
	MinPressureValue = PressureValue1[n - 1];                                              //先把第一帧的值赋给MinPressureValue对帧数进行排序，取最小值
	int  MinIndex = n;                                                                   //最小值索引
	int  MaxIndex = n;                                                                   //最大值索引
	for (int j = PressureValue1.size() - 1; j >PressureValue1.size() - 5; j--)
	{
		PressureValueSum += PressureValue1[j];                                           //求和
		if (MinPressureValue > PressureValue1[j] && PressureValue1[j] != 0)              //求最小值
		{
			MinPressureValue = PressureValue1[j];
			MinIndex = j + 1;
		}
		if (MaxPressureValue < PressureValue1[j] && PressureValue1[j] != 0)              //求最大值
		{
			MaxPressureValue = PressureValue1[j];
			MaxIndex = j + 1;

		}

	}

	FinalPressureValue1 = PressureValueSum / 4;                      //得到压力值的平均值

	//把数字转换成字符串用于显示在ListBox控件中
	CString TextcCamera1 = "平均压力值", TextcCamera2 = "第", TextcCamera3 = "帧压力值最大为:",
		TextcCamera4 = "帧压力值最小为：";                                                       //需要输出的文本
	CString AverageinalDigitCamera, MaxDigitCamera, MinDigitCamera;                              //平均值以及最大最小值   
	CString MinIndexCamera, MaxIndexCamera;                                                      //最大帧以及最小帧索引
	AverageinalDigitCamera.Format(_T("%.3f"), FinalPressureValue1); 
	//MaxDigitCamera.Format(_T("%lf"), MaxPressureValue);
	//MinDigitCamera.Format(_T("%lf"), MinPressureValue);
	//MinIndexCamera.Format(_T("%d"), MinIndex);
	//MaxIndexCamera.Format(_T("%d"), MaxIndex);
	//GetDlgItem(IDC_EDIT1)->SetWindowText(MaxDigitCamera);
	//GetDlgItem(IDC_EDIT2)->SetWindowText(MinDigitCamera);
	GetDlgItem(IDC_EDIT3)->SetWindowText(AverageinalDigitCamera+"MPa");


	//ShowMessage(TextcCamera2 + MaxIndexCamera + TextcCamera3 + MaxDigitCamera);
	//ShowMessage(TextcCamera2 + MinIndexCamera + TextcCamera4 + MinDigitCamera);
	//ShowMessage(TextcCamera2 + TextcCamera1 + AverageinalDigitCamera);
	
	MaxRangeValue = -1;                                                             //把量程参数重新设置为-1，使得每次进入检测时重新选择量程
	return;
}


//调用视频检测
void CInstrumentDetectionDlg::OnClickedButtoncallvideo()
{
	// TODO:  在此添加控件通知处理程序代码
	Initialization();                                                        //调用初始化函数，使得之前检测的vector中的数值清零
	VideoDetection = 1;                                                      //确定检测的方式，此处表示视频检测
	if (MaxRangeValue == -1)
	{
		MaxRangeValue=0.6;
		//return;

	}
	
	CString st = "------------------------------VideoDetectionBegin------------------------------";
	//ShowMessage(st);


	//加载图片的路径
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "All Files|*.*|txt|*.txt||");
	INT_PTR nRet = dlg.DoModal();
	if (nRet != IDOK)
	{
		return;
	}

	strFilePath1 = dlg.GetPathName();
	//ShowMessage("视频地址" + strFilePath1);

	if (!PathFileExists(strFilePath1))
	{
		//ShowMessage("文件 [%s] 不存在!\n");
		return;
	}
	strFilePath = strFilePath1.GetBuffer(0);


	//启动摄像机
	VideoCapture capture(strFilePath);
	double rate = capture.get(CV_CAP_PROP_FPS);                                                  // 获取帧率 
	long nFrame = static_cast<long>(capture.get(CV_CAP_PROP_FRAME_COUNT));                       // 获取总帧数

	for (int position = 10; position < nFrame; position = position + 100)
	{

		
		capture >> frame;  //读取当前帧
		
		if (frame.empty())                                                                       //判断是否到视频的结尾
		{
			break;
			cout << "Video loading ending" << endl;
		}


		ShowImage(frame, IDC_STATIC_PIC1);                                                        //在Picture控件中显示当前采集的图像
		waitKey(30);                                                                              //延时30ms 


		//********************************************************************************
		//         下面程序是对图像进行处理（寻找圆并得到其直径）
		//********************************************************************************
		CentralPoint_x = 0;
		CentralPoint_y = 0;
		radius = 0;
		int CheckCircle = HoughCirclesVideoDetection(frame);
		//判断是否检测到圆，如果没有检测到，说明是参数有问题或者是图像中没有圆(也就是没有表，此时跳过此帧，进行下一帧)

		if (CheckCircle == 0)
		{
			//cout << "未检测到圆，进行下一帧的处理！" << endl;
			continue;
		}

		/**************************************************************************************************
		*        把圆心以及半径信息显示到列表框中
		***************************************************************************************************
		*/
		
		Digit1.Format(_T("%lf"), CentralPoint_x);                               //得到
		Digit2.Format(_T("%lf"), CentralPoint_y);
		Digit3.Format(_T("%lf"), radius);
		//ShowMessage(Text1 + Digit1 + Text3 + Digit2 + Text4 + Text2 + Digit3);


		

		//********************************************************************************
		double  Gray_Sum[271] = { 0 };
		int CheckPointer = FindPointerPosition(Gray_Sum);

		//********************************************************************************
		// 下面程序是对灰度值数组进行排序，找到最小的那个数组所代表的索引就是指针旋转的度数
		//********************************************************************************
		int angle = 0;                                                                   //指针的旋转角度
		angle = SearchingMinimumGrayValueIndex(Gray_Sum);


		//********************************************************************************
		// 根据计算的指针的角度值，换算出压力值并输出
		//********************************************************************************
		double PressureValue = AngleToPressureValue(angle);
		CString FinalStr;
		CString Title = "压力值为：";
		CString ShowPressureValue;
		ShowPressureValue.Format(_T("%lf"), PressureValue);
		FinalStr = Title + ShowPressureValue;
		//ShowMessage(FinalStr);
		PressureValue1.push_back(PressureValue);                                         //存储所有检测到的压力值
		int check;
		if ((check = TerminationFilterJudgment()) == 1)
		{
			break;
		}


	}
	
	int n = PressureValue1.size();
	PressureValueSum =0;                                                                 //把所有的帧处理的压力加起来，取平均值        
	MaxPressureValue = PressureValue1[n-1];                                              //先把第一帧的值赋给MaxPressureValue对帧数进行排序，取最大值
	MinPressureValue = PressureValue1[n-1];                                              //先把第一帧的值赋给MinPressureValue对帧数进行排序，取最小值
	int  MinIndex = n;                                                                   //最小值索引
	int  MaxIndex = n;                                                                   //最大值索引
	for (int j = PressureValue1.size()-1; j >PressureValue1.size()-5; j--)
	{
		PressureValueSum += PressureValue1[j];                                           //求和
		if (MinPressureValue > PressureValue1[j] && PressureValue1[j] != 0)              //求最小值
		{
			MinPressureValue = PressureValue1[j];
			MinIndex = j + 1;
		}
		if (MaxPressureValue < PressureValue1[j] && PressureValue1[j] != 0)              //求最大值
		{
			MaxPressureValue = PressureValue1[j];
			MaxIndex = j + 1;

		}

	}

	FinalPressureValue1 = PressureValueSum / 4;                 //得到压力值的平均值

	//把数字转换成字符串用于显示在ListBox控件中
	CString TextcVideo1 = "平均压力值", TextcVideo2 = "第", TextcVideo3 = "帧压力值最大为:",
		    TextcVideo4 = "帧压力值最小为：";                                           //需要输出的文本
	CString AverageinalDigitVideo, MaxDigitVideo, MinDigitVideo ;                       //平均值以及最大最小值   
	CString MinIndexVideo, MaxIndexVoideo ;                                             //最大帧以及最小帧索引
	AverageinalDigitVideo.Format(_T("%.3f"), FinalPressureValue1);
	//MaxDigitVideo.Format(_T("%lf"), MaxPressureValue);
	//MinDigitVideo.Format(_T("%lf"), MinPressureValue);
	//MinIndexVideo.Format(_T("%d"), MinIndex);
	//MaxIndexVoideo.Format(_T("%d"), MaxIndex);
	//GetDlgItem(IDC_EDIT1)->SetWindowText(MaxDigitVideo);
	//GetDlgItem(IDC_EDIT2)->SetWindowText(MinDigitVideo);
	GetDlgItem(IDC_EDIT3)->SetWindowText(AverageinalDigitVideo+"MPa");


	//ShowMessage(TextcVideo2 + MaxIndexVoideo + TextcVideo3 + MaxDigitVideo);
	//ShowMessage(TextcVideo2 + MinIndexVideo + TextcVideo4 + MinDigitVideo);
	//ShowMessage(TextcVideo2 + TextcVideo1+AverageinalDigitVideo);
    
	MaxRangeValue = -1;                                                             //把量程参数重新设置为-1，使得每次进入检测时重新选择量程
	return;
}


//调用图像检测
void CInstrumentDetectionDlg::OnClickedButtoncallpicture()
{
	// TODO:  在此添加控件通知处理程序代码
	
	     Initialization();                                                          //调用初始化函数，使得之前检测的vector中的数值清零
		 PictureDetection = 1;                                                      //确定检测的方式，此处表示图像检测
	     if (MaxRangeValue == -1)
	      {
			 MaxRangeValue=0.6;
		    //return;

	      }
	     CString st = "------------------------------PictureDetectionBegin------------------------------";
	     //ShowMessage(st);
	
	     //加载图片的路径
	     CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "All Files|*.*|txt|*.txt||");
	     INT_PTR nRet = dlg.DoModal();
	     if (nRet != IDOK)
	      {
              return;
	      }

	     strFilePathPicture1 = dlg.GetPathName();
	     //ShowMessage("视频地址" + strFilePathPicture1);

	     if (!PathFileExists(strFilePathPicture1))
	      {
		   // ShowMessage("文件 [%s] 不存在!\n");
		    return;
	      }
	     strFilePathPicture = strFilePathPicture1.GetBuffer(0);


	    
         frame = imread(strFilePathPicture);  //读取当前帧
		 ShowImage(frame, IDC_STATIC_PIC1);                                                        //在Picture控件中显示当前采集的图像
		 waitKey(30);                                                                              //延时30ms 


		//********************************************************************************
		//         下面程序是对图像进行处理（寻找圆并得到其直径）
		//********************************************************************************
		CentralPoint_x = 0;
		CentralPoint_y = 0;
		radius = 0;
		int CheckCircle = HoughCirclesPictureDetection(frame);
		//判断是否检测到圆，如果没有检测到，说明是参数有问题或者是图像中没有圆(也就是没有表，此时跳过此帧，进行下一帧)

		
		/**************************************************************************************************
		*        把圆心以及半径信息显示到列表框中
		***************************************************************************************************
		*/
		CString TextPicture1 = "圆心:", TextPicture2 = "半径:", TextPicture3 = ",", TextPicture4 = "  ";
		CString DigitPicture1, DigitPicture2, DigitPicture3;
		DigitPicture1.Format(_T("%lf"), CentralPoint_x);                               //得到
		DigitPicture2.Format(_T("%lf"), CentralPoint_y);
		DigitPicture3.Format(_T("%lf"), radius);
		//ShowMessage(TextPicture1 + DigitPicture1 + TextPicture3 + DigitPicture2 + TextPicture4 + TextPicture2 + DigitPicture3);


		//********************************************************************************
		//         下面程序是寻找指针
		//********************************************************************************
		double  Gray_Sum[271] = { 0 };
		int CheckPointer = FindPointerPosition(Gray_Sum);

		//********************************************************************************
		// 下面程序是对灰度值数组进行排序，找到最小的那个数组所代表的索引就是指针旋转的度数
		//********************************************************************************
		int angle = 0;                                                                   //指针的旋转角度
		angle = SearchingMinimumGrayValueIndex(Gray_Sum);


		//********************************************************************************
		// 根据计算的指针的角度值，换算出压力值并输出
		//********************************************************************************
		double PressureValue = AngleToPressureValue(angle);
		CString FinalStr;
		CString Title = "压力值为：";
		CString ShowPressureValue;
		ShowPressureValue.Format(_T("%0.3f"), PressureValue);
		FinalStr = Title + ShowPressureValue;
		//ShowMessage(FinalStr);
		
		//GetDlgItem(IDC_EDIT1)->SetWindowText(ShowPressureValue);
		//GetDlgItem(IDC_EDIT2)->SetWindowText(ShowPressureValue);
		GetDlgItem(IDC_EDIT3)->SetWindowText(ShowPressureValue+"MPa");

		MaxRangeValue = -1;                                                             //把量程参数重新设置为-1，使得每次进入检测时重新选择量程                                                             
		return;
	
}


//退出程序处理
void CInstrumentDetectionDlg::OnClickedButtonExit()
{
	// TODO:  在此添加控件通知处理程序代码
	if (MessageBox("确认退出", "", MB_YESNO | MB_ICONQUESTION) != IDYES)
	{
		
		return;
	}
	CDialog::OnOK();
	AfxGetMainWnd()->PostMessage(WM_CLOSE, 0, 0);

}

//量程确认选择处理


//终止滤波判断程序处理（跳出继续检测，已经得到稳定的压力值）
int CInstrumentDetectionDlg::TerminationFilterJudgment()
{   

	double temp = 0;
	int i = PressureValue1.size()-1;
	if (PressureValue1.size() < 5)
	{
		return 0;
	}
	else 
	{   
		if (abs(PressureValue1[i] - PressureValue1[i - 1]) <= 0.02&&abs(PressureValue1[i] - PressureValue1[i - 2]) <= 0.02&&
			abs(PressureValue1[i] - PressureValue1[i - 3]) <= 0.02&&abs(PressureValue1[i] - PressureValue1[i - 4]) <= 0.02)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
}

//用来初始化下一个检测项目时的初始化
int CInstrumentDetectionDlg::Initialization()
{   
	Coordinate.clear();                                                   //把之前vector中存储的圆周上的点清零
	PressureValue1.clear();                                               //把之前vector中检测的压力值清零

	//清零检测方式的标志位
    CallCamera=0;                                                         //用于判断是否是相机检测
	VideoDetection=0;                                                     //用于判断是否是视频检测
	PictureDetection=0;                                                   //用于判断是否是图像检测


	//需要把编辑框中的数字清零
	CString ResetZzeo = "0.00";
	//GetDlgItem(IDC_EDIT1)->SetWindowText(ResetZzeo);
	//GetDlgItem(IDC_EDIT2)->SetWindowText(ResetZzeo);
	GetDlgItem(IDC_EDIT3)->SetWindowText(ResetZzeo+"MPa");
	return 1;
}

//用于确认之后的图像保存以及日志的写入
void CInstrumentDetectionDlg::OnClickedButtonconfirmandpreservation()
{
	// TODO:  在此添加控件通知处理程序代码

	
	TheTime = CTime::GetCurrentTime();
	CString str3, str4 = ".bmp", str5;
	string str6;
	str3.Format(_T("%04d%02d%02d_%02d%02d%02d"), TheTime.GetYear(), TheTime.GetMonth(), TheTime.GetDay(), TheTime.GetHour(), TheTime.GetMinute(), TheTime.GetSecond());
	

	if (CallCamera == 1)
	{   
		str5 = strCallCamera + str3 + str4;
		str6 = str5.GetBuffer(0);
		imwrite(str6, frame);
	}
    if (VideoDetection == 1)
	{
		str5 = strVideoDetection + str3 + str4;
		str6 = str5.GetBuffer(0);
		imwrite(str6, frame);
	}
	if (PictureDetection == 1)
	{
		str5 = strPictureDetection + str3 + str4;
		str6 = str5.GetBuffer(0);
		imwrite(str6, frame);
	}
	return;

}

//设置按钮调用对应设置的子窗口
void CInstrumentDetectionDlg::OnClickedButtonInstall()
{
	// TODO:  在此添加控件通知处理程序代码
	InstrumentDetectionDlg1 dlg1;
	InstrumentDetectionDlg2 dlg2;
	InstrumentDetectionDlg3 dlg3;
	UpdateData(TRUE);
	switch (m_DetectionType)
	{
	  case 0:
		  dlg1.DoModal();
		  break;
	  case 1:
		  dlg2.DoModal();
		  break;
	  case 2:
		  dlg3.DoModal();
		  break;
	  default:
		  MessageBox("请选择检测方法！");
		  break;
	}
	
	return;
}

//单选按钮选择不同的检测类型
void CInstrumentDetectionDlg::OnClickedButtonDetection()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	switch (m_DetectionType)
	{
	 case 0:
		 OnClickedButtoncallcamera();
	     break;
 /*
	 case 1:
		 OnClickedButtoncallvideo();
		 break;
	 case 2:
		 OnClickedButtoncallpicture();
		 break;
*/
	default:
		MessageBox("现在只可以进行压力检测！");
		break;
	}
	return;
}


