
// InstrumentDetectionDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CInstrumentDetectionDlg �Ի���



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


// CInstrumentDetectionDlg ��Ϣ�������

BOOL CInstrumentDetectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	

	CString InitResetZzeo = "0.00";
	
	GetDlgItem(IDC_EDIT3)->SetWindowText(InitResetZzeo+"MPa");

	//����������̵ĳ�ʼֵ�������ж��Ƿ�ѡ������
	MaxRangeValue = -1;  
	cfont.CreatePointFont(150, _T("����"), NULL);
	GetDlgItem(IDC_STATIC1)->SetFont(&cfont);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CInstrumentDetectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CInstrumentDetectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



/**********************************************************************************************************
*�˺����Ĺ���ΪѰ��ͼ����������Ŀ��ͼ��֡�е�Բ
*����Ϊ�����ץ����ͼ�����Ϊ�ҶȻ�֮���ͼ��Բ�����ĵ�������Լ�Բ�İ뾶
**********************************************************************************************************
*/
int CInstrumentDetectionDlg::HoughCirclesDetection(Mat image)
{    


	cvtColor(image, imageGray, CV_RGB2GRAY);                                //��RGBͼ��ת��Ϊ�Ҷ�ͼ��
	GaussianBlur(imageGray, imageGray, Size(3, 3), 1, 2);                   //��˹�˲�     Size(3, 3)Ϊ�˲���ģ���С           
	//imshow("Gaussian Image", imageGray);
	//imwrite("imageGray.jpg", imageGray);
	                                                                        //�洢����Բ����㷨��⵽������Բ��Բ���Լ��뾶

	//����Բ�任�е�350������ʵ����350Ϊ��Ѳ�������ָ���׶�Բ�ĵ��ۼ�����ֵ��ԽС���ʾ���Լ������౾�����ڵ�Բ��Խ����ͨ������Բ�͸��ӽӽ�������Բ��

	HoughCircles(imageGray, circles, CV_HOUGH_GRADIENT, 1, 5, 200,230, 0);//����8λ��ͨ���Ҷ�ͼ��circles��Բ�ĺͰ뾶���

	//�����ж��Ƿ��⵽Բ������һ֡��û��Բ
	if (circles.size() == 0)
	{
		
		return 0;
	}

	//�������ҵ���Բ�ĺͰ뾶����ȡƽ��ֵ
	for (int i = 0; i < circles.size(); i++)
	{
		CentralPoint_x += circles[i][0];
		CentralPoint_y += circles[i][1];
		radius += circles[i][2];
	}
	CentralPoint_x = CentralPoint_x / circles.size();                       //�õ����յ�Բ������Ͱ뾶
	CentralPoint_y = CentralPoint_y / circles.size();
	radius = radius / circles.size();
   



	if ((CameraWidth / 2 - CentralPoint_x) >= 8 | (CameraHeight / 2 - CentralPoint_y) >= 8)
	{
		
		return 0;

	}

	Point circleCenter(CentralPoint_x, CentralPoint_y);                     //��ͼ����������ϵ���Ͻ�Ϊԭ������
	circle(image, circleCenter, radius, Scalar(0, 0, 255), 3);              //�ڻҶ�ͼ���ϻ�������ɫ��
	circle(image, circleCenter, 3, Scalar(255, 0, 0), 3);                   //�ڻҶ�ͼ���ϻ���Բ�ģ���ɫ�� 



	//***********************����ʵ��һЩ��ʾ����******************************************************

	/**************************************************************************************************
	*         �Ƿ񻭳�����ʾ����Բ�仯���ҵ���Բ
	***************************************************************************************************
	*/
	//imshow("Circle Image", image);
	//imwrite("Circle_Image.bmp", image);                                   //������л�����Բ��ͼ��

	

	return 1;
}


/**********************************************************************************************************
*�˺����Ĺ���ΪѰ����ƵĿ��ͼ��֡�е�Բ
*����Ϊ�����ץ����ͼ�����Ϊ�ҶȻ�֮���ͼ��Բ�����ĵ�������Լ�Բ�İ뾶
**********************************************************************************************************
*/
//Ϊ��Ƶ׼�����Բ׼���Ļ���Բ��⺯��
int CInstrumentDetectionDlg::HoughCirclesVideoDetection(Mat image)
{
	cvtColor(image, imageGray, CV_RGB2GRAY);                                //��RGBͼ��ת��Ϊ�Ҷ�ͼ��
	GaussianBlur(imageGray, imageGray, Size(3, 3), 1, 2);                   //��˹�˲�     Size(3, 3)Ϊ�˲���ģ���С           
	//imshow("Gaussian Image", imageGray);
	//imwrite("imageGray.jpg", imageGray);
	//�洢����Բ����㷨��⵽������Բ��Բ���Լ��뾶

	//����Բ�任�е�350������ʵ����350Ϊ��Ѳ�������ָ���׶�Բ�ĵ��ۼ�����ֵ��ԽС���ʾ���Լ������౾�����ڵ�Բ��Խ����ͨ������Բ�͸��ӽӽ�������Բ��

	HoughCircles(imageGray, circles, CV_HOUGH_GRADIENT, 1, 5, 200, 300, 0);//����8λ��ͨ���Ҷ�ͼ��circles��Բ�ĺͰ뾶���

	//�����ж��Ƿ��⵽Բ������һ֡��û��Բ
	if (circles.size() == 0)
	{
		//cout << "û�м�⵽Բ�������������" << endl;
		return 0;
	}

	//�������ҵ���Բ�ĺͰ뾶����ȡƽ��ֵ
	for (int i = 0; i < circles.size(); i++)
	{
		CentralPoint_x += circles[i][0];
		CentralPoint_y += circles[i][1];
		radius += circles[i][2];
	}
	CentralPoint_x = CentralPoint_x / circles.size();                       //�õ����յ�Բ������Ͱ뾶
	CentralPoint_y = CentralPoint_y / circles.size();
	radius = radius / circles.size();




	if ((CameraWidth / 2 - CentralPoint_x) >= 10 | (CameraHeight / 2 - CentralPoint_y) >= 10)
	{
		cout << "��ѱ��̵����ĺ�ͼ������Ķ�׼" << endl;
		return 0;

	}

	Point circleCenter(CentralPoint_x, CentralPoint_y);                     //��ͼ����������ϵ���Ͻ�Ϊԭ������
	circle(image, circleCenter, radius, Scalar(0, 0, 255), 3);              //�ڻҶ�ͼ���ϻ�������ɫ��
	circle(image, circleCenter, 3, Scalar(255, 0, 0), 3);                   //�ڻҶ�ͼ���ϻ���Բ�ģ���ɫ�� 



	//***********************����ʵ��һЩ��ʾ����******************************************************

	/**************************************************************************************************
	*         �Ƿ񻭳�����ʾ����Բ�仯���ҵ���Բ
	***************************************************************************************************
	*/
	//imshow("Circle Image", image);
	//imwrite("Circle_Image.bmp", image);                                   //������л�����Բ��ͼ��



	return 1;
}

/**********************************************************************************************************
*�˺����Ĺ���ΪѰ��ͼ��Ŀ��ͼ��֡�е�Բ
*����Ϊ�����ץ����ͼ�����Ϊ�ҶȻ�֮���ͼ��Բ�����ĵ�������Լ�Բ�İ뾶
**********************************************************************************************************
*/
//Ϊͼ��׼�����Բ׼���Ļ���Բ��⺯��
int CInstrumentDetectionDlg::HoughCirclesPictureDetection(Mat image)
{
	cvtColor(image, imageGray, CV_RGB2GRAY);                                //��RGBͼ��ת��Ϊ�Ҷ�ͼ��
	GaussianBlur(imageGray, imageGray, Size(3, 3), 1, 2);                   //��˹�˲�     Size(3, 3)Ϊ�˲���ģ���С           
	//imshow("Gaussian Image", imageGray);
	//imwrite("imageGray.jpg", imageGray);
	//�洢����Բ����㷨��⵽������Բ��Բ���Լ��뾶

	//����Բ�任�е�350������ʵ����350Ϊ��Ѳ�������ָ���׶�Բ�ĵ��ۼ�����ֵ��ԽС���ʾ���Լ������౾�����ڵ�Բ��Խ����ͨ������Բ�͸��ӽӽ�������Բ��

	HoughCircles(imageGray, circles, CV_HOUGH_GRADIENT, 1, 5, 200, 160, 0);//����8λ��ͨ���Ҷ�ͼ��circles��Բ�ĺͰ뾶���

	//�����ж��Ƿ��⵽Բ������һ֡��û��Բ
	if (circles.size() == 0)
	{
		//cout << "û�м�⵽Բ�������������" << endl;
		return 0;
	}

	//�������ҵ���Բ�ĺͰ뾶����ȡƽ��ֵ
	for (int i = 0; i < circles.size(); i++)
	{
		CentralPoint_x += circles[i][0];
		CentralPoint_y += circles[i][1];
		radius += circles[i][2];
	}
	CentralPoint_x = CentralPoint_x / circles.size();                       //�õ����յ�Բ������Ͱ뾶
	CentralPoint_y = CentralPoint_y / circles.size();
	radius = radius / circles.size();




	if ((CameraWidth / 2 - CentralPoint_x) >= 10 | (CameraHeight / 2 - CentralPoint_y) >= 10)
	{
		cout << "��ѱ��̵����ĺ�ͼ������Ķ�׼" << endl;
		return 0;

	}

	Point circleCenter(CentralPoint_x, CentralPoint_y);                     //��ͼ����������ϵ���Ͻ�Ϊԭ������
	circle(image, circleCenter, radius, Scalar(0, 0, 255), 3);              //�ڻҶ�ͼ���ϻ�������ɫ��
	circle(image, circleCenter, 3, Scalar(255, 0, 0), 3);                   //�ڻҶ�ͼ���ϻ���Բ�ģ���ɫ�� 



	//***********************����ʵ��һЩ��ʾ����******************************************************

	/**************************************************************************************************
	*         �Ƿ񻭳�����ʾ����Բ�仯���ҵ���Բ
	***************************************************************************************************
	*/
	//imshow("Circle Image", image);
	//imwrite("Circle_Image.bmp", image);                                   //������л�����Բ��ͼ��



	return 1;
}


/**********************************************************************************************************
*�˺����Ĺ���ΪѰ��ָ���λ��
*����Ϊ�����ץ����ͼ��ĻҶȻ�ͼ�����Ϊÿ�ȵĻҶ�ֵ֮��
**********************************************************************************************************
*/
int CInstrumentDetectionDlg::FindPointerPosition(double  *Gray_Sum)
{   

	//Gray_Sum[271] = { 0 };
	IplImage* src = &IplImage(imageGray);                                //��Mat��ʽ�ĻҶ�ͼ��ת��ΪIplImageͼ��ָ��                
	int width = src->width;                                              //��ȡ�Ҷ�ͼ��Ŀ��                          
	int height = src->height;                                            //��ȡ�Ҷ�ͼ��ĸ߶�
	double  coordinate_x;                                                //Բ���ϵ�x����
	double  coordinate_y;                                                //Բ���ϵ�y����
	double  k = 0;                                                       //ֱ�ߵ�б��                                             //ÿ��ֱ�ߵĻҶ�ֵ֮��
	int t = 0;
	for (int j = 0; j < 270; j = j + 1)

	{

		int coordinate_x = radius*cos(j*PI / 180 -PI / 4) + CentralPoint_x;     //ѭ������Բ���ϵ�(x,y)����
		int coordinate_y = -radius*sin(j*PI / 180 - PI / 4) + CentralPoint_y;    //y��
		Point coordinate(coordinate_x, coordinate_y);
		Coordinate.push_back(coordinate);                               //����������뵽Coordinate��


		/**************************************************************************************************
		*         �Ƿ񻭳�ͼ����0-270��Ѱ�ҵ���
		*************************************************************************************************
		*/
		//Point circleCenter(CentralPoint_x, CentralPoint_y);
		//line(image, circleCenter, coordinate, Scalar(255, 255, 255), 1, 8);
		//imwrite("Image.jpg", image);



		if (coordinate_x >= CentralPoint_x && coordinate_y <= CentralPoint_y&&coordinate_y>0) //��һ����
		{

			for (double p = CentralPoint_x; p < coordinate_x; p = p + (coordinate_x - CentralPoint_x) / radius)
			{
				k = (CentralPoint_y - (double)coordinate_y) / ((double)coordinate_x - CentralPoint_x);
				int cols = p;
				//ȷ����һ�����صĻҶ�ֵ
				int row = -k*(p - CentralPoint_x) + CentralPoint_y;
				uchar* ptr = (uchar*)src->imageData + row*src->width;        //ȷ����������
				int intensity = ptr[cols];                                   //����ȷ����ȷ������������ȡ�����صĻҶ�ֵ
				Gray_Sum[t] = Gray_Sum[t] + intensity;                       //������ֵ�����ۼ�
			}

		}
		if (coordinate_x > CentralPoint_x && coordinate_y > CentralPoint_y&&coordinate_y>0)                         //��������
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
		if (coordinate_x < CentralPoint_x && coordinate_y >CentralPoint_y&&coordinate_y>0)                         //��������
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
		if (coordinate_x < CentralPoint_x && coordinate_y <CentralPoint_y&&coordinate_y>0)                         //�ڶ�����
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
*�˺����Ĺ���ΪѰ�һҶ�ֵ��С�����������ʾָ��ָʾ�Ķ���
*����Ϊ�Ҷ�ֵ���������Ϊ��С�Ҷ�ֵ������
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
	*        ��������Ƿ�Ҫ����Ѱ�ҵ���ָ���������
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
*�˺����Ĺ������ɼ�����ĽǶ�ֵ���ɳɶ�Ӧ��ѹ��ֵ
*����Ƕȣ����Ϊ�����ѹ��ֵ
**********************************************************************************************************
*/

double CInstrumentDetectionDlg::AngleToPressureValue(int angle)

{
	double PressureValue = 0;
	double angle_MPa = MaxRangeValue / Angle;
	if (angle >= 0 && angle <= 270)
	{
		PressureValue = MaxRangeValue - angle*angle_MPa;
		//cout << "ѹ��ֵ�ǣ�" << PressureValue << endl;
	}

	return PressureValue;
	
}

//������PictureBox������ʾͼƬ
void CInstrumentDetectionDlg::ShowImage(Mat Img, UINT ID)
{
	//��Matת����IplImage*����ʽ�����ڿؼ�����ʾ
	IplImage* pBinary = &IplImage(Img);                                                          //ǳ����
	IplImage *img = cvCloneImage(pBinary);                                                       //��ǳ����ת��Ϊ���

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




//������������
void CInstrumentDetectionDlg::OnClickedButtoncallcamera()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Initialization();                                                          //���ó�ʼ��������ʹ��֮ǰ����vector�е���ֵ����
	CallCamera = 1;                                                            //ȷ�����ķ�ʽ���˴���ʾ����ͷ���

	//���������
	if (MaxRangeValue == -1)
	{
		MaxRangeValue=0.6;
		//return;

	}
	VideoCapture capture(0);

	//����ͷ��ʧ��
	if (!capture.isOpened())                          
	{
		MessageBox("������ͷʧ�ܣ��˳�");
		exit(-1);
	}
	//����������ڵĴ�С
    capture.set(CV_CAP_PROP_FRAME_WIDTH, CameraWidth);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, CameraHeight);

	//�������������ȷ��ʮ�ֹ���λ�ò��һ�����׼����
	Point circleCenter(CameraWidth / 2, CameraHeight / 2);

	//���½�Բ���ϵĵ㣨��������λ�ã�
	Point ZeroPoint(CameraWidth / 2 - CameraHeight / 2 * sin(PI / 4), CameraHeight / 2 + CameraHeight / 2 * sin(PI / 4));
	//���½�Բ�����ϵĵ㣨��ʾ�յ��λ�ã�
	Point FinalPoint(CameraWidth / 2 + CameraHeight / 2 * sin(PI / 4), CameraHeight / 2 + CameraHeight / 2 * sin(PI / 4));
	//�����־Բ��������µ����ĵ�
	Point WidthCenterPoint1(CameraWidth / 2, (CameraHeight / 2) - 20);
	Point WidthCenterPoint2(CameraWidth / 2, (CameraHeight / 2) + 20);
	//�����־Բ����ߵ��������ĵ�
	Point HeightCenterPoint1(CameraWidth / 2 - 20, CameraHeight / 2);
	Point HeightCenterPoint2(CameraWidth / 2 + 20, CameraHeight / 2);

	int i = 0;
	while (1)
	{
	
		capture >> frame;  //��ȡ��ǰ֡

		//����ͼ��Ϊ��
		if (frame.empty())
		{
			break;

		}

        circle(frame, circleCenter, CameraHeight / 2, Scalar(0, 0, 255), 3);                      //�ڻҶ�ͼ���ϻ�������ɫ��
		circle(frame, circleCenter, 3, Scalar(255, 0, 0), 3);                                     //�ڻҶ�ͼ���ϻ���Բ�ģ���ɫ�� 

	    line(frame, WidthCenterPoint1, WidthCenterPoint2, Scalar(0, 0, 255), 2, 8);               //�ӻ���Բ�ĵ�����ֱ����Ϊ��־��
		line(frame, HeightCenterPoint1, HeightCenterPoint2, Scalar(0, 0, 255), 2, 8);             //�ӻ���Բ�ĵ�����ֱ����Ϊ��־��
		//line(frame, circleCenter, ZeroPoint, Scalar(255, 255, 255), 1, 8);
		//line(frame, circleCenter, FinalPoint, Scalar(255, 255, 255), 1, 8);
		ShowImage(frame, IDC_STATIC_PIC1);                                                        //��Picture�ؼ�����ʾ��ǰ�ɼ���ͼ��
		waitKey(30);                                                                              //��ʱ30ms 

		
		//********************************************************************************
		//         ��������Ƕ�ͼ����д���Ѱ��Բ���õ���ֱ����
		//********************************************************************************
		CentralPoint_x = 0;
		CentralPoint_y = 0;
		radius = 0;
		int CheckCircle = HoughCirclesDetection(frame);
		//�ж��Ƿ��⵽Բ�����û�м�⵽��˵���ǲ��������������ͼ����û��Բ(Ҳ����û�б���ʱ������֡��������һ֡)
		
		if (CheckCircle == 0)
		{
			frame = 0;
			circles.clear();
			continue;
		}

		/**************************************************************************************************
		*        ��Բ���Լ��뾶��Ϣ��ʾ���б����
		***************************************************************************************************
		*/
		/*
		CString Text1 = "Բ��:", Text2 = "�뾶:", Text3 = ",", Text4 = "  ", Digit1, Digit2, Digit3;
		Digit1.Format(_T("%lf"), CentralPoint_x);                               //�õ�
		Digit2.Format(_T("%lf"), CentralPoint_y);
		Digit3.Format(_T("%lf"), radius);
		
		*/

		//********************************************************************************
		//         ���������Ѱ��ָ��
		//********************************************************************************
		double  Gray_Sum[271] = { 0 };
		int CheckPointer = FindPointerPosition(Gray_Sum);

		//********************************************************************************
		// ��������ǶԻҶ�ֵ������������ҵ���С���Ǹ��������������������ָ����ת�Ķ���
		//********************************************************************************
		int angle = 0;                                                                   //ָ�����ת�Ƕ�
		angle = SearchingMinimumGrayValueIndex(Gray_Sum);


		//********************************************************************************
		// ���ݼ����ָ��ĽǶ�ֵ�������ѹ��ֵ�����
		//********************************************************************************
		double PressureValue = AngleToPressureValue(angle);
		//CString FinalStr;
		//CString Title = "ѹ��ֵΪ��";
		//CString ShowPressureValue ;
		//ShowPressureValue.Format(_T("%lf"), PressureValue);
		//FinalStr = Title + ShowPressureValue;
		//ShowMessage(FinalStr);
		PressureValue1.push_back(PressureValue);                                           //�洢���м�⵽��ѹ��ֵ
		
		int check1 = 0;
		if ((check1 = TerminationFilterJudgment()) == 1)
		{
			break;
		}


     	circle(frame, circleCenter, 3, Scalar(255, 0, 0), 3);                              //�ڻҶ�ͼ���ϻ���Բ�ģ���ɫ��
		//imshow("��ȡ��Ƶ", frame);  //��ʾ��ǰ֡
		//waitKey(30);  //��ʱ30ms 

		

		
	}
	int n = PressureValue1.size();
	PressureValueSum = 0;                                                                 //�����е�֡�����ѹ����������ȡƽ��ֵ        
	MaxPressureValue = PressureValue1[n - 1];                                              //�Ȱѵ�һ֡��ֵ����MaxPressureValue��֡����������ȡ���ֵ
	MinPressureValue = PressureValue1[n - 1];                                              //�Ȱѵ�һ֡��ֵ����MinPressureValue��֡����������ȡ��Сֵ
	int  MinIndex = n;                                                                   //��Сֵ����
	int  MaxIndex = n;                                                                   //���ֵ����
	for (int j = PressureValue1.size() - 1; j >PressureValue1.size() - 5; j--)
	{
		PressureValueSum += PressureValue1[j];                                           //���
		if (MinPressureValue > PressureValue1[j] && PressureValue1[j] != 0)              //����Сֵ
		{
			MinPressureValue = PressureValue1[j];
			MinIndex = j + 1;
		}
		if (MaxPressureValue < PressureValue1[j] && PressureValue1[j] != 0)              //�����ֵ
		{
			MaxPressureValue = PressureValue1[j];
			MaxIndex = j + 1;

		}

	}

	FinalPressureValue1 = PressureValueSum / 4;                      //�õ�ѹ��ֵ��ƽ��ֵ

	//������ת�����ַ���������ʾ��ListBox�ؼ���
	CString TextcCamera1 = "ƽ��ѹ��ֵ", TextcCamera2 = "��", TextcCamera3 = "֡ѹ��ֵ���Ϊ:",
		TextcCamera4 = "֡ѹ��ֵ��СΪ��";                                                       //��Ҫ������ı�
	CString AverageinalDigitCamera, MaxDigitCamera, MinDigitCamera;                              //ƽ��ֵ�Լ������Сֵ   
	CString MinIndexCamera, MaxIndexCamera;                                                      //���֡�Լ���С֡����
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
	
	MaxRangeValue = -1;                                                             //�����̲�����������Ϊ-1��ʹ��ÿ�ν�����ʱ����ѡ������
	return;
}


//������Ƶ���
void CInstrumentDetectionDlg::OnClickedButtoncallvideo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Initialization();                                                        //���ó�ʼ��������ʹ��֮ǰ����vector�е���ֵ����
	VideoDetection = 1;                                                      //ȷ�����ķ�ʽ���˴���ʾ��Ƶ���
	if (MaxRangeValue == -1)
	{
		MaxRangeValue=0.6;
		//return;

	}
	
	CString st = "------------------------------VideoDetectionBegin------------------------------";
	//ShowMessage(st);


	//����ͼƬ��·��
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "All Files|*.*|txt|*.txt||");
	INT_PTR nRet = dlg.DoModal();
	if (nRet != IDOK)
	{
		return;
	}

	strFilePath1 = dlg.GetPathName();
	//ShowMessage("��Ƶ��ַ" + strFilePath1);

	if (!PathFileExists(strFilePath1))
	{
		//ShowMessage("�ļ� [%s] ������!\n");
		return;
	}
	strFilePath = strFilePath1.GetBuffer(0);


	//���������
	VideoCapture capture(strFilePath);
	double rate = capture.get(CV_CAP_PROP_FPS);                                                  // ��ȡ֡�� 
	long nFrame = static_cast<long>(capture.get(CV_CAP_PROP_FRAME_COUNT));                       // ��ȡ��֡��

	for (int position = 10; position < nFrame; position = position + 100)
	{

		
		capture >> frame;  //��ȡ��ǰ֡
		
		if (frame.empty())                                                                       //�ж��Ƿ���Ƶ�Ľ�β
		{
			break;
			cout << "Video loading ending" << endl;
		}


		ShowImage(frame, IDC_STATIC_PIC1);                                                        //��Picture�ؼ�����ʾ��ǰ�ɼ���ͼ��
		waitKey(30);                                                                              //��ʱ30ms 


		//********************************************************************************
		//         ��������Ƕ�ͼ����д���Ѱ��Բ���õ���ֱ����
		//********************************************************************************
		CentralPoint_x = 0;
		CentralPoint_y = 0;
		radius = 0;
		int CheckCircle = HoughCirclesVideoDetection(frame);
		//�ж��Ƿ��⵽Բ�����û�м�⵽��˵���ǲ��������������ͼ����û��Բ(Ҳ����û�б���ʱ������֡��������һ֡)

		if (CheckCircle == 0)
		{
			//cout << "δ��⵽Բ��������һ֡�Ĵ���" << endl;
			continue;
		}

		/**************************************************************************************************
		*        ��Բ���Լ��뾶��Ϣ��ʾ���б����
		***************************************************************************************************
		*/
		
		Digit1.Format(_T("%lf"), CentralPoint_x);                               //�õ�
		Digit2.Format(_T("%lf"), CentralPoint_y);
		Digit3.Format(_T("%lf"), radius);
		//ShowMessage(Text1 + Digit1 + Text3 + Digit2 + Text4 + Text2 + Digit3);


		

		//********************************************************************************
		double  Gray_Sum[271] = { 0 };
		int CheckPointer = FindPointerPosition(Gray_Sum);

		//********************************************************************************
		// ��������ǶԻҶ�ֵ������������ҵ���С���Ǹ��������������������ָ����ת�Ķ���
		//********************************************************************************
		int angle = 0;                                                                   //ָ�����ת�Ƕ�
		angle = SearchingMinimumGrayValueIndex(Gray_Sum);


		//********************************************************************************
		// ���ݼ����ָ��ĽǶ�ֵ�������ѹ��ֵ�����
		//********************************************************************************
		double PressureValue = AngleToPressureValue(angle);
		CString FinalStr;
		CString Title = "ѹ��ֵΪ��";
		CString ShowPressureValue;
		ShowPressureValue.Format(_T("%lf"), PressureValue);
		FinalStr = Title + ShowPressureValue;
		//ShowMessage(FinalStr);
		PressureValue1.push_back(PressureValue);                                         //�洢���м�⵽��ѹ��ֵ
		int check;
		if ((check = TerminationFilterJudgment()) == 1)
		{
			break;
		}


	}
	
	int n = PressureValue1.size();
	PressureValueSum =0;                                                                 //�����е�֡�����ѹ����������ȡƽ��ֵ        
	MaxPressureValue = PressureValue1[n-1];                                              //�Ȱѵ�һ֡��ֵ����MaxPressureValue��֡����������ȡ���ֵ
	MinPressureValue = PressureValue1[n-1];                                              //�Ȱѵ�һ֡��ֵ����MinPressureValue��֡����������ȡ��Сֵ
	int  MinIndex = n;                                                                   //��Сֵ����
	int  MaxIndex = n;                                                                   //���ֵ����
	for (int j = PressureValue1.size()-1; j >PressureValue1.size()-5; j--)
	{
		PressureValueSum += PressureValue1[j];                                           //���
		if (MinPressureValue > PressureValue1[j] && PressureValue1[j] != 0)              //����Сֵ
		{
			MinPressureValue = PressureValue1[j];
			MinIndex = j + 1;
		}
		if (MaxPressureValue < PressureValue1[j] && PressureValue1[j] != 0)              //�����ֵ
		{
			MaxPressureValue = PressureValue1[j];
			MaxIndex = j + 1;

		}

	}

	FinalPressureValue1 = PressureValueSum / 4;                 //�õ�ѹ��ֵ��ƽ��ֵ

	//������ת�����ַ���������ʾ��ListBox�ؼ���
	CString TextcVideo1 = "ƽ��ѹ��ֵ", TextcVideo2 = "��", TextcVideo3 = "֡ѹ��ֵ���Ϊ:",
		    TextcVideo4 = "֡ѹ��ֵ��СΪ��";                                           //��Ҫ������ı�
	CString AverageinalDigitVideo, MaxDigitVideo, MinDigitVideo ;                       //ƽ��ֵ�Լ������Сֵ   
	CString MinIndexVideo, MaxIndexVoideo ;                                             //���֡�Լ���С֡����
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
    
	MaxRangeValue = -1;                                                             //�����̲�����������Ϊ-1��ʹ��ÿ�ν�����ʱ����ѡ������
	return;
}


//����ͼ����
void CInstrumentDetectionDlg::OnClickedButtoncallpicture()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	     Initialization();                                                          //���ó�ʼ��������ʹ��֮ǰ����vector�е���ֵ����
		 PictureDetection = 1;                                                      //ȷ�����ķ�ʽ���˴���ʾͼ����
	     if (MaxRangeValue == -1)
	      {
			 MaxRangeValue=0.6;
		    //return;

	      }
	     CString st = "------------------------------PictureDetectionBegin------------------------------";
	     //ShowMessage(st);
	
	     //����ͼƬ��·��
	     CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "All Files|*.*|txt|*.txt||");
	     INT_PTR nRet = dlg.DoModal();
	     if (nRet != IDOK)
	      {
              return;
	      }

	     strFilePathPicture1 = dlg.GetPathName();
	     //ShowMessage("��Ƶ��ַ" + strFilePathPicture1);

	     if (!PathFileExists(strFilePathPicture1))
	      {
		   // ShowMessage("�ļ� [%s] ������!\n");
		    return;
	      }
	     strFilePathPicture = strFilePathPicture1.GetBuffer(0);


	    
         frame = imread(strFilePathPicture);  //��ȡ��ǰ֡
		 ShowImage(frame, IDC_STATIC_PIC1);                                                        //��Picture�ؼ�����ʾ��ǰ�ɼ���ͼ��
		 waitKey(30);                                                                              //��ʱ30ms 


		//********************************************************************************
		//         ��������Ƕ�ͼ����д���Ѱ��Բ���õ���ֱ����
		//********************************************************************************
		CentralPoint_x = 0;
		CentralPoint_y = 0;
		radius = 0;
		int CheckCircle = HoughCirclesPictureDetection(frame);
		//�ж��Ƿ��⵽Բ�����û�м�⵽��˵���ǲ��������������ͼ����û��Բ(Ҳ����û�б���ʱ������֡��������һ֡)

		
		/**************************************************************************************************
		*        ��Բ���Լ��뾶��Ϣ��ʾ���б����
		***************************************************************************************************
		*/
		CString TextPicture1 = "Բ��:", TextPicture2 = "�뾶:", TextPicture3 = ",", TextPicture4 = "  ";
		CString DigitPicture1, DigitPicture2, DigitPicture3;
		DigitPicture1.Format(_T("%lf"), CentralPoint_x);                               //�õ�
		DigitPicture2.Format(_T("%lf"), CentralPoint_y);
		DigitPicture3.Format(_T("%lf"), radius);
		//ShowMessage(TextPicture1 + DigitPicture1 + TextPicture3 + DigitPicture2 + TextPicture4 + TextPicture2 + DigitPicture3);


		//********************************************************************************
		//         ���������Ѱ��ָ��
		//********************************************************************************
		double  Gray_Sum[271] = { 0 };
		int CheckPointer = FindPointerPosition(Gray_Sum);

		//********************************************************************************
		// ��������ǶԻҶ�ֵ������������ҵ���С���Ǹ��������������������ָ����ת�Ķ���
		//********************************************************************************
		int angle = 0;                                                                   //ָ�����ת�Ƕ�
		angle = SearchingMinimumGrayValueIndex(Gray_Sum);


		//********************************************************************************
		// ���ݼ����ָ��ĽǶ�ֵ�������ѹ��ֵ�����
		//********************************************************************************
		double PressureValue = AngleToPressureValue(angle);
		CString FinalStr;
		CString Title = "ѹ��ֵΪ��";
		CString ShowPressureValue;
		ShowPressureValue.Format(_T("%0.3f"), PressureValue);
		FinalStr = Title + ShowPressureValue;
		//ShowMessage(FinalStr);
		
		//GetDlgItem(IDC_EDIT1)->SetWindowText(ShowPressureValue);
		//GetDlgItem(IDC_EDIT2)->SetWindowText(ShowPressureValue);
		GetDlgItem(IDC_EDIT3)->SetWindowText(ShowPressureValue+"MPa");

		MaxRangeValue = -1;                                                             //�����̲�����������Ϊ-1��ʹ��ÿ�ν�����ʱ����ѡ������                                                             
		return;
	
}


//�˳�������
void CInstrumentDetectionDlg::OnClickedButtonExit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (MessageBox("ȷ���˳�", "", MB_YESNO | MB_ICONQUESTION) != IDYES)
	{
		
		return;
	}
	CDialog::OnOK();
	AfxGetMainWnd()->PostMessage(WM_CLOSE, 0, 0);

}

//����ȷ��ѡ����


//��ֹ�˲��жϳ���������������⣬�Ѿ��õ��ȶ���ѹ��ֵ��
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

//������ʼ����һ�������Ŀʱ�ĳ�ʼ��
int CInstrumentDetectionDlg::Initialization()
{   
	Coordinate.clear();                                                   //��֮ǰvector�д洢��Բ���ϵĵ�����
	PressureValue1.clear();                                               //��֮ǰvector�м���ѹ��ֵ����

	//�����ⷽʽ�ı�־λ
    CallCamera=0;                                                         //�����ж��Ƿ���������
	VideoDetection=0;                                                     //�����ж��Ƿ�����Ƶ���
	PictureDetection=0;                                                   //�����ж��Ƿ���ͼ����


	//��Ҫ�ѱ༭���е���������
	CString ResetZzeo = "0.00";
	//GetDlgItem(IDC_EDIT1)->SetWindowText(ResetZzeo);
	//GetDlgItem(IDC_EDIT2)->SetWindowText(ResetZzeo);
	GetDlgItem(IDC_EDIT3)->SetWindowText(ResetZzeo+"MPa");
	return 1;
}

//����ȷ��֮���ͼ�񱣴��Լ���־��д��
void CInstrumentDetectionDlg::OnClickedButtonconfirmandpreservation()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	
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

//���ð�ť���ö�Ӧ���õ��Ӵ���
void CInstrumentDetectionDlg::OnClickedButtonInstall()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		  MessageBox("��ѡ���ⷽ����");
		  break;
	}
	
	return;
}

//��ѡ��ťѡ��ͬ�ļ������
void CInstrumentDetectionDlg::OnClickedButtonDetection()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox("����ֻ���Խ���ѹ����⣡");
		break;
	}
	return;
}


