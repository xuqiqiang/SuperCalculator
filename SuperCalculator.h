
// SuperCalculator.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSuperCalculatorApp: 
// �йش����ʵ�֣������ SuperCalculator.cpp
//

class CSuperCalculatorApp : public CWinApp
{
public:
	CSuperCalculatorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSuperCalculatorApp theApp;