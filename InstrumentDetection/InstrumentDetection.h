
// InstrumentDetection.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CInstrumentDetectionApp: 
// �йش����ʵ�֣������ InstrumentDetection.cpp
//

class CInstrumentDetectionApp : public CWinApp
{
public:
	CInstrumentDetectionApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CInstrumentDetectionApp theApp;